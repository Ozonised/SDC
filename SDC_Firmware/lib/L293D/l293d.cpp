#include "l293d.h"


// L293D pins
const uint8_t EN34 = PB2, EN12 = PB1, _1A = PC0, _2A = PC1, _3A = PC2, _4A = PC3;


void l293d_init()
{
    DDRC |= (1 << _1A) | (1 << _2A) | (1 << _3A) | (1 << _4A);
    PORTC &= ~((1 << _1A) | (1 << _2A) | (1 << _3A) | (1 << _4A));

    // Non inveting 8 - bit PWM mode, prescaler of 64 and a frequency of 976Hz
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
    TCCR1B = _BV(WGM12) | _BV(CS11) | _BV(CS10);
    TCNT1 = 0;
    OCR1A = 0;
    OCR1B = 0;

    DDRB |= (1 << EN34) | (1 << EN12);
}

void motorMove(Direction direction)
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

void motorMove(Direction direction, uint8_t lPWM, uint8_t rPWM)
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