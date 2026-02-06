#pragma once

#include <JuceHeader.h>

/**
 * CrossPlatformUtils: Platform-specific utilities
 */
class CrossPlatformUtils
{
public:
    /**
     * Get plugin data directory (presets, IR cache, etc)
     */
    static juce::File getPluginDataDir()
    {
        #if JUCE_WINDOWS
        // Windows: AppData\Roaming\RiverberiAudio\RiverberiM7
        auto appData = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory);
        return appData.getChildFile("RiverberiAudio").getChildFile("RiverberiM7");

        #elif JUCE_MAC
        // macOS: ~/Library/Application Support/RiverberiAudio/RiverberiM7
        auto appSupport = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory);
        return appSupport.getChildFile("RiverberiAudio").getChildFile("RiverberiM7");

        #else // JUCE_LINUX
        // Linux: ~/.config/RiverberiAudio/RiverberiM7
        auto home = juce::File::getSpecialLocation(juce::File::userHomeDirectory);
        return home.getChildFile(".config").getChildFile("RiverberiAudio").getChildFile("RiverberiM7");
        #endif
    }

    /**
     * Get VST3 plugin directory
     */
    static juce::File getVST3Directory()
    {
        #if JUCE_WINDOWS
        auto programFiles = juce::File("C:\\Program Files\\Common Files\\VST3");
        return programFiles;

        #elif JUCE_MAC
        auto libraryDir = juce::File::getSpecialLocation(juce::File::userHomeDirectory)
                                      .getChildFile("Library").getChildFile("Audio").getChildFile("Plug-Ins")
                                      .getChildFile("VST3");
        return libraryDir;

        #else // JUCE_LINUX
        auto home = juce::File::getSpecialLocation(juce::File::userHomeDirectory);
        return home.getChildFile(".vst3");
        #endif
    }

    /**
     * Get AU plugin directory (macOS only)
     */
    static juce::File getAUDirectory()
    {
        #if JUCE_MAC
        auto libraryDir = juce::File::getSpecialLocation(juce::File::userHomeDirectory)
                                      .getChildFile("Library").getChildFile("Audio").getChildFile("Plug-Ins")
                                      .getChildFile("Components");
        return libraryDir;
        #else
        return juce::File();
        #endif
    }

    /**
     * Get platform-specific line ending
     */
    static juce::String getLineEnding()
    {
        #if JUCE_WINDOWS
        return "\r\n";
        #else
        return "\n";
        #endif
    }

    /**
     * Get number of logical CPU cores
     */
    static int getNumCores()
    {
        return std::thread::hardware_concurrency();
    }

    /**
     * Enable high-performance mode (reduce latency)
     */
    static void enableHighPerformanceMode()
    {
        #if JUCE_WINDOWS
        // Set thread priority high
        SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

        #elif JUCE_MAC
        // Would use macOS-specific threading APIs
        #endif
    }

    /**
     * Get current audio driver information
     */
    static juce::String getAudioDriverInfo()
    {
        #if JUCE_WINDOWS
        return "ASIO / Windows Audio";

        #elif JUCE_MAC
        return "Core Audio";

        #else // JUCE_LINUX
        return "ALSA / Jack";
        #endif
    }

    /**
     * Check available memory
     */
    static size_t getAvailableMemory()
    {
        #if JUCE_WINDOWS
        MEMORYSTATUSEX memStatus;
        memStatus.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memStatus);
        return memStatus.ullAvailPhys;

        #else
        // Simplified - would need platform-specific implementations
        return 0;
        #endif
    }

    /**
     * Get optimal thread pool size
     */
    static int getOptimalThreadPoolSize()
    {
        int numCores = getNumCores();

        // Leave one core for OS
        if (numCores > 1)
            return numCores - 1;

        return 1;
    }
};

/**
 * PerformanceMonitor: Monitor CPU and memory usage
 */
class PerformanceMonitor
{
public:
    struct Stats
    {
        float cpuUsage = 0.0f;
        float memoryUsage = 0.0f;
        float processingTime = 0.0f;
    };

    static void startMeasurement()
    {
        measurementStart = std::chrono::high_resolution_clock::now();
    }

    static float endMeasurement()
    {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - measurementStart);
        return duration.count() / 1000.0f; // Convert to milliseconds
    }

    static Stats getCurrentStats()
    {
        Stats stats;

        // CPU usage estimation (simplified)
        auto processingTime = endMeasurement();
        stats.processingTime = processingTime;

        // Would need platform-specific implementations for accurate CPU/memory
        #if JUCE_WINDOWS
        // Use GetProcessMemoryInfo on Windows
        stats.memoryUsage = 0.0f;
        #endif

        return stats;
    }

private:
    static std::chrono::high_resolution_clock::time_point measurementStart;
};
