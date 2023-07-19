#include <Arduino.h>
#include <avr/interrupt.h>

#include "servo.h"
#include "hcsr04.h"
#include "l293d.h"
#include "state.h"

// HCSR04 pins
const uint8_t TRIG_PIN = A4, ECHO_PIN = A5;

volatile unsigned long measured_left_motor_count = 0, measured_right_motor_count = 0;

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN);

Direction dir = Direction::STOP;
void (*currentState)(void);
// static unsigned long left_motor_count = 0, right_motor_count = 0;

void setup(void)
{
  // Interrupts on failing edge for the encoders
  // left encoder at PD2 pin, right encoder at pin PD3;
  cli();
  MCUCR |= _BV(ISC11) | _BV(ISC01);
  GICR |= _BV(INT1) | _BV(INT0);
  sei();
  
  servoInit();
  l293d_init();
  currentState = scanDistance;
}

void loop(void)
{
  currentState();
}

ISR(INT0_vect)
{
  measured_left_motor_count++;
}

ISR(INT1_vect)
{
  measured_right_motor_count++;
}