# Project: TrainController

## Description
This project is an Arduino-based train controller system. It manages multiple components such as motors, servos, rotary encoders, and hall sensors to control and monitor a model train setup.

## Files
- **Project.ino**: Main file containing the setup and loop functions.
- **src/SerialHandler.h**: Header file for serial communication utilities.
- **src/CommandHandler.h**: Header file for command function utilities.
- **src/MotorDriver.h**: Header file for motor driver utilities.
- **src/RotaryEncoder.h**: Header file for rotary encoder utilities.
- **src/HallSensor.h**: Header file for hall sensor utilities.
- **src/Servo.h**: Header file for servo controller utilities.
- **program/Signal.h**: Header file for individual signal management.
- **program/LineManager.h**: Header file for managing a line, including blocks of Signals.
- **program/RailwayManager.h**: Header file for managing a set of LineManagers.
- **program/ScheneryLighting.h**: Header file for scenery lighting management.
- **program/SpeedController.h**: Header file for speed controller utilities.
- **program/Turnout.h**: Header file for turnout management.

## Language
- **C++**: The project is written in C++ for the Arduino platform.
- **Board**: The target board for this project is an Arduino Mega

## Usage
- **setup()**: Initializes all components.
- **loop()**: Main loop to handle commands and updates.

## Developer Information
- **Response Preferences**:
  - NEVER modify existing pin values without specifically being asked to do so. 
  - If there is no available pin, or it is not of the appropriate type, warn me
  - Responses should be succinct.
  - Responses should focus on the specific request.
  - As an addendum to responses, note any recommendations or improvements.
  - Prioritise best practice and clarity of code.
  - Ensure code is linted and formatted clearly and consistently.
  - Respect the `.clang-format` rules
  - Add documentation in the form of JSDoc
  - Do not include inline comment for self-evident functionality
  - Prefer to use a basic digital pin. Use analog and PWM only when necessary.
  - Update the ##Files section in this file as needed
