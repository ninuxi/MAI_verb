#!/bin/bash

# Riverberi M7 Plugin - Compilation Information & Diagnostics
# This script provides system information and compilation recommendations

echo "╔════════════════════════════════════════════════════════════════════════════╗"
echo "║           RIVERBERI M7 - BUILD SYSTEM DIAGNOSTICS                         ║"
echo "╚════════════════════════════════════════════════════════════════════════════╝"
echo ""

# System Information
echo "┌─ SYSTEM INFORMATION ─────────────────────────────────────────────────────┐"
UNAME=$(uname -s)
ARCH=$(uname -m)

case "$UNAME" in
    Darwin)
        OS="macOS"
        KERNEL=$(uname -r)
        echo "Operating System:  $OS $(sw_vers -productVersion)"
        ;;
    Linux)
        OS="Linux"
        KERNEL=$(uname -r)
        DISTRO=$(lsb_release -ds 2>/dev/null || echo "Unknown")
        echo "Operating System:  $DISTRO"
        echo "Kernel:            $KERNEL"
        ;;
    *)
        OS="Unknown"
        echo "Operating System:  $OS"
        ;;
esac

echo "Architecture:      $ARCH"
echo "Processors:        $(nproc || sysctl -n hw.ncpu || echo "Unknown")"
echo ""

# Check Build Tools
echo "┌─ BUILD TOOLS ───────────────────────────────────────────────────────────┐"

# CMake
if command -v cmake &> /dev/null; then
    echo "✓ CMake:           $(cmake --version | head -n1 | cut -d' ' -f3)"
else
    echo "✗ CMake:           NOT INSTALLED (required 3.22+)"
fi

# Compiler
case "$OS" in
    macOS)
        if command -v clang &> /dev/null; then
            echo "✓ Clang:           $(clang --version | head -n1)"
        fi
        if command -v xcode-select &> /dev/null; then
            XCODE_PATH=$(xcode-select -p)
            echo "✓ Xcode Tools:     $XCODE_PATH"
        fi
        ;;
    Linux)
        if command -v gcc &> /dev/null; then
            echo "✓ GCC:             $(gcc --version | head -n1)"
        fi
        if command -v clang &> /dev/null; then
            echo "✓ Clang:           $(clang --version | head -n1)"
        fi
        ;;
esac

# Git
if command -v git &> /dev/null; then
    echo "✓ Git:             $(git --version)"
else
    echo "✗ Git:             NOT INSTALLED (optional)"
fi

# Make
if command -v make &> /dev/null; then
    echo "✓ Make:            $(make --version | head -n1)"
fi

echo ""

# Check JUCE Installation
echo "┌─ JUCE FRAMEWORK ─────────────────────────────────────────────────────┐"

JUCE_LOCAL="./JUCE"
JUCE_PATH_SET=$JUCE_PATH

# Check local JUCE first
if [ -d "$JUCE_LOCAL" ]; then
    echo "✓ JUCE (Local):        Found in ./JUCE"
    export JUCE_PATH="$JUCE_LOCAL"
    
    if [ -d "$JUCE_PATH/modules/juce_core" ]; then
        echo "✓ JUCE Modules:        FOUND"
        MODULE_COUNT=$(find "$JUCE_PATH/modules" -maxdepth 1 -type d | wc -l)
        echo "  Modules Available:    $((MODULE_COUNT - 1))"
    else
        echo "✗ JUCE Modules:        NOT FOUND or invalid path"
    fi
elif [ ! -z "$JUCE_PATH_SET" ]; then
    echo "✓ JUCE_PATH:           $JUCE_PATH_SET"
    
    if [ -d "$JUCE_PATH_SET/modules/juce_core" ]; then
        echo "✓ JUCE Modules:        FOUND"
        MODULE_COUNT=$(find "$JUCE_PATH_SET/modules" -maxdepth 1 -type d | wc -l)
        echo "  Modules Available:    $((MODULE_COUNT - 1))"
    else
        echo "✗ JUCE Modules:        NOT FOUND or invalid path"
    fi
else
    echo "✗ JUCE:                NOT FOUND (local or via JUCE_PATH)"
    echo ""
    echo "  Place JUCE in ./JUCE directory or set JUCE_PATH environment variable"
fi

echo ""

