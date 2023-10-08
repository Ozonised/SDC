#include "PID.h"

PID::PID()
{
    KI = 0;
    KP = 0;
    KD = 0;
    I = 0;

    setPoint = 0;
    error = 0;
    prevError = 0;

    maxLimit = 0;
    minLimit = 0;
    interval = 0;
}

PID::PID(float maxOutput, float minOutput, float interval)
    : maxLimit(maxOutput), minLimit(minOutput), interval(interval)
{
    KI = 0;
    KP = 0;
    KD = 0;
    I = 0;

    setPoint = 0;
    error = 0;
    prevError = 0;
}

float PID::calculate(float measuredValue)
{
    float D = 0;

    error = setPoint - measuredValue;

    // integrator clamping by checking for integrator saturation
    if ((pid > maxLimit && error > 0 && I > 0) || (pid < minLimit && error < 0 && I < 0))
        I = I;
    else
        I = I + error * interval;

    D = (error - prevError) / interval;

    pid = (KP * error) + (KI * I) + (KD * D);

    // clamping PID value
    if (pid > maxLimit)
        pid = maxLimit;

    if (pid < minLimit)
        pid = minLimit;

    prevError = error;

    return pid;
}