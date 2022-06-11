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

PROGMEM const uint8_t MAP_Segment_Type01_00[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,38,38,38,38,38,38,  // 0
    38,38,38,38,38,38,38,38,38,  // 1
    38,38,38,38,38,38,38,38,38,  // 2
    24,24,68,24,24,98,38,38,38,  // 3
     0, 0, 0, 0, 0,23,38,38,38,  // 4
    22,22,22,36, 0,23,38,38,38,  // 5
    38,38,38,21, 0,65,38,38,38,  // 6
    38,38,38,21, 0,23,38,38,38,  // 7
    38,38,38,21, 0,23,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    0,

    // Enemy Options ---------------------
    4,
    0,Object::FireTOP,1,4,HEALTH_NONE,
    0,Object::FireBOT,2,4,HEALTH_NONE,
    1,Object::SpikeLHS,4,6,HEALTH_NONE,
    1,Object::SpikeRHS,4,7,HEALTH_NONE,
    2,Object::FireTOP,1,4,HEALTH_NONE,
    2,Object::FireBOT,2,4,HEALTH_NONE,
    2,Object::SpikeLHS,4,6,HEALTH_NONE,
    2,Object::SpikeRHS,4,7,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    2,
    2,4,
    4,7,    
};

PROGMEM const uint8_t MAP_Segment_Type01_01[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,38,38,38,38,38,38,  // 0
    38,38,38,24,68,24,38,38,38,  // 1
    38,38,25, 0, 0, 0,26,38,38,  // 2
    24,35, 0, 0, 0, 0, 0,23,38,  // 3
     0, 0, 0, 0, 0, 0, 0,65,38,  // 4
    22,36, 0, 0, 0, 0, 0,23,38,  // 5
    38,38,27, 0, 0, 0,28,38,38,  // 6
    38,38,38,36, 0,37,38,38,38,  // 7
    38,38,38,21, 0,23,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    2,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,4,3,
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
    0,

    // Entrance / Exit Options -----------
    2,
    3,2,
    5,6,
};

PROGMEM const uint8_t MAP_Segment_Type01_02[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    98,24,24,68,24,68,24,24,98,  // 0
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 1
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 2
    35, 0, 0, 0, 0, 0, 0, 0,23,  // 3
     0, 0, 0, 0, 0, 0, 0, 0,23,  // 4
    36, 0, 0, 0, 0, 0, 0, 0,23,  // 5
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 6
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 7
    98,22,22,36, 0,37,22,22,98,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    2,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,3,1,
    0,MapTiles::Barrel,4,1,
    0,MapTiles::Barrel,7,2,
    0,MapTiles::Barrel,5,2,
    1,MapTiles::Barrel,7,6,
    1,MapTiles::Barrel,5,7,
    1,MapTiles::Barrel,6,7,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    4,
    0,Object::Bat, 1, 2, HEALTH_BAT,
    0,Object::Spider, 2, 2, HEALTH_SPIDER,
    1,Object::Eye, 1, 2, HEALTH_EYE,
    1,Object::Skeleton, 2, 2, HEALTH_SKELETON,
    2,Object::Eye, 1, 2, HEALTH_EYE,
    2,Object::Bat, 2, 2, HEALTH_BAT,
    3,Object::Eye, 1, 2, HEALTH_EYE,
    3,Object::Snake, 2, 2, HEALTH_SNAKE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    2,
    4,4,
    1,7,

};


