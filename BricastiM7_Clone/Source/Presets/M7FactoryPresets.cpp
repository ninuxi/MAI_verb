#include "M7FactoryPresets.h"

// Helper macro to reduce verbosity
#define P(id, val) {id, val}

const std::vector<M7Preset> M7FactoryPresets::presets = {
    // ======================== HALLS (0-6) ========================
    // 0: Hall 1 - Medium Concert Hall
    {"Hall 1 - Concert",
     {P(M7Parameters::DECAY_LOW_ID, 3.5f), P(M7Parameters::DECAY_MID_ID, 2.8f), P(M7Parameters::DECAY_HIGH_ID, 1.8f),
      P(M7Parameters::PRE_DELAY_ID, 45.0f), P(M7Parameters::DAMPING_LOW_ID, 0.3f), P(M7Parameters::DAMPING_HIGH_ID, 0.4f),
      P(M7Parameters::MOD_RATE_ID, 0.8f), P(M7Parameters::MOD_DEPTH_ID, 0.3f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.6f), P(M7Parameters::EARLY_DECAY_ID, 0.4f),
      P(M7Parameters::SIZE_ID, 0.8f), P(M7Parameters::DIFFUSION_ID, 0.7f),
      P(M7Parameters::LOW_SHELF_ID, -2.0f), P(M7Parameters::HIGH_SHELF_ID, 1.5f),
      P(M7Parameters::MID_GAIN_ID, -1.0f), P(M7Parameters::MID_FREQ_ID, 1000.0f),
      P(M7Parameters::MIX_ID, 0.5f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 0.0f)}},

    // 1: Hall 2 - Large Hall
    {"Hall 2 - Large",
     {P(M7Parameters::DECAY_LOW_ID, 4.5f), P(M7Parameters::DECAY_MID_ID, 3.5f), P(M7Parameters::DECAY_HIGH_ID, 2.0f),
      P(M7Parameters::PRE_DELAY_ID, 60.0f), P(M7Parameters::DAMPING_LOW_ID, 0.3f), P(M7Parameters::DAMPING_HIGH_ID, 0.5f),
      P(M7Parameters::MOD_RATE_ID, 0.7f), P(M7Parameters::MOD_DEPTH_ID, 0.25f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.5f), P(M7Parameters::EARLY_DECAY_ID, 0.5f),
      P(M7Parameters::SIZE_ID, 0.85f), P(M7Parameters::DIFFUSION_ID, 0.75f),
      P(M7Parameters::LOW_SHELF_ID, -1.5f), P(M7Parameters::HIGH_SHELF_ID, 1.0f),
      P(M7Parameters::MID_GAIN_ID, 0.0f), P(M7Parameters::MID_FREQ_ID, 800.0f),
      P(M7Parameters::MIX_ID, 0.45f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 1.0f)}},

    // 2: Hall 3 - Grand Hall
    {"Hall 3 - Grand",
     {P(M7Parameters::DECAY_LOW_ID, 5.5f), P(M7Parameters::DECAY_MID_ID, 4.2f), P(M7Parameters::DECAY_HIGH_ID, 2.5f),
      P(M7Parameters::PRE_DELAY_ID, 80.0f), P(M7Parameters::DAMPING_LOW_ID, 0.2f), P(M7Parameters::DAMPING_HIGH_ID, 0.45f),
      P(M7Parameters::MOD_RATE_ID, 0.6f), P(M7Parameters::MOD_DEPTH_ID, 0.35f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.55f), P(M7Parameters::EARLY_DECAY_ID, 0.45f),
      P(M7Parameters::SIZE_ID, 0.9f), P(M7Parameters::DIFFUSION_ID, 0.8f),
      P(M7Parameters::LOW_SHELF_ID, -2.5f), P(M7Parameters::HIGH_SHELF_ID, 0.5f),
      P(M7Parameters::MID_GAIN_ID, -0.5f), P(M7Parameters::MID_FREQ_ID, 1200.0f),
      P(M7Parameters::MIX_ID, 0.4f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 2.0f)}},

    // 3: Hall 4 - Small Warm Hall
    {"Hall 4 - Warm",
     {P(M7Parameters::DECAY_LOW_ID, 2.5f), P(M7Parameters::DECAY_MID_ID, 2.0f), P(M7Parameters::DECAY_HIGH_ID, 1.2f),
      P(M7Parameters::PRE_DELAY_ID, 30.0f), P(M7Parameters::DAMPING_LOW_ID, 0.4f), P(M7Parameters::DAMPING_HIGH_ID, 0.35f),
      P(M7Parameters::MOD_RATE_ID, 0.9f), P(M7Parameters::MOD_DEPTH_ID, 0.2f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.65f), P(M7Parameters::EARLY_DECAY_ID, 0.35f),
      P(M7Parameters::SIZE_ID, 0.7f), P(M7Parameters::DIFFUSION_ID, 0.65f),
      P(M7Parameters::LOW_SHELF_ID, -1.0f), P(M7Parameters::HIGH_SHELF_ID, 2.0f),
      P(M7Parameters::MID_GAIN_ID, 0.5f), P(M7Parameters::MID_FREQ_ID, 1500.0f),
      P(M7Parameters::MIX_ID, 0.5f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 3.0f)}},

    // 4: Hall 5 - Cathedral
    {"Hall 5 - Cathedral",
     {P(M7Parameters::DECAY_LOW_ID, 7.0f), P(M7Parameters::DECAY_MID_ID, 5.5f), P(M7Parameters::DECAY_HIGH_ID, 3.0f),
      P(M7Parameters::PRE_DELAY_ID, 100.0f), P(M7Parameters::DAMPING_LOW_ID, 0.2f), P(M7Parameters::DAMPING_HIGH_ID, 0.5f),
      P(M7Parameters::MOD_RATE_ID, 0.5f), P(M7Parameters::MOD_DEPTH_ID, 0.4f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.4f), P(M7Parameters::EARLY_DECAY_ID, 0.5f),
      P(M7Parameters::SIZE_ID, 0.95f), P(M7Parameters::DIFFUSION_ID, 0.85f),
      P(M7Parameters::LOW_SHELF_ID, -3.0f), P(M7Parameters::HIGH_SHELF_ID, 0.0f),
      P(M7Parameters::MID_GAIN_ID, -1.5f), P(M7Parameters::MID_FREQ_ID, 900.0f),
      P(M7Parameters::MIX_ID, 0.35f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 4.0f)}},

    // 5: Hall 6 - Bright Hall
    {"Hall 6 - Bright",
     {P(M7Parameters::DECAY_LOW_ID, 3.0f), P(M7Parameters::DECAY_MID_ID, 2.2f), P(M7Parameters::DECAY_HIGH_ID, 1.5f),
      P(M7Parameters::PRE_DELAY_ID, 35.0f), P(M7Parameters::DAMPING_LOW_ID, 0.35f), P(M7Parameters::DAMPING_HIGH_ID, 0.3f),
      P(M7Parameters::MOD_RATE_ID, 1.0f), P(M7Parameters::MOD_DEPTH_ID, 0.3f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.7f), P(M7Parameters::EARLY_DECAY_ID, 0.3f),
      P(M7Parameters::SIZE_ID, 0.75f), P(M7Parameters::DIFFUSION_ID, 0.7f),
      P(M7Parameters::LOW_SHELF_ID, -1.5f), P(M7Parameters::HIGH_SHELF_ID, 2.5f),
      P(M7Parameters::MID_GAIN_ID, 0.0f), P(M7Parameters::MID_FREQ_ID, 2000.0f),
      P(M7Parameters::MIX_ID, 0.5f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 5.0f)}},

    // 6: Hall 7 - Infinite
    {"Hall 7 - Infinite",
     {P(M7Parameters::DECAY_LOW_ID, 10.0f), P(M7Parameters::DECAY_MID_ID, 8.0f), P(M7Parameters::DECAY_HIGH_ID, 4.0f),
      P(M7Parameters::PRE_DELAY_ID, 120.0f), P(M7Parameters::DAMPING_LOW_ID, 0.15f), P(M7Parameters::DAMPING_HIGH_ID, 0.55f),
      P(M7Parameters::MOD_RATE_ID, 0.4f), P(M7Parameters::MOD_DEPTH_ID, 0.45f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.3f), P(M7Parameters::EARLY_DECAY_ID, 0.6f),
      P(M7Parameters::SIZE_ID, 1.0f), P(M7Parameters::DIFFUSION_ID, 0.9f),
      P(M7Parameters::LOW_SHELF_ID, -4.0f), P(M7Parameters::HIGH_SHELF_ID, -1.0f),
      P(M7Parameters::MID_GAIN_ID, -2.0f), P(M7Parameters::MID_FREQ_ID, 800.0f),
      P(M7Parameters::MIX_ID, 0.3f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 6.0f)}},

    // ======================== PLATES (7-11) ========================
    // 7: Plate 1 - Classic
    {"Plate 1 - Classic",
     {P(M7Parameters::DECAY_LOW_ID, 2.5f), P(M7Parameters::DECAY_MID_ID, 1.8f), P(M7Parameters::DECAY_HIGH_ID, 0.9f),
      P(M7Parameters::PRE_DELAY_ID, 20.0f), P(M7Parameters::DAMPING_LOW_ID, 0.2f), P(M7Parameters::DAMPING_HIGH_ID, 0.6f),
      P(M7Parameters::MOD_RATE_ID, 1.2f), P(M7Parameters::MOD_DEPTH_ID, 0.5f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.15f), P(M7Parameters::EARLY_DECAY_ID, 0.2f),
      P(M7Parameters::SIZE_ID, 0.6f), P(M7Parameters::DIFFUSION_ID, 0.9f),
      P(M7Parameters::LOW_SHELF_ID, 0.0f), P(M7Parameters::HIGH_SHELF_ID, 2.0f),
      P(M7Parameters::MID_GAIN_ID, 0.0f), P(M7Parameters::MID_FREQ_ID, 2000.0f),
      P(M7Parameters::MIX_ID, 0.6f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 7.0f)}},

    // 8: Plate 2 - Long Bright
    {"Plate 2 - Bright",
     {P(M7Parameters::DECAY_LOW_ID, 3.5f), P(M7Parameters::DECAY_MID_ID, 2.5f), P(M7Parameters::DECAY_HIGH_ID, 1.2f),
      P(M7Parameters::PRE_DELAY_ID, 15.0f), P(M7Parameters::DAMPING_LOW_ID, 0.2f), P(M7Parameters::DAMPING_HIGH_ID, 0.55f),
      P(M7Parameters::MOD_RATE_ID, 1.0f), P(M7Parameters::MOD_DEPTH_ID, 0.45f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.1f), P(M7Parameters::EARLY_DECAY_ID, 0.15f),
      P(M7Parameters::SIZE_ID, 0.55f), P(M7Parameters::DIFFUSION_ID, 0.95f),
      P(M7Parameters::LOW_SHELF_ID, 0.5f), P(M7Parameters::HIGH_SHELF_ID, 3.0f),
      P(M7Parameters::MID_GAIN_ID, 0.0f), P(M7Parameters::MID_FREQ_ID, 2500.0f),
      P(M7Parameters::MIX_ID, 0.55f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 8.0f)}},

    // 9: Plate 3 - Short Tight
    {"Plate 3 - Tight",
     {P(M7Parameters::DECAY_LOW_ID, 1.8f), P(M7Parameters::DECAY_MID_ID, 1.2f), P(M7Parameters::DECAY_HIGH_ID, 0.7f),
      P(M7Parameters::PRE_DELAY_ID, 10.0f), P(M7Parameters::DAMPING_LOW_ID, 0.25f), P(M7Parameters::DAMPING_HIGH_ID, 0.5f),
      P(M7Parameters::MOD_RATE_ID, 1.5f), P(M7Parameters::MOD_DEPTH_ID, 0.55f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.1f), P(M7Parameters::EARLY_DECAY_ID, 0.1f),
      P(M7Parameters::SIZE_ID, 0.5f), P(M7Parameters::DIFFUSION_ID, 0.92f),
      P(M7Parameters::LOW_SHELF_ID, -1.0f), P(M7Parameters::HIGH_SHELF_ID, 1.5f),
      P(M7Parameters::MID_GAIN_ID, 0.5f), P(M7Parameters::MID_FREQ_ID, 3000.0f),
      P(M7Parameters::MIX_ID, 0.55f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 9.0f)}},

    // 10: Plate 4 - Dark Warm
    {"Plate 4 - Dark",
     {P(M7Parameters::DECAY_LOW_ID, 4.0f), P(M7Parameters::DECAY_MID_ID, 3.0f), P(M7Parameters::DECAY_HIGH_ID, 1.5f),
      P(M7Parameters::PRE_DELAY_ID, 25.0f), P(M7Parameters::DAMPING_LOW_ID, 0.15f), P(M7Parameters::DAMPING_HIGH_ID, 0.65f),
      P(M7Parameters::MOD_RATE_ID, 0.8f), P(M7Parameters::MOD_DEPTH_ID, 0.4f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.2f), P(M7Parameters::EARLY_DECAY_ID, 0.25f),
      P(M7Parameters::SIZE_ID, 0.65f), P(M7Parameters::DIFFUSION_ID, 0.88f),
      P(M7Parameters::LOW_SHELF_ID, 0.0f), P(M7Parameters::HIGH_SHELF_ID, -2.0f),
      P(M7Parameters::MID_GAIN_ID, -0.5f), P(M7Parameters::MID_FREQ_ID, 1800.0f),
      P(M7Parameters::MIX_ID, 0.5f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 10.0f)}},

    // 11: Plate 5 - Shimmer
    {"Plate 5 - Shimmer",
     {P(M7Parameters::DECAY_LOW_ID, 2.0f), P(M7Parameters::DECAY_MID_ID, 1.5f), P(M7Parameters::DECAY_HIGH_ID, 0.8f),
      P(M7Parameters::PRE_DELAY_ID, 5.0f), P(M7Parameters::DAMPING_LOW_ID, 0.3f), P(M7Parameters::DAMPING_HIGH_ID, 0.4f),
      P(M7Parameters::MOD_RATE_ID, 1.3f), P(M7Parameters::MOD_DEPTH_ID, 0.5f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.05f), P(M7Parameters::EARLY_DECAY_ID, 0.1f),
      P(M7Parameters::SIZE_ID, 0.45f), P(M7Parameters::DIFFUSION_ID, 0.95f),
      P(M7Parameters::LOW_SHELF_ID, -2.0f), P(M7Parameters::HIGH_SHELF_ID, 4.0f),
      P(M7Parameters::MID_GAIN_ID, 0.0f), P(M7Parameters::MID_FREQ_ID, 4000.0f),
      P(M7Parameters::MIX_ID, 0.6f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 11.0f)}},

    // ======================== ROOMS (12-15) ========================
    // 12: Room 1 - Medium Room
    {"Room 1 - Medium",
     {P(M7Parameters::DECAY_LOW_ID, 1.8f), P(M7Parameters::DECAY_MID_ID, 1.2f), P(M7Parameters::DECAY_HIGH_ID, 0.8f),
      P(M7Parameters::PRE_DELAY_ID, 15.0f), P(M7Parameters::DAMPING_LOW_ID, 0.4f), P(M7Parameters::DAMPING_HIGH_ID, 0.3f),
      P(M7Parameters::MOD_RATE_ID, 0.5f), P(M7Parameters::MOD_DEPTH_ID, 0.2f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.7f), P(M7Parameters::EARLY_DECAY_ID, 0.3f),
      P(M7Parameters::SIZE_ID, 0.4f), P(M7Parameters::DIFFUSION_ID, 0.6f),
      P(M7Parameters::LOW_SHELF_ID, -1.0f), P(M7Parameters::HIGH_SHELF_ID, 0.5f),
      P(M7Parameters::MID_GAIN_ID, 0.0f), P(M7Parameters::MID_FREQ_ID, 1500.0f),
      P(M7Parameters::MIX_ID, 0.4f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 12.0f)}},

    // 13: Room 2 - Small Tight
    {"Room 2 - Small",
     {P(M7Parameters::DECAY_LOW_ID, 1.2f), P(M7Parameters::DECAY_MID_ID, 0.8f), P(M7Parameters::DECAY_HIGH_ID, 0.5f),
      P(M7Parameters::PRE_DELAY_ID, 8.0f), P(M7Parameters::DAMPING_LOW_ID, 0.5f), P(M7Parameters::DAMPING_HIGH_ID, 0.25f),
      P(M7Parameters::MOD_RATE_ID, 0.4f), P(M7Parameters::MOD_DEPTH_ID, 0.15f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.8f), P(M7Parameters::EARLY_DECAY_ID, 0.25f),
      P(M7Parameters::SIZE_ID, 0.3f), P(M7Parameters::DIFFUSION_ID, 0.5f),
      P(M7Parameters::LOW_SHELF_ID, -0.5f), P(M7Parameters::HIGH_SHELF_ID, 0.0f),
      P(M7Parameters::MID_GAIN_ID, 0.5f), P(M7Parameters::MID_FREQ_ID, 2000.0f),
      P(M7Parameters::MIX_ID, 0.35f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 13.0f)}},

    // 14: Room 3 - Large Room
    {"Room 3 - Large",
     {P(M7Parameters::DECAY_LOW_ID, 2.2f), P(M7Parameters::DECAY_MID_ID, 1.5f), P(M7Parameters::DECAY_HIGH_ID, 1.0f),
      P(M7Parameters::PRE_DELAY_ID, 25.0f), P(M7Parameters::DAMPING_LOW_ID, 0.35f), P(M7Parameters::DAMPING_HIGH_ID, 0.35f),
      P(M7Parameters::MOD_RATE_ID, 0.6f), P(M7Parameters::MOD_DEPTH_ID, 0.25f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.6f), P(M7Parameters::EARLY_DECAY_ID, 0.35f),
      P(M7Parameters::SIZE_ID, 0.5f), P(M7Parameters::DIFFUSION_ID, 0.65f),
      P(M7Parameters::LOW_SHELF_ID, -1.5f), P(M7Parameters::HIGH_SHELF_ID, 1.0f),
      P(M7Parameters::MID_GAIN_ID, -0.5f), P(M7Parameters::MID_FREQ_ID, 1200.0f),
      P(M7Parameters::MIX_ID, 0.4f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 14.0f)}},

    // 15: Room 4 - Tiny
    {"Room 4 - Tiny",
     {P(M7Parameters::DECAY_LOW_ID, 0.8f), P(M7Parameters::DECAY_MID_ID, 0.5f), P(M7Parameters::DECAY_HIGH_ID, 0.3f),
      P(M7Parameters::PRE_DELAY_ID, 3.0f), P(M7Parameters::DAMPING_LOW_ID, 0.6f), P(M7Parameters::DAMPING_HIGH_ID, 0.2f),
      P(M7Parameters::MOD_RATE_ID, 0.3f), P(M7Parameters::MOD_DEPTH_ID, 0.1f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.85f), P(M7Parameters::EARLY_DECAY_ID, 0.2f),
      P(M7Parameters::SIZE_ID, 0.2f), P(M7Parameters::DIFFUSION_ID, 0.4f),
      P(M7Parameters::LOW_SHELF_ID, 0.0f), P(M7Parameters::HIGH_SHELF_ID, -1.0f),
      P(M7Parameters::MID_GAIN_ID, 1.0f), P(M7Parameters::MID_FREQ_ID, 2500.0f),
      P(M7Parameters::MIX_ID, 0.3f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 15.0f)}},

    // ======================== CHAMBERS (16-18) ========================
    // 16: Chamber 1 - Classic
    {"Chamber 1 - Classic",
     {P(M7Parameters::DECAY_LOW_ID, 2.8f), P(M7Parameters::DECAY_MID_ID, 2.0f), P(M7Parameters::DECAY_HIGH_ID, 1.3f),
      P(M7Parameters::PRE_DELAY_ID, 35.0f), P(M7Parameters::DAMPING_LOW_ID, 0.35f), P(M7Parameters::DAMPING_HIGH_ID, 0.4f),
      P(M7Parameters::MOD_RATE_ID, 0.7f), P(M7Parameters::MOD_DEPTH_ID, 0.3f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.5f), P(M7Parameters::EARLY_DECAY_ID, 0.4f),
      P(M7Parameters::SIZE_ID, 0.6f), P(M7Parameters::DIFFUSION_ID, 0.75f),
      P(M7Parameters::LOW_SHELF_ID, -1.0f), P(M7Parameters::HIGH_SHELF_ID, 1.5f),
      P(M7Parameters::MID_GAIN_ID, 0.0f), P(M7Parameters::MID_FREQ_ID, 1000.0f),
      P(M7Parameters::MIX_ID, 0.45f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 16.0f)}},

    // 17: Chamber 2 - Large
    {"Chamber 2 - Large",
     {P(M7Parameters::DECAY_LOW_ID, 3.5f), P(M7Parameters::DECAY_MID_ID, 2.5f), P(M7Parameters::DECAY_HIGH_ID, 1.6f),
      P(M7Parameters::PRE_DELAY_ID, 50.0f), P(M7Parameters::DAMPING_LOW_ID, 0.3f), P(M7Parameters::DAMPING_HIGH_ID, 0.45f),
      P(M7Parameters::MOD_RATE_ID, 0.6f), P(M7Parameters::MOD_DEPTH_ID, 0.35f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.45f), P(M7Parameters::EARLY_DECAY_ID, 0.45f),
      P(M7Parameters::SIZE_ID, 0.65f), P(M7Parameters::DIFFUSION_ID, 0.8f),
      P(M7Parameters::LOW_SHELF_ID, -2.0f), P(M7Parameters::HIGH_SHELF_ID, 1.0f),
      P(M7Parameters::MID_GAIN_ID, -0.5f), P(M7Parameters::MID_FREQ_ID, 900.0f),
      P(M7Parameters::MIX_ID, 0.4f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 17.0f)}},

    // 18: Chamber 3 - Warm
    {"Chamber 3 - Warm",
     {P(M7Parameters::DECAY_LOW_ID, 2.0f), P(M7Parameters::DECAY_MID_ID, 1.5f), P(M7Parameters::DECAY_HIGH_ID, 1.0f),
      P(M7Parameters::PRE_DELAY_ID, 25.0f), P(M7Parameters::DAMPING_LOW_ID, 0.4f), P(M7Parameters::DAMPING_HIGH_ID, 0.35f),
      P(M7Parameters::MOD_RATE_ID, 0.8f), P(M7Parameters::MOD_DEPTH_ID, 0.25f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.55f), P(M7Parameters::EARLY_DECAY_ID, 0.35f),
      P(M7Parameters::SIZE_ID, 0.55f), P(M7Parameters::DIFFUSION_ID, 0.7f),
      P(M7Parameters::LOW_SHELF_ID, -0.5f), P(M7Parameters::HIGH_SHELF_ID, -1.0f),
      P(M7Parameters::MID_GAIN_ID, 0.5f), P(M7Parameters::MID_FREQ_ID, 1500.0f),
      P(M7Parameters::MIX_ID, 0.45f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 18.0f)}},

    // ======================== SPECIAL (19-24) ========================
    // 19: Vocal Hall
    {"Vocal Hall",
     {P(M7Parameters::DECAY_LOW_ID, 2.2f), P(M7Parameters::DECAY_MID_ID, 1.8f), P(M7Parameters::DECAY_HIGH_ID, 1.0f),
      P(M7Parameters::PRE_DELAY_ID, 40.0f), P(M7Parameters::DAMPING_LOW_ID, 0.4f), P(M7Parameters::DAMPING_HIGH_ID, 0.45f),
      P(M7Parameters::MOD_RATE_ID, 0.6f), P(M7Parameters::MOD_DEPTH_ID, 0.2f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.55f), P(M7Parameters::EARLY_DECAY_ID, 0.35f),
      P(M7Parameters::SIZE_ID, 0.65f), P(M7Parameters::DIFFUSION_ID, 0.7f),
      P(M7Parameters::LOW_SHELF_ID, -3.0f), P(M7Parameters::HIGH_SHELF_ID, 1.0f),
      P(M7Parameters::MID_GAIN_ID, 1.5f), P(M7Parameters::MID_FREQ_ID, 2500.0f),
      P(M7Parameters::MIX_ID, 0.35f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 0.0f)}},

    // 20: Ambient Pad
    {"Ambient Pad",
     {P(M7Parameters::DECAY_LOW_ID, 8.0f), P(M7Parameters::DECAY_MID_ID, 6.0f), P(M7Parameters::DECAY_HIGH_ID, 3.5f),
      P(M7Parameters::PRE_DELAY_ID, 80.0f), P(M7Parameters::DAMPING_LOW_ID, 0.15f), P(M7Parameters::DAMPING_HIGH_ID, 0.5f),
      P(M7Parameters::MOD_RATE_ID, 0.3f), P(M7Parameters::MOD_DEPTH_ID, 0.5f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.2f), P(M7Parameters::EARLY_DECAY_ID, 0.6f),
      P(M7Parameters::SIZE_ID, 1.0f), P(M7Parameters::DIFFUSION_ID, 0.95f),
      P(M7Parameters::LOW_SHELF_ID, -2.0f), P(M7Parameters::HIGH_SHELF_ID, -2.0f),
      P(M7Parameters::MID_GAIN_ID, 0.0f), P(M7Parameters::MID_FREQ_ID, 800.0f),
      P(M7Parameters::MIX_ID, 0.7f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 6.0f)}},

    // 21: Snare Room
    {"Snare Room",
     {P(M7Parameters::DECAY_LOW_ID, 1.0f), P(M7Parameters::DECAY_MID_ID, 0.7f), P(M7Parameters::DECAY_HIGH_ID, 0.4f),
      P(M7Parameters::PRE_DELAY_ID, 5.0f), P(M7Parameters::DAMPING_LOW_ID, 0.5f), P(M7Parameters::DAMPING_HIGH_ID, 0.3f),
      P(M7Parameters::MOD_RATE_ID, 0.4f), P(M7Parameters::MOD_DEPTH_ID, 0.1f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.9f), P(M7Parameters::EARLY_DECAY_ID, 0.2f),
      P(M7Parameters::SIZE_ID, 0.35f), P(M7Parameters::DIFFUSION_ID, 0.55f),
      P(M7Parameters::LOW_SHELF_ID, -2.0f), P(M7Parameters::HIGH_SHELF_ID, 2.0f),
      P(M7Parameters::MID_GAIN_ID, 1.0f), P(M7Parameters::MID_FREQ_ID, 3500.0f),
      P(M7Parameters::MIX_ID, 0.25f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 12.0f)}},

    // 22: Piano Hall
    {"Piano Hall",
     {P(M7Parameters::DECAY_LOW_ID, 3.0f), P(M7Parameters::DECAY_MID_ID, 2.5f), P(M7Parameters::DECAY_HIGH_ID, 1.5f),
      P(M7Parameters::PRE_DELAY_ID, 30.0f), P(M7Parameters::DAMPING_LOW_ID, 0.25f), P(M7Parameters::DAMPING_HIGH_ID, 0.4f),
      P(M7Parameters::MOD_RATE_ID, 0.5f), P(M7Parameters::MOD_DEPTH_ID, 0.25f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.6f), P(M7Parameters::EARLY_DECAY_ID, 0.4f),
      P(M7Parameters::SIZE_ID, 0.8f), P(M7Parameters::DIFFUSION_ID, 0.75f),
      P(M7Parameters::LOW_SHELF_ID, -1.0f), P(M7Parameters::HIGH_SHELF_ID, 1.5f),
      P(M7Parameters::MID_GAIN_ID, -1.0f), P(M7Parameters::MID_FREQ_ID, 1200.0f),
      P(M7Parameters::MIX_ID, 0.4f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 0.0f)}},

    // 23: Guitar Spring
    {"Guitar Spring",
     {P(M7Parameters::DECAY_LOW_ID, 1.5f), P(M7Parameters::DECAY_MID_ID, 1.2f), P(M7Parameters::DECAY_HIGH_ID, 0.6f),
      P(M7Parameters::PRE_DELAY_ID, 10.0f), P(M7Parameters::DAMPING_LOW_ID, 0.45f), P(M7Parameters::DAMPING_HIGH_ID, 0.5f),
      P(M7Parameters::MOD_RATE_ID, 2.0f), P(M7Parameters::MOD_DEPTH_ID, 0.6f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.3f), P(M7Parameters::EARLY_DECAY_ID, 0.15f),
      P(M7Parameters::SIZE_ID, 0.35f), P(M7Parameters::DIFFUSION_ID, 0.5f),
      P(M7Parameters::LOW_SHELF_ID, -1.5f), P(M7Parameters::HIGH_SHELF_ID, 3.0f),
      P(M7Parameters::MID_GAIN_ID, 2.0f), P(M7Parameters::MID_FREQ_ID, 3000.0f),
      P(M7Parameters::MIX_ID, 0.5f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 7.0f)}},

    // 24: Gated Reverb
    {"Gated Reverb",
     {P(M7Parameters::DECAY_LOW_ID, 0.5f), P(M7Parameters::DECAY_MID_ID, 0.3f), P(M7Parameters::DECAY_HIGH_ID, 0.2f),
      P(M7Parameters::PRE_DELAY_ID, 0.0f), P(M7Parameters::DAMPING_LOW_ID, 0.6f), P(M7Parameters::DAMPING_HIGH_ID, 0.2f),
      P(M7Parameters::MOD_RATE_ID, 0.3f), P(M7Parameters::MOD_DEPTH_ID, 0.1f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.9f), P(M7Parameters::EARLY_DECAY_ID, 0.1f),
      P(M7Parameters::SIZE_ID, 0.5f), P(M7Parameters::DIFFUSION_ID, 0.9f),
      P(M7Parameters::LOW_SHELF_ID, 0.0f), P(M7Parameters::HIGH_SHELF_ID, 3.0f),
      P(M7Parameters::MID_GAIN_ID, 0.0f), P(M7Parameters::MID_FREQ_ID, 2000.0f),
      P(M7Parameters::MIX_ID, 0.6f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 12.0f)}},

    // ======================== UTILITY (25-29) ========================
    // 25: Mono Room
    {"Mono Room",
     {P(M7Parameters::DECAY_LOW_ID, 1.5f), P(M7Parameters::DECAY_MID_ID, 1.0f), P(M7Parameters::DECAY_HIGH_ID, 0.6f),
      P(M7Parameters::PRE_DELAY_ID, 10.0f), P(M7Parameters::DAMPING_LOW_ID, 0.45f), P(M7Parameters::DAMPING_HIGH_ID, 0.35f),
      P(M7Parameters::MOD_RATE_ID, 0.4f), P(M7Parameters::MOD_DEPTH_ID, 0.15f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.75f), P(M7Parameters::EARLY_DECAY_ID, 0.25f),
      P(M7Parameters::SIZE_ID, 0.35f), P(M7Parameters::DIFFUSION_ID, 0.55f),
      P(M7Parameters::LOW_SHELF_ID, -1.0f), P(M7Parameters::HIGH_SHELF_ID, 0.0f),
      P(M7Parameters::MID_GAIN_ID, 0.5f), P(M7Parameters::MID_FREQ_ID, 1800.0f),
      P(M7Parameters::MIX_ID, 0.3f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 13.0f)}},

    // 26: Wide Stereo
    {"Wide Stereo",
     {P(M7Parameters::DECAY_LOW_ID, 3.0f), P(M7Parameters::DECAY_MID_ID, 2.2f), P(M7Parameters::DECAY_HIGH_ID, 1.3f),
      P(M7Parameters::PRE_DELAY_ID, 50.0f), P(M7Parameters::DAMPING_LOW_ID, 0.3f), P(M7Parameters::DAMPING_HIGH_ID, 0.4f),
      P(M7Parameters::MOD_RATE_ID, 0.8f), P(M7Parameters::MOD_DEPTH_ID, 0.4f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.7f), P(M7Parameters::EARLY_DECAY_ID, 0.45f),
      P(M7Parameters::SIZE_ID, 0.85f), P(M7Parameters::DIFFUSION_ID, 0.8f),
      P(M7Parameters::LOW_SHELF_ID, -1.5f), P(M7Parameters::HIGH_SHELF_ID, 2.0f),
      P(M7Parameters::MID_GAIN_ID, 0.0f), P(M7Parameters::MID_FREQ_ID, 1500.0f),
      P(M7Parameters::MIX_ID, 0.45f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 0.0f)}},

    // 27: Dark Warm
    {"Dark Warm",
     {P(M7Parameters::DECAY_LOW_ID, 4.0f), P(M7Parameters::DECAY_MID_ID, 3.0f), P(M7Parameters::DECAY_HIGH_ID, 1.2f),
      P(M7Parameters::PRE_DELAY_ID, 40.0f), P(M7Parameters::DAMPING_LOW_ID, 0.2f), P(M7Parameters::DAMPING_HIGH_ID, 0.7f),
      P(M7Parameters::MOD_RATE_ID, 0.5f), P(M7Parameters::MOD_DEPTH_ID, 0.3f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.5f), P(M7Parameters::EARLY_DECAY_ID, 0.4f),
      P(M7Parameters::SIZE_ID, 0.75f), P(M7Parameters::DIFFUSION_ID, 0.75f),
      P(M7Parameters::LOW_SHELF_ID, 1.0f), P(M7Parameters::HIGH_SHELF_ID, -4.0f),
      P(M7Parameters::MID_GAIN_ID, -1.0f), P(M7Parameters::MID_FREQ_ID, 800.0f),
      P(M7Parameters::MIX_ID, 0.45f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 0.0f)}},

    // 28: Bright Airy
    {"Bright Airy",
     {P(M7Parameters::DECAY_LOW_ID, 2.0f), P(M7Parameters::DECAY_MID_ID, 2.5f), P(M7Parameters::DECAY_HIGH_ID, 2.0f),
      P(M7Parameters::PRE_DELAY_ID, 30.0f), P(M7Parameters::DAMPING_LOW_ID, 0.4f), P(M7Parameters::DAMPING_HIGH_ID, 0.2f),
      P(M7Parameters::MOD_RATE_ID, 1.0f), P(M7Parameters::MOD_DEPTH_ID, 0.35f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.6f), P(M7Parameters::EARLY_DECAY_ID, 0.3f),
      P(M7Parameters::SIZE_ID, 0.7f), P(M7Parameters::DIFFUSION_ID, 0.8f),
      P(M7Parameters::LOW_SHELF_ID, -3.0f), P(M7Parameters::HIGH_SHELF_ID, 4.0f),
      P(M7Parameters::MID_GAIN_ID, 1.0f), P(M7Parameters::MID_FREQ_ID, 3000.0f),
      P(M7Parameters::MIX_ID, 0.5f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 7.0f)}},

    // 29: Long Decay
    {"Long Decay",
     {P(M7Parameters::DECAY_LOW_ID, 12.0f), P(M7Parameters::DECAY_MID_ID, 10.0f), P(M7Parameters::DECAY_HIGH_ID, 5.0f),
      P(M7Parameters::PRE_DELAY_ID, 60.0f), P(M7Parameters::DAMPING_LOW_ID, 0.15f), P(M7Parameters::DAMPING_HIGH_ID, 0.5f),
      P(M7Parameters::MOD_RATE_ID, 0.3f), P(M7Parameters::MOD_DEPTH_ID, 0.5f),
      P(M7Parameters::EARLY_LEVEL_ID, 0.25f), P(M7Parameters::EARLY_DECAY_ID, 0.55f),
      P(M7Parameters::SIZE_ID, 1.0f), P(M7Parameters::DIFFUSION_ID, 0.9f),
      P(M7Parameters::LOW_SHELF_ID, -3.0f), P(M7Parameters::HIGH_SHELF_ID, -1.0f),
      P(M7Parameters::MID_GAIN_ID, -1.5f), P(M7Parameters::MID_FREQ_ID, 700.0f),
      P(M7Parameters::MIX_ID, 0.35f), P(M7Parameters::FREEZE_ID, 0.0f), P(M7Parameters::ALGORITHM_ID, 6.0f)}},
};

#undef P

M7Preset M7FactoryPresets::getPreset(int index)
{
    if (index >= 0 && index < static_cast<int>(presets.size()))
        return presets[static_cast<size_t>(index)];
    return presets[0];
}
