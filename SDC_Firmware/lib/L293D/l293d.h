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

void l293d_init();
void motorMove(Direction direction);
void motorMove(Direction direction, uint8_t lPWM, uint8_t rPWM);