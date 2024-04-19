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

void Rfid::readCardUID()
{
    // Look for new cards
    if (!rfidReader.PICC_IsNewCardPresent())
    {
        return;
    }

    // Select one of the cards
    if (!rfidReader.PICC_ReadCardSerial())
    {
        return;
    }

    // Store card UID. Should be 7 bytes for KTH RFID cards
    for (byte i = 0; i < rfidReader.uid.size; i++)
    {
        cardUID[i] = rfidReader.uid.uidByte[i];
    }

    printCardUID();
}

bool Rfid::compareCardUID()
{
    // Compare card UID with stored UID
    for (byte i = 0; i < sizeof(cardUID) / sizeof(uint8_t); i++)
    {
        if (cardUID[i] != EEPROM.read(i))
        {
            return false;
        }
    }

    return true;
}

void Rfid::storeCardUID()
{
    // Store card UID in EEPROM
    for (byte i = 0; i < sizeof(cardUID) / sizeof(uint8_t); i++)
    {
        EEPROM.write(i, cardUID[i]);
    }
}

void Rfid::clearCardUID()
{
    // Clear stored UID in EEPROM
    for (byte i = 0; i < sizeof(cardUID) / sizeof(uint8_t); i++)
    {
        EEPROM.write(i, 0);
    }
}

void Rfid::printCardUID(void)
{
    Serial.println();
    Serial.print(" UID: ");
    String content = "";
    for (byte i = 0; i < rfidReader.uid.size; i++)
    {
        Serial.print(cardUID[i] < 0x10 ? " 0" : " ");
        Serial.print(cardUID[i], HEX);
        content.concat(String(cardUID[i] < 0x10 ? " 0" : " "));
        content.concat(String(cardUID[i], HEX));
    }
    content.toUpperCase();
    Serial.println();
}
