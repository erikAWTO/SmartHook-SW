/* Motor driver for DRV8833 for single motor with no speed control

Erik Lindsten @ KTH 2024
*/

#include "drv8833.h"

// Constructor
DRV8833::DRV8833(uint8_t motorInput1Pin, uint8_t motorInput2Pin)
{
    this->motorInput1Pin = motorInput1Pin;
    this->motorInput2Pin = motorInput2Pin;
}

// Initialize motor pins
void DRV8833::begin()
{
    pinMode(motorInput1Pin, OUTPUT);
    pinMode(motorInput2Pin, OUTPUT);

    analogWrite(motorInput1Pin, 0);
    analogWrite(motorInput2Pin, 0);
}

// Control motor direction
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

// Stop motor 
void DRV8833::stopMotor(void)
{

    analogWrite(motorInput1Pin, 0);
    analogWrite(motorInput2Pin, 0);
}
