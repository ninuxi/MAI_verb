// IR_SAMPLES_README.md - Impulse Response Sample Guide

# Loading Custom Impulse Responses

Place your IR files in this directory and load them through the plugin UI.

## Supported Formats

- WAV (PCM, 16/24/32-bit, 44.1k-192k)
- AIFF (PCM formats)
- FLAC (if system supports)

## Recommended IR Characteristics

### File Size
- Optimal: 100-500ms (44k-192k samples)
- Range: 50ms-10s supported
- Note: Larger IRs use more CPU

### Sample Rate
- Auto-resampled to match DAW
- 44.1kHz, 48kHz, 96kHz, 192kHz preferred
- Non-standard rates supported but may require conversion

### Loudness
- -3dB to -6dB FS recommended
- Avoid clipping in original file
- Plugin applies normalization automatically

### Stereo Configuration
- Mono: Converted to stereo (mono → L/R)
- Stereo: Both channels used (natural imaging)
- Surround: First 2 channels used

## Sourcing IR Files

### Free Resources

1. **openair** - Free convolver IRs
   - http://www.openair.hosted.york.ac.uk/
   - 1000+ High-quality room IRs

2. **University of York Audio Lab**
   - Academic research IRs
   - Real spaces (cathedrals, halls)

3. **MIT Media Lab**
   - Architectural acoustics
   - Room database

4. **Acoustics Measurements Database**
   - Various spaces and equipment
   - High-resolution captures

### Commercial Collections

- Bricasti M7 IR Library (~$49)
- Sonible room IRs
- Altiverb 7 expansions
- Convolutron IR packs

## Creating Your Own IRs

### Measurement Technique

1. Use sweep tone (20Hz-20kHz sine)
2. Capture room response
3. Deconvolve to extract IR
4. Normalize and trim silence

### Tools

- Audacity + deconvolution plugin
- Adobe Audition
- SoX command-line tools
- REW (Room EQ Wizard)

Example SoX command:
```bash
sox sweep.wav response.wav noiseprof
sox -p noiseprof sweep.profile | sox response.wav -t wav - noiseprof sweep.profile
```

## IR Organization Suggestions

```
IR_Samples/
├── Halls/
│   ├── concert_hall_1.wav
│   ├── concert_hall_2.wav
│   └── stone_hall.wav
├── Plates/
│   ├── vintage_plate.wav
│   └── spring_plate.wav
├── Rooms/
│   ├── small_office.wav
│   ├── large_room.wav
│   └── tile_bathroom.wav
├── Outdoor/
│   ├── courtyard.wav
│   ├── canyon.wav
│   └── stairwell.wav
└── Creative/
    ├── reverse.wav
    ├── shimmer.wav
    └── gated.wav
```

## Loading and Tweaking

### Initial Setup
1. Click "Load IR" button
2. Select WAV/AIFF file
3. Adjust parameters:
   - **Decay**: Increase for longer tail
   - **Pre-Delay**: Add space before reverb
   - **Damping**: High frequencies roll-off

### Fine-Tuning
- **Stereo Width**: Widen reverb image (0.5-0.9)
- **Early Reflections**: Balance direct/early reflections
- **Diffusion**: Smoothness of reverb (0.6-0.9)

### A/B Comparison
1. Save preset with current IR
2. Load different IR
3. Adjust similar parameter values
4. Compare through plugin comparison

## Performance Tips

### For Large IRs (>1 second)
- Increase DAW buffer size
- Use on individual tracks (not master)
- Disable freeze mode until needed
- Monitor CPU in track meter

### For CPU-Limited Systems
- Choose IRs <300ms duration
- Use smaller buffer size (128-256)
- Reduce plugin instance count
- Enable Low Latency mode if available

## Troubleshooting

### No Sound After Loading IR
- Check file is readable (not corrupted)
- Verify IR has audio data
- Check Mix level > 0%
- Try different IR file to test

### Clicking/Artifacts
- IR may contain silence gaps - trim before loading
- Increase DAW buffer size
- Check IR normalization
- Test with shorter IR file

### Plugin Appears Offline
- IR loading failed - check file permissions
- Sample rate incompatibility - verify file rate
- Memory limit exceeded - use smaller IR

## Technical Specifications

### Maximum IR Length
- 192kHz, 10 seconds = ~1.92M samples
- Memory: ~7.7MB per channel
- CPU impact: Significant, use for special effects only

### Recommended Maximum
- 44.1kHz, 5 seconds = ~220k samples
- Memory: ~880KB per channel
- CPU impact: Manageable (~5-10%)

### Optimal Range
- 44.1kHz, 2 seconds = ~88k samples
- Memory: ~352KB per channel
- CPU impact: Minimal (~2-3%)

## File Format Details

### WAV Headers
- RIFF container format
- PCM audio subchunk
- Metadata (sample rate, bit depth, channels)
- Compatible with all platforms

### AIFF Headers
- Audio IFF container
- Common Audio subchunk
- Native on macOS, supported cross-platform
- Equivalent quality to WAV

## Reference IR Testing

### Provided Test IRs (if included)

- Small Room (50ms) - Quick startup test
- Medium Hall (200ms) - Balanced reverb
- Large Cathedral (2s) - Extended tail

Load these to verify plugin operation.

---

Questions? See README.md or TECHNICAL.md
