/* MFRC522 driver with EEPROM storage for RFID UIDs

Erik Lindsten @ KTH 2024
*/

#include <rfid.h>


Rfid::Rfid(void)
{
}

void Rfid::begin()
{
    // Initialize SPI bus
    SPI.begin();

    // Initialize RFID reader
    rfidReader.PCD_Init();
    rfidReader.PCD_DumpVersionToSerial();
}

bool Rfid::readCardUID()
{
    // Look for new cards
    if (!rfidReader.PICC_IsNewCardPresent())
    {
        return false;
    }

    // Select one of the cards
    if (!rfidReader.PICC_ReadCardSerial())
    {
        return false;
    }

    // Store card UID. Should be 7 bytes for KTH RFID cards
    for (uint8_t i = 0; i < rfidReader.uid.size; i++)
    {
        cardUID[i] = rfidReader.uid.uidByte[i];
    }

    printCardUID();

    return true;
}

bool Rfid::compareCardUID()
{
    // Compare card UID with stored UID
    for (uint8_t i = 0; i < sizeof(cardUID) / sizeof(uint8_t); i++)
    {
        if (cardUID[i] != EEPROM.read(i + UID_ADDRESS))
        {
            return false;
        }
    }

    return true;
}

bool Rfid::storeCardUID()
{
    // Store card UID in EEPROM with offset UID_ADDRESS
    for (uint8_t i = 0; i < sizeof(cardUID) / sizeof(uint8_t); i++)
    {
        EEPROM.write(i + UID_ADDRESS, cardUID[i]);
    }

    return true;

}

bool Rfid::clearCardUID()
{
    // Clear stored UID in EEPROM
    for (uint8_t i = 0; i < sizeof(cardUID) / sizeof(uint8_t); i++)
    {
        EEPROM.write(i + UID_ADDRESS, 0);
    }
    
    return true;
}

void Rfid::printCardUID(void)
{
    Serial.println();
    Serial.print(" UID: ");
    String content = "";
    for (uint8_t i = 0; i < rfidReader.uid.size; i++)
    {
        Serial.print(cardUID[i] < 0x10 ? " 0" : " ");
        Serial.print(cardUID[i], HEX);
        content.concat(String(cardUID[i] < 0x10 ? " 0" : " "));
        content.concat(String(cardUID[i], HEX));
    }
    content.toUpperCase();
    Serial.println();
}
