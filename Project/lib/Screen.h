#ifndef SCREEN_H
#define SCREEN_H

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

class Screen {
public:
    Screen(uint8_t cs, uint8_t dc, uint8_t rst) : tft(cs, dc, rst) {}

    void begin() {
        tft.init(240, 320);
        tft.fillScreen(ST77XX_BLACK);
    }

private:
  Adafruit_ST7789 tft;
}

#endif // SCREEN_H
