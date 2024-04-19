#include <Arduino.h>
#include <Servo.h>
#include <drv8833.h>
#include <MFRC522.h>
#include <EEPROM.h>




void lockHook();
void unlockHook();

void closeDoor();
void openDoor();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("SmartHook");

  // Initialize motor driver
  DRV8833 motorDriver(2, 3, 4, 5);
  motorDriver.begin();

  // Initialize servo
  Servo lockServo;
  lockServo.attach(6);

  // Initialize RFID reader
  MFRC522 rfid(10, 9);
  rfid.PCD_Init();
}


void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}