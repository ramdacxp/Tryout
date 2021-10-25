// https://blog.jeronimus.net/2018/03/rfid-and-wemos-d1-mini-1.html

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN D3 // D3 = GPIO 0
#define SS_PIN D8  // D8 = GPIO15

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(5);
  }

  Serial.println(F(""));
  Serial.println(F("D1 Mini RFID"));
  Serial.println(F("Serial Monitor connected."));

  Serial.print(F("Init: SPI ... "));
  SPI.begin();

  Serial.print(F("RFID ... "));
  mfrc522.PCD_Init();
  delay(4);
  Serial.println(F("Done."));

  Serial.print(F("Max antenna gain: "));
  Serial.println(mfrc522.RxGain_max);
  Serial.print(F("Setting max gain ..."));
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);

  Serial.print(F(" Current gain now: "));
  byte gain = mfrc522.PCD_GetAntennaGain();
  Serial.println(gain);

  mfrc522.PCD_DumpVersionToSerial();
  Serial.println(F("Init done."));
}

// Returns the card UID as string.
// Those methods must have be called successfully before!
// - rfid.PICC_IsNewCardPresent()
// - rfid.PICC_ReadCardSerial()
String getCardUid()
{
  String id = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    if (mfrc522.uid.uidByte[i] < 0x10)
    {
      id += "0";
    }
    id += String(mfrc522.uid.uidByte[i], HEX);
  }
  return id;
}

// Returns true if UID of new card was read.
// Call getCardUid() to get it as string.
bool readCardInfo()
{
  return mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial();
}

void loop()
{
  if (readCardInfo())
  {
    String id = getCardUid();
    Serial.println("Card UID: " + id);

    // wait some time to debounce
    delay(1000);
  }
}
