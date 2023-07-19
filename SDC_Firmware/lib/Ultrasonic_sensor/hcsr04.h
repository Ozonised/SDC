#pragma once

#include <Arduino.h>

class HCSR04
{
private:
    uint8_t trig;
    uint8_t echo;

public:
    unsigned long duration;
    uint16_t distance;

    HCSR04(uint8_t trigPin, uint8_t echoPin);

    unsigned long getDistance();
};
