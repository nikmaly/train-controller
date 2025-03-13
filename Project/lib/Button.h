#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

/**
 * @class Button
 * @brief A class to manage a button connected to an Arduino pin.
 */
class Button {
public:
    /**
     * @brief Construct a new Button object.
     * @param name The name of the button.
     * @param pin The pin number the button is connected to.
     */
    Button(const char* name, int pin);

    /**
     * @brief Initialize the button pin.
     */
    void begin();

    /**
     * @brief Check if the button is pressed.
     * @return true if the button is pressed, false otherwise.
     */
    bool isPressed() const;

    /**
     * @brief Get the name of the button.
     * @return The name of the button.
     */
    const char* getName() const;

private:
    const char* name; ///< The name of the button.
    int pin; ///< The pin number the button is connected to.
};

#endif // BUTTON_H

Button::Button(const char* name, int pin) : name(name), pin(pin) {}

void Button::begin() {
    pinMode(pin, INPUT);
}

bool Button::isPressed() const {
    return digitalRead(pin) == HIGH;
}

const char* Button::getName() const {
    return name;
}
