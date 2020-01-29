#include <Arduino.h>

// SPI header is needed on top of the Adafruit headers if using PlatformIO.
// See: https://community.platformio.org/t/spi-h-for-adafruit-16x8-led-matrix/11699

#include <SPI.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

String text = "    Bitte nicht wundern **** DAS IST EIN TEST **** 1234 **** ENDE   ";

// -------------------------------------------------------------------------------------------------------------------------------
void setup(void)
{
  // default adress if no jumper is set
  alpha4.begin(0x70);

  alpha4.writeDigitRaw(3, 0x0);
  alpha4.writeDigitRaw(0, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(0, 0x0);
  alpha4.writeDigitRaw(1, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(1, 0x0);
  alpha4.writeDigitRaw(2, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(2, 0x0);
  alpha4.writeDigitRaw(3, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);

  alpha4.clear();
  alpha4.writeDisplay();
}

unsigned int i = 0;

// -------------------------------------------------------------------------------------------------------------------------------
void loop(void)
{
  alpha4.writeDigitAscii(0, text[i]);
  alpha4.writeDigitAscii(1, text[i + 1]);
  alpha4.writeDigitAscii(2, text[i + 2]);
  alpha4.writeDigitAscii(3, text[i + 3]);
  alpha4.writeDisplay();
  delay(200);

  i++;
  if (i > (text.length() - 4))
    i = 0;

  // display every character,
  // for (uint8_t i = '!'; i <= 'z'; i++)
  // {
  //   alpha4.writeDigitAscii(0, i);
  //   alpha4.writeDigitAscii(1, i + 1);
  //   alpha4.writeDigitAscii(2, i + 2);
  //   alpha4.writeDigitAscii(3, i + 3);
  //   alpha4.writeDisplay();

  //   delay(300);
  // }
}