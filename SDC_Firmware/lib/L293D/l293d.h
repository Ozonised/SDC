#pragma once

#include <Arduino.h>
#include <avr/interrupt.h>

enum class Direction : uint8_t
{
    FORWARD,
    RIGHT,
    LEFT,
    BACK,
    STOP
};

extern Direction dir;

namespace Motor
{
    namespace Right
    {
        extern volatile long count;
    } // namespace rightMotor

    namespace Left
    {
        extern volatile long count;
    } // namespace leftMotor

    void Init();
    void Move(Direction direction);
    void Move(Direction direction, uint8_t lPWM, uint8_t rPWM);
} // namespace Motor
