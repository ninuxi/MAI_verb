# Riverberi M7 - Technical Documentation

## Architecture Overview

### Core DSP Processing Chain

```
Input Buffer
    ↓
[Pre-Delay Stage]
    ↓
[Convolution Engine]
    ↓
[Decay Scaling]
    ↓
[Wet/Dry Mixing]
    ↓
[Output Limiter]
    ↓
Output Buffer
```

## ConvolutionEngine Implementation

### Time-Domain Convolution

The plugin uses time-domain convolution for flexibility and low latency:

```cpp
y[n] = Σ(h[k] × x[n-k]) for k=0 to IR_length
```

Where:
- `x[n]` = input signal
- `h[k]` = impulse response
- `y[n]` = output signal

### Memory Efficiency

- Circular buffers prevent unbounded memory growth
- IR data cached in memory for real-time access
- Pre-delay implemented as ring buffer

### Processing Strategy

1. **Block Processing**: Process audio in chunks (configurable 32-2048 samples)
2. **Overlap-Add**: Internal buffering for seamless convolution
3. **Sample Rate Adaptation**: Automatic IR resampling based on sample rate

## Parameter System (APVTS)

### Value Tree State Integration

All parameters stored in `AudioProcessorValueTreeState` for:
- DAW automation support
- State saving/loading
- Parameter modulation capabilities

### Parameter Ranges and Mapping

| Parameter | Normalized | Actual Unit | Formula |
|-----------|-----------|------------|---------|
| Decay | 0.0-1.0 | 0.5-10s | `0.5 + norm * 9.5` |
| PreDelay | 0.0-1.0 | 0-1000ms | `norm * 1000` |
| Damping | 0.0-1.0 | 0.0-1.0 | Direct mapping |
| Mix | 0.0-1.0 | 0.0-1.0 | Direct mapping |

## Sample Rate Support

### Resampling Strategy

For loading IRs at different sample rates:

```cpp
resamplingFactor = targetRate / sourceRate

// Linear interpolation
y[n] = x[n] * (1-frac) + x[n+1] * frac
```

### Latency Compensation

- Block size automatically adjusted per sample rate
- Tail length updated for IR duration
- Reported to DAW for automatic compensation

## Real-Time Processing Constraints

### Lock-Free Design

- Parameter changes: lockfree atomic operations
- IR loading: background thread with safe swap
- UI updates: decoupled from audio thread

### CPU Optimization

1. **SIMD**: Leverages JUCE DSP for vectorization
2. **Cache Locality**: IR data organized for L1 cache efficiency
3. **Branch Prediction**: Minimal conditional logic in audio loop

## FFT-Based Convolution (Future)

For large IRs (>1 second), consider partitioned FFT convolution:

```
IR Size: 131k samples → 4 partitions of 32k
Process each partition separately
Combine using overlap-add method
```

Benefits:
- Complexity: O(N log N) vs O(N²)
- CPU cost: ~15% vs 100%
- Latency: Same (block-based)

## UI/Editor Architecture

### LookAndFeel Customization

Custom knob rendering using:
- Rotary arc visualization
- Smooth pointer animation
- Real-time parameter feedback

### Parameter Binding

```cpp
sliderAttachments.push_back(
    std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(
        valueTreeState, parameterId, slider)
);
```

Automatic bidirectional sync between:
- Slider UI value
- Parameter state
- Audio processor

## IR Loading Pipeline

### File Validation

1. Check file exists and is readable
2. Detect format (WAV, AIFF, etc.)
3. Validate audio data integrity
4. Verify sample rate compatibility

### Normalization

Prevent clipping using:

```cpp
maxVal = max(abs(IR[n]))
if (maxVal > 0)
    IR[n] *= 0.95 / maxVal  // 5% headroom
```

### Crossfading IRs

Smooth transitions between IRs:

```cpp
output[n] = from[n] * (1-pos) + to[n] * pos
```

Position ranges 0.0 (from) to 1.0 (to)

## Memory Management

### Allocation Strategy

```
Fixed allocations (prepare phase):
- IRBuffer:      ~1MB (up to 131k @ 44.1k)
- PreDelayBuffer: ~500KB (1 second stereo)
- ProcessingBuffers: ~100KB (working memory)
- UIComponents: ~1-5MB (custom drawing)

Total: ~50MB typical
```

### Buffer Reuse

- Input/output buffers provided by DAW
- Internal circular buffers minimize allocations
- No allocations during audio processing (real-time safe)

## Thread Safety

### Audio Thread
- Real-time constraints (no allocations, no blocking)
- Lockfree parameter reading
- Copy-free buffer processing

### UI Thread
- Parameter slider updates
- File loading dialogs
- Display refresh (non-critical)

### Background Threads
- IR file loading
- Preset management
- Non-critical operations

## Performance Metrics

### CPU Usage Estimation

```
Convolution: IRSize * SampleRate / SystemSpeed
Example: 100k IR @ 48k / 2GHz CPU ≈ 2.4%

+ DSP overhead: ~2-3%
+ UI rendering: ~0.5-1%

Total: 5-10% on modern CPU
```

### Latency Budget

- Convolution: 0ms (offline processing)
- Buffer latency: BlockSize/SampleRate
- DAW compensation: Automatic

## Debugging and Testing

### Parameter Monitoring

Add runtime checks:

```cpp
jassert(decayValue >= 0.5f && decayValue <= 10.0f);
jassert(irData.size() <= maxIRSize);
```

### Memory Profiling

Monitor in debugger:
- Peak memory usage
- Allocation count
- Cache efficiency

### CPU Profiling

Use platform tools:
- macOS: Xcode Instruments
- Windows: Visual Studio Profiler
- Linux: perf, valgrind

## Plugin State Management

### XmlElement Storage

```xml
<RiverberiM7>
    <Parameter id="decay" value="3.5"/>
    <Parameter id="predelay" value="25.0"/>
    <!-- ... -->
</RiverberiM7>
```

### State Restoration

1. Load XML from DAW
2. Restore all parameters atomically
3. Reload IR if path available
4. Update UI representations

## Cross-Platform Considerations

### Platform-Specific Code

Windows:
```cpp
#if JUCE_WINDOWS
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
#endif
```

macOS:
```cpp
#if JUCE_MAC
    // Core Audio specific optimizations
#endif
```

Linux:
```cpp
#if JUCE_LINUX
    // ALSA/Jack specific handling
#endif
```

### Plugin Format Differences

| Format | Windows | macOS | Linux |
|--------|---------|-------|-------|
| VST3 | ✓ | ✓ | ✓ |
| AU | ✗ | ✓ | ✗ |
| Standalone | ✓ | ✓ | ✓ |

## Future Optimization Roadmap

### Phase 1: FFT Convolution
- Partition IR for large files
- Implement fast convolution via FFT
- Target: 50% CPU reduction

### Phase 2: Multi-Core Processing
- Split convolution across cores
- Thread pool for parallel processing
- Target: Linear scaling with cores

### Phase 3: SIMD Optimization
- Vectorize time-domain loop
- AVX2/AVX-512 support
- Target: 2-4x speedup

### Phase 4: GPU Acceleration
- CUDA/Metal compute shaders
- Large-scale convolution
- Target: 10x speedup for large IRs

## References

1. "Fast Convolution Algorithms" - MIT OpenCourseWare
2. JUCE Framework Documentation
3. VST3 Specification (Steinberg)
4. Real-Time Audio Programming Techniques - Paul Kellett
5. Bricasti M7 Architecture Analysis

---

For questions or contributions, see README.md
