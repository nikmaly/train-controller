#ifndef TURNOUT_H
#define TURNOUT_H

#include "../sensor/Servo.h"

class Turnout {
 private:
  String name;
  ServoController* servo;
  int truePosition;
  int falsePosition;
  bool switchState;

 public:
  Turnout(const String& name, ServoController* servo, int truePosition, int falsePosition)
      : name(name), servo(servo), truePosition(truePosition), falsePosition(falsePosition), switchState(false) {
    setSwitchState(false);
  }

  bool getSwitchState() const {
    return switchState;
  }

  void setSwitchState(bool state) {
    switchState = state;
    if (switchState) {
      servo->setAngle(truePosition);
    } else {
      servo->setAngle(falsePosition);
    }
  }

  String getName() const {
    return name;
  }
};

#endif // TURNOUT_H
