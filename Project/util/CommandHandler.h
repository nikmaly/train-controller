#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "SerialHandler.h"
#include "../sensor/MotorDriver.h"
#include "../sensor/Servo.h"
#include "../sensor/RotaryEncoder.h"

// Define ServoMapping struct
struct ServoMapping {
  String name;
  ServoController* controller;
};

class CommandHandler {
  private:
    MotorDriver* trackLineA;
    MotorDriver* trackLineB;
    MotorDriver* activeTrackLine;
    ServoMapping* servoMap;
    int servoMapSize;

  public:
    CommandHandler(MotorDriver* trackLineA, MotorDriver* trackLineB, MotorDriver* activeTrackLine, ServoMapping* servoMap, int servoMapSize)
      : trackLineA(trackLineA), trackLineB(trackLineB), activeTrackLine(activeTrackLine), servoMap(servoMap), servoMapSize(servoMapSize) {}

    void handleCommand(const String& target, const String& action, const String& value) {
      if (target == "motor") {
        if (action == "stop") {
          trackLineA->setStop();
          trackLineB->setStop();
          Serial.println("Motors stopped");
        } 
        else if (action == "direction") {
          trackLineA->setDirection(value);
          trackLineB->setDirection(value);
          Serial.println("Motors direction set to " + value);
        } 
        else if (action == "speed") {
          int speedValue = value.toInt();
          trackLineA->setSpeed(speedValue);
          trackLineB->setSpeed(speedValue);
          Serial.println("Motors speed set to " + String(speedValue));
        } 
        else if (action == "change track") {
          if (value == "Track A") {
            activeTrackLine = trackLineA;
          } else if (value == "Track B") {
            activeTrackLine = trackLineB;
          } else {
            if (activeTrackLine == trackLineA) {
              activeTrackLine = trackLineB;
            } else {
              activeTrackLine = trackLineA;
            }
          }
          Serial.println("Switched active track line to " + activeTrackLine->getName());
        }
      }

      if (target == "servo") {
        String servoName = action;
        int targetAngle = value.toInt();
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
};

#endif // COMMAND_HANDLER_H
