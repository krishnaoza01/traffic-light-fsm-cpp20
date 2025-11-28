#pragma once
#include <chrono>
#include <thread>
#include <functional>

class Timer {
public:
    static void delayMs(int ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    static void runPeriodic(int periodMs, const std::function<void()> &task) {
        while (true) {
            auto start = std::chrono::high_resolution_clock::now();
            task();
            auto end = std::chrono::high_resolution_clock::now();

            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            int remaining = periodMs - elapsed.count();
            if (remaining > 0)
                delayMs(remaining);
        }
    }
};
