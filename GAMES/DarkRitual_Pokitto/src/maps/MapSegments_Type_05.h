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


PROGMEM const uint8_t MAP_Segment_Type05_00[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,38,38,38,38,38,38,  // 0
    38,38,38,38,38,38,38,38,38,  // 1
    38,38,38,38,38,38,38,38,38,  // 2
    24,24,68,24,24,24,24,24,24,  // 3
     0, 0, 0, 0, 0, 0, 0, 0, 0,  // 4
    22,22,22,22,22,22,67,22,22,  // 5
    38,38,38,38,38,38,38,38,38,  // 6
    38,38,38,38,38,38,38,38,38,  // 7
    38,38,38,38,38,38,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    2,
    1,MapTiles::CornerLR,1,3,
    1,MapTiles::StraightBOT,2,2,
    1,MapTiles::CornerLL,3,3,
    1,MapTiles::CornerTR,5,5,
    1,MapTiles::StraightTOP,6,6,
    1,MapTiles::CornerTL,7,5,
    1,MapTiles::SwitchOn,2,3,
    1,MapTiles::SwitchOn,6,5,
    1,MapTiles::SpearDoorLHS,4,4,
    END_OF_OPTIONS,

    1,2,3,4,4,
    1,6,5,4,4,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    2,
    0,Object::Coin,0,4,HEALTH_NONE,
    1,Object::Coin,8,4,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    2,
    1,4,
    7,4,
};


PROGMEM const uint8_t MAP_Segment_Type05_01[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,38,38,38,38,38,38,  // 0
    38,98,24,24,68,24,24,98,38,  // 1
    38,21, 0, 0, 0, 0, 0,23,38,  // 2
    24,35, 0, 0, 0, 0, 0,34,24,  // 3
     0, 0, 0, 0, 0, 0, 0, 0, 0,  // 4
    22,36, 0, 0, 0, 0, 0,37,22,  // 5
    38,21, 0, 0, 0, 0, 0,23,38,  // 6
    38,98,22,22,67,22,22,98,38,  // 7
    38,38,38,38,38,38,38,38,38,  // 8

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
    2,Object::SackOCash,5,2,HEALTH_NONE,
    2,Object::Spider,2,6,HEALTH_SPIDER,
    3,Object::Chicken,6,6,HEALTH_NONE,
    3,Object::Spider,2,2,HEALTH_SPIDER,
    3,Object::Skeleton,3,2,HEALTH_SKELETON,
    3,Object::Eye,2,3,HEALTH_EYE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,
};

PROGMEM const uint8_t MAP_Segment_Type05_02[] = {
  // 0  1  2  3  4  5  6  7  8
    98,24,24,24,68,24,24,24,98, // 0
    21, 0, 0, 0, 0, 0, 0, 0,23, // 1
    21, 0, 0, 0, 0, 0,45, 0,23, // 2
    24,44,36, 0, 0, 0,43, 0,34, // 3
     0, 0,43, 0, 0, 0,43, 0, 0, // 4
    36, 0,43, 0, 0, 0,34,44,22, // 5
    21, 0,46, 0, 0, 0, 0, 0,23, // 6
    21, 0, 0, 0, 0, 0, 0, 0,23, // 7
    98,22,22,22,67,22,22,22,98, // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    2,

    // Tilemap Options -------------------
    // Opt, Tile, x, y
    0,MapTiles::SwitchOn,1,1,
    0,MapTiles::SwitchOn,7,7,
    0,MapTiles::StraightLHS,2,4,
    0,MapTiles::EndTRB,3,4,
    0,MapTiles::SpearDoorTOP,4,4,
    0,MapTiles::EndTBL,5,4,
    0,MapTiles::StraightRHS,6,4,

    1,MapTiles::Fill,0,0,
    1,MapTiles::Fill,0,1,
    1,MapTiles::Fill,0,2,
    1,MapTiles::Fill,1,0,
    1,MapTiles::Fill,1,1,
    1,MapTiles::Fill,1,2,
    1,MapTiles::StraightRHS,2,1,
    1,MapTiles::StraightRHS,2,2,
    1,MapTiles::StraightRHS,2,3,
    1,MapTiles::StraightBOT,1,3,
    1,MapTiles::Fill,7,6,
    1,MapTiles::Fill,7,7,
    1,MapTiles::Fill,7,8,
    1,MapTiles::Fill,8,6,
    1,MapTiles::Fill,8,7,
    1,MapTiles::Fill,8,8,
    1,MapTiles::StraightLHS,6,5,
    1,MapTiles::StraightLHS,6,6,
    1,MapTiles::StraightLHS,6,7,
    1,MapTiles::StraightTOP,7,5,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    0,1,1,4,4,
    0,7,7,4,4,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    3,
    0,Object::Bat,3,2,HEALTH_BAT,
    0,Object::Bat,5,6,HEALTH_BAT,
    0,Object::Coin,3,1,HEALTH_NONE,
    1,Object::Spider,3,2,HEALTH_SPIDER,
    1,Object::Bat,5,6,HEALTH_BAT,
    1,Object::Coin,3,1,HEALTH_NONE,
    1,Object::Coin,5,7,HEALTH_NONE,
    2,Object::Snake,3,2,HEALTH_SNAKE,
    2,Object::Snake,5,6,HEALTH_SNAKE,
    2,Object::SackOCash,3,1,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    2,
    4,1,
    4,7,

};


PROGMEM const uint8_t MAP_Segment_Type05_03[] = {
//   0  1  2  3  4  5  6  7  8
    38,38, 0,24,24,98,98,24,98, // 0
    38,38,21,11, 0,23,35,11,23, // 1
    98,24,24,36, 0,46, 0, 0,23, // 2
    35, 0, 0,43, 0,58, 0, 0,34, // 3
     0, 0, 0,46, 0,45, 0, 0, 0, // 4
    36, 0, 0,57, 0,43, 0, 0,37, // 5
    21, 0, 0,45, 0,34,22,22,98, // 6
    21,11,37,21, 0,11,23,38,38, // 7
     0,22,98,98,22,22, 0,38,38, // 8
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
    0,3,1,3,5,
    0,7,1,5,3,
    0,5,7,5,3,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    0,

    // Entrance / Exit Options -----------
    2,
    6,5,
    2,3,

};
