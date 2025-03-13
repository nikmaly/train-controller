#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "../lib/MotorDriver.h"
#include "../lib/RotaryEncoder.h"
#include "../lib/Servo.h"
#include "SerialHandler.h"

// Define ServoMapping struct
struct ServoMapping {
  String name;
  ServoController* controller;
};

// Define Switch struct
struct Switch {
  String name;
  bool status;  // true for active, false for inactive
  int activePosition;
  int inactivePosition;
  ServoController* associatedServo;
};

// Define Track struct
struct Track {
  String name;
  MotorDriver* motorDriver;
};

class CommandHandler {
 private:
  MotorDriver* activeTrackLine;
  ServoMapping* servoMap;
  int servoMapSize;
  Switch* switches;
  int switchCount;
  Track* tracks;
  int trackCount;

 public:
  /**
   * Constructor for CommandHandler.
   * @param {MotorDriver*} activeTrackLine - The active track line motor driver.
   * @param {ServoMapping*} servoMap - The map of servo controllers.
   * @param {int} servoMapSize - The size of the servo map.
   * @param {Switch*} switches - The array of switches.
   * @param {int} switchCount - The number of switches.
   * @param {Track*} tracks - The array of tracks.
   * @param {int} trackCount - The number of tracks.
   */
  CommandHandler(MotorDriver* activeTrackLine, ServoMapping* servoMap, int servoMapSize,
                 Switch* switches, int switchCount, Track* tracks, int trackCount)
      : activeTrackLine(activeTrackLine),
        servoMap(servoMap),
        servoMapSize(servoMapSize),
        switches(switches),
        switchCount(switchCount),
        tracks(tracks),
        trackCount(trackCount) {
  }

  /**
   * Handles a command.
   * @param {String} target - The target of the command.
   * @param {String} action - The action to be performed.
   * @param {String} value - The value associated with the action.
   */
  void handleCommand(const String& target, const String& action, const String& value) {
    if (target == "motor") {
      if (action == "stop") {
        for (int i = 0; i < trackCount; i++) {
          tracks[i].motorDriver->setStop();
        }

        Serial.println("Motors stopped");
      } else if (action == "direction") {
        for (int i = 0; i < trackCount; i++) {
          tracks[i].motorDriver->setDirection(value);
        }

        Serial.println("Motors direction set to " + value);
      } else if (action == "speed") {
        int speedValue = value.toInt();
        String direction = "forward";

        if (speedValue < 0) {
          direction = "backward";
          speedValue = abs(speedValue);
        }

        for (int i = 0; i < trackCount; i++) {
          tracks[i].motorDriver->setDirection(direction);
          tracks[i].motorDriver->setSpeed(speedValue);
        }

        Serial.println(
          "Motors direction set to "
          + direction
          + " and speed set to "
          + String(speedValue)
        );
      } else if (action == "change track") {
        for (int i = 0; i < trackCount; i++) {
          if (tracks[i].name == value) {
            activeTrackLine = tracks[i].motorDriver;
            Serial.println("Switched active track line to " + tracks[i].name);
            break;
          }
        }
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

    if (target == "switch") {
      for (int i = 0; i < switchCount; i++) {
        if (switches[i].name == action) {
          if (value == "activate") {
            switches[i].associatedServo->setAngle(switches[i].activePosition);
            switches[i].status = true;
            Serial.println("Activated switch " + switches[i].name);
          } else if (value == "deactivate") {
            switches[i].associatedServo->setAngle(switches[i].inactivePosition);
            switches[i].status = false;
            Serial.println("Deactivated switch " + switches[i].name);
          }

          break;
        }
      }
    }

    if (target == "track") {
      for (int i = 0; i < trackCount; i++) {
        if (tracks[i].name == action) {
          if (value == "activate") {
            activeTrackLine = tracks[i].motorDriver;
            Serial.println("Activated track " + tracks[i].name);
          }

          break;
        }
      }
    }
  }
};

#endif  // COMMAND_HANDLER_H
