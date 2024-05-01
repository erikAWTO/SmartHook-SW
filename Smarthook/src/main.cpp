#include <Arduino.h>
#include <Servo.h>
#include <drv8833.h>
#include <rfid.h>
#include <pindefs.h>
#include <predefs.h>
#include <EEPROM.h>

DRV8833 motor(MOTOR_PIN_1, MOTOR_PIN_2);
Servo lockServo;
Rfid rfid;

bool doorLocked = false;
unsigned long doorUnlockTime = 0;

unsigned int lockServoPos = 0;

void closeDoor();
void openDoor();

void servoLock();
void servoUnlock();

void blinkLED(int pin, int iterations, int delayTime);

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing SmartHook...");

  pinMode(LIM_SW_CLOSED_PIN, INPUT_PULLUP);
  pinMode(LIM_SW_OPENED_PIN, INPUT_PULLUP);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);

  motor.begin();

  lockServo.attach(LOCK_SERVO_PIN);

  rfid.begin();

  doorLocked = EEPROM.get(doorLockedAddress, doorLocked); // Read door status from EEPROM

  for (int i = 0; i < 3; i++) // Blink LEDs to indicate initialization
  {
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, HIGH);
    delay(500);
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);
    delay(500);
  }

  Serial.println("Initialization done!");
}

void loop()
{
  if (rfid.readCardUID()) // Card detected
  {
    if (doorLocked)
    {
      if (rfid.compareCardUID()) // Card matches stored UID
      {
        blinkLED(LED_GREEN_PIN, 3, 500); // Blink green LED to indicate authorized access
        openDoor();
        rfid.clearCardUID();
        EEPROM.put(doorLockedAddress, doorLocked); // Write doorLocked to EEPROM, so that the door stays unlocked after power loss
      }
      else
      {
        blinkLED(LED_RED_PIN, 3, 500); // Blink red LED to indicate authorized access
      }
    }
    else
    {
      blinkLED(LED_GREEN_PIN, 3, 500); // Blink green LED to indicate unauthorized access

      rfid.storeCardUID();

      closeDoor();

      EEPROM.put(doorLockedAddress, doorLocked); // Write doorLocked to EEPROM, so that the door stays locked after power loss
    }
  }
}

void blinkLED(int pin, int iterations, int delayTime)
{
  for (int i = 0; i < iterations; i++)
  {
    digitalWrite(pin, HIGH);
    delay(delayTime);
    digitalWrite(pin, LOW);
    delay(delayTime);
  }
}

void openDoor()
{
  servoUnlock();
  delay(3000);                            // Wait for lock to unlock
  while (!digitalRead(LIM_SW_OPENED_PIN)) // Open door until limit switch is pressed
  {
    motor.controlMotor(motor.UP);
  }
  motor.stopMotor();
  doorLocked = false;
}

void closeDoor()
{
  while (!digitalRead(LIM_SW_CLOSED_PIN)) // Close door until limit switch is pressed
  {
    motor.controlMotor(motor.DOWN);
  }
  motor.stopMotor();
  delay(3000);
  servoLock();
  doorLocked = true;
}

void servoLock()
{
  for (int pos = 0; pos <= LOCK_PWM_VAL; pos += 1)
  {
    // in steps of 1 degree
    lockServo.write(pos);
    delay(10);
  }
}

void servoUnlock()
{
  for (int pos = LOCK_PWM_VAL; pos >= 0; pos -= 1)
  {
    // in steps of 1 degree
    lockServo.write(pos);
    delay(10);
  }
}
