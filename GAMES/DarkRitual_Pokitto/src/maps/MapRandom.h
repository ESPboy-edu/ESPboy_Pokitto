#pragma once

#include "Pokitto.h"
#include "MapRandom_Size_00.h"
#include "MapRandom_Size_01.h"
#include "MapRandom_Size_02.h"
#include "MapRandom_Size_03.h"


using PC = Pokitto::Core;
using PD = Pokitto::Display;


/*
Bit 7       Blank segment.
Bit 6       Any Segment from the nominated Type.
Bit 5       Specify a specific segment (over two bytes, sgement type, index)
Bit 4 .. 0  Segment specification (range 0 - 31).
*/

#define BLANK_SEG   128
#define ANY_SEG     64
#define THIS_SEG    32
#define SEG_00      0
#define SEG_01      1
#define SEG_02      2
#define SEG_03      3
#define SEG_04      4
#define SEG_05      5
#define SEG_06      6
#define SEG_07      7
#define SEG_08      8
#define SEG_09      9
#define SEG_10      10
#define SEG_11      11
#define SEG_12      12
#define SEG_13      13
#define SEG_14      14
#define SEG_15      15

/* -------------------------------------------------------------------------------------

Type 0       1         2         3         4         5         6         7         8   
.......   .......   .......   .......   .......   .......   .......   .......   .......
.     .   .     .   .  |  .   .  |  .   .  |  .   .     .   .  |  .   .  |  .   .     .
.  +--.   .--+  .   .  +--.   .--+  .   .  |  .   .-----.   .--+--.   .  +--.   .--+--.
.  |  .   .  |  .   .     .   .     .   .  |  .   .     .   .     .   .  |  .   .  |  .
.......   .......   .......   .......   .......   .......   .......   .......   .......
┌         ┐         └         ┘         │         ─         ┴         ├         ┬

Type 9       10        11        12        13        14        15
.......   .......   .......   .......   .......   .......   .......    
.  |  .   .  |  .   .     .   .  |  .   .     .   .     .   .     .   
.--+  .   .--+--.   .  o  .   .  o  .   .--o  .   .  o--.   .  ?  .   
.  |  .   .  |  .   .  |  .   .     .   .     .   .     .   .     .   
.......   .......   .......   .......   .......   .......   .......    
┤         ┼         ╿         ╽         ╼         ╾         ?


┌ ┐ └ ┘ ├ ┤ ┬ ┴  ┼  ╼ ╾ ╽ ╿ │ ─

*/

/* -----------------------------------------------------------------------------

  0 1 2 
0 ┌─┬─┐
1 ├─┼─┤
2 └─┴─┘
*/

PROGMEM const uint8_t Map_Random_Test[] = {
    /* Map Size */   4,1,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 1,
    /* px, py, EolX, EolY */
    0,0,3,0,
//    1,0,0,0,
    /* Map Data */
    THIS_SEG | 14, 1,
    THIS_SEG | 15, 1,
    THIS_SEG | 15, 2,
    THIS_SEG | 15, 3,
};