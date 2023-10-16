#pragma once

class PID 
{
    private:
        float I;

    public:
        float KI, KP, KD;   // gains
        float pid;
        float setPoint;
        float error;
        float prevError;
        float maxLimit; // maximum output limit
        float minLimit; // minimum output limit
        float interval; // loop period

        PID();

        PID(float maxOutput, float minOutput, float interval);

        /**
         * @brief calculates the PID value
         * @param measuredValue value measured from the sensor
         * @return PID value
        */
        float calculate(float measuredValue);
};