# Project Structure
echo "┌─ PROJECT STRUCTURE ──────────────────────────────────────────────────────┐"

PROJ_DIR="/Users/mainenti/make_plugin_riverberi"

echo "Source Files:"
find "$PROJ_DIR/source" -name "*.cpp" -o -name "*.h" 2>/dev/null | wc -l | xargs echo "  C++ Files:"
echo "  Presets:          $(find "$PROJ_DIR/source" -name "*.xml" | wc -l)"

echo ""
echo "Documentation:"
find "$PROJ_DIR" -maxdepth 1 -name "*.md" -o -name "*.txt" 2>/dev/null | wc -l | xargs echo "  Documentation Files:"

echo ""

# Build Recommendations
echo "┌─ BUILD RECOMMENDATIONS ──────────────────────────────────────────────────┐"

case "$OS" in
    macOS)
        echo "Platform:          macOS"
        echo "Recommended Build: cmake -B build -G Xcode -DCMAKE_BUILD_TYPE=Release"
        echo "Open with:         xcode-select -p"
        ;;
    Linux)
        echo "Platform:          Linux"
        echo "Recommended Build: cmake -B build -DCMAKE_BUILD_TYPE=Release"
        echo "Make jobs:         -j$(nproc || echo 4)"
        ;;
    *)
        echo "Platform:          Unknown"
        echo "Recommended Build: cmake -B build -DCMAKE_BUILD_TYPE=Release"
        ;;
esac

echo ""
echo "Command:"
echo "  ./build.sh -t Release -i"
echo ""

# Performance Tips
echo "┌─ PERFORMANCE OPTIMIZATION TIPS ──────────────────────────────────────────┐"

case "$ARCH" in
    arm64|aarch64)
        echo "CPU Architecture:  ARM 64-bit"
        echo "Optimization:      Enable NEON SIMD"
        echo "  Add: -march=armv8-a+simd"
        ;;
    x86_64)
        echo "CPU Architecture:  Intel/AMD x86-64"
        echo "Optimization:      Enable AVX2"
        echo "  Add: -march=native or -march=haswell"
        if grep -q "avx512" /proc/cpuinfo 2>/dev/null; then
            echo "AVX-512 Available: Yes (advanced optimization)"
        fi
        ;;
    *)
        echo "CPU Architecture:  $ARCH"
        echo "Optimization:      Use -march=native for best results"
        ;;
esac

echo ""

# Parallel Build
NPROC=$(nproc || sysctl -n hw.ncpu || echo "4")
echo "Parallel Build:"
echo "  Recommended Jobs: $NPROC"
echo "  Command:         ./build.sh -j$NPROC -i"

echo ""

# Memory Check
echo "┌─ SYSTEM RESOURCES ──────────────────────────────────────────────────────┐"

case "$OS" in
    macOS)
        TOTAL_MEM=$(vm_stat | grep "Pages free:" | awk '{print $3}' | sed 's/\.//' | numfmt --to=iec --suffix=B 2>/dev/null || echo "Unknown")
        echo "Available Memory:  ~8GB+ recommended"
        ;;
    Linux)
        TOTAL_MEM=$(free -h | awk 'NR==2 {print $2}')
        AVAIL_MEM=$(free -h | awk 'NR==2 {print $7}')
        echo "Total Memory:      $TOTAL_MEM"
        echo "Available:         $AVAIL_MEM"
        ;;
esac

DISK_SPACE=$(df -h . | tail -1 | awk '{print $4}')
echo "Free Disk Space:   $DISK_SPACE (500MB+ needed for build)"

echo ""

# Final Recommendations
echo "┌─ NEXT STEPS ─────────────────────────────────────────────────────────────┐"

echo ""
echo "1. Verify JUCE installation:"
echo "   export JUCE_PATH=/path/to/JUCE"
echo ""
echo "2. Run initial setup:"
echo "   ./setup.sh"
echo ""
echo "3. Build the plugin:"
echo "   ./build.sh -t Release -i"
echo ""
echo "4. Install to DAW plugin directory"
echo ""
echo "5. Rescan plugins in your DAW"
echo ""

echo "╔════════════════════════════════════════════════════════════════════════════╗"
echo "║                    BUILD DIAGNOSTICS COMPLETE                             ║"
echo "╚════════════════════════════════════════════════════════════════════════════╝"
