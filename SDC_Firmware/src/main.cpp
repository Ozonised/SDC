#include <Arduino.h>

#include "hcsr04.h"
#include "state.h"

// HCSR04 pins
const uint8_t TRIG_PIN = A4, ECHO_PIN = A5;

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN);

void (*currentState)(void);

void setup(void)
{
  PID_Init();
  Motor::Init();
  Servo::Init();
  currentState = scanArea;
  // the first reading on start up from the hcsr04 can be erroneous, so we just run it once to ignore the first reading
  hcsr04.getDistance();
  hcsr04.distance = 0;
}

void loop(void)
{
  currentState();
}
