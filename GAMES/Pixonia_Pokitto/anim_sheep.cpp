

/*
 * BMP image as 4bpp (16 colour index) data
 */

#include <stdint.h>
#include "Pixonia.h"

PROGMEM const uint16_t anim_sheep_pal[] = {
22530,12922,10764,9284,13670,20137,65312,41728,33280,65535,46486,38066,29614,0,63488,63519
};

PROGMEM const uint8_t anim_sheep[] = {
8,8,
255,255,255,255,249,153,153,156,
250,154,170,154,250,170,9,200,
250,170,170,194,248,170,170,175,
255,255,160,15,255,255,15,255,

};
