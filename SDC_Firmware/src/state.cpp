#include "state.h"

static const uint8_t maintainDistance = 20; // distance to be maintained between the object and vechicle
// static const uint8_t encoderSlotsCount = 20;       // no of slots on the encoder wheel
// static const float wheelCircumference = 19;

static const uint8_t motorTicksToTurn = 10; // no of ticks to make a 90 degree turn

static unsigned long currentMillis, prevMillis;
static const unsigned long loopPeriod = 60; // loop period in ms

PID drivePID(255, -255, 0.06);
PID turnPID(255, -255, 0.06);

void PID_Init()
{
    drivePID.setPoint = maintainDistance;
    drivePID.KP = -23;
    turnPID.KD = 0.28;
    turnPID.setPoint = motorTicksToTurn;
    turnPID.KP = 25;
    turnPID.KD = 0.15;
}

void scanArea()
{
    static uint8_t servoAngles[3] = {0, 90, 180};
    uint8_t maxDistanceServoAngle; // The  servo angle at which the measured distance is maximum
    unsigned short objectDistance = 0;

    Servo::Set(90);
    delay(200);

    objectDistance = hcsr04.getDistance();

    if (objectDistance > maintainDistance)
    {
        dir = Direction::FORWARD;
    }
    else
    {
        // scan the space in a 180 degree arc and find the servo angle at which there's maximum distance available
        for (uint8_t i = 0; i < 3; i++)
        {
            Servo::Set(servoAngles[i]);
            delay(200);
            if (hcsr04.getDistance() > objectDistance)
            {
                objectDistance = hcsr04.distance;
                maxDistanceServoAngle = servoAngles[i];
            }
        }

        if (maxDistanceServoAngle < 90)
            dir = Direction::RIGHT;
        else if (maxDistanceServoAngle > 90)
            dir = Direction::LEFT;
        else
            dir = Direction::FORWARD;
    }

    currentState = drive;
}

void drive()
{
    unsigned long temp_left_motor_count = 0, temp_right_motor_count = 0, average_motor_count = 0, prev_motor_count = 0;
    unsigned short measurement;
    short pwm;

    Servo::Set(90);
    delay(200);

    while (dir == Direction::LEFT || dir == Direction::RIGHT)
    {
        currentMillis = millis();

        if ((currentMillis - prevMillis) > loopPeriod)
        {
            cli();
            temp_right_motor_count = Motor::Right::count;
            temp_left_motor_count = Motor::Left::count;
            sei();

            average_motor_count = (temp_left_motor_count + temp_right_motor_count) / 2;
            pwm = turnPID.calculate(average_motor_count);

            Motor::Move(dir, pwm, pwm);

            if (turnPID.error <= -1)
            {
                Motor::Move(Direction::STOP);
                dir = Direction::FORWARD;
                cli();
                Motor::Left::count = 0;
                Motor::Right::count = 0;
                sei();
            }

            prevMillis = currentMillis;
        }
    }

    while (dir == Direction::FORWARD || dir == Direction::BACK)
    {
        currentMillis = millis();

        if (currentMillis - prevMillis >= loopPeriod)
        {
            measurement = hcsr04.getDistance();

            cli();
            temp_right_motor_count = Motor::Right::count;
            temp_left_motor_count = Motor::Left::count;
            sei();

            average_motor_count = (temp_left_motor_count + temp_right_motor_count) / 2;

            pwm = drivePID.calculate(measurement);

            if (drivePID.error < 0)
                dir = Direction::FORWARD;
            else if (drivePID.error > 0)
                dir = Direction::BACK;

            if (pwm < 0)
                pwm *= -1;

            Motor::Move(dir, pwm, pwm);

            // if the vechicle is off by 2cm from the maintainDistance
            // prev_motor_count == average_motor_count ,i.e, the vechicle is not moving
            if (drivePID.error <= 2 && drivePID.error >= -2 && prev_motor_count == average_motor_count)
            {
                dir = Direction::STOP;
                Motor::Move(dir);
            }

            prevMillis = currentMillis;
            prev_motor_count = average_motor_count;
        }
    }
    currentState = scanArea;
}
