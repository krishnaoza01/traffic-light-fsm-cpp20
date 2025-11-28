#pragma once
#include <atomic>

class EmergencySensor {
public:
    void trigger() {
        emergency = true;
    }

    bool isEmergency() {
        if (emergency) {
            emergency = false;
            return true;
        }
        return false;
    }

private:
    std::atomic<bool> emergency = false;
};
