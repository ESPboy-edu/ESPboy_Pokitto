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

PROGMEM const uint8_t MAP_Segment_Type08_00[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,38,38,38,38,38,38,  // 0
    38,38,38,38,38,38,38,38,38,  // 1
    38,38,38,38,38,38,38,38,38,  // 2
    24,24,68,24,24,24,68,24,24,  // 3
     0, 0, 0, 0, 0, 0, 0, 0, 0,  // 4
    22,22,22,36, 0,37,22,22,22,  // 5
    38,38,38,21, 0,23,38,38,38,  // 6
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
    0,Object::FireTOP,2,4,HEALTH_NONE,
    0,Object::FireBOT,3,4,HEALTH_NONE,
    1,Object::FireTOP,6,4,HEALTH_NONE,
    1,Object::FireTOP,7,4,HEALTH_NONE,
    2,Object::SpikeLHS,4,6,HEALTH_NONE,
    2,Object::SpikeRHS,4,7,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,

};


PROGMEM const uint8_t MAP_Segment_Type08_01[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,38,38,38,38,38,38,  // 0
    38,38,38,24,68,24,38,38,38,  // 1
    38,38,25, 0, 0, 0,26,38,38,  // 2
    24,35, 0, 0, 0, 0, 0,34,24,  // 3
     0, 0, 0, 0, 0, 0, 0, 0, 0,  // 4
    22,36, 0, 0, 0, 0, 0,37,22,  // 5
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
    3,
    0,Object::Bat, 2, 5, HEALTH_BAT,
    0,Object::Spider, 3, 6, HEALTH_SPIDER,
    1,Object::Skeleton, 2, 5, HEALTH_SKELETON,
    1,Object::Spider, 3, 6, HEALTH_SPIDER,
    2,Object::Bat, 2, 5, HEALTH_BAT,
    2,Object::Snake, 3, 6, HEALTH_SNAKE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,
};

PROGMEM const uint8_t MAP_Segment_Type08_02[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    98,24,68,24,24,24,68,24,98,  // 0
    21,83, 0, 0, 0, 0, 0, 0,23,  // 1
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 2
    35, 0, 0, 0, 0, 0, 0, 0,34,  // 3
     0, 0, 0, 0, 0, 0, 0, 0, 0,  // 4
    36, 0, 0, 0, 0, 0, 0, 0,37,  // 5
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 6
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 7
    98,22,22,36, 0,37,22,22,98,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    3,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,3,2,
    0,MapTiles::Barrel,4,2,
    0,MapTiles::Barrel,4,3,
    0,MapTiles::Barrel,5,2,
    0,MapTiles::SpearDoorLHS,8,4,
    0,MapTiles::SwitchOff,1,1,
    1,MapTiles::Barrel,7,6,
    1,MapTiles::Barrel,5,7,
    1,MapTiles::Barrel,6,7,
    2,MapTiles::CornerTL,3,3,
    2,MapTiles::StraightTOP,4,3,
    2,MapTiles::CornerTR,5,3,
    2,MapTiles::StraightLHS,3,4,
    2,MapTiles::Fill,4,4,
    2,MapTiles::StraightRHS,5,4,
    2,MapTiles::CornerLL,3,5,
    2,MapTiles::StraightBOT,4,5,
    2,MapTiles::CornerLR,5,5,
    2,MapTiles::Barrel,3,1,
    2,MapTiles::Barrel,4,1,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    0,1,1,8,4,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    3,
    0,Object::Bat, 1, 2, HEALTH_BAT,
    0,Object::Bat, 2, 1, HEALTH_BAT,
    0,Object::Bat, 2, 3, HEALTH_BAT,
    0,Object::Bread, 7, 7, HEALTH_NONE,
    1,Object::Coin, 2, 2, HEALTH_NONE, 
    1,Object::Coin, 2, 1, HEALTH_NONE, 
    1,Object::Coin, 1, 2, HEALTH_NONE, 
    1,Object::Bat, 6, 6, HEALTH_BAT,
    1,Object::Bat, 2, 2, HEALTH_BAT,
    1,Object::Bat, 7, 2, HEALTH_BAT,
    2,Object::Eye, 2, 2, HEALTH_EYE,
    2,Object::Snake, 3, 7, HEALTH_SNAKE,
    2,Object::Snake, 5, 6, HEALTH_SNAKE,
    2,Object::Chicken, 1, 2, HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    2,
    1,8,
    7,7,

};

