#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>

void servoInit();
void servoSet(uint8_t pos);