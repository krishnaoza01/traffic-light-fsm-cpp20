#include <iostream>
#include "TrafficLightController.hpp"
#include "HardwareAbstraction.hpp"
#include "PedestrianButton.hpp"
#include "EmergencySensor.hpp"
#include "NightMode.hpp"
#include "Timer.hpp"

int main() {
    LED redLED, yellowLED, greenLED;
    PedestrianButton pedestrianButton;
    EmergencySensor emergencySensor;
    NightMode nightMode(yellowLED);

    TrafficLightController controller(
        redLED, yellowLED, greenLED,
        pedestrianButton,
        emergencySensor,
        nightMode
    );

    controller.setup();

    std::cout << "Traffic Light FSM Started.\n";
    std::cout << "======================================\n";
    std::cout << "Press ENTER anytime to simulate pedestrian button.\n";
    std::cout << "Type 'e' + ENTER to simulate emergency vehicle.\n";
    std::cout << "======================================\n";

    std::thread inputThread([&]() {
        while (true) {
            std::string user;
            std::getline(std::cin, user);

            if (user == "e") {
                std::cout << "[USER] Emergency triggered!\n";
                emergencySensor.trigger();
            } else {
                std::cout << "[USER] Pedestrian button pressed!\n";
                pedestrianButton.press();
            }
        }
    });

    inputThread.detach();

    while (true) {
        controller.runCycle();
    }

    return 0;
}
