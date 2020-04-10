// https://blog.jeronimus.net/2018/03/rfid-and-wemos-d1-mini-1.html

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 0 // 3
#define SS_PIN 15 // 8

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    delay(5);
  }

  Serial.println(F(""));
  Serial.println(F("D1 Mini RFID"));
  Serial.println(F("Serial Monitor connected."));

  SPI.begin();
  Serial.println(F("SPI initialized."));

  mfrc522.PCD_Init();
  Serial.println(F("RC initialized."));
  delay(4);

  mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop()
{
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
