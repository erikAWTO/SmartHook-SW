/*Library for interfacing RFID UIDs with EEPROM 

Erik Lindsten @ KTH 2024
*/

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
    // Constructor
    Rfid(void);

    // Initialize RFID reader
    void begin();

    // Read card UID
    bool readCardUID();

    // Compare card UID with stored UID
    bool compareCardUID();

    // Store card UID
    bool storeCardUID();

    // Clear stored UID
    bool clearCardUID();

    // Print card UID
    void printCardUID();

private:
    // Card UID
    uint8_t cardUID[7];

    // RFID reader
    MFRC522 rfidReader = MFRC522(SS_PIN, RST_PIN);
};


#endif