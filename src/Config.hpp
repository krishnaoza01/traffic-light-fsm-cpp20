#pragma once

namespace Config {
    // Timings in milliseconds
    inline constexpr int RED_TIME = 5000;
    inline constexpr int RED_YELLOW_TIME = 2000;
    inline constexpr int GREEN_TIME = 5000;
    inline constexpr int YELLOW_TIME = 2000;

    // Pedestrian crossing duration
    inline constexpr int PEDESTRIAN_TIME = 6000;

    // Night mode blink period
    inline constexpr int NIGHT_BLINK_PERIOD = 700;

    // Emergency override duration
    inline constexpr int EMERGENCY_DURATION = 4000;
}
