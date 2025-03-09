#ifndef SCENERY_LIGHTING_H
#define SCENERY_LIGHTING_H

#include <Arduino.h>

class SceneryLighting {
public:
    /**
     * Constructor for SceneryLighting.
     * @param {const char*} name - The name of the lighting item.
     * @param {const int*} pins - The array of pins associated with the lighting item.
     * @param {int} pinCount - The number of pins.
     */
    SceneryLighting(const char* name, const int* pins, int pinCount) 
        : name(name), pins(pins), pinCount(pinCount) {
        for (int i = 0; i < pinCount; ++i) {
            pinMode(pins[i], OUTPUT);
        }
    }

    /**
     * Turns on the lighting.
     */
    void turnOn() {
        for (int i = 0; i < pinCount; ++i) {
            digitalWrite(pins[i], HIGH);
        }
    }

    /**
     * Turns off the lighting.
     */
    void turnOff() {
        for (int i = 0; i < pinCount; ++i) {
            digitalWrite(pins[i], LOW);
        }
    }

    /**
     * Gets the name of the lighting item.
     * @returns {const char*} The name of the lighting item.
     */
    const char* getName() const {
        return name;
    }

private:
    const char* name;
    const int* pins;
    int pinCount;
};

#endif // SCENERY_LIGHTING_H
