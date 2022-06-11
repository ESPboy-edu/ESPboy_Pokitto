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

Type 9       10        11        12        13        14        15
.......   .......   .......   .......   .......   .......   .......    
.  |  .   .  |  .   .     .   .  |  .   .     .   .     .   .     .   
.--+  .   .--+--.   .  o  .   .  o  .   .--o  .   .  o--.   .  ?  .   
.  |  .   .  |  .   .  |  .   .     .   .     .   .     .   .     .   
.......   .......   .......   .......   .......   .......   .......      

*/

PROGMEM const uint8_t MAP_Segment_Type14_00[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,38,38,38,38,38,38,  // 0
    38,38,38,38,38,38,38,38,38,  // 1
    38,38,38,38,38,38,38,38,38,  // 2
    38,38,98,24,24,24,24,24,24,  // 3
    38,38,21, 0, 0, 0, 0, 0, 0,  // 4
    38,38,98,22,22,22,22,22,22,  // 5
    38,38,38,38,38,38,38,38,38,  // 6
    38,38,38,38,38,38,38,38,38,  // 7
    38,38,38,38,38,38,38,38,38,  // 8


    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    2,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    1,MapTiles::CornerLR,3,3,
    1,MapTiles::StraightBOT,4,2,
    1,MapTiles::CornerLL,5,3,
    1,MapTiles::SwitchOn,4,3,
    1,MapTiles::SpearDoorRHS,5,4,

    1,MapTiles::CornerTR,6,5,
    1,MapTiles::StraightTOP,7,6,
    1,MapTiles::CornerTL,8,5,
    1,MapTiles::SwitchOn,7,5,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    1,4,3,5,4,
    1,7,5,5,4,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    0,

    // Entrance / Exit Options -----------
    1,
    3,4,

};

PROGMEM const uint8_t MAP_Segment_Type14_01[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,38,38,38,38,38,38,  // 0
    38,38,38,24,24,24,38,38,38,  // 1
    38,38,25, 0, 0, 0,26,38,38,  // 2
    38,21, 0, 0, 0, 0, 0,34,24,  // 3
    38,66, 0, 0, 0, 0, 0, 0, 0,  // 4
    38,21, 0, 0, 0, 0, 0,37,22,  // 5
    38,38,27, 0, 0, 0,28,38,38,  // 6
    38,38,38,22,22,22,38,38,38,  // 7
    38,38,38,38,38,38,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    2,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,4,2,
    0,MapTiles::Barrel,3,5,
    1,MapTiles::Barrel,5,3,
    1,MapTiles::Barrel,5,4,
    1,MapTiles::Barrel,5,5,
    1,MapTiles::Barrel,4,4,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    2,
    0,Object::Bat, 3, 2, 20,
    1,Object::Spider, 3, 2, 40,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,

};


PROGMEM const uint8_t MAP_Segment_Type14_02[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,98,24,24,24,98,38,38,  // 0
    38,38,21, 0, 0, 0,23,38,38,  // 1
    38,38,66, 0,45, 0,65,38,38,  // 2
    98,24,21, 0,43, 0,23,24,24,  // 3
    21, 0,43, 0,43, 0,43, 0, 0,  // 4
    21, 0,43, 0,43, 0,43, 0,37,  // 5
    66, 0,46, 0,43, 0,46, 0,65,  // 6
    21, 0, 0, 0,43, 0, 0, 0,23,  // 7
    98,22,22,22,98,22,22,22,98,  // 8
    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    0,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    2,
    0,Object::Bat,3,1,20,
    0,Object::Bat,5,1,20,
    1,Object::Spider,4,1,40,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    1,4,

};


PROGMEM const uint8_t MAP_Segment_Type14_03[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,98,24,24,24,24,98,  // 0
    38,38,38,21, 0, 0, 0, 0,23,  // 1
    38,98,24,35, 0,47,36, 0,23,  // 2
    38,21, 0, 0, 0, 0,43, 0,34,  // 3
    38,66, 0, 0, 0, 0,43, 0, 0,  // 4
    38,21, 0, 0, 0, 0,23,22,22,  // 5
    38,98,22,67,22,22,98,38,38,  // 6
    38,38,38,38,38,38,38,38,38,  // 7
    38,38,38,38,38,38,38,38,38,  // 8
    
    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    2,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,2,3,
    0,MapTiles::Barrel,2,5,
    1,MapTiles::Barrel,5,3,
    1,MapTiles::Barrel,5,5,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    1,
    0,Object::Bat,2,4,20,
    0,Object::Spider,7,1,40,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,

};