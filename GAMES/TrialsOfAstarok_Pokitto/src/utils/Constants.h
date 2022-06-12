#pragma once

#define _NO_DEATH
#define SOUNDS
#define COOKIE_INITIALISED 44

namespace Constants {
    
    constexpr uint8_t ParticlesMax              = 35;
    constexpr uint8_t TileSize                  = 12;
    constexpr uint8_t GameSeeds                 = 4;
    constexpr uint8_t MinLevelWidth             = 12;

    constexpr uint8_t RoomWidth                 = 12; 
    constexpr uint8_t RoomHeight                = 16;
    
    constexpr uint8_t RoomBytes                 = RoomWidth;

    constexpr uint8_t MapRooms                  = 3; 
    constexpr uint8_t MapObjects                = 15;
    constexpr uint8_t SpriteCap                 = 20;

    constexpr uint8_t Points_Health             = 100;
    constexpr uint8_t Points_Skill              = 20;
    constexpr uint8_t Points_Coin               = 20;
    constexpr uint8_t Points_Match              = 100;

    constexpr uint8_t No_Slot                   = 255;
    constexpr uint8_t NumberOfScores            = 3;

    constexpr uint8_t Fireball_NotMoving        = 127;
    constexpr int8_t Fireball_StartPos          = -20;

    constexpr uint8_t EventCounter_Death        = 50;
    constexpr uint8_t EventCounter_Flash        = 50;
    constexpr uint8_t EventCounter_LevelStart   = 21;

    constexpr uint8_t NoPlatform                = 255;
    constexpr uint8_t Collision_Platform        = 255;

    constexpr uint8_t UpperPlatform[]           = { 3, 3, 3, 3, 
                                                    3, 3, 3, 4, 
                                                    3, 4, 4, 0,                                              
                                                    3, 4, 4, 3,  
                                                    3, 3, 4, 4, 
                                                  };   

                             
}
