#include <Arduino.h>

#include <MD_MAX72xx.h>
#include <SPI.h>

/*******************************************************************************
 * D1 Mini C defines use the GPIO values, not the Dxx labels printed on the board.
 * GPIO 2 (D4) is connected to the built in LED; also available as LED_BUILTIN.
 ******************************************************************************/
#define D1MINI_D0 16
#define D1MINI_D1 5
#define D1MINI_D2 4
#define D1MINI_D3 0
// #define D1MINI_D4 2 // internal LED, do not use
#define D1MINI_D5 14
#define D1MINI_D6 12
#define D1MINI_D7 13
#define D1MINI_D8 15

// Matrix on SPI pins
#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES 1

#define CLK_PIN   D1MINI_D5 // or SCK
#define DATA_PIN  D1MINI_D7 // or MOSI
#define CS_PIN    D1MINI_D8 // or SS

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void scrollText(const char *p)
{
  uint8_t charWidth;
  uint8_t cBuf[8];  // this should be ok for all built-in fonts

  mx.clear();

  while (*p != '\0')
  {
    charWidth = mx.getChar(*p++, sizeof(cBuf) / sizeof(cBuf[0]), cBuf);

    for (uint8_t i=0; i<=charWidth; i++)	// allow space between characters
    {
      mx.transform(MD_MAX72XX::TSL);
      if (i < charWidth)
        mx.setColumn(0, cBuf[i]);
      delay(100);
    }
  }
}

void setup()
{
  // on board LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  // Matrix
  mx.begin();
  mx.clear();
  mx.control(MD_MAX72XX::INTENSITY, 2);
  mx.setPoint(1, 1, true);

  // init done
  delay(1000);
  digitalWrite(LED_BUILTIN, 1);
}

void loop()
{
  scrollText("Hello World!  ");
}
