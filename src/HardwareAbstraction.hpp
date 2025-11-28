#pragma once
#include <iostream>

class LED {
public:
    void on(const std::string &color) {
        std::cout << "[LED] " << color << " ON\n";
    }
    void off(const std::string &color) {
        std::cout << "[LED] " << color << " OFF\n";
    }
};

class Buzzer {
public:
    void beep() {
        std::cout << "[BUZZER] Beep!\n";
    }
};

class Display {
public:
    void show(const std::string &msg) {
        std::cout << "[DISPLAY] " << msg << "\n";
    }
};
