#pragma once
#include "HardwareAbstraction.hpp"
#include "Timer.hpp"
#include <atomic>

class NightMode {
public:
    NightMode(LED &ledYellow) : yellow(ledYellow) {}

    void enable() { active = true; }
    void disable() { active = false; }

    bool isActive() const { return active; }

    void run() {
        if (!active) return;

        yellow.on("YELLOW");
        Timer::delayMs(300);
        yellow.off("YELLOW");
        Timer::delayMs(300);
    }

private:
    LED &yellow;
    std::atomic<bool> active = false;
};
