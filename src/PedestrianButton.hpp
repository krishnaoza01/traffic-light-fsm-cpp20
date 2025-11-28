#pragma once
#include <atomic>

class PedestrianButton {
public:
    void press() {
        pressed = true;
    }

    bool isPressed() {
        if (pressed) {
            pressed = false;
            return true;
        }
        return false;
    }

private:
    std::atomic<bool> pressed = false;
};
