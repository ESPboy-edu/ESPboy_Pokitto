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

PROGMEM const uint8_t MAP_Segment_Type07_00[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,21, 0,23,38,38,38,  // 0
    38,38,38,21, 0,23,38,38,38,  // 1
    38,38,38,66, 0,23,38,38,38,  // 2
    38,38,38,21, 0,34,24,24,24,  // 3
    38,38,38,21, 0, 0, 0, 0, 0,  // 4
    38,38,38,21, 0,37,22,22,22,  // 5
    38,38,38,66, 0,23,38,38,38,  // 6
    38,38,38,21, 0,23,38,38,38,  // 7
    38,38,38,21, 0,23,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    0,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    4,
    0,Object::FireTOP,6,4,HEALTH_NONE,
    0,Object::FireBOT,7,4,HEALTH_NONE,
    1,Object::SpikeLHS,4,1,HEALTH_NONE,
    1,Object::SpikeRHS,4,2,HEALTH_NONE,
    2,Object::SpikeLHS,4,6,HEALTH_NONE,
    2,Object::SpikeRHS,4,7,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,

};

PROGMEM const uint8_t MAP_Segment_Type07_01[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,21, 0,23,38,38,38,  // 0
    38,38,38,35, 0,34,38,38,38,  // 1
    38,38,25, 0, 0, 0,26,38,38,  // 2
    38,21, 0, 0, 0, 0, 0,34,24,  // 3
    38,66, 0, 0, 0, 0, 0, 0, 0,  // 4
    38,21, 0, 0, 0, 0, 0,37,22,  // 5
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
    4,
    0,Object::Bat, 2, 5, HEALTH_NONE,
    0,Object::Spider, 3, 6, HEALTH_SPIDER,
    1,Object::Bat, 2, 3, HEALTH_NONE,
    1,Object::Bat, 2, 4, HEALTH_NONE,
    1,Object::Bat, 2, 5, HEALTH_NONE,
    2,Object::Spider, 3, 6, HEALTH_SPIDER,
    2,Object::Eye, 2, 5, HEALTH_EYE,
    3,Object::Spider, 3, 6, HEALTH_SPIDER,
    3,Object::Eye, 2, 5, HEALTH_EYE,
    3,Object::Skeleton, 3, 6, HEALTH_SKELETON,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    2,
    3,2,
    5,6,
};

PROGMEM const uint8_t MAP_Segment_Type07_02[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    98,24,24,35, 0,34,24,24,98,  // 0
    21,83, 0, 0, 0, 0, 0, 0,23,  // 1
    66, 0, 0, 0, 0, 0, 0, 0,23,  // 2
    21, 0, 0, 0, 0, 0, 0, 0,34,  // 3
    21, 0, 0, 0, 0, 0, 0, 0, 0,  // 4
    21, 0, 0, 0, 0, 0, 0, 0,37,  // 5
    66, 0, 0, 0, 0, 0, 0, 0,23,  // 6
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
    3,
    0,Object::Bat, 1, 2, HEALTH_BAT,
    0,Object::Spider, 2, 2, HEALTH_SPIDER,
    1,Object::Skeleton, 1, 2, HEALTH_SKELETON,
    1,Object::Spider, 2, 2, HEALTH_SPIDER,
    2,Object::Snake, 1, 2, HEALTH_SNAKE,
    2,Object::Spider, 2, 2, HEALTH_SPIDER,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    2,
    4,4,
    1,7,

};

