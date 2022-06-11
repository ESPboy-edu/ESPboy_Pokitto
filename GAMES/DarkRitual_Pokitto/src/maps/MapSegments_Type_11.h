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

PROGMEM const uint8_t MAP_Segment_Type11_00[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,38,38,38,38,38,38,  // 0
    38,38,38,38,38,38,38,38,38,  // 1
    38,38,38,98,24,98,38,38,38,  // 2
    38,38,38,21, 0,23,38,38,38,  // 3
    38,38,38,21, 0,23,38,38,38,  // 4
    38,38,38,21, 0,23,38,38,38,  // 5
    38,38,38,21, 0,23,38,38,38,  // 6
    38,38,38,21, 0,23,38,38,38,  // 7
    38,38,38,21, 0,23,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    2,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    1,MapTiles::CornerTR,3,8,
    1,MapTiles::StraightRHS,2,7,
    1,MapTiles::CornerLR,3,6,
    1,MapTiles::SwitchOn,3,7,
    1,MapTiles::SpearDoorBOT,4,6,

    1,MapTiles::CornerLL,5,4,
    1,MapTiles::StraightLHS,6,5,
    1,MapTiles::CornerTL,5,6,
    1,MapTiles::SwitchOn,5,5,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    1,3,7,4,6,
    1,5,5,4,6,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    0,

    // Entrance / Exit Options -----------
    1,
    4,3,

};

PROGMEM const uint8_t MAP_Segment_Type11_01[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,38,38,38,38,38,38,  // 0
    38,38,38,24,68,24,38,38,38,  // 1
    38,38,25, 0, 0, 0,26,38,38,  // 2
    38,21, 0, 0, 0, 0, 0,23,38,  // 3
    38,21, 0, 0, 0, 0, 0,23,38,  // 4
    38,21, 0, 0, 0, 0, 0,23,38,  // 5
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
    5,
    0,Object::Bat, 3, 2, HEALTH_BAT,
    1,Object::Spider, 3, 2, HEALTH_SPIDER,
    2,Object::Snake, 3, 2, HEALTH_SNAKE,
    3,Object::Skeleton, 3, 2, HEALTH_SKELETON,
    4,Object::Hobgoblin, 3, 2, HEALTH_HOBGOBLIN,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,

};

PROGMEM const uint8_t MAP_Segment_Type11_02[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,98,24,68,24,24,98,  // 0
    38,38,38,21, 0, 0, 0, 0,23,  // 1
    98,24,68,24,44,44,48, 0,23,  // 2
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 3
    21, 0,47,44,44,44,44,44,98,  // 4
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 5
    98,22,67,22,44,44,48, 0,23,  // 6
    38,38,38,21, 0, 0, 0, 0,23,  // 7
    38,38,38,21, 0,37,67,22,98,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    0,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    4,
    0,Object::Bat,1,3,HEALTH_BAT,
    0,Object::Bat,1,5,HEALTH_BAT,
    1,Object::Spider,1,4,HEALTH_SPIDER,
    2,Object::Snake,1,4,HEALTH_SNAKE,
    3,Object::Hobgoblin,1,4,HEALTH_HOBGOBLIN,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,1,

};


PROGMEM const uint8_t MAP_Segment_Type11_03[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,38,38,38,38,38,38,  // 0
    38,38,98,24,68,24,98,38,38,  // 1
    38,38,21, 0, 0, 0,23,38,38,  // 2
    98,24,35, 0, 0, 0,65,38,38,  // 3
    21, 0, 0, 0, 0, 0,23,38,38,  // 4
    66, 0,45, 0, 0, 0,23,38,38,  // 5
    21, 0,34,44,44,22, 0,38,38,  // 6
    21, 0, 0, 0, 0,23,38,38,38,  // 7
    98,22,22,36, 0,23,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    2,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,3,2,
    0,MapTiles::Barrel,5,2,
    1,MapTiles::Barrel,3,5,
    1,MapTiles::Barrel,5,5,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    4,
    0,Object::Bat,2,4,HEALTH_BAT,
    0,Object::Spider,1,7,HEALTH_SPIDER,
    1,Object::Bat,2,4,HEALTH_BAT,
    1,Object::Snake,1,7,HEALTH_SNAKE,
    2,Object::Snake,2,4,HEALTH_SNAKE,
    2,Object::Hobgoblin,1,7,HEALTH_HOBGOBLIN,
    3,Object::Skeleton,2,4,HEALTH_SKELETON,
    3,Object::Hobgoblin,1,7,HEALTH_HOBGOBLIN,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,

};