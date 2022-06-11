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

PROGMEM const uint8_t MAP_Segment_Type02_00[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,21, 0,23,38,38,38,  // 0
    38,38,38,21, 0,23,38,38,38,  // 1
    38,38,38,66, 0,23,38,38,38,  // 2
    38,38,38,21, 0,34,24,24,24,  // 3
    38,38,38,21, 0, 0, 0, 0, 0,  // 4
    38,38,38,98,22,22,67,22,22,  // 5
    38,38,38,38,38,38,38,38,38,  // 6
    38,38,38,38,38,38,38,38,38,  // 7
    38,38,38,38,38,38,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    0,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    4,
    0,Object::FireTOP,5,4,HEALTH_NONE,
    0,Object::FireBOT,6,4,HEALTH_NONE,
    1,Object::SpikeLHS,4,1,HEALTH_NONE,
    1,Object::SpikeRHS,4,2,HEALTH_NONE,
    2,Object::FireTOP,5,4,HEALTH_NONE,
    2,Object::FireBOT,6,4,HEALTH_NONE,
    2,Object::SpikeLHS,4,1,HEALTH_NONE,
    2,Object::SpikeRHS,4,2,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,

};

PROGMEM const uint8_t MAP_Segment_Type02_01[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,21, 0,23,38,38,38,  // 0
    38,38,38,35, 0,34,38,38,38,  // 1
    38,38,25, 0, 0, 0,26,38,38,  // 2
    38,21, 0, 0, 0, 0, 0,34,24,  // 3
    38,66, 0, 0, 0, 0, 0, 0, 0,  // 4
    38,21, 0, 0, 0, 0, 0,37,22,  // 5
    38,38,27, 0, 0, 0,28,38,38,  // 6
    38,38,38,22,67,22,38,38,38,  // 7
    38,38,38,38,38,38,38,38,38,  // 8

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
    5,
    0,Object::Bat, 2, 5, HEALTH_BAT,
    0,Object::Spider, 3, 6, HEALTH_SPIDER,
    1,Object::Bat, 2, 5, HEALTH_BAT,
    1,Object::Skeleton, 3, 6, HEALTH_SKELETON,
    2,Object::Spider, 2, 5, HEALTH_SPIDER,
    2,Object::Eye, 3, 6, HEALTH_EYE,
    3,Object::Spider, 2, 5, HEALTH_SPIDER,
    3,Object::Snake, 3, 6, HEALTH_SNAKE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    2,
    3,2,
    5,6,
};

PROGMEM const uint8_t MAP_Segment_Type02_02[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    98,24,24,35, 0,34,24,24,98,  // 0
    21,83, 0, 0, 0, 0, 0, 0,23,  // 1
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 2
    21, 0, 0, 0, 0, 0, 0, 0,34,  // 3
    21, 0, 0, 0, 0, 0, 0, 0, 0,  // 4
    21, 0, 0, 0, 0, 0, 0, 0,37,  // 5
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 6
    21, 0, 0, 0, 0, 0, 0,85,23,  // 7
    98,22,22,67,22,67,22,22,98,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    2,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,3,1,
    0,MapTiles::Barrel,4,1,
    0,MapTiles::Barrel,2,4,
    0,MapTiles::Barrel,5,2,
    1,MapTiles::Barrel,7,6,
    1,MapTiles::Barrel,5,7,
    1,MapTiles::Barrel,6,7,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    0,1,1,8,4,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    4,
    0,Object::Bat, 1, 2, HEALTH_BAT,
    0,Object::Spider, 2, 2, HEALTH_SPIDER,
    1,Object::Eye, 1, 2, HEALTH_EYE,
    1,Object::Spider, 2, 2, HEALTH_SPIDER,
    2,Object::Eye, 1, 2, HEALTH_EYE,
    2,Object::Skeleton, 2, 2, HEALTH_SKELETON,
    3,Object::Snake, 1, 2, HEALTH_SNAKE,
    3,Object::Skeleton, 2, 2, HEALTH_SKELETON,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    2,
    4,4,
    1,7,

};

