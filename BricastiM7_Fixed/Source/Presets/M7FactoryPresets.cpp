#include "M7FactoryPresets.h"

const std::vector<M7Preset> M7FactoryPresets::presets = {
    // Hall 1
    {
        "Hall 1",
        {
            {M7Parameters::DECAY_LOW_ID, 3.5f},
            {M7Parameters::DECAY_MID_ID, 2.8f},
            {M7Parameters::DECAY_HIGH_ID, 1.8f},
            {M7Parameters::PRE_DELAY_ID, 45.0f},
            {M7Parameters::DAMPING_LOW_ID, 0.7f},
            {M7Parameters::DAMPING_HIGH_ID, 0.4f},
            {M7Parameters::MOD_RATE_ID, 0.8f},
            {M7Parameters::MOD_DEPTH_ID, 0.3f},
            {M7Parameters::EARLY_LEVEL_ID, 0.6f},
            {M7Parameters::EARLY_DECAY_ID, 0.4f},
            {M7Parameters::SIZE_ID, 0.8f},
            {M7Parameters::DIFFUSION_ID, 0.7f},
            {M7Parameters::LOW_SHELF_ID, -2.0f},
            {M7Parameters::HIGH_SHELF_ID, 1.5f},
            {M7Parameters::MID_GAIN_ID, -1.0f},
            {M7Parameters::MID_FREQ_ID, 1000.0f},
            {M7Parameters::MIX_ID, 0.5f},
            {M7Parameters::FREEZE_ID, 0.0f},
            {M7Parameters::ALGORITHM_ID, 0.0f}
        }
    },
    // Plate 1
    {
        "Plate 1",
        {
            {M7Parameters::DECAY_LOW_ID, 2.5f},
            {M7Parameters::DECAY_MID_ID, 1.8f},
            {M7Parameters::DECAY_HIGH_ID, 0.9f},
            {M7Parameters::PRE_DELAY_ID, 20.0f},
            {M7Parameters::DAMPING_LOW_ID, 0.3f},
            {M7Parameters::DAMPING_HIGH_ID, 0.6f},
            {M7Parameters::MOD_RATE_ID, 1.2f},
            {M7Parameters::MOD_DEPTH_ID, 0.5f},
            {M7Parameters::EARLY_LEVEL_ID, 0.3f},
            {M7Parameters::EARLY_DECAY_ID, 0.2f},
            {M7Parameters::SIZE_ID, 0.6f},
            {M7Parameters::DIFFUSION_ID, 0.9f},
            {M7Parameters::LOW_SHELF_ID, 0.0f},
            {M7Parameters::HIGH_SHELF_ID, 2.0f},
            {M7Parameters::MID_GAIN_ID, 0.0f},
            {M7Parameters::MID_FREQ_ID, 2000.0f},
            {M7Parameters::MIX_ID, 0.6f},
            {M7Parameters::FREEZE_ID, 0.0f},
            {M7Parameters::ALGORITHM_ID, 7.0f}
        }
    },
    // Room 1
    {
        "Room 1",
        {
            {M7Parameters::DECAY_LOW_ID, 1.8f},
            {M7Parameters::DECAY_MID_ID, 1.2f},
            {M7Parameters::DECAY_HIGH_ID, 0.8f},
            {M7Parameters::PRE_DELAY_ID, 15.0f},
            {M7Parameters::DAMPING_LOW_ID, 0.5f},
            {M7Parameters::DAMPING_HIGH_ID, 0.5f},
            {M7Parameters::MOD_RATE_ID, 0.5f},
            {M7Parameters::MOD_DEPTH_ID, 0.2f},
            {M7Parameters::EARLY_LEVEL_ID, 0.4f},
            {M7Parameters::EARLY_DECAY_ID, 0.3f},
            {M7Parameters::SIZE_ID, 0.5f},
            {M7Parameters::DIFFUSION_ID, 0.6f},
            {M7Parameters::LOW_SHELF_ID, -1.0f},
            {M7Parameters::HIGH_SHELF_ID, 0.5f},
            {M7Parameters::MID_GAIN_ID, 0.0f},
            {M7Parameters::MID_FREQ_ID, 1500.0f},
            {M7Parameters::MIX_ID, 0.4f},
            {M7Parameters::FREEZE_ID, 0.0f},
            {M7Parameters::ALGORITHM_ID, 12.0f}
        }
    },
    // Add more presets here...
};

M7Preset M7FactoryPresets::getPreset(int index)
{
    if (index >= 0 && index < presets.size())
        return presets[index];
    return presets[0];
}