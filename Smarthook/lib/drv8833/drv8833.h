/* Bibliotek för DRV8833 utan hastighetsreglering och enbart en kanal. */

#ifndef DRV8833_H
#define DRV8833_H

#include <Arduino.h>

class DRV8833 {
  public:
    DRV8833(uint8_t motorInput1Pin, uint8_t motorInput2Pin);

    void begin();

    void controlMotor(bool direction);

    void stopMotor();

  typedef enum {
    UP = 0,
    DOWN = 1,
  } MOTOR_DIRECTION;

  private:
    uint8_t motorInput1Pin;
    uint8_t motorInput2Pin;
};

#endif