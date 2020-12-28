#include <Arduino.h>
#include <LiquidCrystal.h>

/*******************************************************************************
 * Based on: http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld
*
 * LCD 1 VSS -> GND
 * LCD 2 VDD -> +5V
 * LCD 3 VEE -> Poti 10K between GND and +5V
 * LCD 4 RS -> Mini D3
 * LCD 5 R/W -> GND
 * LCD 6 Enable -> Mini D1
 * LCD 7 D0 -> not used in 4 bit mode
 * LCD 8 D1 -> not used in 4 bit mode
 * LCD 9 D2 -> not used in 4 bit mode
 * LCD 10 D3 -> not used in 4 bit mode
 * LCD 11 D4 -> Mini D2
 * LCD 12 D5 -> Mini D5
 * LCD 13 D6 -> Mini D6
 * LCD 14 D7 -> Mini D7
 * LCD 15 A LED Backlight -> GND
 * LCD 16 K LED Backlight -> via R270 to +5V
 *
 * D1 Mini C defines use the GPIO values, not the Dxx labels printed on the board.
 * - GPIO 0 (D3) is used while flashing (try to avoid this)
 * - GPIO 2 (D4) is connected to built in LED.
 ******************************************************************************/
#define D1MINI_D0 16
#define D1MINI_D1 5
#define D1MINI_D2 4
#define D1MINI_D3 0
#define D1MINI_D4 2
#define D1MINI_D5 14
#define D1MINI_D6 12
#define D1MINI_D7 13
#define D1MINI_D8 15

// Platine
#define LCD_RS D1MINI_D3
#define LCD_E D1MINI_D2
#define LCD_D4 D1MINI_D1
#define LCD_D5 D1MINI_D7
#define LCD_D6 D1MINI_D6
#define LCD_D7 D1MINI_D5

// Breadboard
// #define LCD_RS D1MINI_D3
// #define LCD_E D1MINI_D1
// #define LCD_D4 D1MINI_D2
// #define LCD_D5 D1MINI_D5
// #define LCD_D6 D1MINI_D6
// #define LCD_D7 D1MINI_D7

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup()
{
  // on board LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  // init lcd
  lcd.begin(16, 2);
  lcd.print("Hallo Test");
}

void loop()
{
  digitalWrite(LED_BUILTIN, 1);
  delay(500);
  digitalWrite(LED_BUILTIN, 0);
  delay(500);

  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
}
