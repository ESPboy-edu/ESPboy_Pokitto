

/*
 * BMP image as 4bpp (16 colour index) data
 */

#include <stdint.h>
#include "Pixonia.h"

// map colors correctly
// 3 - 2
// 8 - 5
// 11- 4
// 6 - 1
// 0 - 3
// 5 - 10
// 9 = 9


PROGMEM const uint16_t pokulous_pal[] = {
22530,
12922,
10764,
9284,

13670, //4
20137,
0, // GOLD !!
41728,

33280, //8
65535,
46486,
38066,

29614, //12
0,
63488,
63519
};

PROGMEM const uint16_t night_palette_orig[] = {
18697,33104,18506,22830,27280,56830,2249,8517,552,2145,6371,2859,257,545,18952,0
};

PROGMEM const uint16_t night_palette[] = {
18697, //0
2249,  //33104, //1
22830, //18506, //2
18697, //22830, //3
2859,  //27280, //4
552,   //56830, //5
65312, // GOLD!! 2249,  //6
8517,  //7
552,   //8
65535, //2145,  //9
27280, //56830, //6371,  //10 //too bright !
2859,  //11
257,   //12
545,   //13
63488, //14 Werewolf eyes
0      //15
};