PROGMEM const uint8_t MAP_Segment_Type07_03[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    98,24,24,35, 0,23,38,38,38,  // 0
    21, 0, 0, 0, 0,23,38,38,38,  // 1
    66, 0, 0, 0, 0,23,38,38,38,  // 2
    21, 0, 0,47,44,24,24,24,24,  // 3
    21, 0, 0, 0, 0, 0, 0, 0, 0,  // 4
    21, 0, 0,47,44,22,22,22,22,  // 5
    66, 0, 0, 0, 0,23,38,38,38,  // 6
    21, 0, 0, 0, 0,23,38,38,38,  // 7
    98,22,22,36, 0,23,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    3,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,2,1,
    0,MapTiles::Barrel,1,3,
    0,MapTiles::Barrel,4,6,
    1,MapTiles::Barrel,1,7,
    1,MapTiles::Barrel,2,7,
    1,MapTiles::Barrel,2,2,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    4,
    0,Object::Bat,1,2,HEALTH_BAT,
    0,Object::Bat,2,4,HEALTH_BAT,
    1,Object::Bat,2,6,HEALTH_BAT,
    1,Object::Bat,2,4,HEALTH_BAT,
    1,Object::Hobgoblin,1,4,HEALTH_HOBGOBLIN,
    2,Object::Bat,2,3,HEALTH_BAT,
    2,Object::Eye,2,6,HEALTH_BAT,
    2,Object::Chicken,4,2,HEALTH_NONE,
    2,Object::Snake,2,3,HEALTH_SNAKE,
    2,Object::Eye,2,6,HEALTH_BAT,
    2,Object::Bread,4,2,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    1,1,

};


PROGMEM const uint8_t MAP_Segment_Type07_04[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,21, 0,34,24,24,98,  // 0
    38,38,38,21, 0, 0, 0, 0,23,  // 1
    98,24,24,24,44,48, 0, 0,23,  // 2
    21, 0, 0, 0, 0, 0, 0, 0,34,  // 3
    21, 0, 0, 0, 0, 0, 0, 0, 0,  // 4
    21, 0, 0, 0, 0, 0, 0, 0,37,  // 5
    21, 0, 0,47,44,22,22,22,98,  // 6
    21, 0, 0, 0, 0,23,38,38,38,  // 7
    98,22,22,36, 0,23,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    3,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,6,5,
    0,MapTiles::Barrel,5,5,
    1,MapTiles::Barrel,2,3,
    1,MapTiles::Barrel,3,3,
    2,MapTiles::Barrel,1,4,
    2,MapTiles::Barrel,4,5,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    3,
    0,Object::Bat,3,4,HEALTH_BAT,
    0,Object::Bat,3,5,HEALTH_BAT,
    0,Object::Bread,5,4,HEALTH_NONE,
    1,Object::Bat,7,1,HEALTH_BAT,
    1,Object::Eye,5,4,HEALTH_EYE,
    1,Object::Hobgoblin,5,4,HEALTH_HOBGOBLIN,
    2,Object::Bat,7,1,HEALTH_BAT,
    2,Object::Eye,5,4,HEALTH_EYE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    1,3,

};


PROGMEM const uint8_t MAP_Segment_Type07_05[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,98,35, 0,23,38,38,38,  // 0
    38,38,21,11, 0,23,38,38,38,  // 1
    98,24,24,48,59,34,98,24, 0,  // 2
    21,11, 0, 0, 0, 0,46,11,34,  // 3
    21,11, 0, 0, 0, 0,58, 0, 0,  // 4
    21,11, 0, 0, 0, 0,37,22,22,  // 5
    98,22,22,36,60,47,98,38,38,  // 6
    38,38,38,21, 0,11,23,38,38,  // 7
    38,38,38,21, 0,37,98,38,38,  // 8

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
    0,3,1,4,2,
    0,7,3,6,4,
    0,5,7,4,6,
    0,1,3,4,2,
    0,1,4,6,4,
    0,1,5,4,6,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    3,
    0,Object::Bat,2,3,HEALTH_BAT,
    0,Object::Bat,2,5,HEALTH_BAT,
    0,Object::Coin,5,3,HEALTH_NONE,
    0,Object::Coin,5,5,HEALTH_NONE,
    1,Object::Hobgoblin,2,3,HEALTH_HOBGOBLIN,
    1,Object::Skeleton,2,5,HEALTH_SKELETON,
    1,Object::SackOCash,5,3,HEALTH_NONE,
    1,Object::Bread,5,5,HEALTH_NONE,
    2,Object::Eye,2,3,HEALTH_EYE,
    2,Object::Snake,2,5,HEALTH_SNAKE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,

};

