/* Motor driver for DRV8833 with no speed control

Erik Lindsten @ KTH 2024
*/

#ifndef DRV8833_H
#define DRV8833_H

#include <Arduino.h>

class DRV8833 {
  public:
    // Constructor
    DRV8833(uint8_t motorInput1Pin, uint8_t motorInput2Pin);

    // Initialize motor pins
    void begin();

    // Control motor A speed and direction
    void controlMotor(bool direction);

    // Stop motor A
    void stopMotor(void);

  typedef enum {
    UP = 0,
    DOWN = 1,
  } MOTOR_DIRECTION;

  private:
    // Motor control pins
    uint8_t motorInput1Pin;
    uint8_t motorInput2Pin;
};

#endif