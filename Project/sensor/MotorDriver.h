#ifndef UTIL_MOTORDRIVER_H
#define UTIL_MOTORDRIVER_H

/*
 * Motor class for controlling a motor with PWM and direction pins.
 * Supports setting speed, direction, and stopping.
 * Can be configured to use either a single direction pin or a dual-direction pin setup.
 */
class MotorDriver {
 private:
  int outPwm;               // PWM output pin
  int outDirection1;        // First direction control pin
  int outDirection2;        // Second direction control pin (if dual mode enabled)
  bool dualDirection;       // Flag for dual direction mode
  String motorName;         // Name of the motor
  String currentDirection;  // Current motor direction
  float currentSpeed;       // Current motor speed percentage

  void logChange(String parameter, String value) {
    Serial.println(motorName + " changed " + parameter + " to " + value);
  }

  void logState() {
    Serial.println(
      motorName
      + " current state: direction="
      + currentDirection
      + ", speed="
      + String(currentSpeed)
      + "%"
    );
  }

  void writeToPins() {
    if (dualDirection) {
      if (currentDirection == "forward") {
        digitalWrite(outDirection1, HIGH);
        digitalWrite(outDirection2, LOW);
      } else if (currentDirection == "backward") {
        digitalWrite(outDirection1, LOW);
        digitalWrite(outDirection2, HIGH);
      } else {
        digitalWrite(outDirection1, LOW);
        digitalWrite(outDirection2, LOW);
      }
    } else {
      if (currentDirection == "forward") {
        digitalWrite(outDirection1, HIGH);
      } else if (currentDirection == "backward") {
        digitalWrite(outDirection1, LOW);
      }
    }

    int dutyCycle = currentSpeed * 255 / 100;

    analogWrite(outPwm, dutyCycle);
    logState();
  }

 public:
  /**
   * Constructs a MotorDriver object.
   * @param {int} outPwm - The PWM output pin.
   * @param {int} outDirection1 - The first direction control pin.
   * @param {String} motorName - The name of the motor.
   * @param {bool} dualDirectionPin - Flag for dual direction mode.
   * @param {int} outDirection2 - The second direction control pin (if dual mode enabled).
   */
  MotorDriver(
    int outPwm,
    int outDirection1,
    String motorName,
    bool dualDirectionPin = false,
    int outDirection2 = -1
  ) {
    this->outPwm = outPwm;
    this->outDirection1 = outDirection1;
    this->motorName = motorName;
    this->dualDirection = dualDirectionPin;
    this->outDirection2 = outDirection2;
    this->currentDirection = "stopped";
    this->currentSpeed = 0;

    pinMode(outPwm, OUTPUT);
    pinMode(outDirection1, OUTPUT);

    if (dualDirection) {
      pinMode(outDirection2, OUTPUT);
    }
  }

  /**
   * Sets the direction of the motor.
   * @param {String} direction - The direction to set ("forward" or "backward").
   */
  void setDirection(String direction) {
    if (currentDirection != direction) {
      currentDirection = direction;
      logChange("direction", direction);
      writeToPins();
    }
  }

  /**
   * Sets the speed of the motor.
   * @param {float} speedPercentage - The speed percentage to set (0-100).
   */
  void setSpeed(float speedPercentage) {
    if (currentSpeed != speedPercentage) {
      currentSpeed = speedPercentage;
      logChange("speed", String(speedPercentage) + "%");
      writeToPins();
    }
  }

  /**
   * Stops the motor.
   */
  void setStop() {
    currentSpeed = 0;
    currentDirection = "stopped";
    logChange("state", "stopped");
    writeToPins();
  }

  /**
   * Gets the name of the motor.
   * @returns {String} The name of the motor.
   */
  String getName() {
    return motorName;
  }
};

#endif  // UTIL_MOTORDRIVER_H