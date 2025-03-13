#ifndef SIGNAL_H
#define SIGNAL_H

#include "../lib/HallSensor.h"
#include <Arduino.h>

/**
 * @class Signal
 * @brief A class to handle a signal consisting of a hall sensor and two LEDs.
 */
class Signal {
  private:
    String name;
    HallSensor hallSensor;
    int greenLedPin;
    int redLedPin;
    bool isSafe;

  public:
    /**
     * @brief Constructor for Signal.
     * @param name The name of the signal.
     * @param greenLedPin The pin number for the green LED.
     * @param redLedPin The pin number for the red LED.
     * @param hallSensorPin The pin number for the hall sensor.
     */
    Signal(const String& name, int hallSensorPin, int greenLedPin, int redLedPin) :
      name(name),
      hallSensor(hallSensorPin, name + ' sensor'),
      greenLedPin(greenLedPin),
      redLedPin(redLedPin),
      isSafe(true) {
        pinMode(greenLedPin, OUTPUT);
        pinMode(redLedPin, OUTPUT);
        setState(true);
    }

    /**
     * @brief Gets the value from the hall sensor.
     * @return The digital value read from the hall sensor pin.
     */
    int getHallSensorValue() {
        return hallSensor.read();
    }

    /**
     * @brief Sets the signal state.
     * @param state The state to set (true for safe, false for unsafe).
     */
    void setState(bool state) {
        isSafe = state;
        if (isSafe) {
            digitalWrite(greenLedPin, HIGH);
            digitalWrite(redLedPin, LOW);
        } else {
            digitalWrite(greenLedPin, LOW);
            digitalWrite(redLedPin, HIGH);
        }
    }

    /**
     * @brief Gets the current state of the signal.
     * @return The current state (true for safe, false for unsafe).
     */
    bool getState() const {
        return isSafe;
    }

    String getName() const {
        return name;
    }
};

#endif // SIGNAL_H
