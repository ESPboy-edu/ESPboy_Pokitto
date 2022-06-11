
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

  0 1 2 
0 ┌─┬─┐
1 ├─┼─┤
2 └─┴─┘
*/

PROGMEM const uint8_t Map_Random_Size_01_00[] = {
    /* Map Size */   3,3,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 4,
    /* px, py, EolX, EolY */
    0,0,2,2,
    0,0,0,2,
    2,2,0,0,
    2,2,0,2,    
    /* Map Data */
    ANY_SEG | 0,  ANY_SEG | 8,  ANY_SEG | 1,
    ANY_SEG | 7,  ANY_SEG | 10, ANY_SEG | 9,
    ANY_SEG | 2,  ANY_SEG | 6,  ANY_SEG | 3,
};


/* -----------------------------------------------------------------------------

  0 1 2 
0 ┌─┐
1 └─┼─┐
2   └─┘
*/

PROGMEM const uint8_t Map_Random_Size_01_01[] = {
    /* Map Size */   3,3,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 2,
    /* px, py, EolX, EolY */
    0,0,2,2,
    2,2,0,0,
    /* Map Data */
    ANY_SEG | 0,  ANY_SEG | 1,  BLANK_SEG,
    ANY_SEG | 2,  ANY_SEG | 10, ANY_SEG | 1,
    BLANK_SEG,    ANY_SEG | 2,  ANY_SEG | 3,
};


/* -----------------------------------------------------------------------------

  0 1 2 
0 ╿ ┌─┐
1 ├─┼─┤
2 └─┴─┘
*/

PROGMEM const uint8_t Map_Random_Size_01_02[] = {
    /* Map Size */   3,3,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 2,
    /* px, py, EolX, EolY */
    0,0,2,2,
    2,2,0,0,
    /* Map Data */
    ANY_SEG | 11, ANY_SEG | 0,  ANY_SEG | 1,
    ANY_SEG | 7,  ANY_SEG | 10, ANY_SEG | 9,
    ANY_SEG | 2,  ANY_SEG | 6,  ANY_SEG | 3,
};


/* -----------------------------------------------------------------------------

  0 1 2 
0 ┌─┬─┐
1 └─┼─┤
2 ╾─┴─┘
*/

PROGMEM const uint8_t Map_Random_Size_01_03[] = {
    /* Map Size */   3,3,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 2,
    /* px, py, EolX, EolY */
    0,2,2,0,
    2,0,0,2,
    /* Map Data */
    ANY_SEG | 0,  ANY_SEG | 8,  ANY_SEG | 1,
    ANY_SEG | 2,  ANY_SEG | 10, ANY_SEG | 9,
    ANY_SEG | 14, ANY_SEG | 6,  ANY_SEG | 3,
};


/* -----------------------------------------------------------------------------

  0 1 2 
0 ┌─┬─╼
1 └─┼─┐
2 ╾─┴─┘
*/

PROGMEM const uint8_t Map_Random_Size_01_04[] = {
    /* Map Size */   3,3,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 2,
    /* px, py, EolX, EolY */
    0,2,2,0,
    2,0,0,2,
    /* Map Data */
    ANY_SEG | 0,  ANY_SEG | 8,  ANY_SEG | 13,
    ANY_SEG | 2,  ANY_SEG | 10, ANY_SEG | 1,
    ANY_SEG | 14, ANY_SEG | 6,  ANY_SEG | 3,
};