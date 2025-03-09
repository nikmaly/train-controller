// External Libraries
#include <Servo.h>
// Files
#include "util/CommandHandler.h"
#include "util/SerialHandler.h"
#include "sensor/RotaryEncoder.h"
#include "sensor/HallSensor.h"
#include "sensor/Servo.h"
#include "program/Signal.h"
#include "program/LineManager.h"
#include "program/RailwayManager.h"
#include "program/Turnout.h"
#include "program/SpeedController.h"
#include "program/SceneryLighting.h"

MotorDriver trackLineA(2, 3, "Track A");
MotorDriver trackLineB(4, 5, "Track B");
// MotorDriver trackLineC(10, 11, "Track C");
ServoController servo1(9, "Servo1");
// ServoController servo2(15, "Servo2");
RotaryEncoder speedEncoder(7, 6, 5);
SpeedController speedController(&speedEncoder, &trackLineA, &trackLineB);
HallSensor hallSensor(13, true);
SerialHandler serialHandler;
MotorDriver* activeTrackLine = &trackLineA;

Track tracks[] = {
  {"Track A", &trackLineA},
  {"Track B", &trackLineB},
  // {"Track C", &trackLineC},
};

const int trackCount = sizeof(tracks) / sizeof(tracks[0]);

ServoMapping servoMap[] = {
  {"Servo1", &servo1},
  // {"Servo2", &servo2}
};

const int servoMapSize = sizeof(servoMap) / sizeof(servoMap[0]);

Switch switches[] = {
  {"Switch1", false, 90, 0, &servo1},
  // {"Switch2", false, 90, 0, &servo2}
};

const int switchCount = sizeof(switches) / sizeof(switches[0]);

CommandHandler commandHandler(activeTrackLine, servoMap, servoMapSize, switches, switchCount, tracks, trackCount);

// Create Signal objects for OuterLine
Signal lineASignals[] = {
  Signal("Signal1", 22, 28, 34),
  Signal("Signal2", 23, 29, 35),
  Signal("Signal3", 24, 30, 36)
};

// Create Signal objects for InnerLine
Signal lineBSignals[] = {
  Signal("Signal4", 25, 31, 37),
  Signal("Signal5", 26, 32, 38),
  Signal("Signal6", 27, 33, 39)
};

// Create Turnout objects for OuterLine
Turnout lineATurnouts[] = {
  Turnout("Turnout1", &servo1, 90, 0)
};

// Create Turnout objects for InnerLine
Turnout lineBTurnouts[] = {
  Turnout("Turnout2", &servo1, 90, 0)
};

// Create LineManager objects
LineManager lineManagers[] = {
  LineManager("OuterLine", lineASignals, sizeof(lineASignals) / sizeof(lineASignals[0]), lineATurnouts, sizeof(lineATurnouts) / sizeof(lineATurnouts[0])),
  LineManager("InnerLine", lineBSignals, sizeof(lineBSignals) / sizeof(lineBSignals[0]), lineBTurnouts, sizeof(lineBTurnouts) / sizeof(lineBTurnouts[0]))
};

const int lineManagerCount = sizeof(lineManagers) / sizeof(lineManagers[0]);

// Create RailwayManager object
RailwayManager railwayManager(lineManagers, lineManagerCount);

// Define lighting items
const int lightingPins1[] = {40, 41, 42};
SceneryLighting lighting1("Lighting1", lightingPins1, sizeof(lightingPins1) / sizeof(lightingPins1[0]));

SceneryLighting sceneries[] = {
  lighting1
};

const int sceneryCount = sizeof(sceneries) / sizeof(sceneries[0]);

/**
 * Initializes the setup.
 */
void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
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
  // Update the railway manager
  railwayManager.update();

  // Read the serial input
  SerialCommand serialCommand = serialHandler.readCommand();
  if (serialCommand.isValid()) {
    Serial.println("Received serial command: " + serialCommand.target + " " + serialCommand.action + " " + serialCommand.value);
    commandHandler.handleCommand(serialCommand.target, serialCommand.action, serialCommand.value);
  }

  // Read the speed controller
  EncoderCommand encoderCommand = speedController.update();
  if (encoderCommand.isValid()) {
    Serial.println("Received encoder command: " + encoderCommand.target + " " + encoderCommand.action + " " + encoderCommand.value);
    commandHandler.handleCommand(encoderCommand.target, encoderCommand.action, encoderCommand.value);
  }

  // Handle track swap request
  if (encoderCommand.trackSwapRequested) {
    speedController.swapTrack();
    activeTrackLine = speedController.getActiveTrackLine();
    Serial.println("Track swap requested. Active track line switched.");
  }

  delay(1);
}
