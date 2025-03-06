#include <Servo.h>

/**
 * ServoController class for controlling a servo motor.
 */
class ServoController {
  private:
    Servo servo;
    int pin;
    String servoName;

  public:
    /**
     * Constructs a ServoController object.
     * @param {int} pin - The pin connected to the servo.
     * @param {String} servoName - The name of the servo.
     */
    ServoController(int pin, String servoName) {
      this->pin = pin;
      this->servoName = servoName;
    }

    /**
     * Initializes the servo controller.
     */
    void begin() {
      servo.attach(pin);

    }

    /**
     * Sets the target angle of the servo.
     * @param {int} angle - The target angle to set (0-180).
     */
    void setAngle(int angle) {
      servo.write(angle);
      Serial.println("Set servo " + servoName + " to angle " + String(angle));
    }

    /**
     * Gets the name of the servo.
     * @returns {String} The name of the servo.
     */
    String getName() {
      return servoName;
    }
};
