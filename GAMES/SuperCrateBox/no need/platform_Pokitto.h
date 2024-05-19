#define POKITTO


#include "Pokitto.h"
#include "PokittoCookie.h"

#define _LCDWIDTH 110
#define _LCDHEIGHT 86

extern  Pokitto::Core pb;

void drawBitmapMono(uint16_t x, uint16_t y,uint8_t color, const uint8_t *buffer, uint8_t rotation=NOROT, uint8_t flip=NOFLIP)
{
    const uint8_t w = pgm_read_byte(buffer);
    const uint8_t h = pgm_read_byte(buffer + 1);
    buffer = buffer + 2; //add an offset to the pointer to start after the width and height
    int8_t i, j, //coordinates in the raw bitmap
            k, l, //coordinates in the rotated/flipped bitmap
            byteNum, bitNum, byteWidth = (w + 7) >> 3;

    rotation %= 4;

    for (i = 0; i < w; i++) {
        byteNum = i / 8;
        bitNum = i % 8;
        for (j = 0; j < h; j++) {
            if (pgm_read_byte(buffer + j * byteWidth + byteNum) & (B10000000 >> bitNum)) {
                switch (rotation) {
                    case NOROT: //no rotation
                        k = i;
                        l = j;
                        break;
                    case ROTCCW: //90° counter-clockwise
                        k = j;
                        l = w - i - 1;
                        break;
                    case ROT180: //180°
                        k = w - i - 1;
                        l = h - j - 1;
                        break;
                    case ROTCW: //90° clockwise
                        k = h - j - 1;
                        l = i;
                        break;
                }
                if (flip) {
                    flip %= 4;
                    if (flip & B00000001) { //horizontal flip
                        k = w - k - 1;
                    }
                    if (flip & B00000010) { //vertical flip
                        l = h - l;
                    }
                }
                k += x; //place the bitmap on the screen
                l += y;
                Pokitto::Core::display.setColor(color);
                Pokitto::Core::display.drawPixel(k, l);
            }
        }
    }
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#undef BLACK
#undef WHITE

 #define  BLACK         0
 #define  DARK_BLUE     1
 #define  DARK_PURPLE   2
 #define  DARK_GREEN    3

 #define  BROWN         4
 #define  DARK_GRAY     5
 #define  LIGHT_GRAY    6
 #define  WHITE         7

 #define  RED           8
 #define  ORANGE        9
 #define  YELLOW        10
 #define  GREEN         11

 #define  BLUE          12
 #define  INDIGO        13
 #define  PINK          14
 #define  PEACH         15