PROGMEM const uint8_t MAP_Segment_Type01_03[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38, 0,24,24,24,24,24,98,  // 0
    38,38,21,83, 0, 0, 0,84,23,  // 1
    38,38,21, 0, 0, 0, 0, 0,23,  // 2
    24,24,35, 0, 0,45, 0, 0,65,  // 3
     0, 0, 0, 0, 0,43, 0, 0,23,  // 4
    22,22,22,22,44,35, 0, 0,65,  // 5
    38,38,38,21, 0, 0, 0, 0,23,  // 6
    38,38,38,21, 0, 0, 0, 0,23,  // 7
    38,38,38,21, 0,37,22,22,98,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    2,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,7,7,
    0,MapTiles::Barrel,6,7,
    1,MapTiles::Barrel,5,7,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    3,
    0,Object::Bat,3,1,HEALTH_BAT,
    0,Object::Spider,4,4,HEALTH_SPIDER,
    0,Object::Coin,1,4,HEALTH_NONE,
    1,Object::Bat,4,6,HEALTH_BAT,
    1,Object::Skeleton,3,1,HEALTH_SKELETON,
    1,Object::Coin,6,1,HEALTH_NONE,
    1,Object::Coin,7,1,HEALTH_NONE,
    2,Object::Snake,4,6,HEALTH_SNAKE,
    2,Object::Skeleton,3,1,HEALTH_SKELETON,
    2,Object::SackOCash,6,1,HEALTH_NONE,
    2,Object::Coin,7,1,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    7,7,

};


PROGMEM const uint8_t MAP_Segment_Type01_04[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,98,24,24,68,24,24,98,  // 0
     0,24,21, 0, 0, 0, 0,11,23,  // 1
    21,11,46, 0, 0, 0, 0, 0,23,  // 2
    35, 0,57, 0, 0, 0, 0, 0,65,  // 3
     0, 0,45, 0, 0, 0, 0, 0,23,  // 4
    36, 0,43, 0, 0, 0, 0, 0,23,  // 5
    21, 0,34,44,48,60,47,22,98,  // 6
    21, 0, 0, 0, 0, 0,11,23,38,  // 7
     0,22,22,36, 0,37,22, 0,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    3,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,3,1,
    0,MapTiles::Barrel,4,1,
    1,MapTiles::Barrel,1,3,
    1,MapTiles::Barrel,7,4,
    1,MapTiles::Barrel,4,5,
    1,MapTiles::FullSquare,4,2,
    1,MapTiles::FullSquare,6,2,
    1,MapTiles::FullSquare,6,2,
    1,MapTiles::FullSquare,6,4,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    0,1,2,5,6,
    0,6,7,2,3,
    0,7,1,5,6,
    0,7,1,2,3,
    1,1,2,5,6,
    1,6,7,2,3,
    1,7,1,5,6,
    1,7,1,2,3,
    2,1,2,5,6,
    2,6,7,2,3,
    2,7,1,5,6,
    2,7,1,2,3,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    3,
    0,Object::Bat,3,4,HEALTH_BAT,
    0,Object::Spider,6,5,HEALTH_SPIDER,
    0,Object::Coin,4,3,HEALTH_NONE,
    1,Object::Bat,3,4,HEALTH_BAT,
    1,Object::Skeleton,6,5,HEALTH_SKELETON,
    1,Object::Chicken,4,3,HEALTH_NONE,
    1,Object::SpikeLHS,1,6,HEALTH_NONE,
    1,Object::FireBOT,2,7,HEALTH_NONE,
    2,Object::Snake,3,4,HEALTH_SNAKE,
    2,Object::Skeleton,6,5,HEALTH_SKELETON,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    2,
    1,7,
    3,5

};


PROGMEM const uint8_t MAP_Segment_Type01_05[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,38,38,38,38,38,38,  // 0
    38,38,38,38,38,38,38,38,38,  // 1
    38,38,38,38,38,38,38,38,38,  // 2
    24,24,24,38,38,38,38,38,38,  // 3
     0, 0, 0,26,38,38,38,38,38,  // 4
    36, 0, 0, 0,26,38,38,38,38,  // 5
    21, 0, 0, 0, 0,23,38,38,38,  // 6
    21, 0, 0, 0, 0,23,38,38,38,  // 7
    98,22,22,36, 0,23,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    2,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,2,4,
    0,MapTiles::Barrel,4,6,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    4,
    0,Object::Bat,3,5,HEALTH_BAT,
    1,Object::Spider,3,5,HEALTH_SPIDER,
    2,Object::Eye,3,5,HEALTH_EYE,
    2,Object::Snake,3,5,HEALTH_SNAKE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    1,7,

};