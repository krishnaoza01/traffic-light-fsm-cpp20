cmake_minimum_required(VERSION 3.16)
project(TrafficLightFSM CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

add_executable(traffic_light
    src/main.cpp
    src/TrafficLightController.cpp
    src/Timer.cpp
    src/Logger.cpp
    src/PedestrianButton.cpp
    src/EmergencySensor.cpp
)

enable_testing()
add_executable(test_fsm tests/test_fsm.cpp)
