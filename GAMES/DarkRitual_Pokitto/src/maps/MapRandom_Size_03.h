#pragma once

#include "Pokitto.h"


using PC = Pokitto::Core;
using PD = Pokitto::Display;



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

*/



/* -----------------------------------------------------------------------------

  0 1 2 3
0     ╿
1 ┌─┐ │
2 ├─┴─┼─╼
3 ╽   ╽
*/
PROGMEM const uint8_t Map_Random_Size_03_00[] = {
    /* Map Size */   4,4,
    /* Timer */      200,
    /* Player Start Segment / End of Level Segment */ 12,
    /* px, py, EolX, EolY */
    2,0,3,2,
    2,0,2,3,
    2,0,0,3,

    3,2,2,0,
    3,2,2,3,
    3,2,0,3,

    0,3,2,0,
    0,3,3,2,
    0,3,2,3,

    2,3,2,0,
    2,3,3,2,
    2,3,0,3,
    /* Map Data */
    BLANK_SEG,    BLANK_SEG,   ANY_SEG | 11, BLANK_SEG,
    ANY_SEG | 0,  ANY_SEG | 1, ANY_SEG | 4,  BLANK_SEG,
    ANY_SEG | 7,  ANY_SEG | 6, ANY_SEG | 10, ANY_SEG | 13,
    ANY_SEG | 12, BLANK_SEG,   ANY_SEG | 12, BLANK_SEG,
};


/* -----------------------------------------------------------------------------

  0 1 2 3 4
0     ╿
1 ┌─┐ ├─┐
2 └─┴─┼─┼─┐
3     ╽ └─┘
*/
PROGMEM const uint8_t Map_Random_Size_03_01[] = {
    /* Map Size */   5,4,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 8,
    /* px, py, EolX, EolY */
    2,0,0,2,
    2,0,4,3,
    0,2,2,0,
    0,2,4,3,
    4,3,2,0,
    4,3,0,1,
    2,3,0,1,
    2,3,4,3,
    /* Map Data */
    BLANK_SEG,    BLANK_SEG,   ANY_SEG | 11, BLANK_SEG,    BLANK_SEG,
    ANY_SEG | 0,  ANY_SEG | 1, ANY_SEG | 7,  ANY_SEG | 1,  BLANK_SEG,
    ANY_SEG | 2,  ANY_SEG | 6, ANY_SEG | 10, ANY_SEG | 10, ANY_SEG | 1,
    BLANK_SEG,    BLANK_SEG,   ANY_SEG | 12, ANY_SEG | 2,  ANY_SEG | 3,
};


/* -----------------------------------------------------------------------------

  0 1 2 3 4
0   ┌─╼ ╿
1 ╾─┼─┬─┼─┐ 
2   ├─┴─┘ │
3   └─┬─┬─┤
4     └─┴─┘
*/
PROGMEM const uint8_t Map_Random_Size_03_02[] = {
    /* Map Size */   5,5,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 9,
    /* px, py, EolX, EolY */
    2,0,3,0,
    2,0,2,4,
    2,0,4,4,
    3,0,2,0,
    3,0,2,4,
    3,0,4,4,
    0,1,3,0,
    0,1,2,4,
    1,1,4,4,
    /* Map Data */
    BLANK_SEG,    ANY_SEG | 0,  ANY_SEG | 13, ANY_SEG | 11,  BLANK_SEG,
    ANY_SEG | 14, ANY_SEG | 10, ANY_SEG | 8,  ANY_SEG | 10,  ANY_SEG | 1,
    BLANK_SEG,    ANY_SEG | 7 , ANY_SEG | 6,  ANY_SEG | 3,   ANY_SEG | 4,
    BLANK_SEG,    ANY_SEG | 2 , ANY_SEG | 8,  ANY_SEG | 8,   ANY_SEG | 9,
    BLANK_SEG,    BLANK_SEG,    ANY_SEG | 2,  ANY_SEG | 6,   ANY_SEG | 3,

};



/* -----------------------------------------------------------------------------

  0 1 2 3 4
0 ┌─┐
1 ├─┘     ╿
2 └─?─?─?-┤
3   ╾─┬─┬─┤
4     └─┴─┘
*/
PROGMEM const uint8_t Map_Random_Size_03_03[] = {
    /* Map Size */   5,5,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 3,
    /* px, py, EolX, EolY */
    1,1,1,3,
    1,1,4,1,
    1,1,2,4,
    /* Map Data */
    ANY_SEG | 0,  ANY_SEG | 1,       BLANK_SEG,         BLANK_SEG,         BLANK_SEG,
    ANY_SEG | 7,  THIS_SEG | 3, 4,   BLANK_SEG,         BLANK_SEG,         ANY_SEG | 11,
    ANY_SEG | 2,  THIS_SEG | 15, 1,  THIS_SEG | 15, 2,  THIS_SEG | 15, 3,  ANY_SEG | 9,
    BLANK_SEG,    ANY_SEG | 14,      ANY_SEG | 8,       ANY_SEG | 8,       ANY_SEG | 9,
    BLANK_SEG,    BLANK_SEG,         ANY_SEG | 2,       ANY_SEG | 6,       ANY_SEG | 3,

};
