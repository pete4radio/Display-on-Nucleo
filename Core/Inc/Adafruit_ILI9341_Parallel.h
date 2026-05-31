#ifndef ADAFRUIT_ILI9341_PARALLEL_H
#define ADAFRUIT_ILI9341_PARALLEL_H

#include <stdint.h>
#include "../../Adafruit_GFX_Library/Adafruit_GFX.h"
#include "lcd_touch.h"

#define ILI9341_BLACK 0x0000
#define ILI9341_NAVY 0x000F
#define ILI9341_DARKGREEN 0x03E0
#define ILI9341_DARKCYAN 0x03EF
#define ILI9341_MAROON 0x7800
#define ILI9341_PURPLE 0x780F
#define ILI9341_OLIVE 0x7BE0
#define ILI9341_LIGHTGREY 0xC618
#define ILI9341_DARKGREY 0x7BEF
#define ILI9341_BLUE 0x001F
#define ILI9341_GREEN 0x07E0
#define ILI9341_CYAN 0x07FF
#define ILI9341_RED 0xF800
#define ILI9341_MAGENTA 0xF81F
#define ILI9341_YELLOW 0xFFE0
#define ILI9341_WHITE 0xFFFF
#define ILI9341_ORANGE 0xFD20
#define ILI9341_PINK 0xFE19

class Adafruit_ILI9341 : public Adafruit_GFX {
public:
  Adafruit_ILI9341();
  void begin(void);
  void setRotation(uint8_t r) override;
  uint8_t readcommand8(uint8_t command);

  void drawPixel(int16_t x, int16_t y, uint16_t color) override;
  void drawFastVLine(int16_t x, int16_t y, int16_t h,
                     uint16_t color) override;
  void drawFastHLine(int16_t x, int16_t y, int16_t w,
                     uint16_t color) override;
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                uint16_t color) override;
  void fillScreen(uint16_t color) override;
};

#endif // ADAFRUIT_ILI9341_PARALLEL_H
