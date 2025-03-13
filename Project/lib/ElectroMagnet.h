#ifndef ELECTROMAGNET_H
#define ELECTROMAGNET_H

/**
 * @class ElectroMagnet
 * @brief A class to handle the electromagnet.
 */
class ElectroMagnet {
  private:
    int pin;
    String name;
    bool state; // true = on, false = off

  public:
    /**
     * @brief Constructor for ElectroMagnet.
     * @param pin The pin number where the sensor is connected.
     * @param name The name of the Electromagnet.
     */
    ElectroMagnet(int pin, String name) :
      pin(pin),
      name(name)
    {}

    /**
     * @brief Initialize the electromagnet by setting the pin mode.
     */
    void begin() {
      pinMode(pin, OUTPUT);
      state = false;
      digitalWrite(pin, LOW);
    }

    /**
     * @brief Set the state of the electromagnet.
     * @param newState The new state of the electromagnet (true = on, false = off).
     */
    void setState(bool newState) {
      state = newState;
      digitalWrite(pin, state ? HIGH : LOW);
    }

    /**
     * @brief Toggle the state of the electromagnet.
     */
    void toggleState() {
      setState(!state);
    }

    /**
     * @brief Get the current state of the electromagnet.
     * @return The current state of the electromagnet (true = on, false = off).
     */
    bool getState() const {
      return state;
    }

    /**
     * @brief Get the name of the electromagnet.
     * @return The name of the electromagnet.
     */
    String getName() const {
      return name;
    }
};

#endif  // ELECTROMAGNET_H