#ifndef PREDEFS_H
#define PREDEFS_H

const int SERVO_LOCK_PWM_VAL = 0;
const int SERVO_UNLOCK_PWM_VAL = 90;

const int doorLockedAddress = 16;

typedef enum
{
    MOTOR_FORWARD = 0,
    MOTOR_BACKWARD = 1,
} motorDirection;

#endif