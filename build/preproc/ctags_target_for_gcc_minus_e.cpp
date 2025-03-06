# 1 "/Users/nik/_dev/2-arduino/TrainController/TrainController.ino"
// External Libraries
# 3 "/Users/nik/_dev/2-arduino/TrainController/TrainController.ino" 2
// Files
# 5 "/Users/nik/_dev/2-arduino/TrainController/TrainController.ino" 2
# 6 "/Users/nik/_dev/2-arduino/TrainController/TrainController.ino" 2
# 7 "/Users/nik/_dev/2-arduino/TrainController/TrainController.ino" 2
# 8 "/Users/nik/_dev/2-arduino/TrainController/TrainController.ino" 2
# 9 "/Users/nik/_dev/2-arduino/TrainController/TrainController.ino" 2

MotorDriver trackLineA(2, 3, "Track A");
MotorDriver trackLineB(4, 5, "Track B", true, 6);
RotaryEncoder encoder(7, 6, 5, &trackLineA, &trackLineB);
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
  Serial.begin(115200);
  trackLineA.begin();
  trackLineB.begin();
  encoder.begin();
  serialHandler.begin();
  servo1.begin();
  servo2.begin();
  Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 43 "/Users/nik/_dev/2-arduino/TrainController/TrainController.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 43 "/Users/nik/_dev/2-arduino/TrainController/TrainController.ino"
                "---------------\nSetup complete\n---------------"
# 43 "/Users/nik/_dev/2-arduino/TrainController/TrainController.ino" 3
                ); &__c[0];}))
# 43 "/Users/nik/_dev/2-arduino/TrainController/TrainController.ino"
                )));
}

/**
 * Main loop to handle commands and updates.
 */
void loop() {
  SerialCommand serialCommand = serialHandler.readCommand();

  if (serialCommand.target == "motor") {
    if (serialCommand.action == "stop") {
      trackLineA.setStop();
      trackLineB.setStop();
    }
    else if (serialCommand.action == "direction") {
      trackLineA.setDirection(serialCommand.value);
      trackLineB.setDirection(serialCommand.value);
    }
    else if (serialCommand.action == "speed") {
      int speedValue = serialCommand.value.toInt();
      trackLineA.setSpeed(speedValue);
      trackLineB.setSpeed(speedValue);
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
        break;
      }
    }
    if (!servoFound) {
      Serial.println("Servo " + servoName + " not found");
    }
  }

  EncoderCommand encoderCommand = encoder.update();
  if (encoderCommand.target == "motor") {
    if (encoderCommand.action == "speed") {
      int speedValue = encoderCommand.value.toInt();
      if (speedValue > 0) {
        activeTrackLine->setDirection("forward");
      } else {
        activeTrackLine->setDirection("backward");
      }
      activeTrackLine->setSpeed(((speedValue)>0?(speedValue):-(speedValue)));
    } else if (encoderCommand.action == "switch") {
      if (activeTrackLine == &trackLineA) {
        activeTrackLine = &trackLineB;
      } else {
        activeTrackLine = &trackLineA;
      }
      Serial.println("Switched active track line to " + activeTrackLine->getName());
    }
  }

  delay(1);
}
