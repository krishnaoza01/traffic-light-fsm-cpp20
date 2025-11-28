#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

class Logger {
public:
    enum class Level { INFO, WARN, ERROR };

    static void log(Level lvl, const std::string &msg) {
        const char *lvlStr =
            (lvl == Level::INFO) ? "INFO" :
            (lvl == Level::WARN) ? "WARN" : "ERROR";

        auto now = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now()
        );

        std::cout << "[" << lvlStr << "] "
                  << std::ctime(&now)
                  << " > " << msg << "\n";
    }
};
