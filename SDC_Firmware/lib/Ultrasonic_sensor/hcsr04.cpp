#include "Arduino.h"
#include "hcsr04.h"

HCSR04::HCSR04(uint8_t trigPin, uint8_t echoPin)
{
    trig = trigPin;
    echo = echoPin;
    distance = 0;

    digitalWrite(trig, LOW);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

// Calculates the distance and stores it into the distance member variable
unsigned long HCSR04::getDistance()
{
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    // The echo pulse is approx 36mS if no object is detected. 
    // Thus the pulse in function will timeout after 36mS or 36000uS
    duration = pulseIn(echo, HIGH, 36000);
    duration /= 2;
    distance = 343 * duration / 10000; // m/s into cm/us    delay(40);
    return distance;
}
