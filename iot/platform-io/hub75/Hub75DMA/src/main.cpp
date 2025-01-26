#include <Arduino.h>

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#define PANEL_RES_X 64 // Number of pixels wide of each INDIVIDUAL panel module.
#define PANEL_RES_Y 64 // 32     // Number of pixels tall of each INDIVIDUAL panel module.
#define PANEL_CHAIN 2  // Total number of panels chained one to another

// https://github.com/mrcodetastic/ESP32-HUB75-MatrixPanel-DMA?tab=readme-ov-file#2-wiring-the-esp32-to-an-led-matrix-panel
#define R1_PIN 25
#define G1_PIN 26
#define B1_PIN 27
#define R2_PIN 14
#define G2_PIN 12
#define B2_PIN 13

#define A_PIN 23
#define B_PIN 19
#define C_PIN 5
#define D_PIN 17
#define E_PIN 32 // -1 // IMPORTANT: Change to a valid pin if using a 64x64px panel.

#define LAT_PIN 4
#define OE_PIN 15
#define CLK_PIN 16

HUB75_I2S_CFG::i2s_pins _pins = {
    R1_PIN, G1_PIN, B1_PIN,
    R2_PIN, G2_PIN, B2_PIN,
    A_PIN, B_PIN, C_PIN, D_PIN, E_PIN,
    LAT_PIN, OE_PIN, CLK_PIN};

HUB75_I2S_CFG mxconfig(
    PANEL_RES_X, // module width
    PANEL_RES_Y, // module height
    PANEL_CHAIN, // Chain length
    _pins        // pin mapping
);

MatrixPanel_I2S_DMA *dma_display = nullptr;

void setup()
{
  // mxconfig.gpio.e = 18;
  // mxconfig.clkphase = false;
  // mxconfig.driver = HUB75_I2S_CFG::FM6126A;

  // Display Setup
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->begin();
  dma_display->setBrightness8(90); // 0-255
  dma_display->clearScreen();

  // myGREEN = dma_display->color565(0, 255, 0);
  // dma_display->fillScreen(myGREEN);

  // line red
  dma_display->drawLine(0, 0, dma_display->width() - 1, dma_display->height() - 1, dma_display->color444(15, 0, 0));

  // border
  dma_display->drawLine(0, 0, 0, 63, dma_display->color444(0, 15, 0));
  dma_display->drawLine(0, 0, 127, 0, dma_display->color444(0, 0, 15));
  dma_display->drawLine(127, 63, 0, 63, dma_display->color444(15, 15, 0));
  dma_display->drawLine(127, 63, 127, 0, dma_display->color444(0, 15, 15));

  // Text
  dma_display->setTextSize(1);     // size 1 == 8 pixels high
  dma_display->setTextWrap(false); // Don't wrap at end of line - will do ourselves
  dma_display->setCursor(5, 8);    // start at top left, with 8 pixel of spacing
  dma_display->print("Mischa möchte");

  dma_display->setTextSize(2);
  dma_display->setCursor(32, 32);
  dma_display->print("Testen");

  // End
  dma_display->drawPixel(0, 0, dma_display->color444(15, 15, 15));
  dma_display->drawPixel(dma_display->width() - 1, dma_display->height() - 1, dma_display->color444(15, 0, 15));
}

void loop()
{
}
