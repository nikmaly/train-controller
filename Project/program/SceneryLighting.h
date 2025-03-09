#ifndef SCENERY_LIGHTING_H
#define SCENERY_LIGHTING_H

#include <Arduino.h>

class SceneryLighting {
public:
    SceneryLighting(const char* name, const int* pins, int pinCount) 
        : name(name), pins(pins), pinCount(pinCount) {
        for (int i = 0; i < pinCount; ++i) {
            pinMode(pins[i], OUTPUT);
        }
    }

    void turnOn() {
        for (int i = 0; i < pinCount; ++i) {
            digitalWrite(pins[i], HIGH);
        }
    }

    void turnOff() {
        for (int i = 0; i < pinCount; ++i) {
            digitalWrite(pins[i], LOW);
        }
    }

    const char* getName() const {
        return name;
    }

private:
    const char* name;
    const int* pins;
    int pinCount;
};

#endif // SCENERY_LIGHTING_H
