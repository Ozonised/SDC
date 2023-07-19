#pragma once

#include <Arduino.h>
#include "servo.h"
#include "hcsr04.h"
#include "l293d.h"


extern HCSR04 hcsr04;
extern Direction dir;
extern volatile unsigned long measured_left_motor_count, measured_right_motor_count;
extern void (*currentState)(void);

void scanDistance();
void drive();