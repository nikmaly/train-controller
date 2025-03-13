#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

class RotaryEncoder {
 private:
  int pinCLK;
  int pinDT;
  int pinSwitch;
  volatile int count = 0;
  boolean bool_CW;

  static RotaryEncoder* instance;

  static void handleInterruptCLK() {
    if (instance) {
      instance->updateCount();
    }
  }

  void updateCount() {
    if (digitalRead(pinDT) != digitalRead(pinCLK)) {
      count++;
      bool_CW = true;
    } else {
      count--;
      bool_CW = false;
    }
    count = constrain(count, -10, 10);
  }

 public:
  /**
   * Constructor for RotaryEncoder.
   * @param {int} pinCLK - The pin for the CLK signal.
   * @param {int} pinDT - The pin for the DT signal.
   * @param {int} pinSwitch - The pin for the switch.
   */
  RotaryEncoder(int pinCLK, int pinDT, int pinSwitch)
      : pinCLK(pinCLK), pinDT(pinDT), pinSwitch(pinSwitch) {
    pinMode(pinCLK, INPUT);
    pinMode(pinDT, INPUT);
    pinMode(pinSwitch, INPUT_PULLUP);
    instance = this;
    attachInterrupt(digitalPinToInterrupt(pinCLK), handleInterruptCLK, CHANGE);
  }

  /**
   * Gets the current count.
   * @returns {int} The current count.
   */
  int getCount() const {
    return count;
  }

  /**
   * Checks if the button is pressed.
   * @returns {bool} True if the button is pressed, false otherwise.
   */
  bool isButtonPressed() const {
    return digitalRead(pinSwitch) == LOW;
  }
};

// Define the static instance pointer
RotaryEncoder* RotaryEncoder::instance = nullptr;

#endif  // ROTARYENCODER_H