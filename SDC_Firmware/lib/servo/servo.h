#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>

namespace Servo
{
    void Init();
    void Set(uint8_t pos);
} // namespace Servo
