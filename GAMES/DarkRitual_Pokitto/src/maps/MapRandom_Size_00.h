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

  0 1  
0 ╾─┐
1 ╾─┘
*/

PROGMEM const uint8_t Map_Random_Size_00_00[] = {
    /* Map Size */   2,2,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 2,
    /* px, py, EolX, EolY */
    0,0,0,1,
    0,1,0,0,    
    /* Map Data */
    ANY_SEG | 14, ANY_SEG | 1,
    ANY_SEG | 14, ANY_SEG | 3,
};


/* -----------------------------------------------------------------------------

  0 1  
0 ┌─┐
1 └─┘
*/

PROGMEM const uint8_t Map_Random_Size_00_01[] = {
    /* Map Size */   2,2,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 2,
    /* px, py, EolX, EolY */
    0,0,1,1,
    1,1,0,0,    
    /* Map Data */
    ANY_SEG | 0,  ANY_SEG | 1,
    ANY_SEG | 2,  ANY_SEG | 3,
};


/* -----------------------------------------------------------------------------

  0 1 2 
0 ╾─┐
1   └─╼
*/
PROGMEM const uint8_t Map_Random_Size_00_02[] = {
    /* Map Size */   3,2,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 2,
    /* px, py, EolX, EolY */
    0,0,2,1,
    2,1,0,0,
    /* Map Data */
    ANY_SEG | 14, ANY_SEG | 1, BLANK_SEG,
    BLANK_SEG,    ANY_SEG | 2, ANY_SEG | 13,
};


/* -----------------------------------------------------------------------------

  0 1 2 
0   ┌─╼
1 ╾─┘
*/
PROGMEM const uint8_t Map_Random_Size_00_03[] = {
    /* Map Size */   3,2,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 2,
    /* px, py, EolX, EolY */
    0,1,2,0,
    2,0,0,1,
    /* Map Data */
    BLANK_SEG,    ANY_SEG | 0, ANY_SEG | 13,
    ANY_SEG | 14, ANY_SEG | 3, BLANK_SEG,
};



/* -----------------------------------------------------------------------------

  0 1 2 
0 ┌─┬─┐
1 └─┴─┘
*/

PROGMEM const uint8_t Map_Random_Size_00_04[] = {
    /* Map Size */   3,2,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 2,
    /* px, py, EolX, EolY */
    0,0,2,1,
    2,1,0,0,    
    /* Map Data */
    ANY_SEG | 0,  ANY_SEG | 8,  ANY_SEG | 1,
    ANY_SEG | 2,  ANY_SEG | 6,  ANY_SEG | 3,
};
