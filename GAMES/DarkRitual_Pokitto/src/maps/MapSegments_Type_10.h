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


PROGMEM const uint8_t MAP_Segment_Type10_00[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,21, 0,23,38,38,38,  // 0
    38,38,38,66, 0,23,38,38,38,  // 1
    38,38,38,21, 0,23,38,38,38,  // 2
    24,24,24,35, 0,34,24,68,24,  // 3
     0, 0, 0, 0, 0, 0, 0, 0, 0,  // 4
    22,67,22,36, 0,37,22,22,22,  // 5
    38,38,38,21, 0,23,38,38,38,  // 6
    38,38,38,21, 0,65,38,38,38,  // 7
    38,38,38,21, 0,23,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    0,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    4,
    0,Object::Bat,1,4,HEALTH_BAT,
    0,Object::Eye,4,7,HEALTH_EYE,
    1,Object::Spider,7,4,HEALTH_SPIDER,
    2,Object::Coin,2,4,HEALTH_NONE,
    2,Object::Coin,6,4,HEALTH_NONE,
    2,Object::Coin,4,2,HEALTH_NONE,
    2,Object::Coin,4,6,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,

};


PROGMEM const uint8_t MAP_Segment_Type10_01[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    98,24,24,35, 0,34,24,24,98,  // 0
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 1
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

    0,MapTiles::Barrel,2,2,
    0,MapTiles::Barrel,3,3,
    0,MapTiles::Barrel,5,5,
    1,MapTiles::Barrel,2,2,
    1,MapTiles::Barrel,3,3,
    1,MapTiles::Barrel,5,5,
    2,MapTiles::FullSquare,2,2,
    2,MapTiles::FullSquare,6,2,
    2,MapTiles::FullSquare,2,6,
    2,MapTiles::FullSquare,6,6,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    3,
    0,Object::Bat,1,5,HEALTH_BAT,
    0,Object::Bat,7,2,HEALTH_BAT,
    0,Object::Coin,3,1,HEALTH_NONE,
    0,Object::Coin,5,7,HEALTH_NONE,
    1,Object::Spider, 1, 5, HEALTH_SPIDER,
    1,Object::Spider, 7, 2, HEALTH_SPIDER,
    2,Object::Snake, 1, 5, HEALTH_SNAKE,
    2,Object::Snake, 7, 2, HEALTH_SNAKE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    3,
    4,4,
    1,7,
    7,7,

};

PROGMEM const uint8_t MAP_Segment_Type10_02[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,38,21, 0,23,38,38,38,  // 0
    38,38,38,25, 0,26,38,38,38,  // 1
    38,38,25, 0, 0, 0,26,38,38,  // 2
    24,25, 0, 0, 0, 0, 0,26,24,  // 3
     0, 0, 0, 0, 0, 0, 0, 0, 0,  // 4
    22,27, 0, 0, 0, 0, 0,28,22,  // 5
    38,38,27, 0, 0, 0,28,38,38,  // 6
    38,38,38,27, 0,28,38,38,38,  // 7
    38,38,38,21, 0,23,38,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    3,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,3,3,
    0,MapTiles::Barrel,5,5,
    1,MapTiles::Barrel,3,3,
    1,MapTiles::Barrel,5,5,
    2,MapTiles::EndTRL,4,3,
    2,MapTiles::EndTBL,3,4,
    2,MapTiles::EndRBL,4,5,
    2,MapTiles::EndTRB,5,4,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    3,
    0,Object::Bat,5,2,HEALTH_BAT,
    0,Object::Bat,3,2,HEALTH_BAT,
    0,Object::Coin,3,6,HEALTH_NONE,
    0,Object::Coin,5,6,HEALTH_NONE,
    1,Object::Spider,3,6,HEALTH_SPIDER,
    1,Object::Spider,5,6,HEALTH_SPIDER,
    2,Object::Snake,5,2,HEALTH_SNAKE,
    2,Object::Snake,3,2,HEALTH_SNAKE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    4,
    2,3,
    5,3,
    2,5,
    5,5,


};


