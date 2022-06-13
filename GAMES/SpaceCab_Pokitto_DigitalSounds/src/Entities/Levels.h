#pragma once

#include "../Utils/Constants.h"
#include "../Utils/Structs.h"

#ifdef INC_LEVEL_DETAILS

PROGMEM constexpr  uint8_t level1MapX[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x10, 0x0B, // Length / Width
0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xAA, 0xAA, 0xAA, 0xAA, 0x40, 0x00, 
0x33, 0x38, 0x88, 0x88, 0x88, 0x88, 0x83, 0x33, 
0x04, // Starting Positions
0x04, 0x09, 0x0B, 0x09,
0x04, // Ending Positions
0x03, 0x09, 0x0C, 0x09,
0x00, 0x00, // Level Offset x / y
0x18, 0x2D, // Player Offset
0x14, // Fuel ( *  10)
0x00, // Fares Required
0x00, // Name Offset
0x02, // Number of positions
0x06, 0x09, // Gate Left / Right
0x00, // Gate Interval * 10

};

#endif