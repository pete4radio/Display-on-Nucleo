#include "mock_ili9341_demo.h"
#include "Adafruit_ILI9341_Parallel.h"
#include "stm32l4xx_hal.h"

static Adafruit_ILI9341 tft;

static uint32_t micros(void) {
  return HAL_GetTick() * 1000u;
}

static void delay(uint32_t ms) {
  HAL_Delay(ms);
}

static unsigned long testFillScreen(void) {
  unsigned long start = micros();
  tft.fillScreen(ILI9341_BLACK);
  yield();
  tft.fillScreen(ILI9341_RED);
  yield();
  tft.fillScreen(ILI9341_GREEN);
  yield();
  tft.fillScreen(ILI9341_BLUE);
  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();
  return micros() - start;
}

static unsigned long testText(void) {
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.println(1234.56f);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(3);
  tft.println(0xDEADBEEF, 16);
  tft.println();
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts,");
  tft.println("see if I don't!");
  return micros() - start;
}

static unsigned long testLines(uint16_t color) {
  unsigned long start;
  int x1, y1, x2, y2, w = tft.width(), h = tft.height();

  tft.fillScreen(ILI9341_BLACK);
  yield();

  x1 = y1 = 0;
  y2 = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6)
    tft.drawLine(x1, y1, x2, y2, color);
  x2 = w - 1;
  for (y2 = 0; y2 < h; y2 += 6)
    tft.drawLine(x1, y1, x2, y2, color);
  unsigned long t = micros() - start;

  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();

  x1 = w - 1;
  y1 = 0;
  y2 = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6)
    tft.drawLine(x1, y1, x2, y2, color);
  x2 = 0;
  for (y2 = 0; y2 < h; y2 += 6)
    tft.drawLine(x1, y1, x2, y2, color);
  t += micros() - start;

  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();

  x1 = 0;
  y1 = h - 1;
  y2 = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6)
    tft.drawLine(x1, y1, x2, y2, color);
  x2 = w - 1;
  for (y2 = 0; y2 < h; y2 += 6)
    tft.drawLine(x1, y1, x2, y2, color);
  t += micros() - start;

  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();

  x1 = w - 1;
  y1 = h - 1;
  y2 = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6)
    tft.drawLine(x1, y1, x2, y2, color);
  x2 = 0;
  for (y2 = 0; y2 < h; y2 += 6)
    tft.drawLine(x1, y1, x2, y2, color);

  yield();
  return t;
}

static unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for (y = 0; y < h; y += 5)
    tft.drawFastHLine(0, y, w, color1);
  for (x = 0; x < w; x += 5)
    tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

static unsigned long testRects(uint16_t color) {
  unsigned long start;
  int n, i, i2, cx = tft.width() / 2, cy = tft.height() / 2;

  tft.fillScreen(ILI9341_BLACK);
  n = (tft.width() < tft.height()) ? tft.width() : tft.height();
  start = micros();
  for (i = 2; i < n; i += 6) {
    i2 = i / 2;
    tft.drawRect(cx - i2, cy - i2, i, i, color);
  }

  return micros() - start;
}

static unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int n, i, i2, cx = tft.width() / 2 - 1, cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  n = (tft.width() < tft.height()) ? tft.width() : tft.height();
  for (i = n; i > 0; i -= 6) {
    i2 = i / 2;
    start = micros();
    tft.fillRect(cx - i2, cy - i2, i, i, color1);
    t += micros() - start;
    tft.drawRect(cx - i2, cy - i2, i, i, color2);
    yield();
  }

  return t;
}

void runMockILI9341Demo(void) {
  tft.begin();
  testFillScreen();
  delay(500);
  testText();
  delay(3000);
  testLines(ILI9341_CYAN);
  delay(500);
  testFastLines(ILI9341_RED, ILI9341_BLUE);
  delay(500);
  testRects(ILI9341_GREEN);
  delay(500);
  testFilledRects(ILI9341_YELLOW, ILI9341_MAGENTA);
  delay(500);
  tft.fillScreen(ILI9341_BLACK);
  for (uint8_t rotation = 0; rotation < 4; rotation++) {
    tft.setRotation(rotation);
    testText();
    delay(1000);
  }
}
