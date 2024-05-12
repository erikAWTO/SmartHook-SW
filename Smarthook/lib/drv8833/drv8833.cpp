/* Motordrivare för DRV8833 utan hastighetsreglering och enbart en kanal. */

#include "drv8833.h"

DRV8833::DRV8833(uint8_t motorInput1Pin, uint8_t motorInput2Pin)
{
    this->motorInput1Pin = motorInput1Pin;
    this->motorInput2Pin = motorInput2Pin;
}

void DRV8833::begin()
{
    pinMode(motorInput1Pin, OUTPUT);
    pinMode(motorInput2Pin, OUTPUT);

    analogWrite(motorInput1Pin, 0);
    analogWrite(motorInput2Pin, 0);
}

void DRV8833::controlMotor(bool direction)
{
    if (direction == true)
    {
        analogWrite(motorInput1Pin, 128);
        analogWrite(motorInput2Pin, 0);
    }
    else
    {
        analogWrite(motorInput1Pin, 0);
        analogWrite(motorInput2Pin, 128);
    }
}

void DRV8833::stopMotor()
{

    analogWrite(motorInput1Pin, 0);
    analogWrite(motorInput2Pin, 0);
}
