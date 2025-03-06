// External Libraries
#include <Servo.h>
// Files
#include "util_MotorDriver.h"
#include "util_Serial.h"
#include "util_RotaryEncoder.h"
#include "util_HallSensor.h"
#include "sensors/sensor_Servo.h"

MotorDriver trackLineA(2, 3, "Track A");
MotorDriver trackLineB(4, 5, "Track B");
RotaryEncoder speedEncoder(7, 6, 5, &trackLineA, &trackLineB);
HallSensor hallSensor(8, true);
SerialHandler serialHandler;
MotorDriver* activeTrackLine = &trackLineA;

ServoController servo1(9, "Servo1");
ServoController servo2(10, "Servo2");

struct ServoMapping {
  String name;
  ServoController* controller;
};

ServoMapping servoMap[] = {
  {"Servo1", &servo1},
  {"Servo2", &servo2}
};

const int servoMapSize = sizeof(servoMap) / sizeof(servoMap[0]);

/**
 * Initializes the setup.
 */
void setup() {
  Serial.begin(115200); // Ensure serial communication is initialized
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }
  delay(100); // Add a delay to ensure serial communication is ready
  servo1.begin();
  servo2.begin();
  Serial.println(F("---------------\nSetup complete\n---------------"));
}

/**
 * Main loop to handle commands and updates.
 */
void loop() {
  SerialCommand serialCommand = serialHandler.readCommand();
  if (serialCommand.isValid()) {
    Serial.println("Received serial command: " + serialCommand.target + " " + serialCommand.action + " " + serialCommand.value);

    if (serialCommand.target == "motor") {
      if (serialCommand.action == "stop") {
        trackLineA.setStop();
        trackLineB.setStop();
        Serial.println("Motors stopped");
      } 
      else if (serialCommand.action == "direction") {
        trackLineA.setDirection(serialCommand.value);
        trackLineB.setDirection(serialCommand.value);
        Serial.println("Motors direction set to " + serialCommand.value);
      } 
      else if (serialCommand.action == "speed") {
        int speedValue = serialCommand.value.toInt();
        trackLineA.setSpeed(speedValue);
        trackLineB.setSpeed(speedValue);
        Serial.println("Motors speed set to " + String(speedValue));
      } 
      else if (serialCommand.action == "change track") {
        if (serialCommand.value == "Track A") {
          activeTrackLine = &trackLineA;
        } else if (serialCommand.value == "Track B") {
          activeTrackLine = &trackLineB;
        } else {
          if (activeTrackLine == &trackLineA) {
            activeTrackLine = &trackLineB;
          } else {
            activeTrackLine = &trackLineA;
          }
        }
        Serial.println("Switched active track line to " + activeTrackLine->getName());
      }
    }

    if (serialCommand.target == "servo") {
      String servoName = serialCommand.action;
      int targetAngle = serialCommand.value.toInt();
      bool servoFound = false;
      for (int i = 0; i < servoMapSize; i++) {
        if (servoMap[i].name == servoName) {
          servoMap[i].controller->setAngle(targetAngle);
          servoFound = true;
          Serial.println("Set " + servoName + " to angle " + String(targetAngle));
          break;
        }
      }
      if (!servoFound) {
        Serial.println("Servo " + servoName + " not found");
      }
    }
  }

  EncoderCommand encoderCommand = speedEncoder.update();
  if (encoderCommand.isValid()) {
    Serial.println("Received encoder command: " + encoderCommand.target + " " + encoderCommand.action + " " + encoderCommand.value);

    if (encoderCommand.target == "motor") {
      if (encoderCommand.action == "speed") {
        int speedValue = encoderCommand.value.toInt();
        if (speedValue > 0) {
          activeTrackLine->setDirection("forward");
        } else {
          activeTrackLine->setDirection("backward");
        }
        activeTrackLine->setSpeed(abs(speedValue));
        Serial.println("Encoder speed set to " + String(speedValue));
      } else if (encoderCommand.action == "switch") {
        if (activeTrackLine == &trackLineA) {
          activeTrackLine = &trackLineB;
        } else {
          activeTrackLine = &trackLineA;
        }
        Serial.println("Switched active track line to " + activeTrackLine->getName());
      }
    }
  }

  delay(1);
}
