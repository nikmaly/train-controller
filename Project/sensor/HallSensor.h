/**
 * @class HallSensor
 * @brief A class to handle the Hall effect sensor.
 */
class HallSensor {
  private:
    int sensorPin; ///< The pin number where the sensor is connected.
    bool usePullup; ///< Whether to use the internal pull-up resistor.

  public:
    /**
     * @brief Constructor for HallSensor.
     * @param pin The pin number where the sensor is connected.
     * @param enablePullup Whether to enable the internal pull-up resistor (default: false).
     */
    HallSensor(int pin, bool enablePullup = false) : sensorPin(pin), usePullup(enablePullup) {
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