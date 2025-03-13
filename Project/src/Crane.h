#ifndef CRANE_H
#define CRANE_H
#include "../lib/Servo.h"
#include "../lib/ElectroMagnet.h"
#include "SerialHandler.h"

/**
 * @class Crane
 * @brief A class to handle a crane consisting of three servos and an electromagnet.
 */
class Crane {
  private:
    String name;
    ServoController* servoX;
    ServoController* servoY;
    ServoController* servoZ;
    ElectroMagnet* electromagnet;
    bool electromagnetState = false;
    int xPosition = 0;
    int yPosition = 0;
    int zPosition = 0;
    int xTarget = 0;
    int yTarget = 0;
    int zTarget = 0;
    int xSpeed;
    int ySpeed;
    int zSpeed;

    void moveServo(ServoController* servo, int& position, int target, int speed) {
      if (position < target) {
        position = min(position + speed, target);
      } else if (position > target) {
        position = max(position - speed, target);
      }
      servo->setAngle(position);
    }

    void controlX() {
      moveServo(servoX, xPosition, xTarget, xSpeed);
    }

    void controlY() {
      moveServo(servoY, yPosition, yTarget, ySpeed);
    }

    void controlZ() {
      moveServo(servoZ, zPosition, zTarget, zSpeed);
    }

    void controlElectromagnet(bool state) {
      electromagnet->setState(state);
    }

  public:
    /**
     * Constructor for Crane.
     * @param {String} name - The name of the crane.
     * @param {ServoController*} servoX - The servo for movement on the X plane.
     * @param {ServoController*} servoY - The servo for movement on the Y plane.
     * @param {ServoController*} servoZ - The servo for movement on the Z plane.
     * @param {ElectroMagnet*} electromagnet - The electromagnet for the crane.
     * @param {int} xSpeed - The speed of movement on the X plane.
     * @param {int} ySpeed - The speed of movement on the Y plane.
     * @param {int} zSpeed - The speed of movement on the Z plane.
     */
    Crane(const String& name, ServoController* servoX, ServoController* servoY, ServoController* servoZ, ElectroMagnet* electromagnet, int xSpeed, int ySpeed, int zSpeed)
      : name(name), servoX(servoX), servoY(servoY), servoZ(servoZ), electromagnet(electromagnet), xSpeed(xSpeed), ySpeed(ySpeed), zSpeed(zSpeed) {}

    /**
     * Gets the name of the crane.
     * @returns {String} The name of the crane.
     */
    String getName() const {
      return name;
    }

    /**
     * Control the crane's movement and electromagnet state.
     * @param {int} x - The target position on the X plane (optional).
     * @param {int} y - The target position on the Y plane (optional).
     * @param {int} z - The target position on the Z plane (optional).
     * @param {bool} electromagnetState - The state of the electromagnet (optional).
     */
    void control(int x = -1, int y = -1, int z = -1, bool electromagnetState = false) {
      if (x != -1) xTarget = x;
      if (y != -1) yTarget = y;
      if (z != -1) zTarget = z;
      if (electromagnetState) controlElectromagnet(electromagnetState);

      controlX();
      controlY();
      controlZ();
    }
};

#endif  // CRANE_H
