cmake_minimum_required(VERSION 3.22)
project(RiverberoCloneM7 VERSION 0.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# JUCE settings
set(JUCE_FORMATS VST3 AU Standalone)

# Use local JUCE from ./JUCE directory
set(JUCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/JUCE" CACHE PATH "Path to JUCE framework")

if(NOT EXISTS "${JUCE_DIR}")
    message(FATAL_ERROR "JUCE framework not found at ${JUCE_DIR}")
endif()

# Add JUCE as subdirectory
add_subdirectory("${JUCE_DIR}" juce_build)

# Create the plugin
juce_add_plugin(RiverberoCloneM7
    COMPANY_NAME "BricastiClone"
    PLUGIN_MANUFACTURER_CODE Bric
    PLUGIN_CODE M7Rv
    FORMATS ${JUCE_FORMATS}
    PRODUCT_NAME "Bricasti M7"
    DESCRIPTION "Professional Reverb Effect"
    PLUGIN_VERSION_STRING "1.0.0"
    VST_NUM_MIDI_INPUTS 0
    VST_NUM_MIDI_OUTPUTS 0
    VST_COPY_DIR ""
    AAX_IDENTIFIER com.bricastiClone.BricastiM7
)

# Add source files
target_sources(RiverberoCloneM7 PRIVATE
    ../BricastiM7_Clone/Source/PluginProcessor.cpp
    ../BricastiM7_Clone/Source/PluginEditor.cpp
    ../BricastiM7_Clone/Source/DSP/M7ReverbEngine.cpp
    ../BricastiM7_Clone/Source/DSP/FDN4x4.cpp
    ../BricastiM7_Clone/Source/DSP/EarlyReflections.cpp
    ../BricastiM7_Clone/Source/DSP/M7Modulation.cpp
    ../BricastiM7_Clone/Source/DSP/M7EQ.cpp
    ../BricastiM7_Clone/Source/Presets/M7FactoryPresets.cpp
    ../BricastiM7_Clone/Source/UI/M7LookAndFeel.cpp
)

# Include directories
target_include_directories(RiverberoCloneM7 PRIVATE
    ../BricastiM7_Clone/Source
)

# Link JUCE libraries
target_link_libraries(RiverberoCloneM7 PRIVATE
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_gui_basics
    juce::juce_gui_extra
)

# Compiler-specific settings
if(MSVC)
    target_compile_options(RiverberoCloneM7 PRIVATE /fp:fast /arch:AVX2)
elseif(APPLE)
    target_compile_options(RiverberoCloneM7 PRIVATE -ffast-math -march=native)
else()
    target_compile_options(RiverberoCloneM7 PRIVATE -ffast-math -march=native -mfpmath=sse)
endif()

# Enable simd support for DSP
if(WIN32)
    target_compile_definitions(RiverberoCloneM7 PRIVATE JUCE_USE_WINDOWS_MEDIA_FORMAT=1)
endif()

if(APPLE)
    target_compile_definitions(RiverberoCloneM7 PRIVATE JUCE_USE_CURL=0 JUCE_USE_OPENGL=0)
endif()

# VST3-only plugin - no VST2 conflicts
target_compile_definitions(RiverberoCloneM7 PRIVATE JUCE_IGNORE_VST3_MISMATCHED_PARAMETER_ID_WARNING=1)

# Warnings
if(MSVC)
    target_compile_options(RiverberoCloneM7 PRIVATE /W3)
else()
    target_compile_options(RiverberoCloneM7 PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Set output directories
set_target_properties(RiverberoCloneM7 PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
