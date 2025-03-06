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
RotaryEncoder speedEncoder(7, 6, 5, &trackLineA, &trackLineB);
HallSensor hallSensor(8, true);
SerialHandler serialHandler;
MotorDriver* activeTrackLine = &trackLineA;

ServoController servo1(9, "Servo1");
ServoController servo2(10, "Servo2");

ServoMapping servoMap[] = {
  {"Servo1", &servo1},
  {"Servo2", &servo2}
};

const int servoMapSize = sizeof(servoMap) / sizeof(servoMap[0]);

CommandHandler commandHandler(&trackLineA, &trackLineB, activeTrackLine, servoMap, servoMapSize);

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
    commandHandler.handleCommand(serialCommand.target, serialCommand.action, serialCommand.value);
  }

  EncoderCommand encoderCommand = speedEncoder.update();
  if (encoderCommand.isValid()) {
    Serial.println("Received encoder command: " + encoderCommand.target + " " + encoderCommand.action + " " + encoderCommand.value);
    commandHandler.handleCommand(encoderCommand.target, encoderCommand.action, encoderCommand.value);
  }

  delay(1);
}
