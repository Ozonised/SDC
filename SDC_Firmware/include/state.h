#pragma once

#include <Arduino.h>
#include "servo.h"
#include "hcsr04.h"
#include "l293d.h"
#include "PID.h"

extern HCSR04 hcsr04;
extern Direction dir;
extern void (*currentState)(void);

void PID_Init();
void scanArea();
void drive();