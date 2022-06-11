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

PROGMEM const uint8_t MAP_Segment_Type13_00[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,38,38,38,38,38,38,  // 0
    38,38,38,38,38,38,38,38,38,  // 1
    38,38,38,38,38,38,38,38,38,  // 2
    24,24,24,24,24,24,98,38,38,  // 3
     0, 0, 0, 0, 0, 0,23,38,38,  // 4
    22,22,22,22,22,22,98,38,38,  // 5
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

    1,MapTiles::CornerLR,0,3,
    1,MapTiles::StraightBOT,1,2,
    1,MapTiles::CornerLL,2,3,
    1,MapTiles::SwitchOn,1,3,
    1,MapTiles::SpearDoorLHS,3,4,

    1,MapTiles::CornerTR,3,5,
    1,MapTiles::StraightTOP,4,6,
    1,MapTiles::CornerTL,5,5,
    1,MapTiles::SwitchOn,4,5,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    1,4,5,3,4,
    1,1,3,3,4,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    0,

    // Entrance / Exit Options -----------
    1,
    5,4,

};

PROGMEM const uint8_t MAP_Segment_Type13_01[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,38,38,38,38,38,38,  // 0
    38,38,38,24,24,24,38,38,38,  // 1
    38,38,25, 0, 0, 0,26,38,38,  // 2
    24,35, 0, 0, 0, 0, 0,23,38,  // 3
     0, 0, 0, 0, 0, 0, 0,65,38,  // 4
    22,36, 0, 0, 0, 0, 0,23,38,  // 5
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


PROGMEM const uint8_t MAP_Segment_Type13_02[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,98,24,24,24,98,38,98,  // 0
    38,38,21, 0, 0, 0,23,38,38,  // 1
    38,38,66, 0,45, 0,65,38,38,  // 2
    24,24,21, 0,43, 0,23,24,98,  // 3
     0, 0,43, 0,43, 0,43, 0,23,  // 4
    36, 0,43, 0,43, 0,43, 0,23,  // 5
    21, 0,46, 0,43, 0,46, 0,23,  // 6
    21, 0, 0, 0,43, 0, 0, 0,23,  // 7
    98,22,67,22,98,22,67,22,98,  // 8
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
    7,4,

};


PROGMEM const uint8_t MAP_Segment_Type13_03[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    98,24,24,24,24,98,38,38,38,   // 0
    21, 0, 0, 0, 0,23,38,38,38,   // 1
    21, 0,37,48, 0,34,24,98,38,   // 2
    35, 0,43, 0, 0, 0, 0,23,38,   // 3
     0, 0,43, 0, 0, 0, 0,65,38,   // 4
    22,22,21, 0, 0, 0, 0,23,38,   // 5
    38,38,98,22,22,67,22,98,38,   // 6
    38,38,38,38,38,38,38,38,38,   // 7
    38,38,38,38,38,38,38,38,38,   // 8

    
    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    2,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,6,3,
    0,MapTiles::Barrel,6,5,
    1,MapTiles::Barrel,3,3,
    1,MapTiles::Barrel,3,5,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    1,
    0,Object::Bat,6,4,20,
    0,Object::Spider,1,1,40,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,

};