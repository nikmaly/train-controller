#ifndef TURNOUT_H
#define TURNOUT_H

#include "../src/Servo.h"

class Turnout {
 private:
  String name;
  ServoController* servo;
  int truePosition;
  int falsePosition;
  bool switchState;

 public:
  /**
   * Constructor for Turnout.
   * @param {String} name - The name of the turnout.
   * @param {ServoController*} servo - The associated servo controller.
   * @param {int} truePosition - The position for the true state.
   * @param {int} falsePosition - The position for the false state.
   */
  Turnout(const String& name, ServoController* servo, int truePosition, int falsePosition)
      : name(name), servo(servo), truePosition(truePosition), falsePosition(falsePosition), switchState(false) {
    setSwitchState(false);
  }

  /**
   * Gets the current switch state.
   * @returns {bool} The current switch state.
   */
  bool getSwitchState() const {
    return switchState;
  }

  /**
   * Sets the switch state.
   * @param {bool} state - The new switch state.
   */
  void setSwitchState(bool state) {
    switchState = state;
    if (switchState) {
      servo->setAngle(truePosition);
    } else {
      servo->setAngle(falsePosition);
    }
  }

  /**
   * Gets the name of the turnout.
   * @returns {String} The name of the turnout.
   */
  String getName() const {
    return name;
  }
};

#endif // TURNOUT_H
