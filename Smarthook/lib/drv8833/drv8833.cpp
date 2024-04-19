/* Motor driver for DRV8833 with no speed control

Erik Lindsten @ KTH 2024
*/

#include "drv8833.h"

// Constructor
DRV8833::DRV8833(uint8_t motorAInput1Pin, uint8_t motorAInput2Pin, uint8_t motorBInput1Pin, uint8_t motorBInput2Pin)
{
    this->motorAInput1Pin = motorAInput1Pin;
    this->motorAInput2Pin = motorAInput2Pin;
    this->motorBInput1Pin = motorBInput1Pin;
    this->motorBInput2Pin = motorBInput2Pin;
}

// Initialize motor pins
void DRV8833::begin()
{
    pinMode(motorAInput1Pin, OUTPUT);
    pinMode(motorAInput2Pin, OUTPUT);
    pinMode(motorBInput1Pin, OUTPUT);
    pinMode(motorBInput2Pin, OUTPUT);
}

// Control motor A speed and direction
void DRV8833::controlMotorA(bool direction)
{
    if (direction == true)
    {
        digitalWrite(motorAInput1Pin, HIGH);
        digitalWrite(motorAInput2Pin, LOW);
    }
    else
    {
        digitalWrite(motorAInput1Pin, LOW);
        digitalWrite(motorAInput2Pin, HIGH);
    }
}

// Control motor B speed and direction
void DRV8833::controlMotorB(bool direction)
{
    if (direction == true)
    {
        digitalWrite(motorBInput1Pin, HIGH);
        digitalWrite(motorBInput2Pin, LOW);
    }
    else
    {
        digitalWrite(motorBInput1Pin, LOW);
        digitalWrite(motorBInput2Pin, HIGH);
    }
}

// Stop motor A
void DRV8833::stopMotorA(void)
{

    digitalWrite(motorAInput1Pin, LOW);
    digitalWrite(motorAInput2Pin, LOW);
}

// Stop motor Bs
void DRV8833::stopMotorB(void)
{

    digitalWrite(motorBInput1Pin, LOW);
    digitalWrite(motorBInput2Pin, LOW);
}
