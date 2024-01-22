#pragma once

#include <Arduino.h>

class HCSR04
{
private:
    unsigned long duration;
    const uint8_t trig;
    const uint8_t echo;

public:
    uint16_t distance;

    HCSR04(uint8_t trigPin, uint8_t echoPin);

    unsigned long getDistance();
};
