#include "TrafficLightController.hpp"
#include "Timer.hpp"

TrafficLightController::TrafficLightController(
    LED &ledRed, LED &ledYellow, LED &ledGreen,
    PedestrianButton &btn,
    EmergencySensor &emergencySensor,
    NightMode &nightMode)
    : red(ledRed), yellow(ledYellow), green(ledGreen),
      button(btn), emergencySensor(emergencySensor),
      nightMode(nightMode)
{
}

void TrafficLightController::setup() {
    fsm.addState(State::RED,
        std::bind(&TrafficLightController::enterRed, this),
        std::bind(&TrafficLightController::exitState, this, "RED")
    );

    fsm.addState(State::RED_YELLOW,
        std::bind(&TrafficLightController::enterRedYellow, this),
        std::bind(&TrafficLightController::exitState, this, "RED_YELLOW")
    );

    fsm.addState(State::GREEN,
        std::bind(&TrafficLightController::enterGreen, this),
        std::bind(&TrafficLightController::exitState, this, "GREEN")
    );

    fsm.addState(State::YELLOW,
        std::bind(&TrafficLightController::enterYellow, this),
        std::bind(&TrafficLightController::exitState, this, "YELLOW")
    );

    fsm.addState(State::PEDESTRIAN,
        std::bind(&TrafficLightController::enterPedestrian, this),
        std::bind(&TrafficLightController::exitState, this, "PEDESTRIAN")
    );

    fsm.addState(State::EMERGENCY,
        std::bind(&TrafficLightController::enterEmergency, this),
        std::bind(&TrafficLightController::exitState, this, "EMERGENCY")
    );

    fsm.addState(State::NIGHT,
        std::bind(&TrafficLightController::enterNight, this),
        std::bind(&TrafficLightController::exitState, this, "NIGHT")
    );

    fsm.addTransition(State::RED, State::RED_YELLOW);
    fsm.addTransition(State::RED_YELLOW, State::GREEN);
    fsm.addTransition(State::GREEN, State::YELLOW);
    fsm.addTransition(State::YELLOW, State::RED);

    fsm.addTransition(State::RED, State::PEDESTRIAN);
    fsm.addTransition(State::GREEN, State::PEDESTRIAN);
    fsm.addTransition(State::YELLOW, State::PEDESTRIAN);

    fsm.addTransition(State::RED, State::EMERGENCY);
    fsm.addTransition(State::GREEN, State::EMERGENCY);

    fsm.addTransition(State::RED, State::NIGHT);

    fsm.setInitial(State::RED);
}

void TrafficLightController::exitState(const std::string &state) {
    Logger::log(Logger::Level::INFO, "Leaving state: " + state);
    red.off("RED");
    yellow.off("YELLOW");
    green.off("GREEN");
}

void TrafficLightController::enterRed() {
    Logger::log(Logger::Level::INFO, "Entering RED");
    nightMode.disable();
    red.on("RED");
    Timer::delayMs(Config::RED_TIME);
}

void TrafficLightController::enterRedYellow() {
    Logger::log(Logger::Level::INFO, "Entering RED_YELLOW");
    red.on("RED");
    yellow.on("YELLOW");
    Timer::delayMs(Config::RED_YELLOW_TIME);
}

void TrafficLightController::enterGreen() {
    Logger::log(Logger::Level::INFO, "Entering GREEN");
    green.on("GREEN");
    Timer::delayMs(Config::GREEN_TIME);
}

void TrafficLightController::enterYellow() {
    Logger::log(Logger::Level::INFO, "Entering YELLOW");
    yellow.on("YELLOW");
    Timer::delayMs(Config::YELLOW_TIME);
}

void TrafficLightController::enterPedestrian() {
    Logger::log(Logger::Level::INFO, "Entering PEDESTRIAN");
    red.on("RED");
    Timer::delayMs(Config::PEDESTRIAN_TIME);
}

void TrafficLightController::enterEmergency() {
    Logger::log(Logger::Level::WARN, "EMERGENCY OVERRIDE!");
    red.on("RED");
    buzzer.beep();
    Timer::delayMs(Config::EMERGENCY_DURATION);
}

void TrafficLightController::enterNight() {
    Logger::log(Logger::Level::INFO, "Night mode enabled");
    nightMode.enable();
    for (int i = 0; i < 10; i++) {
        nightMode.run();
    }
    nightMode.disable();
}

void TrafficLightController::runCycle() {
    if (emergencySensor.isEmergency()) {
        fsm.transition(State::EMERGENCY);
        return;
    }

    if (button.isPressed()) {
        fsm.transition(State::PEDESTRIAN);
        return;
    }

    // Night mode after midnight simulation
    static int cycles = 0;
    cycles++;
    if (cycles == 5) {
        fsm.transition(State::NIGHT);
        cycles = 0;
        return;
    }

    // Normal cycle
    State current = fsm.getState();
    switch (current) {
    case State::RED:
        fsm.transition(State::RED_YELLOW);
        break;
    case State::RED_YELLOW:
        fsm.transition(State::GREEN);
        break;
    case State::GREEN:
        fsm.transition(State::YELLOW);
        break;
    case State::YELLOW:
        fsm.transition(State::RED);
        break;
    default:
        fsm.transition(State::RED);
        break;
    }
}
