# C++20 Traffic Light Controller System

A fully-structured Finite State Machine traffic light controller

## Features
- Complete state machine (RED → RED/YELLOW → GREEN → YELLOW → RED)
- Pedestrian crossing system
- Emergency vehicle override (pre-emption)
- Night mode (blink yellow)
- Mock hardware abstraction (LEDs, Sensors, Buttons)
- Timer scheduler
- Configurable timing parameters
- Logging subsystem
- Modular multi-file architecture
- Unit tests
- CMake build system

## Build & Run
```bash
mkdir build
cd build
cmake ..
make
./traffic_light
