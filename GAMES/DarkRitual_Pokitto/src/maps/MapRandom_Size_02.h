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
0   ╿ 
1 ┌─┼─┐
2 ├─┼─┤
3 └─┴─┘
*/

PROGMEM const uint8_t Map_Random_Size_02_00[] = {
    /* Map Size */   3,4,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 4,
    /* px, py, EolX, EolY */
    1,0,0,3,
    1,0,2,3,
    0,3,1,0,
    2,3,1,0,
    /* Map Data */
    BLANK_SEG,    ANY_SEG | 11, BLANK_SEG,
    ANY_SEG | 0,  ANY_SEG | 10, ANY_SEG | 1,
    ANY_SEG | 7,  ANY_SEG | 10, ANY_SEG | 9,
    ANY_SEG | 2,  ANY_SEG | 6,  ANY_SEG | 3,
};


/* -----------------------------------------------------------------------------

  0 1 2 
0   ╿ 
1 ┌─┼─┐
2 ├─┴─┤
3 └─┬─┘
4 ╾─┴─╼
*/

PROGMEM const uint8_t Map_Random_Size_02_01[] = {
    /* Map Size */   3,5,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 6,
    /* px, py, EolX, EolY */
    1,0,0,4,
    1,0,2,4,
    0,4,1,0,
    0,4,2,4,
    2,4,1,0,
    2,4,0,4,
    /* Map Data */
    BLANK_SEG,    ANY_SEG | 11, BLANK_SEG,
    ANY_SEG | 0,  ANY_SEG | 10, ANY_SEG | 1,
    ANY_SEG | 7,  ANY_SEG | 6,  ANY_SEG | 9,
    ANY_SEG | 2,  ANY_SEG | 8,  ANY_SEG | 3,
    ANY_SEG | 14, ANY_SEG | 6,  ANY_SEG | 13,
};


/* -----------------------------------------------------------------------------

  0 1 2 3
0 ╿ ┌─┬─╼ 
1 ? ├─┘
2 └─┴─╼  
*/
PROGMEM const uint8_t Map_Random_Size_02_02[] = {
    /* Map Size */   4,3,
    /* Timer */      200,
    /* Player Start Segment / End of Level Segment */ 2,
    /* px, py, EolX, EolY */
    3,0,0,0,
    2,2,0,0,
    /* Map Data */
    ANY_SEG | 11,     ANY_SEG | 0, ANY_SEG | 8, ANY_SEG | 13, 
    THIS_SEG | 15, 0, ANY_SEG | 7, ANY_SEG | 3, BLANK_SEG,
    ANY_SEG | 2,      ANY_SEG | 6,ANY_SEG | 13, BLANK_SEG,
};


/* -----------------------------------------------------------------------------

  0 1 2 3
0 ╾─┬─┬─╼ 
1   ├─┘
2   ╽  
*/
PROGMEM const uint8_t Map_Random_Size_02_03[] = {
    /* Map Size */   4,3,
    /* Timer */      200,
    /* Player Start Segment / End of Level Segment */ 6,
    /* px, py, EolX, EolY */
    0,0,3,0,
    0,0,1,2,
    3,0,0,0,
    3,0,1,2,
    1,2,0,0,
    1,2,3,0,
    /* Map Data */
    ANY_SEG | 14, ANY_SEG | 8, ANY_SEG | 8, ANY_SEG | 13, 
    BLANK_SEG,    ANY_SEG | 7,  ANY_SEG | 3, BLANK_SEG,
    BLANK_SEG,    ANY_SEG | 12, BLANK_SEG,   BLANK_SEG,
};




/* -----------------------------------------------------------------------------

  0 1 2 
0 ┌─┬─╼ 
1 ├─┴─╼
2 ╽  
*/
PROGMEM const uint8_t Map_Random_Size_02_04[] = {
    /* Map Size */   3,3,
    /* Timer */      200,
    /* Player Start Segment / End of Level Segment */ 6,
    /* px, py, EolX, EolY */
    0,2,2,1,
    0,2,2,0,
    2,0,0,2,
    2,0,2,1,
    2,1,2,0,
    2,1,0,2,
    /* Map Data */
    ANY_SEG | 0,  ANY_SEG | 8, ANY_SEG | 13, 
    ANY_SEG | 7,  ANY_SEG | 6, ANY_SEG | 13,
    ANY_SEG | 12, BLANK_SEG,   BLANK_SEG,
};



/* -----------------------------------------------------------------------------

  0 1 2 3
0   ┌─╼ ╿
1 ╾─┼─┬─┤
2   └─┴─┘
*/
PROGMEM const uint8_t Map_Random_Size_02_05[] = {
    /* Map Size */   4,3,
    /* Timer */      255,
    /* Player Start Segment / End of Level Segment */ 6,
    /* px, py, EolX, EolY */
    2,0,3,0,
    2,0,0,1,
    3,0,2,0,
    3,0,0,1,
    0,1,2,0,
    0,1,3,0,
    /* Map Data */
    BLANK_SEG,    ANY_SEG | 0,  ANY_SEG | 13, ANY_SEG | 11,
    ANY_SEG | 14, ANY_SEG | 10, ANY_SEG | 8,  ANY_SEG | 9,
    BLANK_SEG,    ANY_SEG | 2 , ANY_SEG | 6,  ANY_SEG | 3,
};
