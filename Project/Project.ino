
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <gfxfont.h>

// External Libraries
#include <Servo.h>
#include <SPI.h>
#include <Adafruit_FRAM_SPI.h>
#include <Adafruit_ST7789.h>

// Files
#include "lib/RotaryEncoder.h"
#include "lib/HallSensor.h"
#include "lib/Servo.h"
#include "lib/Button.h"
#include "lib/Screen.h"
#include "src/CommandHandler.h"
#include "src/SerialHandler.h"
#include "src/SceneryLighting.h"
#include "src/Signal.h"
#include "src/LineManager.h"
#include "src/RailwayManager.h"
#include "src/Turnout.h"
#include "src/SpeedController.h"

// Analog Pins (A0-A15)
#define HALL_SENSOR_A_A0          A0   // Analog: Hall effect sensor A
#define HALL_SENSOR_B_A1          A1   // Analog: Hall effect sensor B
#define HALL_SENSOR_C_A2          A2   // Analog: Hall effect sensor C
#define HALL_SENSOR_D_A3          A3   // Analog: Hall effect sensor D
#define HALL_SENSOR_E_A4          A4   // Analog: Hall effect sensor E
#define HALL_SENSOR_F_A5          A5   // Analog: Hall effect sensor F
#define UNUSUSED_ANALOG_A6        A6   // Analog: Unused pin
#define UNUSUSED_ANALOG_A7        A7   // Analog: Unused pin
#define UNUSUSED_ANALOG_A8        A8   // Analog: Unused pin
#define UNUSUSED_ANALOG_A9        A9   // Analog: Unused pin
#define UNUSUSED_ANALOG_A10       A10  // Analog: Unused pin
#define UNUSUSED_ANALOG_A11       A11  // Analog: Unused pin
#define UNUSUSED_ANALOG_A12       A12  // Analog: Unused pin
#define UNUSUSED_ANALOG_A13       A13  // Analog: Unused pin
#define UNUSUSED_ANALOG_A14       A14  // Analog: Unused pin
#define UNUSUSED_ANALOG_A15       A15  // Analog: Unused pin

// Hardware Serial USB Communication Pins
#define SERIAL_RX_USB_PIN         0    // Serial Input: RX USB
#define SERIAL_TX_USB_PIN         1    // Serial Output: TX0 USB

// Digital PWM Pins
#define TRACK_A_PIN1              2    // Digital PWM: Track A Motor Driver Pin 1
#define TRACK_A_PIN2              3    // Digital PWM: Track A Motor Driver Pin 2
#define TRACK_B_PIN1              4    // Digital PWM: Track B Motor Driver Pin 1
#define TRACK_B_PIN2              5    // Digital PWM: Track B Motor Driver Pin 2
#define SERVO_A_6                 6    // Digital PWM: Servo1 (Turnout1) control pin
#define SERVO_B_7                 7    // Digital PWM: Servo2 (Turnout2) control pin
#define TFT_DC_8                  8    // Digital PWM: 
#define TFT_RST_9                 9    // Digital PWM: 
#define TFT_CS_10                 10   // Digital PWM: 
#define TFT_MOSI_11               11   // Digital PWM: 
#define UNUSED_PWM_12             12   // Digital PWM: Unused pin
#define TFT_SCLK_13               13   // Digital PWM: 

// Hardware Serial Communication Pins
#define SERIAL3_TX_PIN            14  // Serial Output: TX3
#define SERIAL3_RX_PIN            15  // Serial Input: RX3
#define SERIAL2_TX_PIN            16  // Serial Output: TX2
#define SERIAL2_RX_PIN            17  // Serial Input: RX2

// Digital Pins
#define SPEED_ENCODER_A_PIN_A_18  18 // Digital Input: Speed Encoder A pin A (Interrupt capable)
#define SPEED_ENCODER_A_PIN_B_19  19 // Digital Input: Speed Encoder A pin B (Interrupt capable)
#define SPEED_ENCODER_B_PIN_A_20  20 // Digital Input: Speed Encoder B pin A (Interrupt capable)
#define SPEED_ENCODER_B_PIN_B_21  21 // Digital Input: Speed Encoder B pin B (Interrupt capable)
#define SPEED_ENCODER_A_SWITCH_22 22 // Digital Input: Speed Encoder A Switch
#define SPEED_ENCODER_B_SWITCH_23 23 // Digital Input: Speed Encoder B Switch
#define UNUSED_DIGITAL_24         24 // Digital Input: Unused pin
#define UNUSED_DIGITAL_25         25 // Digital Input: Unused pin
#define UNUSED_DIGITAL_26         26  // Digital Input: Unused pin
#define UNUSED_DIGITAL_27         27  // Digital Input: Unused pin
#define UNUSED_DIGITAL_28         28  // Digital Input: Unused pin
#define UNUSED_DIGITAL_29         29  // Digital Input: Unused pin
#define SIGNAL_1_GREEN_PIN_30     30  // Digital Input: Signal 1 Green LED
#define SIGNAL_1_RED_PIN_31       31  // Digital Input: Signal 1 Red LED
#define SIGNAL_2_GREEN_PIN_32     32  // Digital Input: Signal 2 Green LED
#define SIGNAL_2_RED_PIN_33       33  // Digital Input: Signal 2 Red LED
#define SIGNAL_3_GREEN_PIN_34     34  // Digital Input: Signal 3 Green LED
#define SIGNAL_3_RED_PIN_35       35  // Digital Input: Signal 3 Red LED
#define SIGNAL_4_GREEN_PIN_36     36  // Digital Input: Signal 4 Green LED
#define SIGNAL_4_RED_PIN_37       37  // Digital Input: Signal 4 Red LED
#define SIGNAL_5_GREEN_PIN_38     38  // Digital Input: Signal 5 Green LED
#define SIGNAL_5_RED_PIN_39       39  // Digital Input: Signal 5 Red LED
#define SIGNAL_6_GREEN_PIN_40     40  // Digital Input: Signal 6 Green LED
#define SIGNAL_6_RED_PIN_41       41  // Digital Input: Signal 6 Red LED
#define UNUSED_DIGITAL_42         42  // Digital Input: Unused pin
#define UNUSED_DIGITAL_43         43  // Digital Input: Unused pin
#define UNUSED_DIGITAL_44         44  // Digital Input: Unused pin
#define LIGHTING_FACTORY_A_45     45  // Digital Input: Lighting Factory A
#define LIGHTING_HOUSE_A_46       46  // Digital Input: Lighting House A
#define LIGHTING_HOUSE_B_47       47  // Digital Input: Lighting House B
#define LIGHTING_ROAD_A_48        48  // Digital Input: Lighting Road A
#define UNUSED_DIGITAL_49         49  // Digital Input: Unused pin

