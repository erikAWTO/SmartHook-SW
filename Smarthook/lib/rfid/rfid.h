/*Bibliotek för att läsa av RFID UIDs och spara/läsa till EEPROM */

#ifndef RFID_H
#define RFID_H

#include <Arduino.h>
#include <EEPROM.h>
#include <MFRC522.h>
#include <SPI.h>
#include <predefs.h>
#include <pindefs.h>

class Rfid
{
public:
    Rfid();

    void begin();

    bool readCardUID();

    bool compareCardUID();

    bool storeCardUID();

    bool clearCardUID();

    void printCardUID();

private:
    uint8_t cardUID[7];

    MFRC522 rfidReader = MFRC522(SS_PIN, RST_PIN);
};

#endif