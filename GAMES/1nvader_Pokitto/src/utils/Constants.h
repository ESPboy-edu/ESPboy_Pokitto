#pragma once

#include "Enums.h"


// - Debug ------------------------------

#define _DEBUG
#define _SOUNDS

// ---------------------------------------

#define MOTHERSHIP_SIZE_LANDSCAPE SIZE_2X2
#define MOTHERSHIP_SIZE_PORTRAIT SIZE_2X2

namespace Constants {

    constexpr uint8_t Score_DropBomb = 25;
    constexpr uint8_t Score_ChangeDirection = 50;
    constexpr uint8_t Score_Double = 90;

    constexpr uint8_t Random_RemoveEnemy = 5;
    constexpr uint8_t Random_AddEnemy = 25;

    constexpr uint8_t ScreenWidth = 110;
    constexpr uint8_t ScreenHeight = 88;

    constexpr uint8_t ParticlesMax = 30;
    constexpr uint8_t MaskWidth = 1;

    constexpr uint8_t FlashSpeed = 64;
    constexpr uint8_t TugOfWarRowAdjustment = 7;
    constexpr uint8_t WaveIncrease = 50;
    
    constexpr uint8_t PlayerHeight = 8;
    constexpr uint8_t PlayerWidth = 11;
    constexpr uint8_t PlayerHeightNoMask = 7;
    constexpr uint8_t PlayerWidthNoMask = 9;

    constexpr uint8_t BombHeight = 8;
    constexpr uint8_t BombWidth = 5;
    constexpr uint8_t BulletHeight = 7;
    constexpr uint8_t BulletWidth = 5;


    namespace Portrait {
        constexpr int8_t PlayerMinPos = -1;
        constexpr int8_t PlayerMaxPos = ScreenHeight - 11;//  53;
    }

    namespace Landscape {
        constexpr int8_t PlayerMinPos = -1;
        constexpr int8_t PlayerMaxPos = ScreenWidth - 11;
    }

    constexpr uint8_t MothershipHeight = 16;
    constexpr uint8_t MothershipWidth = 23;
    
    constexpr uint8_t MothershipCounterMax = 80;
    constexpr uint8_t MothershipExplosionMax = 8;
    constexpr uint8_t MothershipRowHeight = 8;

    namespace Portrait {
        constexpr int16_t MothershipMinPos = -2800;
        constexpr int16_t MothershipMaxPos = 9800;
        constexpr int16_t MothershipStartHeight = ScreenWidth - 24;
    }

    namespace Landscape {
        constexpr int16_t MothershipMinPos = -2800;
        constexpr int16_t MothershipMaxPos = 13800;
        constexpr int16_t MothershipStartHeight = 16;
    }
    
    constexpr uint8_t Arrow_Frames[] = { 0, 1, 2, 1 };
}

enum class GameState : uint8_t {
    Splash_Init, // 0
    Splash,
    Title_Init,
    Title,
    Game_Init,
    Game,
    TugOfWar_Init,
    TugOfWar,
    GameOver_Init,
    GameOver,
};

enum class GameMode : uint8_t {
    Single,
    Double,
    TugOfWar
};

enum class GameRotation : uint8_t {
    Portrait,
    Landscape
};

enum class Movement : uint8_t {
    Up,
    Down,
    Left,
    Right
};


// --------------------------------------------------------------------

inline GameMode &operator++(GameMode &c ) {
    c = static_cast<GameMode>( static_cast<uint8_t>(c) + 1 );
    return c;
}

inline GameMode operator++(GameMode &c, int ) {
    GameMode result = c;
    ++c;
    return result;
}

inline GameMode &operator--(GameMode &c ) {
    c = static_cast<GameMode>( static_cast<uint8_t>(c) - 1 );
    return c;
}

inline GameMode operator--(GameMode &c, int ) {
    GameMode result = c;
    --c;
    return result;
}

