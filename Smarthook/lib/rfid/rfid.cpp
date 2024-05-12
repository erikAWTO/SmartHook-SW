/* Bibliotek för att läsa av RFID UIDs och spara/läsa till EEPROM */

#include <rfid.h>


Rfid::Rfid(void)
{
}

void Rfid::begin()
{
    SPI.begin();

    rfidReader.PCD_Init();
    rfidReader.PCD_DumpVersionToSerial();
}

bool Rfid::readCardUID()
{
    // Kolla om kort är närvarande
    if (!rfidReader.PICC_IsNewCardPresent())
    {
        return false;
    }

    // Välj ett av korten
    if (!rfidReader.PICC_ReadCardSerial())
    {
        return false;
    }

    // Spara kortets UID. Ska vara 7 byte för KTH RFID-kort
    for (uint8_t i = 0; i < rfidReader.uid.size; i++)
    {
        cardUID[i] = rfidReader.uid.uidByte[i];
    }

    printCardUID();

    return true;
}

bool Rfid::compareCardUID()
{
    // Jämför kortets UID med sparade UID
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
    // Spara kortets UID i EEPROM med förskjutning UID_ADDRESS
    for (uint8_t i = 0; i < sizeof(cardUID) / sizeof(uint8_t); i++)
    {
        EEPROM.write(i + UID_ADDRESS, cardUID[i]);
    }

    return true;

}

bool Rfid::clearCardUID()
{
    // Rensa sparade UID i EEPROM
    for (uint8_t i = 0; i < sizeof(cardUID) / sizeof(uint8_t); i++)
    {
        EEPROM.write(i + UID_ADDRESS, 0);
    }
    
    return true;
}

void Rfid::printCardUID()
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
