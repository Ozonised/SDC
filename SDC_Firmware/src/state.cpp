#include "state.h"

static unsigned short objectDistance, moveDistance;
static const uint8_t maintainDistance = 18; // distance to be maintained between the object and vechicle
static const uint8_t encoderSlotsCount = 20;       // no of slots on the encoder wheel
static const float wheelCircumference = 19;


static uint8_t servoAngles[3] = {0, 90, 180};

void scanDistance()
{
    uint8_t maxDistanceServoAngle; // The  servo angle at which the measured distance is maximum
    servoSet(90);
    objectDistance = hcsr04.getDistance();

    if (objectDistance >= 100)
    {
        objectDistance = 100;
        dir = Direction::FORWARD;
    }
    else if (objectDistance <= maintainDistance) // an obstacle has been encountered
    {
        dir = Direction::STOP;
        motorMove(dir);
        // scan the space in a 180 degree arc and find the maximum distance
        for (uint8_t i = 0; i < 3; i++)
        {
            servoSet(servoAngles[i]);
            delay(400);
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
    else
    {
        dir = Direction::FORWARD;
    }

    cli();
    measured_left_motor_count = 0;
    measured_right_motor_count = 0;
    sei();

    moveDistance = objectDistance - maintainDistance;
    currentState = drive;
}

void drive()
{
    unsigned long distanceToEncoderTicks; // no of encoder ticks to travel a specified distance
    uint8_t left_PWM_val = 0, right_PWM_Val = 0;

    servoSet(90);

    switch (dir)
    {
    case Direction::LEFT:
    case Direction::RIGHT:
        // to turn left or right, the encoder needs to make 5 ticks, this was found with trial and error
        distanceToEncoderTicks = 5;
        left_PWM_val = 150;
        right_PWM_Val = 150;
        break;

    case Direction::FORWARD:
    case Direction::BACK:
        distanceToEncoderTicks = ((float)encoderSlotsCount / wheelCircumference) * moveDistance;
        left_PWM_val = 255;
        right_PWM_Val = 255;
        break;

    default:
        break;
    }

    unsigned long left_motor_count = 0, right_motor_count = 0;

    motorMove(dir, left_PWM_val, right_PWM_Val);
    while (left_motor_count < distanceToEncoderTicks && right_motor_count < distanceToEncoderTicks)
    {
        cli();
        left_motor_count = measured_left_motor_count;
        right_motor_count = measured_right_motor_count;
        sei();
        

        // measure the distance every 100ms when the vechicle is driving in the forward direction
        // if the distance between the vechile and the object is less than  10cm then stop the vechile
        if (dir != Direction::LEFT && dir != Direction::RIGHT && hcsr04.getDistance() <= maintainDistance)
            break;
        delay(50);
    }
    dir = Direction::STOP;
    motorMove(dir);
    currentState = scanDistance;
}