PROGMEM const uint8_t MAP_Segment_Type10_03[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,98,35, 0,34,24,24,98,  // 0
    38,38,21, 0, 0, 0, 0, 0,23,  // 1
    38,38,21, 0,47,44,36, 0,23,  // 2
    24,24,21, 0, 0, 0,43, 0,34,  // 3
     0, 0,43, 0, 0, 0,43, 0, 0,  // 4
    36, 0,43, 0, 0, 0,23,22,22,  // 5
    21, 0,34,44,48, 0,23,38,38,  // 6
    21, 0, 0, 0, 0, 0,23,38,38,  // 7
    98,22,22,36, 0,37,98,38,38,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    2,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,3,5,
    0,MapTiles::Barrel,5,3,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    2,
    0,Object::Bat,1,7,HEALTH_BAT,
    0,Object::Coin,7,1,HEALTH_NONE,
    1,Object::Spider,1,7,HEALTH_SPIDER,
    1,Object::Coin,7,1,HEALTH_NONE,
    2,Object::Bat,1,5,HEALTH_BAT,
    2,Object::Snake,7,2,HEALTH_SNAKE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,

};


PROGMEM const uint8_t MAP_Segment_Type10_04[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    98,24,24,35, 0,34,24,24,98,  // 0
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 1
    21, 0,37,44,44,44,36, 0,23,  // 2
    35, 0,43, 0, 0, 0,43, 0,34,  // 3
     0, 0,43, 0, 0, 0,43, 0, 0,  // 4
    36, 0,43, 0, 0, 0,43, 0,37,  // 5
    21, 0,34,48, 0,47,35, 0,23,  // 6
    21, 0, 0, 0, 0, 0, 0, 0,23,  // 7
    98,22,22,36, 0,37,22,22,98,  // 8

    // -----------------------------------
    // TileMap and Environment Options
    // -----------------------------------
   
    // Number of Options
    3,

    // Tilemap Options -------------------
    // Opt, Tile, x, y

    0,MapTiles::Barrel,3,3,
    1,MapTiles::Barrel,3,5,
    END_OF_OPTIONS,

    // Environment Options ---------------
    // Opt, Source x, y, Dest x, y 

    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    2,
    0,Object::Bat,4,3,HEALTH_BAT,
    0,Object::Coin,1,1,HEALTH_NONE,
    0,Object::Coin,7,1,HEALTH_NONE,
    0,Object::Coin,1,7,HEALTH_NONE,
    0,Object::Coin,7,7,HEALTH_NONE,
    1,Object::Spider,4,3,HEALTH_SPIDER,
    0,Object::Coin,1,7,HEALTH_NONE,
    0,Object::Coin,7,7,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    1,
    4,4,

};


PROGMEM const uint8_t MAP_Segment_Type10_05[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8
    38,38,98,35, 0,34,98,38,38,  // 0
    38,38,21,11, 0,11,23,38,38,  // 1
    98,24,98,36, 0,37,98,24,98,  // 2
    35,11,34,35,59,34,35,11,34,  // 3
     0, 0, 0,57, 0,58, 0, 0, 0,  // 4
    36,11,37,36,60,37,36,11,37,  // 5
    98,22,98,35, 0,34,98,22,98,  // 6
    38,38,21,11, 0,11,23,38,38,  // 7
    38,38,98,36, 0,37,98,38,38,  // 8

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

    0,1,3,3,4,
    0,1,3,4,3,
    0,1,3,5,4,
    0,1,5,4,3,
    0,1,5,5,4,
    0,1,5,4,5,

    0,5,1,4,3,
    0,5,1,5,4,
    0,5,1,4,6,
    0,3,1,5,4,
    0,3,1,4,5,
    0,3,1,3,4,

    0,7,5,5,4,
    0,7,5,4,5,
    0,7,5,3,4,
    0,7,3,4,5,
    0,7,3,3,4,
    0,7,3,4,3,

    0,3,7,4,5,
    0,3,7,3,4,
    0,3,7,4,3,
    0,5,7,3,4,
    0,5,7,4,3,
    0,5,7,5,4,
    END_OF_OPTIONS,

    // Enemy Options ---------------------
    // Opt , Object, x, y, Health 
    1,
    0,Object::SackOCash,4,4,HEALTH_NONE,
    END_OF_OPTIONS,

    // Entrance / Exit Options -----------
    4,
    4,0,
    4,8,
    0,4,
    8,4,

};