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

    digitalWrite(motorInput1Pin, LOW);
    digitalWrite(motorInput2Pin, LOW);
}

// Control motor A speed and direction
void DRV8833::controlMotor(bool direction)
{
    if (direction == true)
    {
        digitalWrite(motorInput1Pin, HIGH);
        digitalWrite(motorInput2Pin, LOW);
    }
    else
    {
        digitalWrite(motorInput1Pin, LOW);
        digitalWrite(motorInput2Pin, HIGH);
    }
}

// Stop motor A
void DRV8833::stopMotor(void)
{

    digitalWrite(motorInput1Pin, LOW);
    digitalWrite(motorInput2Pin, LOW);
}
