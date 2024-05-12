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

  doorLocked = EEPROM.get(DOOR_LOCKED_ADDRESS, doorLocked); // Läs dörr status från EEPROM

  for (int i = 0; i < 3; i++) // Blinka LEDs för att indikera att initiering är klar
  {
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, HIGH);
    delay(250);
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);
    delay(250);
  }

  Serial.println("Initialization done!");
}

void loop()
{
  if (rfid.readCardUID()) // Kort detekterat
  {

    Serial.println("Card detected!");

    if (doorLocked)
    {
      Serial.println("Door is locked!");

      if (rfid.compareCardUID()) // Kort matchar lagrad UID
      {
        Serial.println("Card matches stored UID!");
        blinkLED(LED_GREEN_PIN, 3, 250);
        openDoor();
        rfid.clearCardUID();
        EEPROM.put(DOOR_LOCKED_ADDRESS, doorLocked); // Skriv doorLocked till EEPROM, så att dörren förblir låst efter strömavbrott
      }
      else
      {
        Serial.println("Card does not match stored UID!");
        blinkLED(LED_RED_PIN, 3, 500);
      }
    }
    else
    {
      Serial.println("Door is unlocked!");
      blinkLED(LED_GREEN_PIN, 3, 250);
      rfid.storeCardUID();
      Serial.println("Stored UID!");
      closeDoor();
      EEPROM.put(DOOR_LOCKED_ADDRESS, doorLocked); // Skriv doorLocked till EEPROM, så att dörren förblir låst efter strömavbrott
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
  delay(2000);                           // Vänta 2 sekunder innan dörren öppnas
  while (digitalRead(LIM_SW_OPENED_PIN)) // Öppna dörren tills brytaren är aktiverad
  {
    motor.controlMotor(motor.UP);
  }
  motor.stopMotor();
  doorLocked = false;
}

void closeDoor()
{
  while (digitalRead(LIM_SW_CLOSED_PIN)) // Stäng dörren tills brytaren är aktiverad
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
    lockServo.write(servoPos);
    delay(20);
  }
}

void servoUnlock()
{
  for (servoPos = LOCK_PWM_VAL; servoPos >= UNLOCK_PWM_VAL; servoPos -= 1)
  {
    lockServo.write(servoPos);
    delay(20);
  }
}
