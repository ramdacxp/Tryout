# LCD Display 162C BL (4-Bit Mode)

## Hardware Info

![Hardware](hardware.png)

* [LCD 162C BL LCD-Modul](https://www.reichelt.de/lcd-modul-2x16-h-5-6mm-bl-ws-m-bel--lcd-162c-bl-p53941.html) (Reichelt, 11 EUR)

## Pin Layout

Pin layout example when connected to a WeMos D1 Mini.  
As the pin GPIO 2 (D4) of the D1 Mini is connected to the built-in LED, it is not used.

| Pin LCD | Description         | Connected to                 | Code |
|---------|---------------------|------------------------------|------|
| 1       | VSS                 | GND                          |      |
| 2       | VDD                 | +5V                          |      |
| 3       | VEE                 | Poti 10K between GND and +5V |      |
| 4       | RS                  | D1-Mini D3                   |      |
| 5       | R/W                 | GND                          |      |
| 6       | Enable              | D1-Mini D1                   |      |
| 7       | D0 (LSB)            | not used in 4 bit mode       |      |
| 8       | D1                  | not used in 4 bit mode       |      |
| 9       | D2                  | not used in 4 bit mode       |      |
| 10      | D3                  | not used in 4 bit mode       |      |
| 11      | D4                  | D1-Mini D2                   |      |
| 12      | D5                  | D1-Mini D5                   |      |
| 13      | D6                  | D1-Mini D6                   |      |
| 14      | D7 (MSB)            | D1-Mini D7                   |      |
| 15      | A / LED Backlight + | GND                          |      |
| 16      | K / LED Backlight - | via R270 to +5V              |      |

![Pin Layout](schaltung.png)

```cpp
// D1 Mini mapping of data pins (Dx as printed on the board) to GPIO numbers
#define D1MINI_D0 16
#define D1MINI_D1 5
#define D1MINI_D2 4
#define D1MINI_D3 0
#define D1MINI_D4 2
#define D1MINI_D5 14
#define D1MINI_D6 12
#define D1MINI_D7 13
#define D1MINI_D8 15

// LCD Connections
#define LCD_RS D1MINI_D3
#define LCD_E  D1MINI_D2
#define LCD_D4 D1MINI_D1
#define LCD_D5 D1MINI_D7
#define LCD_D6 D1MINI_D6
#define LCD_D7 D1MINI_D5

// Usage of the library
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
lcd.begin(16, 2);
lcd.print("Hallo Test");
```

## Char map

Use `lcd.print("\xE1");` to output the german umlaut `ä`.

![Charmap](charmap.png)

## Code Samples

* <http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld>
