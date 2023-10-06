#pragma once

class PID 
{
    private:
        float interval;
        float I, prevError;

    public:
        float KI, KP, KD, pid;
        float setPoint;
        float maxLimit; // maximum output limit
        float minLimit; // minimum output limit

        PID(float maxOutput, float minOutput, float interval);

        /**
         * @brief calculates the PID value
         * @param measuredValue value measured from the sensor
         * @return PID value
        */
        float calculate(float measuredValue);
};