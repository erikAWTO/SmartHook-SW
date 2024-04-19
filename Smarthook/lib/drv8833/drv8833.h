/* Motor driver for DRV8833 with no speed control

Erik Lindsten @ KTH 2024
*/

#ifndef DRV8833_MOTOR_DRIVER_H
#define DRV8833_MOTOR_DRIVER_H

#include <Arduino.h>

class DRV8833 {
  public:
    // Constructor
    DRV8833(uint8_t motorAInput1Pin, uint8_t motorAInput2Pin, uint8_t motorBInput1Pin, uint8_t motorBInput2Pin);

    // Initialize motor pins
    void begin();

    // Control motor A speed and direction
    void controlMotorA(bool direction);

    // Control motor B speed and direction
    void controlMotorB(bool direction);

    // Stop motor A
    void stopMotorA(void);

    // Stop motor B
    void stopMotorB(void);

  private:
    // Motor control pins
    uint8_t motorAInput1Pin;
    uint8_t motorAInput2Pin;
    uint8_t motorBInput1Pin;
    uint8_t motorBInput2Pin;
};

#endif