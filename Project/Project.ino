// External Libraries
#include <Servo.h>
// Files
#include "util/CommandHandler.h"
#include "util/SerialHandler.h"
#include "sensor/RotaryEncoder.h"
#include "sensor/HallSensor.h"
#include "sensor/Servo.h"

MotorDriver trackLineA(2, 3, "Track A");
MotorDriver trackLineB(4, 5, "Track B");
// MotorDriver trackLineC(10, 11, "Track C");
// MotorDriver trackLineD(12, 13, "Track D");
ServoController servo1(9, "Servo1");
// ServoController servo2(15, "Servo2");
// ServoController servo3(16, "Servo3");
// ServoController servo4(17, "Servo4");
// ServoController servo5(18, "Servo5");
// ServoController servo6(19, "Servo6");
RotaryEncoder speedEncoder(7, 6, 5, &trackLineA, &trackLineB);
HallSensor hallSensor(13, true);
SerialHandler serialHandler;
MotorDriver* activeTrackLine = &trackLineA;

Track tracks[] = {
  {"Track A", &trackLineA},
  {"Track B", &trackLineB},
  // {"Track C", &trackLineC},
  // {"Track D", &trackLineD}
};

const int trackCount = sizeof(tracks) / sizeof(tracks[0]);

ServoMapping servoMap[] = {
  {"Servo1", &servo1},
  // {"Servo2", &servo2},
  // {"Servo3", &servo3},
  // {"Servo4", &servo4},
  // {"Servo5", &servo5},
  // {"Servo6", &servo6}
};

const int servoMapSize = sizeof(servoMap) / sizeof(servoMap[0]);

Switch switches[] = {
  {"Switch1", false, 90, 0, &servo1},
  // {"Switch2", false, 90, 0, &servo2},
  // {"Switch3", false, 90, 0, &servo3},
  // {"Switch4", false, 90, 0, &servo4},
  // {"Switch5", false, 90, 0, &servo5},
  // {"Switch6", false, 90, 0, &servo6}
};

const int switchCount = sizeof(switches) / sizeof(switches[0]);

CommandHandler commandHandler(activeTrackLine, servoMap, servoMapSize, switches, switchCount, tracks, trackCount);

/**
 * Initializes the setup.
 */
void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }
  delay(100);
  servo1.begin();
  // servo2.begin();
  // servo3.begin();
  // servo4.begin();
  // servo5.begin();
  // servo6.begin();
  Serial.println(F("---------------\nSetup complete\n---------------"));
}

/**
 * Main loop to handle commands and updates.
 */
void loop() {
  SerialCommand serialCommand = serialHandler.readCommand();
  if (serialCommand.isValid()) {
    Serial.println("Received serial command: " + serialCommand.target + " " + serialCommand.action + " " + serialCommand.value);
    commandHandler.handleCommand(serialCommand.target, serialCommand.action, serialCommand.value);
  }

  EncoderCommand encoderCommand = speedEncoder.update();
  if (encoderCommand.isValid()) {
    Serial.println("Received encoder command: " + encoderCommand.target + " " + encoderCommand.action + " " + encoderCommand.value);
    commandHandler.handleCommand(encoderCommand.target, encoderCommand.action, encoderCommand.value);
  }

  delay(1);
}
