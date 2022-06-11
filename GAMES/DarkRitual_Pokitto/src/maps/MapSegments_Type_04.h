#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"

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


PROGMEM const uint8_t MAP_Segment_Type04_00[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,21, 0,23,38,38,38,  // 0
    38,38,38,21, 0,23,38,38,38,  // 1
    38,38,38,66, 0,23,38,38,38,  // 2
    38,38,38,21, 0,23,38,38,38,  // 3
    38,38,38,21, 0,23,38,38,38,  // 4
    38,38,38,21, 0,23,38,38,38,  // 5
    38,38,38,21, 0,65,38,38,38,  // 6
    38,38,38,21, 0,23,38,38,38,  // 7
    38,38,38,21, 0,23,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    1,
    1,MapTiles::CornerLL,5,1,
    1,MapTiles::StraightLHS,6,2,
    1,MapTiles::CornerTL,5,3,
    1,MapTiles::CornerLR,3,5,
    1,MapTiles::StraightRHS,2,6,
    1,MapTiles::CornerTR,3,7,
    1,MapTiles::SwitchOn,5,2,
    1,MapTiles::SwitchOn,3,6,
    1,MapTiles::SpearDoorBOT,4,4,
    END_OF_OPTIONS,

    1,5,2,4,4,
    1,3,6,4,4,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    3,
    0,Object::Coin,4,0,HEALTH_NONE,
    0,Object::Coin,4,8,HEALTH_NONE,
    1,Object::SpikeLHS,4,0,HEALTH_NONE,
    1,Object::SpikeRHS,4,8,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    2,
    4,1,
    4,7,
};


PROGMEM const uint8_t MAP_Segment_Type04_01[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,21, 0,23,38,38,38,  // 0
    38,98,24,35, 0,34,24,98,38,  // 1
    38,21, 0, 0, 0, 0, 0,23,38,  // 2
    38,21, 0, 0, 0, 0, 0,23,38,  // 3
    38,66, 0, 0, 0, 0, 0,65,38,  // 4
    38,21, 0, 0, 0, 0, 0,23,38,  // 5
    38,21, 0, 0, 0, 0, 0,23,38,  // 6
    38,98,22,36, 0,37,22,98,38,  // 7
    38,38,38,21, 0,23,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    0,

    // Enemy Options ---------------------
    4,
    0,Object::Coin,2,2,HEALTH_NONE,
    0,Object::Coin,3,2,HEALTH_NONE,
    0,Object::Coin,2,3,HEALTH_NONE,
    0,Object::Spider,6,5,HEALTH_SPIDER,
    0,Object::Spider,5,6,HEALTH_SPIDER,
    1,Object::Chicken,6,6,HEALTH_NONE,
    1,Object::Spider,2,2,HEALTH_SPIDER,
    1,Object::Bat,3,2,HEALTH_BAT,
    1,Object::Bat,2,3,HEALTH_BAT,
    1,Object::SpikeLHS,4,8,HEALTH_NONE,
    1,Object::SpikeRHS,4,0,HEALTH_NONE,
    2,Object::SackOCash,5,2,HEALTH_NONE,
    2,Object::Spider,2,6,HEALTH_SPIDER,
    3,Object::Coin,2,2,HEALTH_NONE,
    3,Object::Coin,3,2,HEALTH_NONE,
    3,Object::Spider,6,5,HEALTH_SPIDER,
    3,Object::Snake,5,6,HEALTH_SNAKE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,
};

PROGMEM const uint8_t MAP_Segment_Type04_02[] = {
//   0  1  2  3  4  5  6  7  8
    98,24,24,21, 0,34,24,24,98, // 0
    21, 0, 0,43, 0, 0, 0, 0,23, // 1
    21, 0, 0,34,44,44,48, 0,23, // 2
    21, 0, 0, 0, 0, 0, 0, 0,23, // 3
    66, 0, 0, 0, 0, 0, 0, 0,65, // 4
    21, 0, 0, 0, 0, 0, 0, 0,23, // 5
    21, 0,47,44,44,36, 0, 0,23, // 6
    21, 0, 0, 0, 0,43, 0, 0,23, // 7
    98,22,22,36, 0,23,22,22,98, // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    2,

    // Tilemap Options -------------------
    // Opt, Tile, x, y
    0,MapTiles::SwitchOn,1,1,
    0,MapTiles::SwitchOn,7,7,
    0,MapTiles::StraightTOP,4,2,
    0,MapTiles::EndRBL,4,3,
    0,MapTiles::SpearDoorLHS,4,4,
    0,MapTiles::EndTRL,4,5,
    0,MapTiles::StraightTOP,4,6,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    0,1,1,4,4,
    0,7,7,4,4,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    3,
    0,Object::SpikeLHS,1,7,HEALTH_NONE,
    0,Object::SpikeRHS,7,2,HEALTH_NONE,
    1,Object::FireTOP,5,1,HEALTH_NONE,
    1,Object::FireTOP,6,1,HEALTH_NONE,
    1,Object::FireBOT,2,7,HEALTH_NONE,
    1,Object::FireBOT,3,7,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    4,
    2,1,
    1,4,
    7,4,
    6,7,

};


PROGMEM const uint8_t MAP_Segment_Type04_03[] = {
//   0  1  2  3  4  5  6  7  8
    38,38,98,35, 0,34,24,24,98, // 0
    38,38,21, 0, 0, 0, 0,11,23, // 1
    98,24,21, 0, 0, 0, 0,37,98, // 2
    21,11,34,44,48,59,47,24,98, // 3
    21, 0, 0, 0, 0, 0, 0, 0,23, // 4
    98,22,48,60,47,44,36,11,23, // 5
    98,35, 0, 0, 0, 0,23,22, 0, // 6
    21,11, 0, 0, 0, 0,23,38,38, // 7
    98,22,22,36, 0,37,98,38,38, // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    1,

    // Tilemap Options -------------------
    // Opt, Tile, x, y
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    0,1,7,3,5,
    0,7,5,5,3,
    0,1,3,3,5,
    0,7,1,5,3,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    0,

    // Entrance / Exit Options -----------
    2,
    5,6,
    3,2,

};