PROGMEM const uint8_t MAP_Segment_Type02_03[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,21, 0,23,38,38,38,  // 0
    38,38,38,21, 0,23,38,38,38,  // 1
    98,24,24,35, 0,23,38,38,38,  // 2
    21, 0, 0, 0, 0,23,24,24,24,  // 3
    21, 0, 0, 0, 0,43, 0, 0, 0,  // 4
    21, 0, 0,47,44,35, 0, 0,37,  // 5
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 6
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 7
    98,22,22,67,22,67,22,22,98,  // 8

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
    0,Object::Bat, 3, 7, HEALTH_BAT,
    0,Object::Spider, 4, 4, HEALTH_SPIDER,
    0,Object::Coin,1,3,HEALTH_NONE,
    1,Object::Bat, 3, 7, HEALTH_BAT,
    1,Object::Skeleton, 4, 4, HEALTH_SKELETON,
    1,Object::Coin,1,3,HEALTH_NONE,
    1,Object::Coin,1,4,HEALTH_NONE,
    2,Object::Snake, 3, 7, HEALTH_SNAKE,
    2,Object::Skeleton, 4, 4, HEALTH_SKELETON,
    2,Object::SackOCash,1,3,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    1,7,

};


PROGMEM const uint8_t MAP_Segment_Type02_04[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38, 0,24,35, 0,34,24,24,98,  // 0
    38,21,11, 0, 0, 0, 0, 0,23,  // 1
    98,24,48,59,47,44,36, 0,23,  // 2
    21, 0, 0, 0, 0, 0,43, 0,34,  // 3
    21, 0, 0, 0, 0, 0,46, 0, 0,  // 4
    66, 0, 0, 0, 0, 0,58, 0,37,  // 5
    21, 0, 0, 0, 0, 0,45,11,23,  // 6
    21,11, 0, 0, 0, 0,23,22, 0,  // 7
    98,22,22,67,22,22,98,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    3,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,3,7,
    0,MapTiles::Barrel,4,7,
    1,MapTiles::Barrel,1,5,
    1,MapTiles::Barrel,1,4,
    1,MapTiles::Barrel,4,5,
    2,MapTiles::FullSquare,2,4,
    2,MapTiles::FullSquare,4,4,
    2,MapTiles::FullSquare,2,6,
    2,MapTiles::FullSquare,4,6,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    0,7,6,3,2,
    0,2,1,6,5,
    0,1,7,6,5,
    0,1,7,3,2,
    1,7,6,3,2,
    1,2,1,6,5,
    1,1,7,6,5,
    1,1,7,3,2,
    2,7,6,3,2,
    2,2,1,6,5,
    2,1,7,6,5,
    2,1,7,3,2,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    3,
    0,Object::Bat,3,6,HEALTH_BAT,
    0,Object::Spider,2,5,HEALTH_SPIDER,
    0,Object::Coin,3,5,HEALTH_NONE,
    1,Object::Bat,3,6,HEALTH_BAT,
    1,Object::Bat,2,5,HEALTH_BAT,
    1,Object::Bread,5,7,HEALTH_NONE,
    1,Object::FireTOP,5,1,HEALTH_NONE,
    1,Object::SpikeLHS,7,3,HEALTH_NONE,
    2,Object::Skeleton,3,6,HEALTH_SKELETON,
    2,Object::Bat,2,5,HEALTH_BAT,
    2,Object::Bread,5,7,HEALTH_NONE,
    2,Object::FireTOP,5,1,HEALTH_NONE,
    2,Object::SpikeLHS,7,3,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    2,
    7,1,
    5,3

};


PROGMEM const uint8_t MAP_Segment_Type02_05[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,21, 0,34,24,24, 0,  // 0
    38,38,38,21, 0, 0, 0, 0,23,  // 1
    38,38,38,21, 0, 0, 0, 0,23,  // 2
    38,38,38,38,27, 0, 0, 0,34,  // 3
    38,38,38,38,38,27, 0, 0, 0,  // 4
    38,38,38,38,38,38,22,22,22,  // 5
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

    0,MapTiles::Barrel,4,2,
    0,MapTiles::Barrel,6,4,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    5,
    0,Object::Bat,5,3,HEALTH_BAT,
    1,Object::Spider,5,3,HEALTH_SPIDER,
    2,Object::Skeleton,5,3,HEALTH_SKELETON,
    3,Object::Eye,5,3,HEALTH_EYE,
    4,Object::Snake,5,3,HEALTH_SNAKE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    7,1,

};