PROGMEM const uint8_t MAP_Segment_Type08_03[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    98,24,68,24,24,24,68,24,98,  // 0
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 1
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 2
    35, 0, 0,45, 0,45, 0, 0,34,  // 3
     0, 0, 0,43, 0,43, 0, 0, 0,  // 4
    22,22,22,21, 0,23,22,22,22,  // 5
    38,38,38,21, 0,23,38,38,38,  // 6
    38,38,38,21, 0,23,38,38,38,  // 7
    38,38,38,21, 0,23,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    3,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,2,1,
    0,MapTiles::Barrel,1,2,
    0,MapTiles::Barrel,4,3,
    1,MapTiles::Barrel,7,1,
    1,MapTiles::Barrel,7,2,
    1,MapTiles::Barrel,2,3,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    4,
    0,Object::Bat,3,1,HEALTH_BAT,
    0,Object::Bat,2,4,HEALTH_BAT,
    0,Object::Bread,6,4,HEALTH_NONE,
    1,Object::Bat,6,1,HEALTH_BAT,
    1,Object::Bat,6,3,HEALTH_BAT,
    1,Object::Spider,1,3,HEALTH_SPIDER,
    2,Object::Bat,4,6,HEALTH_BAT,
    2,Object::Eye,7,3,HEALTH_EYE,
    2,Object::Chicken,3,1,HEALTH_NONE,
    3,Object::Skeleton,4,6,HEALTH_BAT,
    3,Object::Eye,7,3,HEALTH_EYE,
    3,Object::Coin,3,1,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    1,1,

};


PROGMEM const uint8_t MAP_Segment_Type08_04[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,98,24,24,68,24,24,98,  // 0
    38,38,21, 0, 0, 0, 0, 0,23,  // 1
    38,38,21, 0, 0, 0, 0, 0,23,  // 2
    24,24,21, 0, 0, 0,45, 0,34,  // 3
     0, 0,43, 0, 0, 0,43, 0, 0,  // 4
    36, 0,46, 0, 0, 0,23,22,22,  // 5
    21, 0, 0, 0, 0, 0,23,38,38,  // 6
    21, 0, 0, 0, 0, 0,23,38,38,  // 7
    98,22,22,36, 0,37,98,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    3,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,4,1,
    0,MapTiles::Barrel,5,1,
    1,MapTiles::Barrel,4,1,
    1,MapTiles::Barrel,3,7,
    2,MapTiles::Barrel,6,1,
    2,MapTiles::Barrel,2,7,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    3,
    0,Object::Bat,2,6,HEALTH_BAT,
    0,Object::Bat,3,3,HEALTH_BAT,
    0,Object::Bread,5,7,HEALTH_NONE,
    1,Object::Bat,4,4,HEALTH_BAT,
    1,Object::Bat,4,5,HEALTH_BAT,
    1,Object::Hobgoblin,4,6,HEALTH_HOBGOBLIN,
    2,Object::Bat,4,6,HEALTH_BAT,
    2,Object::Eye,4,5,HEALTH_BAT,
    2,Object::Chicken,5,7,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    3,1,

};


PROGMEM const uint8_t MAP_Segment_Type08_05[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,98,24,24,24,98,38,38,  // 0
    38,38,21,11,11,11,23,38,38,  // 1
    98,24,21, 0, 0, 0,23,38,38,  // 2
    35,11,46, 0, 0, 0,34,24,24,  // 3
     0, 0,58, 0, 0, 0,57, 0, 0,  // 4
    22,22,36, 0, 0, 0,45,11,37,  // 5
    38,38, 0,48,59,37, 0,22,98,  // 6
    38,38,21,11, 0,23,38,38,38,  // 7
    38,38,98,36, 0,23,38,38,38,  // 8

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
    0,1,3,2,4,
    0,3,1,2,4,
    0,3,7,4,6,
    0,4,1,4,6,
    0,7,5,6,4,
    0,5,1,6,4,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    3,
    0,Object::Bat,3,2,HEALTH_BAT,
    0,Object::Bat,5,2,HEALTH_BAT,
    0,Object::Coin,3,5,HEALTH_NONE,
    0,Object::Coin,5,5,HEALTH_NONE,
    1,Object::Snake,3,2,HEALTH_SNAKE,
    1,Object::Hobgoblin,5,2,HEALTH_HOBGOBLIN,
    1,Object::SackOCash,3,5,HEALTH_NONE,
    1,Object::Bread,5,5,HEALTH_NONE,
    2,Object::Eye,3,2,HEALTH_EYE,
    2,Object::Skeleton,5,2,HEALTH_SKELETON,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,

};


