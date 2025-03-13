#ifndef HALLSENSOR_H
#define HALLSENSOR_H

/**
 * @class HallSensor
 * @brief A class to handle the Hall effect sensor.
 */
class HallSensor {
  private:
    int sensorPin;
    bool usePullup;
    String name;

  public:
    /**
     * @brief Constructor for HallSensor.
     * @param pin The pin number where the sensor is connected.
     * @param enablePullup Whether to enable the internal pull-up resistor (default: false).
     * @param name The name of the Hall sensor.
     */
    HallSensor(int pin, String name, bool enablePullup = false) :
      sensorPin(pin),
      name(name),
      usePullup(enablePullup) {
        pinMode(sensorPin, enablePullup ? INPUT_PULLUP : INPUT);
    }

    /**
     * @brief Reads the value from the Hall sensor.
     * @return The digital value read from the sensor pin.
     */
    int read() {
        return digitalRead(sensorPin);
    }
};

#endif  // HALLSENSOR_H