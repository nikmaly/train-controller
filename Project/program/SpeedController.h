#ifndef SPEEDCONTROLLER_H
#define SPEEDCONTROLLER_H

#include "../sensor/RotaryEncoder.h"
#include "../sensor/MotorDriver.h"

/**
 * @typedef {Object} EncoderCommand
 * @property {String} target - The target of the command (e.g., "motor").
 * @property {String} action - The action to be performed (e.g., "speed", "switch").
 * @property {String} value - The value associated with the action (e.g., speed value).
 * @property {bool} trackSwapRequested - Indicates if a track swap has been requested.
 */
struct EncoderCommand {
  String target;
  String action;
  String value;
  bool trackSwapRequested;

  bool isValid() {
    return target.length() > 0 && action.length() > 0;
  }
};

class SpeedController {
 private:
  RotaryEncoder* encoder;
  MotorDriver* activeTrackLine;
  MotorDriver* trackLineA;
  MotorDriver* trackLineB;

 public:
  SpeedController(RotaryEncoder* encoder, MotorDriver* trackLineA, MotorDriver* trackLineB)
      : encoder(encoder), trackLineA(trackLineA), trackLineB(trackLineB), activeTrackLine(trackLineA) {}

  EncoderCommand update() {
    EncoderCommand command = {"", "", "", false};

    // Map the encoder value to motor speed at a 10:1 ratio
    int speedValue = encoder->getCount() * 10;
    command.target = "motor";
    command.action = "speed";
    command.value = String(speedValue);

    // Check if button is pressed (pinSwitch)
    if (encoder->isButtonPressed()) {
      command.trackSwapRequested = true;
      command.target = "motor";
      command.action = "switch";

      delay(500);  // Debounce delay
    }

    return command;
  }

  void swapTrack() {
    if (activeTrackLine == trackLineA) {
      activeTrackLine = trackLineB;
    } else {
      activeTrackLine = trackLineA;
    }
  }

  MotorDriver* getActiveTrackLine() const {
    return activeTrackLine;
  }
};

#endif  // SPEEDCONTROLLER_H