// Other
#define SPI_MISO_PIN_50           50  // SPI Input: MISO
#define SPI_MOSI_PIN_51           51  // SPI Output: MOSI
#define SPI_SCK_PIN_52            52  // SPI Output: SCK
#define SPI_SS_PIN_53             53  // SPI Output: SS

MotorDriver trackLineA(TRACK_A_PIN1, TRACK_A_PIN2, "Track A");
MotorDriver trackLineB(TRACK_B_PIN1, TRACK_B_PIN2, "Track B");
ServoController servo1(SERVO_A_6, "Servo1");
ServoController servo2(SERVO_B_7, "Servo2");
SerialHandler serialHandler;
MotorDriver* activeTrackLine = &trackLineA;
RotaryEncoder speedEncoder(SPEED_ENCODER_A_PIN_A_18, SPEED_ENCODER_A_PIN_B_19, SPEED_ENCODER_A_SWITCH_22);
RotaryEncoder speedEncoderB(SPEED_ENCODER_B_PIN_A_20, SPEED_ENCODER_B_PIN_B_21, SPEED_ENCODER_B_SWITCH_23);
SpeedController speedController(&speedEncoder, &trackLineA, &trackLineB);
Screen screen(TFT_CS_10, TFT_DC_8, TFT_RST_9);

Track tracks[] = {
  {"Track A", &trackLineA},
  {"Track B", &trackLineB},
};

const int trackCount = sizeof(tracks) / sizeof(tracks[0]);

ServoMapping servoMap[] = {
  {"Servo1", &servo1},
  {"Servo2", &servo2}
};

const int servoMapSize = sizeof(servoMap) / sizeof(servoMap[0]);

Switch switches[] = {
  {"Switch1", false, 90, 0, &servo1},
  {"Switch2", false, 90, 0, &servo2}
};

const int switchCount = sizeof(switches) / sizeof(switches[0]);

CommandHandler commandHandler(activeTrackLine, servoMap, servoMapSize, switches, switchCount, tracks, trackCount);

// Create Signal objects for OuterLine
Signal lineASignals[] = {
  Signal("Signal1", HALL_SENSOR_A_A0, SIGNAL_1_GREEN_PIN_30, SIGNAL_1_RED_PIN_31),
  Signal("Signal2", HALL_SENSOR_B_A1, SIGNAL_2_GREEN_PIN_32, SIGNAL_1_RED_PIN_31),
  Signal("Signal3", HALL_SENSOR_C_A2, SIGNAL_3_GREEN_PIN_34, SIGNAL_1_RED_PIN_31)
};

// Create Signal objects for InnerLine
Signal lineBSignals[] = {
  Signal("Signal4", HALL_SENSOR_D_A3, SIGNAL_4_GREEN_PIN_36, SIGNAL_4_RED_PIN_37),
  Signal("Signal5", HALL_SENSOR_E_A4, SIGNAL_5_GREEN_PIN_38, SIGNAL_5_RED_PIN_39),
  Signal("Signal6", HALL_SENSOR_F_A5, SIGNAL_6_GREEN_PIN_40, SIGNAL_6_RED_PIN_41)
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
const int lightingPins1[] = {LIGHTING_FACTORY_A_45, LIGHTING_HOUSE_A_46, LIGHTING_HOUSE_B_47, LIGHTING_ROAD_A_48};
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
  screen.begin();
  // screen.testDisplay();
  Serial.println(F("---------------\nSetup complete\n---------------"));
}

/**
 * Main loop to handle commands and updates.
 */
void loop() {
  // Update the railway manager
  // railwayManager.update();

  // // Read the serial input
  // SerialCommand serialCommand = serialHandler.readCommand();
  // if (serialCommand.isValid()) {
  //   Serial.println("Received serial command: " + serialCommand.target + " " + serialCommand.action + " " + serialCommand.value);
  //   commandHandler.handleCommand(serialCommand.target, serialCommand.action, serialCommand.value);
  // }

  // // Read the speed controller
  // EncoderCommand encoderCommand = speedController.update();
  // if (encoderCommand.isValid()) {
  //   Serial.println("Received encoder command: " + encoderCommand.target + " " + encoderCommand.action + " " + encoderCommand.value);
  //   commandHandler.handleCommand(encoderCommand.target, encoderCommand.action, encoderCommand.value);
  // }

  // // Handle track swap request
  // if (encoderCommand.trackSwapRequested) {
  //   speedController.swapTrack();
  //   activeTrackLine = speedController.getActiveTrackLine();
  //   Serial.println("Track swap requested. Active track line switched.");
  // }

  delay(1);
}
