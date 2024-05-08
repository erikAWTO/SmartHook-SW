#include <Arduino.h>
#include <Servo.h>
#include <drv8833.h>
#include <rfid.h>
#include <pindefs.h>
#include <predefs.h>
#include <EEPROM.h>

#define DEBUG 0

DRV8833 motor(MOTOR_PIN_1, MOTOR_PIN_2);
Servo lockServo;
Rfid rfid;

bool doorLocked = 0;

int servoPos = 0;

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
  lockServo.write(UNLOCK_PWM_VAL);

  rfid.begin();

  doorLocked = EEPROM.get(DOOR_LOCKED_ADDRESS, doorLocked); // Read door status from EEPROM

  for (int i = 0; i < 3; i++) // Blink LEDs to indicate initialization
  {
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, HIGH);
    delay(250);
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);
    delay(250);
  }

  if (DEBUG)
  {
    Serial.println("Dumping EEPROM contents:");
    for (unsigned int address = 0; address < EEPROM.length(); address++)
    {
      uint8_t value = EEPROM.read(address);
      Serial.print("Address: ");
      Serial.print(address);
      Serial.print(" Value: ");
      Serial.println(value);
    }
  }

  Serial.println("Initialization done!");
}

void loop()
{
  if (rfid.readCardUID()) // Card detected
  {

    Serial.println("Card detected!");

    if (doorLocked)
    {
      Serial.println("Door is locked!");

      if (rfid.compareCardUID()) // Card matches stored UID
      {
        Serial.println("Card matches stored UID!");
        blinkLED(LED_GREEN_PIN, 3, 250);
        openDoor();
        rfid.clearCardUID();
        EEPROM.put(DOOR_LOCKED_ADDRESS, doorLocked); // Write doorLocked to EEPROM, so that the door stays unlocked after power loss
      }
      else
      {
        Serial.println("Card does not match stored UID!");
        blinkLED(LED_RED_PIN, 3, 500); // Blink red LED to indicate authorized access
      }
    }
    else
    {
      Serial.println("Door is unlocked!");
      blinkLED(LED_GREEN_PIN, 3, 250);
      rfid.storeCardUID();
      Serial.println("Stored UID!");
      closeDoor();
      EEPROM.put(DOOR_LOCKED_ADDRESS, doorLocked); // Write doorLocked to EEPROM, so that the door stays locked after power loss
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
  delay(2000);                           // Wait for lock to unlock
  while (digitalRead(LIM_SW_OPENED_PIN)) // Open door until limit switch is pressed
  {
    motor.controlMotor(motor.UP);
  }
  motor.stopMotor();
  doorLocked = false;
}

void closeDoor()
{
  while (digitalRead(LIM_SW_CLOSED_PIN)) // Close door until limit switch is pressed
  {
    motor.controlMotor(motor.DOWN);
  }
  motor.stopMotor();
  delay(2000);
  servoLock();
  doorLocked = true;
}

void servoLock()
{
  for (servoPos = UNLOCK_PWM_VAL; servoPos <= LOCK_PWM_VAL; servoPos += 1)
  {
    // in steps of 1 degree
    lockServo.write(servoPos);
    delay(5);
  }
}

void servoUnlock()
{
  for (servoPos = LOCK_PWM_VAL; servoPos >= UNLOCK_PWM_VAL; servoPos -= 1)
  {
    // in steps of 1 degree
    lockServo.write(servoPos);
    delay(5);
  }
}
