#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// LCD connections to D1-Mini:
// - GND -> G
// - VCC -> 5V
// - SDA -> D2
// - SCL -> D1

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte heart[] = {
    B00000,
    B00000,
    B01010,
    B11111,
    B11111,
    B01110,
    B00100,
    B00000};

byte upperTwo[] = {
    B01100,
    B10010,
    B00100,
    B01000,
    B11110,
    B00000,
    B00000,
    B00000};

byte wlan[] = {
    B00000,
    B11111,
    B00001,
    B11101,
    B00101,
    B10101,
    B00000,
    B00000};

void setup()
{
  // on board LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  // lcd
  lcd.init();
  lcd.createChar(2, upperTwo);
  lcd.createChar(3, wlan);
  lcd.createChar(5, heart);
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("CO\x02-Ampel");

  lcd.setCursor(15, 0);
  lcd.write(3);
  lcd.setCursor(15,0);
  lcd.blink();

  digitalWrite(LED_BUILTIN, 1);
}

void loop()
{
}
