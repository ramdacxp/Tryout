#include <Arduino.h>

// This is how many color levels the display shows - the more the slower the update
// #define PxMATRIX_COLOR_DEPTH 8

// Defines the buffer height / the maximum height of the matrix
// #define PxMATRIX_MAX_HEIGHT 64

// Defines the buffer width / the maximum width of the matrix
// #define PxMATRIX_MAX_WIDTH 64

// Defines how long we display things by default
// #define PxMATRIX_DEFAULT_SHOWTIME 30

// Defines the speed of the SPI bus (reducing this may help if you experience noisy images)
// #define PxMATRIX_SPI_FREQUENCY 20000000

// Creates a second buffer for backround drawing (doubles the required RAM)
// #define PxMATRIX_double_buffer true

#include <PxMatrix.h>

// Pins for LED MATRIX
#define P_LAT 22
#define P_A 19
#define P_B 23
#define P_C 18
#define P_D 5
#define P_E 15
#define P_OE 2
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// This defines the 'on' time of the display is us. The larger this number,
// the brighter the display. If too large the ESP will crash
// uint8_t display_draw_time = 60; // 30-70 is usually fine
uint8_t display_draw_time = 10; // 30-70 is usually fine

// PxMATRIX display(32, 16, P_LAT, P_OE, P_A, P_B, P_C);
// PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);
#define matrix_width 64
#define matrix_height 64
PxMATRIX display(matrix_width, matrix_height, P_LAT, P_OE, P_A, P_B, P_C, P_D, P_E);

// Some standard colors
uint16_t myRED = display.color565(255, 0, 0);
uint16_t myGREEN = display.color565(0, 255, 0);
uint16_t myBLUE = display.color565(0, 0, 255);
uint16_t myWHITE = display.color565(255, 255, 255);
uint16_t myYELLOW = display.color565(255, 255, 0);
uint16_t myCYAN = display.color565(0, 255, 255);
uint16_t myMAGENTA = display.color565(255, 0, 255);
uint16_t myBLACK = display.color565(0, 0, 0);

uint16_t myCOLORS[8] = {myRED, myGREEN, myBLUE, myWHITE, myYELLOW, myCYAN, myMAGENTA, myBLACK};

void IRAM_ATTR display_updater()
{
  // Increment the counter and set the time of ISR
  portENTER_CRITICAL_ISR(&timerMux);
  display.display(display_draw_time);
  portEXIT_CRITICAL_ISR(&timerMux);
}

void display_update_enable(bool is_enable)
{
  if (is_enable)
  {
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &display_updater, true);
    timerAlarmWrite(timer, 4000, true);
    timerAlarmEnable(timer);
  }
  else
  {
    timerDetachInterrupt(timer);
    timerAlarmDisable(timer);
  }
}

void setup()
{
  Serial.begin(9600);

  // Define your display layout 1/32 step
  display.begin(32);

  // Define multiplex implemention here {BINARY, STRAIGHT} (default is BINARY)
  // display.setMuxPattern(BINARY);

  // Set the multiplex pattern {LINE, ZIGZAG,ZZAGG, ZAGGIZ, WZAGZIG, VZAG, ZAGZIG} (default is LINE)
  // display.setScanPattern(LINE);

  // Rotate display
  // display.setRotate(true);

  // Flip display
  // display.setFlip(true);

  // Control the minimum color values that result in an active pixel
  // display.setColorOffset(5, 5,5);

  // Set the multiplex implemention {BINARY, STRAIGHT} (default is BINARY)
  // display.setMuxPattern(BINARY);

  // Set the color order {RRGGBB, RRBBGG, GGRRBB, GGBBRR, BBRRGG, BBGGRR} (default is RRGGBB)
  // display.setColorOrder(RRGGBB);

  // Set the time in microseconds that we pause after selecting each mux channel
  // (May help if some rows are missing / the mux chip is too slow)
  // display.setMuxDelay(0,1,0,0,0);

  // Set the number of panels that make up the display area width (default is 1)
  // display.setPanelsWidth(2);

  // Set the brightness of the panels (default is 255)
  display.setBrightness(128);

  // Set driver chip type
  // display.setDriverChip(FM6124);

  display.clearDisplay();

  // display.drawRect(0, 0, 64, 30, myRED);
  // display.drawRect(0, 32, 32, 30, myGREEN);
  // display.drawRect(32, 32, 32, 30, myBLUE);

  display.setTextColor(myCYAN);
  display.setCursor(2, 0);
  display.print("Pixel");

  display.setTextColor(myMAGENTA);
  display.setCursor(2, 8);
  display.print("Time");

  display.setTextColor(myGREEN);
  display.setCursor(2, 16);
  display.print("Testzeile");

  display.setTextColor(myBLUE);
  display.setCursor(2, 24);
  display.print("mit ein");

  display.setTextColor(myYELLOW);
  display.setCursor(2, 32);
  display.print("paar");

  display.setTextColor(myRED);
  display.setCursor(2, 40);
  display.print("weiteren");

  display.setTextColor(myMAGENTA);
  display.setCursor(2, 48);
  display.print("Informationen");

  // Rainbow
  for (int xx = 0; xx < 16; xx++)
  {
    display.drawLine(xx + 40, 0, xx + 40, 5, display.color565(xx * 16, 0, 0));
    display.drawLine(xx + 40, 6, xx + 40, 10, display.color565(0, xx * 16, 0));
    display.drawLine(xx + 40, 11, xx + 40, 15, display.color565(0, 0, xx * 16));
  }

  display.drawLine(0, 0, 63, 0, myRED);
  display.drawLine(0, 0, 0, 63, myGREEN);
  display.drawLine(63, 0, 63, 63, myBLUE);
  display.drawLine(0, 0, 63, 63, myYELLOW);

  display_update_enable(true);
}

unsigned long last_draw = 0;
void scroll_text(uint8_t ypos, unsigned long scroll_delay, String text, uint8_t colorR, uint8_t colorG, uint8_t colorB)
{
  uint16_t text_length = text.length();
  display.setTextWrap(false); // we don't wrap text so it scrolls nicely
  display.setTextSize(1);
  display.setRotation(0);
  display.setTextColor(display.color565(colorR, colorG, colorB));

  // Asuming 5 pixel average character width
  for (int xpos = matrix_width; xpos > -(matrix_width + text_length * 5); xpos--)
  {
    display.setTextColor(display.color565(colorR, colorG, colorB));
    display.clearDisplay();
    display.setCursor(xpos, ypos);
    display.println(text);
    delay(scroll_delay);
    yield();

    // This might smooth the transition a bit if we go slow
    // display.setTextColor(display.color565(colorR/4,colorG/4,colorB/4));
    // display.setCursor(xpos-1,ypos);
    // display.println(text);

    delay(scroll_delay / 5);
    yield();
  }
}

void loop()
{
  // scroll_text(1, 50, "Hello World! Das ist ein Test", 96, 96, 250);
}