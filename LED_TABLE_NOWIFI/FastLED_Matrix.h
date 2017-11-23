#ifndef FastLED_Matrix_h
#define FastLED_Matrix_h

#include "Adafruit_GFX.h"
#include "FastLED.h"
#include "define.h"

#define HT16K33_BLINK_CMD 0x80
#define HT16K33_BLINK_DISPLAYON 0x01
#define HT16K33_BLINK_OFF 0
#define HT16K33_BLINK_2HZ  1
#define HT16K33_BLINK_1HZ  2
#define HT16K33_BLINK_HALFHZ  3

#define HT16K33_CMD_BRIGHTNESS 0xE0


class FastMatrix10x20 : public Adafruit_GFX {
  public:
    CRGB leds[NUM_LEDS];
    uint16_t StripLenght = NUM_LEDS;
    FastMatrix10x20(void);
    void begin();
    void setBrightness(uint8_t b);
    void writeDisplay(void);
    void clear(void);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void drawPixel(int16_t x, int16_t y, const struct CHSV& color);
    void drawPixel(int16_t x, int16_t y, const struct CRGB& color);
    void printDigit(uint8_t n, uint16_t X, uint16_t Y);
    void writeTime(uint8_t H, uint8_t M);
    CRGB OutputBuffer[ROW_COUNT][COLUMN_COUNT];

    void init(uint8_t a);

  protected:
    // Mapping is used to convert Pixel coordinates {Col;Row} to pixel strip number. 
    uint8_t Mapping[ROW_COUNT][COLUMN_COUNT] =
    {
      {19, 20, 59, 60, 99, 100, 139, 140, 179, 180},
      {18, 21, 58, 61, 98, 101, 138, 141, 178, 181},
      {17, 22, 57, 62, 97, 102, 137, 142, 177, 182},
      {16, 23, 56, 63, 96, 103, 136, 143, 176, 183},
      {15, 24, 55, 64, 95, 104, 135, 144, 175, 184},
      {14, 25, 54, 65, 94, 105, 134, 145, 174, 185},
      {13, 26, 53, 66, 93, 106, 133, 146, 173, 186},
      {12, 27, 52, 67, 92, 107, 132, 147, 172, 187},
      {11, 28, 51, 68, 91, 108, 131, 148, 171, 188},
      {10, 29, 50, 69, 90, 109, 130, 149, 170, 189},
      {9, 30, 49, 70, 89, 110, 129, 150, 169, 190},
      {8, 31, 48, 71, 88, 111, 128, 151, 168, 191},
      {7, 32, 47, 72, 87, 112, 127, 152, 167, 192},
      {6, 33, 46, 73, 86, 113, 126, 153, 166, 193},
      {5, 34, 45, 74, 85, 114, 125, 154, 165, 194},
      {4, 35, 44, 75, 84, 115, 124, 155, 164, 195},
      {3, 36, 43, 76, 83, 116, 123, 156, 163, 196},
      {2, 37, 42, 77, 82, 117, 122, 157, 162, 197},
      {1, 38, 41, 78, 81, 118, 121, 158, 161, 198},
      {0, 39, 40, 79, 80, 119, 120, 159, 160, 199},
    };

};

#endif


