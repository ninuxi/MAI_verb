cmake_minimum_required(VERSION 3.22)
project(BricastiM7 VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# JUCE settings
if(APPLE)
    set(JUCE_FORMATS VST3 AU Standalone)
elseif(WIN32)
    set(JUCE_FORMATS VST3 Standalone)
else()
    set(JUCE_FORMATS VST3 LV2 Standalone)
endif()

# Use local JUCE from ../JUCE directory
set(JUCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../JUCE" CACHE PATH "Path to JUCE framework")

if(NOT EXISTS "${JUCE_DIR}")
    message(FATAL_ERROR "JUCE framework not found at ${JUCE_DIR}")
endif()

# Add JUCE as subdirectory
add_subdirectory("${JUCE_DIR}" juce_build)

# Create the plugin
juce_add_plugin(BricastiM7
    COMPANY_NAME "BricastiClone"
    PLUGIN_MANUFACTURER_CODE BrCl
    PLUGIN_CODE BcM7
    FORMATS ${JUCE_FORMATS}
    PRODUCT_NAME "Bricasti M7"
    DESCRIPTION "Bricasti M7 Reverb Clone"
    PLUGIN_VERSION_STRING "1.0.0"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    VST_NUM_MIDI_INPUTS 0
    VST_NUM_MIDI_OUTPUTS 0
    VST_COPY_DIR ""
    AAX_IDENTIFIER com.bricasti.m7
)

# Add source files
target_sources(BricastiM7 PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
    Source/DSP/M7ReverbEngine.cpp
    Source/DSP/FDN4x4.cpp
    Source/DSP/EarlyReflections.cpp
    Source/DSP/M7Modulation.cpp
    Source/DSP/M7EQ.cpp
    Source/Presets/M7FactoryPresets.cpp
    Source/UI/M7LookAndFeel.cpp
)

# Include directories
target_include_directories(BricastiM7 PRIVATE
    Source
    Source/DSP
    Source/UI
    Source/Presets
)

# Link JUCE libraries
target_link_libraries(BricastiM7 PRIVATE
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_core
    juce::juce_audio_basics
    juce::juce_audio_formats
    juce::juce_audio_devices
)

# Compiler-specific settings
if(MSVC)
    target_compile_options(BricastiM7 PRIVATE /fp:fast /arch:AVX2)
elseif(APPLE)
    target_compile_options(BricastiM7 PRIVATE -ffast-math -march=native)
else()
    target_compile_options(BricastiM7 PRIVATE -ffast-math -march=native -mfpmath=sse)
endif()

if(APPLE)
    target_compile_definitions(BricastiM7 PRIVATE JUCE_USE_CURL=0 JUCE_USE_OPENGL=0)
endif()

# VST3-only plugin - no VST2 conflicts
target_compile_definitions(BricastiM7 PRIVATE JUCE_VST3_CAN_REPLACE_VST2=0 JUCE_IGNORE_VST3_MISMATCHED_PARAMETER_ID_WARNING=1)

# Warnings
if(MSVC)
    target_compile_options(BricastiM7 PRIVATE /W3)
else()
    target_compile_options(BricastiM7 PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Set output directories
set_target_properties(BricastiM7 PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)