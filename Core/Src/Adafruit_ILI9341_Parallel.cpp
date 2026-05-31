#include "Adafruit_ILI9341_Parallel.h"

Adafruit_ILI9341::Adafruit_ILI9341()
    : Adafruit_GFX(240, 320) {}

void Adafruit_ILI9341::begin(void) {
  LCD_init();
  setRotation(1);
}

void Adafruit_ILI9341::setRotation(uint8_t r) {
  Adafruit_GFX::setRotation(r);
  LCD_SetRotation(r);
}

uint8_t Adafruit_ILI9341::readcommand8(uint8_t command) {
  (void)command;
  return 0;
}

void Adafruit_ILI9341::drawPixel(int16_t x, int16_t y, uint16_t color) {
  LCD_DrawPixel(x, y, color);
}

void Adafruit_ILI9341::drawFastVLine(int16_t x, int16_t y, int16_t h,
                                     uint16_t color) {
  LCD_DrawFastVLine(x, y, h, color);
}

void Adafruit_ILI9341::drawFastHLine(int16_t x, int16_t y, int16_t w,
                                     uint16_t color) {
  LCD_DrawFastHLine(x, y, w, color);
}

void Adafruit_ILI9341::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                uint16_t color) {
  LCD_FillRect(x, y, w, h, color);
}

void Adafruit_ILI9341::fillScreen(uint16_t color) {
  LCD_FillScreen(color);
}
