#ifndef SCREEN_H
#define SCREEN_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

class Screen {
public:
    Screen(uint8_t dc, uint8_t rst, uint8_t cs = -1) : tft(dc, rst, cs) {}
    void begin() {
        tft.init(240, 240);
        tft.fillScreen(ST77XX_BLACK);
    }
    void testDisplay() {
        tft.fillScreen(ST77XX_BLACK);
        testDrawText("Lorem ipsum dolor sit amet", ST77XX_WHITE);
        delay(1000);
        tftPrintTest();
        delay(4000);
        tft.drawPixel(tft.width() / 2, tft.height() / 2, ST77XX_GREEN);
        delay(500);
        testLines(ST77XX_YELLOW);
        delay(500);
        testFastLines(ST77XX_RED, ST77XX_BLUE);
        delay(500);
        testDrawRects(ST77XX_GREEN);
        delay(500);
        testFillRects(ST77XX_YELLOW, ST77XX_MAGENTA);
        delay(500);
        tft.fillScreen(ST77XX_BLACK);
        testFillCircles(10, ST77XX_BLUE);
        testDrawCircles(10, ST77XX_WHITE);
        delay(500);
        testRoundRects();
        delay(500);
        testTriangles();
        delay(500);
        mediaButtons();
        delay(500);
    }

private:
    Adafruit_ST7789 tft;
    void testLines(uint16_t color) {
        tft.fillScreen(ST77XX_BLACK);
        for (int16_t x = 0; x < tft.width(); x += 6) {
            tft.drawLine(0, 0, x, tft.height() - 1, color);
        }
        for (int16_t y = 0; y < tft.height(); y += 6) {
            tft.drawLine(0, 0, tft.width() - 1, y, color);
        }
    }
    void testDrawText(const char *text, uint16_t color) {
        tft.setCursor(0, 0);
        tft.setTextColor(color);
        tft.setTextWrap(true);
        tft.print(text);
    }
    void testFastLines(uint16_t color1, uint16_t color2) {
        tft.fillScreen(ST77XX_BLACK);
        for (int16_t y = 0; y < tft.height(); y += 5) {
            tft.drawFastHLine(0, y, tft.width(), color1);
        }
        for (int16_t x = 0; x < tft.width(); x += 5) {
            tft.drawFastVLine(x, 0, tft.height(), color2);
        }
    }
    void testDrawRects(uint16_t color) {
        tft.fillScreen(ST77XX_BLACK);
        for (int16_t x = 0; x < tft.width(); x += 6) {
            tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color);
        }
    }
    void testFillRects(uint16_t color1, uint16_t color2) {
        tft.fillScreen(ST77XX_BLACK);
        for (int16_t x = tft.width() - 1; x > 6; x -= 6) {
            tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color1);
            tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color2);
        }
    }
    void testFillCircles(uint8_t radius, uint16_t color) {
        for (int16_t x = radius; x < tft.width(); x += radius * 2) {
            for (int16_t y = radius; y < tft.height(); y += radius * 2) {
                tft.fillCircle(x, y, radius, color);
            }
        }
    }
    void testDrawCircles(uint8_t radius, uint16_t color) {
        for (int16_t x = 0; x < tft.width() + radius; x += radius * 2) {
            for (int16_t y = 0; y < tft.height() + radius; y += radius * 2) {
                tft.drawCircle(x, y, radius, color);
            }
        }
    }
    void testTriangles() {
        tft.fillScreen(ST77XX_BLACK);
        int color = 0xF800;
        int t;
        int w = tft.width() / 2;
        int x = tft.height() - 1;
        int y = 0;
        int z = tft.width();
        for (t = 0; t <= 15; t++) {
            tft.drawTriangle(w, y, y, x, z, x, color);
            x -= 4;
            y += 4;
            z -= 4;
            color += 100;
        }
    }
    void testRoundRects() {
        tft.fillScreen(ST77XX_BLACK);
        int color = 100;
        int i;
        int t;
        for (t = 0; t <= 4; t += 1) {
            int x = 0;
            int y = 0;
            int w = tft.width() - 2;
            int h = tft.height() - 2;
            for (i = 0; i <= 16; i += 1) {
                tft.drawRoundRect(x, y, w, h, 5, color);
                x += 2;
                y += 3;
                w -= 4;
                h -= 6;
                color += 1100;
            }
            color += 100;
        }
    }
    void tftPrintTest() {
        tft.setTextWrap(false);
        tft.fillScreen(ST77XX_BLACK);
        tft.setCursor(0, 30);
        tft.setTextColor(ST77XX_RED);
        tft.setTextSize(1);
        tft.println("Hello World!");
        tft.setTextColor(ST77XX_YELLOW);
        tft.setTextSize(2);
        tft.println("Hello World!");
        tft.setTextColor(ST77XX_GREEN);
        tft.setTextSize(3);
        tft.println("Hello World!");
        tft.setTextColor(ST77XX_BLUE);
        tft.setTextSize(4);
        tft.print(1234.567);
        delay(1500);
        tft.setCursor(0, 0);
        tft.fillScreen(ST77XX_BLACK);
        tft.setTextColor(ST77XX_WHITE);
        tft.setTextSize(0);
        tft.println("Hello World!");
        tft.setTextSize(1);
        tft.setTextColor(ST77XX_GREEN);
        tft.print(3.1415926, 6);
        tft.println(" Want pi?");
        tft.println(" ");
        tft.print(8675309, HEX);
        tft.println(" Print HEX!");
        tft.println(" ");
        tft.setTextColor(ST77XX_WHITE);
        tft.println("Sketch has been");
        tft.println("running for: ");
        tft.setTextColor(ST77XX_MAGENTA);
        tft.print(millis() / 1000);
        tft.setTextColor(ST77XX_WHITE);
        tft.print(" seconds.");
    }
    void mediaButtons() {
        tft.fillScreen(ST77XX_BLACK);
        tft.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
        tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
        delay(500);
        tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
        tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
        tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
        delay(500);
        tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
        delay(50);
        tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
        tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
        tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
    }
};

#endif // SCREEN_H
