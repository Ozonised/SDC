#include "servo.h"

static const uint8_t OCR2_MAX = 36; // OCR2 value for servo angle = 180
static const uint8_t OCR2_MIN = 6;  // OCR2 value for servo angle = 0

namespace Servo
{
    void Init()
    {
        // prescaler of 1024, frequency of 61Hz (approx), phase correct non inverting PWM mode
        TCCR2 = _BV(WGM20) | _BV(COM21) | _BV(WGM21) | _BV(CS20) | _BV(CS21) | _BV(CS22);
        TCNT2 = 0;
        OCR2 = (OCR2_MAX - OCR2_MIN) / 2 + OCR2_MIN; // centering the servo head
        DDRB |= (1 << PB3);
    }

    void Set(uint8_t pos)
    {
        /*
            The servo angle from 0 to 180 will be mapped to a value between OCR2_MIN to OCR2_MAX for the OCR register using the slope
            intercept formula: y = mx + c, where c = OCR2_MIN and m = (OCR2_MAX - OCR_MIN) / (180 - 0)
        */
        if (pos >= 0 && pos <= 180)
            OCR2 = (((OCR2_MAX - OCR2_MIN) * pos) / 180) + OCR2_MIN;
    }
} // namespace Servo
