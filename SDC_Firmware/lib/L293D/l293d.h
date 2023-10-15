#pragma once

#include <Arduino.h>

enum class Direction : uint8_t
{
    FORWARD,
    RIGHT,
    LEFT,
    BACK,
    STOP
};

namespace Motor
{
    void Init();
    void Move(Direction direction);
    void Move(Direction direction, uint8_t lPWM, uint8_t rPWM);
} // namespace Motor
