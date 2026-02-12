#!/bin/bash

# Riverberi M7 Build Helper Script
# Supports Windows, macOS, and Linux builds

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Default values
BUILD_TYPE="Release"
TARGET_PLATFORM="auto"
BUILD_DIR="build"
INSTALL_DIR="install"
NUM_JOBS=$(nproc || echo 4)

# Function to print colored output
print_status() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

# Function to detect platform
detect_platform() {
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        TARGET_PLATFORM="linux"
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        TARGET_PLATFORM="macos"
    elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
        TARGET_PLATFORM="windows"
    else
        print_error "Unknown platform: $OSTYPE"
        exit 1
    fi
    print_status "Detected platform: $TARGET_PLATFORM"
}

# Function to check prerequisites
check_prerequisites() {
    print_status "Checking prerequisites..."

    if ! command -v cmake &> /dev/null; then
        print_error "CMake is not installed. Please install CMake 3.22+"
        exit 1
    fi

    print_status "CMake version: $(cmake --version | head -n1)"

    # Check for local JUCE
    if [ -d "JUCE" ]; then
        print_status "JUCE framework found in local directory"
        export JUCE_PATH="$PWD/JUCE"
    elif [ -z "$JUCE_PATH" ]; then
        print_warning "JUCE_PATH environment variable not set and no local JUCE found"
        print_status "Ensure JUCE is in ./JUCE directory or set JUCE_PATH"
    fi

    case $TARGET_PLATFORM in
        linux)
            if ! command -v make &> /dev/null; then
                print_error "Make is not installed"
                exit 1
            fi
            print_status "Build tools verified"
            ;;
        macos)
            if ! command -v xcode-select &> /dev/null; then
                print_error "Xcode command line tools not installed"
                exit 1
            fi
            print_status "Xcode tools verified"
            ;;
        windows)
            print_status "Windows detected - ensure Visual Studio 2022 is installed"
            ;;
    esac
}

# Function to configure build
configure_build() {
    print_status "Configuring build..."

    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"

    case $TARGET_PLATFORM in
        linux)
            cmake .. \
                -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
                -DCMAKE_CXX_FLAGS_RELEASE="-O3 -march=native -flto" \
                -DCMAKE_EXE_LINKER_FLAGS_RELEASE="-flto"
            ;;
        macos)
            cmake .. \
                -G "Unix Makefiles" \
                -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
                -DCMAKE_OSX_ARCHITECTURES="arm64" \
                -DCMAKE_CXX_FLAGS="-fPIC"
            ;;
        windows)
            cmake .. \
                -G "Visual Studio 17 2022" \
                -DCMAKE_BUILD_TYPE=$BUILD_TYPE
            ;;
    esac

    print_status "Build configured in: $BUILD_DIR"
}

# Function to build
build_project() {
    print_status "Building project..."

    cd "$BUILD_DIR"

    case $TARGET_PLATFORM in
        linux)
            make -j$NUM_JOBS
            ;;
        macos)
            cmake --build . --config $BUILD_TYPE -- -parallelizeTargets -jobs $NUM_JOBS
            ;;
        windows)
            cmake --build . --config $BUILD_TYPE -- /MP:$NUM_JOBS
            ;;
    esac

    print_status "Build complete!"
}

# Function to install
install_plugin() {
    print_status "Installing plugin..."

    mkdir -p "$INSTALL_DIR"

    case $TARGET_PLATFORM in
        linux)
            mkdir -p "$INSTALL_DIR/vst3"
            find "$BUILD_DIR" -name "*.so" -type f | xargs -I {} cp {} "$INSTALL_DIR/vst3/"
            print_status "VST3 plugins installed to: $INSTALL_DIR/vst3/"
            ;;
        macos)
            mkdir -p "$INSTALL_DIR/components"
            mkdir -p "$INSTALL_DIR/vst3"
            find "$BUILD_DIR" -name "*.component" -type d | xargs -I {} cp -r {} "$INSTALL_DIR/components/"
            find "$BUILD_DIR" -name "*.vst3" -type d | xargs -I {} cp -r {} "$INSTALL_DIR/vst3/"
            print_status "Plugins installed to: $INSTALL_DIR/"
            ;;
        windows)
            mkdir -p "$INSTALL_DIR/vst3"
            find "$BUILD_DIR" -name "*.dll" -type f | xargs -I {} cp {} "$INSTALL_DIR/vst3/"
            print_status "VST3 plugins installed to: $INSTALL_DIR/vst3/"
            ;;
    esac
}

# Function to clean build
clean_build() {
    print_status "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
    print_status "Build directory cleaned"
}

# Function to show usage
show_usage() {
    echo "Usage: ./build.sh [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  -t, --type TYPE        Build type: Debug or Release (default: Release)"
    echo "  -p, --platform PLATFORM Platform: linux, macos, windows, auto (default: auto)"
    echo "  -j, --jobs NUM         Number of parallel build jobs (default: auto)"
    echo "  -c, --clean            Clean build before building"
    echo "  -i, --install          Install plugin after building"
    echo "  -h, --help             Show this help message"
    echo ""
    echo "Examples:"
    echo "  ./build.sh                          # Build for current platform"
    echo "  ./build.sh -t Debug -i              # Debug build and install"
    echo "  ./build.sh -c -j 8 -i               # Clean, build with 8 jobs, and install"
}

# Parse command line arguments
parse_args() {
    while [[ $# -gt 0 ]]; do
        case $1 in
            -t|--type)
                BUILD_TYPE="$2"
                shift 2
                ;;
            -p|--platform)
                TARGET_PLATFORM="$2"
                shift 2
                ;;
            -j|--jobs)
                NUM_JOBS="$2"
                shift 2
                ;;
            -c|--clean)
                CLEAN_BUILD=1
                shift
                ;;
            -i|--install)
                INSTALL=1
                shift
                ;;
            -h|--help)
                show_usage
                exit 0
                ;;
            *)
                print_error "Unknown option: $1"
                show_usage
                exit 1
                ;;
        esac
    done
}

# Main script
main() {
    print_status "Riverberi M7 Build Script"
    echo ""

    parse_args "$@"

    if [ "$TARGET_PLATFORM" = "auto" ]; then
        detect_platform
    fi

    check_prerequisites

    if [ "$CLEAN_BUILD" = "1" ]; then
        clean_build
    fi

    configure_build
    build_project

    if [ "$INSTALL" = "1" ]; then
        install_plugin
    fi

    print_status "Build process completed successfully!"
    echo ""
    echo "Next steps:"
    echo "1. Check the plugin in the install directory"
    echo "2. Copy to your DAW's plugin folder"
    echo "3. Rescan plugins in your DAW"
}

# Run main function
main "$@"
