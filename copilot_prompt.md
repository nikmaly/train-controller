# Project: TrainController

## Description
This project is an Arduino-based train controller system. It manages multiple components such as motors, servos, rotary encoders, and hall sensors to control and monitor a model train setup.

## Components
- **MotorDriver**: Controls the speed and direction of the train tracks.
- **ServoController**: Manages the position of servos.
- **RotaryEncoder**: Reads the position and speed of the train.
- **HallSensor**: Detects the presence of the train.
- **SerialHandler**: Handles serial communication for receiving commands.

## Files
- **TrainController.ino**: Main file containing the setup and loop functions.
- **util_MotorDriver.h**: Header file for motor driver utilities.
- **util_Serial.h**: Header file for serial communication utilities.
- **util_RotaryEncoder.h**: Header file for rotary encoder utilities.
- **util_HallSensor.h**: Header file for hall sensor utilities.
- **sensors/sensor_Servo.h**: Header file for servo controller utilities.

## Language
- **C++**: The project is written in C++ for the Arduino platform.

## Usage
- **setup()**: Initializes all components.
- **loop()**: Main loop to handle commands and updates.

## Developer Information
- **Experience**: Experienced developer, but only occasionally works on Arduino projects.
- **Response Preferences**:
  - Responses should be succinct.
  - Responses should focus on the specific request.
  - As an addendum to responses, note any recommendations or improvements.
  - Prioritise best practice and clarity of code.
  - Ensure code is linted and formatted clearly and consistently.
  - Respect the `.clang-format` rules

