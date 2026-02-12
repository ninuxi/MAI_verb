#!/usr/bin/env bash

# Setup script for Riverberi M7 plugin development environment
# Handles JUCE framework setup and initial configuration

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${GREEN}Riverberi M7 Development Environment Setup${NC}"
echo ""

# Check if JUCE is already set
JUCE_LOCAL="${SCRIPT_DIR}/JUCE"

if [ -d "$JUCE_LOCAL" ]; then
    echo -e "${GREEN}✓ JUCE framework found in local directory${NC}"
    export JUCE_PATH="$JUCE_LOCAL"
    SKIP_JUCE=1
elif [ ! -z "$JUCE_PATH" ]; then
    echo -e "${YELLOW}JUCE_PATH already set to: $JUCE_PATH${NC}"
    read -p "Do you want to use this path? (y/n) " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        SKIP_JUCE=1
    fi
fi

if [ -z "$SKIP_JUCE" ]; then
    echo "Please enter the path to your JUCE installation:"
    echo "(Download from https://github.com/juce-framework/JUCE/releases)"
    read -p "JUCE Path: " JUCE_PATH_INPUT
    
    if [ ! -d "$JUCE_PATH_INPUT" ]; then
        echo -e "${RED}Directory not found: $JUCE_PATH_INPUT${NC}"
        exit 1
    fi
    
    export JUCE_PATH="$JUCE_PATH_INPUT"
fi

# Verify JUCE structure
if [ ! -d "$JUCE_PATH/modules/juce_core" ]; then
    echo -e "${RED}Invalid JUCE directory. Missing modules/juce_core${NC}"
    exit 1
fi

echo -e "${GREEN}✓ JUCE framework found${NC}"

# Add JUCE_PATH to shell profile for persistence
SHELL_RC=""
if [ -f ~/.zshrc ]; then
    SHELL_RC=~/.zshrc
elif [ -f ~/.bashrc ]; then
    SHELL_RC=~/.bashrc
fi

if [ ! -z "$SHELL_RC" ]; then
    if ! grep -q "JUCE_PATH" "$SHELL_RC"; then
        echo "" >> "$SHELL_RC"
        echo "# JUCE Framework Path" >> "$SHELL_RC"
        echo "export JUCE_PATH=\"$JUCE_PATH\"" >> "$SHELL_RC"
        echo -e "${GREEN}✓ Added JUCE_PATH to $SHELL_RC${NC}"
    fi
fi

# Create build directory
echo ""
echo "Creating build directory..."
mkdir -p build
echo -e "${GREEN}✓ Build directory created${NC}"

# Verify CMake
echo ""
echo "Checking CMake installation..."
if ! command -v cmake &> /dev/null; then
    echo -e "${RED}CMake is not installed${NC}"
    echo "Install with: brew install cmake (macOS) or apt install cmake (Linux)"
    exit 1
fi

CMAKE_VERSION=$(cmake --version | head -n1)
echo -e "${GREEN}✓ $CMAKE_VERSION${NC}"

# Detect platform
PLATFORM=""
if [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="macOS"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    PLATFORM="Linux"
elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
    PLATFORM="Windows"
fi

echo ""
echo -e "${GREEN}Platform detected: $PLATFORM${NC}"

# Suggest next steps
echo ""
echo -e "${GREEN}Setup complete!${NC}"
echo ""
echo "Next steps:"
echo "1. Build the project:"
echo "   ./build.sh -t Release -i"
echo ""
echo "2. Or build with CMake directly:"
echo "   cmake -B build -DCMAKE_BUILD_TYPE=Release"
echo "   cmake --build build --config Release"
echo ""
echo "3. Load custom IR files:"
echo "   Place WAV/AIFF files in IR_Samples/ directory"
echo ""
echo "Documentation:"
echo "- README.md - General overview and features"
echo "- TECHNICAL.md - Architecture and optimization details"
echo "- IR_SAMPLES/README.md - Impulse response loading guide"
echo ""
