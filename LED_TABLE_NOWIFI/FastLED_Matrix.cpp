#include "FastLED_Matrix.h"

#include "Adafruit_GFX.h"
#include "FastLED.h"


#ifndef _BV
#define _BV(bit) (1<<(bit))
#endif

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

static const uint16_t numbertable[] = {
  0x7B6F, //0
  0x2492, //1
  0x73E7, //2
  0x79A7, //3
  0x49ED, //4
  0x79CF, //5
  0x7BCF, //6
  0x4927, //7
  0x7BEF, //8
  0x79EF, //9
  0x0410  //:
};

/*
  static const uint16_t alphafonttable[] PROGMEM =  {

  0b0000000000000001,
  0b0000000000000010,
  0b0000000000000100,
  0b0000000000001000,
  0b0000000000010000,
  0b0000000000100000,
  0b0000000001000000,
  0b0000000010000000,
  0b0000000100000000,
  0b0000001000000000,
  0b0000010000000000,
  0b0000100000000000,
  0b0001000000000000,
  0b0010000000000000,
  0b0100000000000000,
  0b1000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0001001011001001,
  0b0001010111000000,
  0b0001001011111001,
  0b0000000011100011,
  0b0000010100110000,
  0b0001001011001000,
  0b0011101000000000,
  0b0001011100000000,
  0b0000000000000000, //
  0b0000000000000110, // !
  0b0000001000100000, // "
  0b0001001011001110, // #
  0b0001001011101101, // $
  0b0000110000100100, // %
  0b0010001101011101, // &
  0b0000010000000000, // '
  0b0010010000000000, // (
  0b0000100100000000, // )
  0b0011111111000000, // *
  0b0001001011000000, // +
  0b0000100000000000, // ,
  0b0000000011000000, // -
  0b0000000000000000, // .
  0b0000110000000000, // /
  0b0000110000111111, // 0
  0b0000000000000110, // 1
  0b0000000011011011, // 2
  0b0000000010001111, // 3
  0b0000000011100110, // 4
  0b0010000001101001, // 5
  0b0000000011111101, // 6
  0b0000000000000111, // 7
  0b0000000011111111, // 8
  0b0000000011101111, // 9
  0b0001001000000000, // :
  0b0000101000000000, // ;
  0b0010010000000000, // <
  0b0000000011001000, // =
  0b0000100100000000, // >
  0b0001000010000011, // ?
  0b0000001010111011, // @
  0b0000000011110111, // A
  0b0001001010001111, // B
  0b0000000000111001, // C
  0b0001001000001111, // D
  0b0000000011111001, // E
  0b0000000001110001, // F
  0b0000000010111101, // G
  0b0000000011110110, // H
  0b0001001000000000, // I
  0b0000000000011110, // J
  0b0010010001110000, // K
  0b0000000000111000, // L
  0b0000010100110110, // M
  0b0010000100110110, // N
  0b0000000000111111, // O
  0b0000000011110011, // P
  0b0010000000111111, // Q
  0b0010000011110011, // R
  0b0000000011101101, // S
  0b0001001000000001, // T
  0b0000000000111110, // U
  0b0000110000110000, // V
  0b0010100000110110, // W
  0b0010110100000000, // X
  0b0001010100000000, // Y
  0b0000110000001001, // Z
  0b0000000000111001, // [
  0b0010000100000000, //
  0b0000000000001111, // ]
  0b0000110000000011, // ^
  0b0000000000001000, // _
  0b0000000100000000, // `
  0b0001000001011000, // a
  0b0010000001111000, // b
  0b0000000011011000, // c
  0b0000100010001110, // d
  0b0000100001011000, // e
  0b0000000001110001, // f
  0b0000010010001110, // g
  0b0001000001110000, // h
  0b0001000000000000, // i
  0b0000000000001110, // j
  0b0011011000000000, // k
  0b0000000000110000, // l
  0b0001000011010100, // m
  0b0001000001010000, // n
  0b0000000011011100, // o
  0b0000000101110000, // p
  0b0000010010000110, // q
  0b0000000001010000, // r
  0b0010000010001000, // s
  0b0000000001111000, // t
  0b0000000000011100, // u
  0b0010000000000100, // v
  0b0010100000010100, // w
  0b0010100011000000, // x
  0b0010000000001100, // y
  0b0000100001001000, // z
  0b0000100101001001, // {
  0b0001001000000000, // |
  0b0010010010001001, // }
  0b0000010100100000, // ~
  0b0011111111111111,

  };*/

void FastMatrix10x20::printDigit(uint8_t n, uint16_t X, uint16_t Y)
{
  for (uint8_t x = 0; x < 3; x++)
  {
    for (uint8_t y = 0; y < 5; y++)
    {
      uint8_t index = x + 3 * y;
      if (((numbertable[n] >> index) & 1)==1) 
      {
        drawPixel(X + x, Y + y, CRGB(255, 0, 0));
      }
    }
  }
}

void FastMatrix10x20::writeTime(uint8_t H, uint8_t M)
{
  printDigit(H/10,0,2);
  printDigit(H%10,4,2);
  printDigit(10,8,2);
  printDigit(M/10,12,2);
  printDigit(M%10,16,2);
}



void FastMatrix10x20::setBrightness(uint8_t b) {
}


void FastMatrix10x20::begin() {
}

void FastMatrix10x20::writeDisplay(void)
{
  for (uint8_t x = 0; x < COLUMN_COUNT; x++)    //We check each pixel, if it's supposed to be ON : Set corresponding LED ON, else turn it off
  {
    for (uint8_t y = 0; y < ROW_COUNT; y++)
    {
      uint8_t LED_Number = Mapping[y][x];
      if (LED_Number < StripLenght) this->leds[LED_Number] = OutputBuffer[y][x];
    }
  }
  FastLED.show();
}

void FastMatrix10x20::clear(void) {
  for (uint8_t x = 0; x < COLUMN_COUNT; x++)    //We check each pixel, if it's supposed to be ON : Set corresponding LED ON, else turn it off
  {
    for (uint8_t y = 0; y < ROW_COUNT; y++)
    {
      drawPixel(x, y, CRGB::Black);
    }
  }
}


FastMatrix10x20::FastMatrix10x20(void) : Adafruit_GFX(10, 20)
{
}

void FastMatrix10x20::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  drawPixel(x, y, CRGB((color >> 11 & 0b00011111), (color >> 5 & 0b00111111), (color & 0b00011111)));
}

void FastMatrix10x20::drawPixel(int16_t x, int16_t y, const struct CHSV& color)
{
  drawPixel(x, y, CRGB(color));
}

void FastMatrix10x20::drawPixel(int16_t x, int16_t y, const struct CRGB& color)
{
  // check rotation, move pixel around if necessary
  /*switch (getRotation()) {
    case 2:
      _swap_int16_t(x, y);
      x = COLUMN_COUNT - x - 1;
      break;
    case 3:
      x = COLUMN_COUNT - x - 1;
      y = ROW_COUNT - y - 1;
      break;
    case 0:
      _swap_int16_t(x, y);
      y = ROW_COUNT - y - 1;
      break;
    }*/

  if ((y < 0) || (y >= ROW_COUNT)) return;
  if ((x < 0) || (x >= COLUMN_COUNT)) return;
  OutputBuffer[y][x] = color;
}

