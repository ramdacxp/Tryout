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

  Serial.print(F("Init: SPI ... "));
  SPI.begin();

  Serial.print(F("RFID ... "));
  mfrc522.PCD_Init();
  delay(4);

  Serial.print(F("Max-Antenna-Gain ("));
  Serial.print(mfrc522.RxGain_max);
  Serial.print(F(") ... "));
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);

  Serial.print(F("Gain: "));
  byte gain = mfrc522.PCD_GetAntennaGain();
  Serial.println(gain);

  mfrc522.PCD_DumpVersionToSerial();
  Serial.println(F("Init done."));
}

// Tries to read card uid.
// Returns empty string if no or same card present.
String getCardId()
{
  String id = "";

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
  {
    return id;
  }

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

ulong lastEvent = 0;
String cardId = "";

bool checkTriggerCardEvent()
{
  String currentCard = getCardId();
  if (currentCard != "")
  {
    ulong ts = millis();
    if (ts > lastEvent + 5000)
    {
      lastEvent = ts;
      Serial.print(F("Card: "));
      Serial.println(currentCard);
      return true;
    }
  }
  return false;
}

void loop()
{
  checkTriggerCardEvent();
  delay(1000);
}
