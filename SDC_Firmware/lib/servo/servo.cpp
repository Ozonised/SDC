#include "servo.h"

static const uint8_t OCR2_MIN = 16; // OCR2 value for servo angle = 0
static const uint8_t OCR2_MAX = 32; // OCR2 value for servo angle = 180

/* 
The servo angle from 0 to 180 will be mapped to a value between 16 to 32 for the OCR register using the slope 
intercept formula: y = mx + c, where c = OCR2_MIN and m = (y2 - y1) / (x2 - x1) = (32 - 16) / (180 - 0) = 0.089
*/
static const float m = 0.089;      // slope

void servoInit()
{
    // prescaler of 1024, frequency of 61Hz (approx), phase correct non inverting PWM mode
    TCCR2 = _BV(WGM20) | _BV(COM21) | _BV(WGM21) | _BV(CS20) | _BV(CS21) | _BV(CS22);
    TCNT2 = 0;
    OCR2 = 24;  // centering the servo head
    DDRB |= (1 << PB3);
}

void servoSet(uint8_t pos)
{
    if (pos >= 0 && pos <= 180)
        OCR2 = m * pos + OCR2_MIN;
}