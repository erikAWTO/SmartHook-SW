#include <Arduino.h>
#include <Servo.h>
#include <drv8833.h>
#include <rfid.h>

// DRV8833 motor(2, 3, 4, 5);
// Servo lockServo;
Rfid rfid;


const int limitSwitchClosedPin = 5; // Active low
const int limitSwitchOpenedPin = 7; // Active low


const int lockServoPin = 6;
bool doorLocked = false;
const int lockPwmValue = 0;
const int unlockPwmValue = 90;

void lockDoor();
void unlockDoor();

void closeDoor();
void openDoor();

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("SmartHook");

  pinMode(limitSwitchClosedPin, INPUT_PULLUP);
  pinMode(limitSwitchOpenedPin, INPUT_PULLUP);

  /*
  // Initialize motor driver
  DRV8833 motorDriver(2, 3, 4, 5);
  motorDriver.begin();

  // Initialize servo
  Servo lockServo;
  lockServo.attach(6);*/

  // Initialize RFID reader
  rfid.begin();
}

void loop()
{
  rfid.readCardUID();
  // put your main code here, to run repeatedly:
}

void openDoor()
{
  while (digitalRead(limitSwitchOpenedPin))
  {
    // motorDriver.controlMotorA(false);
    // motorDriver.controlMotorB(false);
  }
  //Stop motor
  // motorDriver.stopMotorA();
  // motorDriver.stopMotorB();
  unlockDoor();
}

void closeDoor()
{
  while (digitalRead(limitSwitchClosedPin))
  {
    // motorDriver.controlMotorA(true);
    // motorDriver.controlMotorB(true);
  }
  //Stop motor
  // motorDriver.stopMotorA();
  // motorDriver.stopMotorB();

  lockDoor();
}

void lockDoor()
{
  // lockServo.write(lockPwmValue);
  doorLocked = true;
}

void unlockDoor()
{
  // lockServo.write(unlockPwmValue);
  doorLocked = false;
}


// rfid_read()
// if doorLocked
//   if compareCardUID()
//    unlockDoor()
// else
//   continue
// if !doorLocked
//   if storeCardUID()
//     lockDoor()

