#pragma once
#include <string>
#include <functional>
#include "StateMachine.hpp"
#include "HardwareAbstraction.hpp"
#include "PedestrianButton.hpp"
#include "EmergencySensor.hpp"
#include "NightMode.hpp"
#include "Config.hpp"
#include "Logger.hpp"

class TrafficLightController {
public:
    enum class State {
        RED,
        RED_YELLOW,
        GREEN,
        YELLOW,
        PEDESTRIAN,
        EMERGENCY,
        NIGHT
    };

    TrafficLightController(LED &ledRed, LED &ledYellow, LED &ledGreen,
                           PedestrianButton &btn,
                           EmergencySensor &emergencySensor,
                           NightMode &nightMode);

    void setup();
    void runCycle();

private:
    LED &red;
    LED &yellow;
    LED &green;
    PedestrianButton &button;
    EmergencySensor &emergencySensor;
    NightMode &nightMode;
    StateMachine<State> fsm;

    void enterRed();
    void enterRedYellow();
    void enterGreen();
    void enterYellow();
    void enterPedestrian();
    void enterEmergency();
    void enterNight();

    void exitState(const std::string &);
};
