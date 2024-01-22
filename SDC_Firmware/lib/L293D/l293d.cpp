#include "l293d.h"

// L293D pins
const uint8_t EN34 = PB2, EN12 = PB1, _1A = PC0, _2A = PC1, _3A = PC2, _4A = PC3;

Direction dir = Direction::STOP;

namespace Motor
{
    namespace Right
    {
        volatile long count = 0;
    } // namespace rightMotor

    namespace Left
    {
        volatile long count = 0;
    } // namespace leftMotor

    void Init()
    {
        DDRC |= (1 << _1A) | (1 << _2A) | (1 << _3A) | (1 << _4A);
        PORTC &= ~((1 << _1A) | (1 << _2A) | (1 << _3A) | (1 << _4A));

        // Non inveting 8 - bit PWM mode, prescaler of 64 and a frequency of 976Hz
        TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
        TCCR1B = _BV(WGM12) | _BV(CS11) | _BV(CS10);
        TCNT1 = 0;
        OCR1A = 0;
        OCR1B = 0;

        // Interrupts on failing edge for the encoders
        // right encoder at PD2 pin, left encoder at pin PD3
        cli();
        MCUCR |= _BV(ISC11) | _BV(ISC01);
        GICR |= _BV(INT1) | _BV(INT0);
        sei();

        DDRB |= (1 << EN34) | (1 << EN12);
    }

    void Move(Direction direction)
    {
        switch (direction)
        {
        case Direction::STOP:
            PORTC &= ~((1 << _1A) | (1 << _2A) | (1 << _3A) | (1 << _4A));
            OCR1A = 0;
            OCR1B = 0;
            break;

        case Direction::FORWARD:
            PORTC = _BV(_1A) | _BV(_3A);
            OCR1A = 255;
            OCR1B = 255;
            break;

        case Direction::RIGHT:
            PORTC = _BV(_2A) | _BV(_3A);
            OCR1A = 255;
            OCR1B = 255;
            break;

        case Direction::LEFT:
            PORTC = _BV(_1A) | _BV(_4A);
            OCR1A = 255;
            OCR1B = 255;
            break;

        case Direction::BACK:
            PORTC = _BV(_2A) | _BV(_4A);
            OCR1A = 255;
            OCR1B = 255;
            break;

        default:
            direction = Direction::STOP;
            break;
        }
    }

    void Move(Direction direction, uint8_t lPWM, uint8_t rPWM)
    {
        switch (direction)
        {
        case Direction::STOP:
            PORTC &= ~((1 << _1A) | (1 << _2A) | (1 << _3A) | (1 << _4A));
            OCR1A = 0;
            OCR1B = 0;
            break;

        case Direction::FORWARD:
            PORTC = _BV(_1A) | _BV(_3A);
            break;

        case Direction::RIGHT:
            PORTC = _BV(_2A) | _BV(_3A);
            break;

        case Direction::LEFT:
            PORTC = _BV(_1A) | _BV(_4A);
            break;

        case Direction::BACK:
            PORTC = _BV(_2A) | _BV(_4A);
            break;

        default:
            direction = Direction::STOP;
            break;
        }
        OCR1A = rPWM;
        OCR1B = lPWM;
    }
} // namespace Motor

ISR(INT0_vect)
{
    Motor::Right::count++;
}

ISR(INT1_vect)
{
    Motor::Left::count++;
}