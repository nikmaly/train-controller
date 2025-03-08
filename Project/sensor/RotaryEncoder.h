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
  RotaryEncoder(int pinCLK, int pinDT, int pinSwitch)
      : pinCLK(pinCLK), pinDT(pinDT), pinSwitch(pinSwitch) {
    pinMode(pinCLK, INPUT);
    pinMode(pinDT, INPUT);
    pinMode(pinSwitch, INPUT_PULLUP);
    instance = this;
    attachInterrupt(digitalPinToInterrupt(pinCLK), handleInterruptCLK, CHANGE);
  }

  int getCount() const {
    return count;
  }

  bool isButtonPressed() const {
    return digitalRead(pinSwitch) == LOW;
  }
};

RotaryEncoder* RotaryEncoder::instance = nullptr;

#endif  // ROTARYENCODER_H