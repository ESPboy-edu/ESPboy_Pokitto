#pragma once

#define _DEBUG
#define SOUNDS
#define COOKIE_INITIALISED 16

namespace Constants {

    constexpr uint8_t No_Score = 255;
    constexpr uint8_t Star_Count = 40;

    constexpr uint8_t Screen_Height = 176;
    constexpr uint8_t Distance = 64;
    constexpr uint8_t GrindToHalt = 113;

    constexpr uint8_t Player_Width = 20;
    constexpr uint8_t Player_Height = 13;
    constexpr uint8_t Player_Inertia = 8;
    constexpr uint8_t Player_X_Max = 220 - Constants::Player_Width - 2;

    constexpr uint8_t Player_Bullet_Count = 6;
    constexpr uint8_t Player_Bullet_Width = 8;
    constexpr uint8_t Player_Bullet_Height = 5;
    constexpr uint8_t Bullet_None = 255;

    constexpr uint8_t Player_Bomb_Count = 2;
    constexpr uint8_t Player_Bomb_Width = 5;
    constexpr uint8_t Player_Bomb_Height = 8;

    constexpr uint8_t Bomb_None = 255;

    constexpr uint8_t Enemy_Bullet_Count = 4;
    constexpr uint8_t Enemy_Bullet_Width = 2;
    constexpr uint8_t Enemy_Bullet_Height = 2;
    constexpr uint8_t Enemy_Max_Width = 50;
    constexpr uint8_t Enemy_Count = 10;
    constexpr uint8_t Enemy_None = 255;    

    constexpr uint8_t Enemy_Space = 3;
    constexpr uint8_t Rocket_Width = 9;
    constexpr uint8_t Rocket_Height = 20;

    constexpr uint8_t FuelDepot_Width = 23;
    constexpr uint8_t FuelDepot_Height = 31;

    constexpr uint8_t GroundPod_Width = 16;
    constexpr uint8_t GroundPod_Height = 16;

    constexpr uint8_t SurfaceAir_Width = 24;
    constexpr uint8_t SurfaceAir_Height = 18;

    constexpr uint8_t Mine_Width = 15;
    constexpr uint8_t Mine_Height = 15;
    constexpr uint8_t Mine_Path_Count = 10;

    constexpr uint8_t City_Width = 50;
    constexpr uint8_t City_Height = 21;

    constexpr uint8_t FuelCan_Width = 12;
    constexpr uint8_t FuelCan_Height = 16;

    constexpr uint8_t Particle_Count = 75;
    constexpr uint8_t Particle_None = 255;
    constexpr uint8_t Shockwave_Count = 20;
    constexpr uint8_t Shockwave_None = 255;

    constexpr uint8_t Stage_Transition_Phase_Length = 172;


    // Scenery limits ..

    constexpr uint16_t Scenery_Top = 15;
    constexpr uint16_t Scenery_DistanceBetween_Min_Start = 0;
    constexpr uint16_t Scenery_DistanceBetween_Min_End = Scenery_DistanceBetween_Min_Start + 100;
    constexpr uint16_t Scenery_DistanceBetween_Normal_Start = Scenery_DistanceBetween_Min_End + 1;
    constexpr uint16_t Scenery_DistanceBetween_Normal_End = Scenery_DistanceBetween_Normal_Start + 100;

    constexpr uint16_t Scenery_DistanceBetweenEnemies_Min = 2;
    constexpr uint16_t Scenery_DistanceBetweenEnemies_Max = 8;


    // Enemy limits ..

    constexpr uint16_t LaunchEnemy_Gap = 2200;
    constexpr uint16_t LaunchEnemy_Start = 0;
    constexpr uint16_t LaunchEnemy_Nothing = LaunchEnemy_Start + LaunchEnemy_Gap;

    constexpr uint16_t LaunchEnemy_City_00_Start = LaunchEnemy_Nothing + 1;
    constexpr uint16_t LaunchEnemy_City_00_End = LaunchEnemy_City_00_Start + 4;
    constexpr uint16_t LaunchEnemy_City_01_Start = LaunchEnemy_City_00_End + 1;
    constexpr uint16_t LaunchEnemy_City_01_End = LaunchEnemy_City_01_Start + 4;
    constexpr uint16_t LaunchEnemy_City_02_Start = LaunchEnemy_City_01_End + 1;
    constexpr uint16_t LaunchEnemy_City_02_End = LaunchEnemy_City_02_Start + 4;

    constexpr uint16_t LaunchEnemy_OneRocket_Start = LaunchEnemy_City_02_End + 1;
    constexpr uint16_t LaunchEnemy_OneRocket_End = LaunchEnemy_OneRocket_Start + 24;
    constexpr uint16_t LaunchEnemy_TwoRocket_Start = LaunchEnemy_OneRocket_End + 1;
    constexpr uint16_t LaunchEnemy_TwoRocket_End = LaunchEnemy_TwoRocket_Start + 12;
    constexpr uint16_t LaunchEnemy_ThreeRocket_Start = LaunchEnemy_TwoRocket_End + 1;
    constexpr uint16_t LaunchEnemy_ThreeRocket_End = LaunchEnemy_ThreeRocket_Start + 1;

    constexpr uint16_t LaunchEnemy_OneRocket_FuelDepot_Start = LaunchEnemy_ThreeRocket_End + 1;
    constexpr uint16_t LaunchEnemy_OneRocket_FuelDepot_End = LaunchEnemy_OneRocket_FuelDepot_Start + 2;
    constexpr uint16_t LaunchEnemy_TwoRocket_FuelDepot_Start = LaunchEnemy_OneRocket_FuelDepot_End + 1;
    constexpr uint16_t LaunchEnemy_TwoRocket_FuelDepot_End = LaunchEnemy_TwoRocket_FuelDepot_Start + 1;

    constexpr uint16_t LaunchEnemy_FuelDepot_OneRocket_Start = LaunchEnemy_TwoRocket_FuelDepot_End + 1;
    constexpr uint16_t LaunchEnemy_FuelDepot_OneRocket_End = LaunchEnemy_FuelDepot_OneRocket_Start + 2;
    constexpr uint16_t LaunchEnemy_FuelDepot_TwoRocket_Start = LaunchEnemy_FuelDepot_OneRocket_End + 1;
    constexpr uint16_t LaunchEnemy_FuelDepot_TwoRocket_End = LaunchEnemy_FuelDepot_TwoRocket_Start + 1;

    constexpr uint16_t LaunchEnemy_OneRocket_FuelDepot_OneRocket_Start = LaunchEnemy_FuelDepot_TwoRocket_End + 1;
    constexpr uint16_t LaunchEnemy_OneRocket_FuelDepot_OneRocket_End = LaunchEnemy_OneRocket_FuelDepot_OneRocket_Start + 1;

    constexpr uint16_t LaunchEnemy_OneRocket_GroundPod_Start = LaunchEnemy_OneRocket_FuelDepot_OneRocket_End + 1;
    constexpr uint16_t LaunchEnemy_OneRocket_GroundPod_End = LaunchEnemy_OneRocket_GroundPod_Start + 1;
    constexpr uint16_t LaunchEnemy_TwoRocket_GroundPod_Start = LaunchEnemy_OneRocket_GroundPod_End + 1;
    constexpr uint16_t LaunchEnemy_TwoRocket_GroundPod_End = LaunchEnemy_TwoRocket_GroundPod_Start + 1;

    constexpr uint16_t LaunchEnemy_GroundPod_OneRocket_Start = LaunchEnemy_TwoRocket_GroundPod_End + 1;
    constexpr uint16_t LaunchEnemy_GroundPod_OneRocket_End = LaunchEnemy_GroundPod_OneRocket_Start + 1;
    constexpr uint16_t LaunchEnemy_GroundPod_TwoRocket_Start = LaunchEnemy_GroundPod_OneRocket_End + 1;
    constexpr uint16_t LaunchEnemy_GroundPod_TwoRocket_End = LaunchEnemy_GroundPod_TwoRocket_Start + 1;

    constexpr uint16_t LaunchEnemy_OneRocket_GroundPod_OneRocket_Start = LaunchEnemy_GroundPod_TwoRocket_End + 1;
    constexpr uint16_t LaunchEnemy_OneRocket_GroundPod_OneRocket_End = LaunchEnemy_OneRocket_GroundPod_OneRocket_Start + 1;

    constexpr uint16_t LaunchEnemy_OneRocket_SurfaceAir_Start = LaunchEnemy_OneRocket_GroundPod_OneRocket_End + 1;
    constexpr uint16_t LaunchEnemy_OneRocket_SurfaceAir_End = LaunchEnemy_OneRocket_SurfaceAir_Start + 1;
    constexpr uint16_t LaunchEnemy_TwoRocket_SurfaceAir_Start = LaunchEnemy_OneRocket_SurfaceAir_End + 1;
    constexpr uint16_t LaunchEnemy_TwoRocket_SurfaceAir_End = LaunchEnemy_TwoRocket_SurfaceAir_Start + 1;

    constexpr uint16_t LaunchEnemy_SurfaceAir_OneRocket_Start = LaunchEnemy_TwoRocket_SurfaceAir_End + 1;
    constexpr uint16_t LaunchEnemy_SurfaceAir_OneRocket_End = LaunchEnemy_SurfaceAir_OneRocket_Start + 1;
    constexpr uint16_t LaunchEnemy_SurfaceAir_TwoRocket_Start = LaunchEnemy_SurfaceAir_OneRocket_End + 1;
    constexpr uint16_t LaunchEnemy_SurfaceAir_TwoRocket_End = LaunchEnemy_SurfaceAir_TwoRocket_Start + 1;

    constexpr uint16_t LaunchEnemy_OneRocket_SurfaceAir_OneRocket_Start = LaunchEnemy_SurfaceAir_TwoRocket_End + 1;
    constexpr uint16_t LaunchEnemy_OneRocket_SurfaceAir_OneRocket_End = LaunchEnemy_OneRocket_SurfaceAir_OneRocket_Start + 1;

    constexpr uint16_t LaunchEnemy_Max = LaunchEnemy_OneRocket_SurfaceAir_OneRocket_End;

};

namespace Pathways {

    constexpr uint8_t Figure8[] = {
        12, 0, 13, 0, 14, 0, 15, 1, 16, 1, 17, 1, 18, 2, 19, 2, 20, 3, 21, 4, 22, 5, 22, 6, 23, 7, 23, 8, 23, 9, 24, 10, 24, 11, 24, 12, 24, 13, 24, 14, 23, 15, 23, 16, 
        23, 17, 22, 18, 22, 19, 21, 20, 20, 21, 19, 22, 18, 22, 15, 23, 16, 23, 17, 23, 14, 24, 13, 24, 12, 24, 11, 24, 10, 24, 9, 25, 8, 25, 7, 25, 6, 26, 5, 26, 4, 27,    
        3, 28, 2, 29, 2, 30, 1, 31, 1, 32, 1, 33, 0, 34, 0, 35, 0, 36, 0, 37, 0, 38, 1, 39, 1, 40, 1, 41, 2, 42, 2, 43, 3, 44, 4, 45, 5, 46, 6, 46, 7, 47, 8, 47, 9, 47, 
        10, 48, 11, 48, 12, 48, 13, 48, 14, 48, 15, 7, 16, 47, 17, 47, 18, 46, 19, 46, 20, 45, 21, 44, 22, 43, 22, 42, 23, 41, 23, 40, 23, 39, 24, 38, 24, 37, 24, 36, 24, 
        35, 24, 34, 23, 33, 23, 32, 23, 31, 22, 30, 22, 29, 21, 28, 20, 27, 19, 26, 18, 26, 17, 25, 16, 25, 15, 25, 14, 24, 13, 24, 12, 24, 11, 24, 10, 24, 9, 23, 8, 23, 
        7, 23, 6, 22, 5, 22, 4, 21, 3, 20, 2, 19, 2, 18, 1, 17, 1, 16, 1, 15, 0, 14, 0, 13, 0, 12, 0, 11, 0, 10, 1, 9, 1, 8, 1, 7, 2, 6, 2, 5, 3, 4, 4, 3, 5, 2, 6, 2, 7, 
        1, 8, 1, 9, 1, 10, 0, 11, 0,
    };

    constexpr uint8_t Circle[] = {
        12, 0, 13, 0, 14, 0, 15, 1, 16, 1, 17, 1, 18, 2, 19, 2, 20, 3, 21, 4, 22, 5, 22, 6, 23, 7, 23, 8, 23, 9, 24, 10, 24, 11, 24, 12, 24, 13, 24, 14, 23, 15, 23, 16, 
        23, 17, 22, 18, 22, 19, 21, 20, 20, 21, 19, 22, 18, 22, 15, 23, 16, 23, 17, 23, 14, 24, 13, 24, 12, 24, 11, 24, 10, 24, 9, 23, 8, 23, 7, 23, 6, 22, 5, 22, 4, 21, 
        3, 20, 2, 19, 2, 18, 1, 17, 1, 16, 1, 15, 0, 14, 0, 13, 0, 12, 0, 11, 0, 10, 1, 9, 1, 8, 1, 7, 2, 6, 2, 5, 3, 4, 4, 3, 5, 2, 6, 2, 7, 1, 8, 1, 9, 1, 10, 0, 11, 0,
    };

    constexpr int8_t TitleSeq[] = {
        -48, -48, -48, -48, -48, -41, -34, -26, -20, -14, -7, 0, 7, 14, 21, 26, 31, 36, 41, 46, 52, 58, 53, 49, 46, 44, 43, 43, 44, 46, 49, 53, 58, 54, 51, 49, 48, 48, 49, 51, 54, 58, 55, 53, 52, 52, 53, 55, 58, 56, 55, 55, 56, 58, 57, 58, 
    };

};

enum class GameStartMode : int16_t {
    LineEntry_Start = 50,
    LineEntry_End = LineEntry_Start + 50,
    TextEntry_Start = LineEntry_End + 1,
    TextEntry_End = TextEntry_Start + 106,
    Pause_Start = TextEntry_End + 1,
    Pause_End = Pause_Start + 150,
    TextExit_Start = Pause_End + 1,
    TextExit_End = TextExit_Start + 111,
    LineExit_Start = TextExit_End + 1,
    LineExit_End = LineExit_Start + 50,
    Sequence_End = LineExit_End + 51
};

enum class TransitionMode : int16_t {
    LineEntry_Start = 50,
    LineEntry_End = LineEntry_Start + 50,
    TextEntry_Start = LineEntry_End + 1,
    TextEntry_End = TextEntry_Start + 99,
    Pause_Start = TextEntry_End + 1,
    Pause_End = Pause_Start + 150,
    TextExit_Start = Pause_End + 1,
    TextExit_End = TextExit_Start + 98,
    LineExit_Start = TextExit_End + 1,
    LineExit_End = LineExit_Start + 50,
    Sequence_End = LineExit_End + 51
};

enum class GameState : uint8_t {
    Splash_Init,
    Splash,
    Title_Init,
    Title,
    Scenario_Init,
    Scenario,
    Game_Init,
    Game_Start,
    Game,
    GameOver,
    HighScore_Init,
    HighScore,
};

enum class EnemyType : uint8_t {
    Rocket,
    FuelDepot,
    GroundPod,
    SurfaceAir,
    Mine,
    City_00,
    City_01,
    City_02,
    FuelCan,
    Eighter,
    Circler,
};

enum class Themes : uint8_t {
    Main,
    StageComplete
};

enum class ExplosionSize : int8_t {
    Small,
    Medium,
    Large,
    Huge
};

enum class ExplosionColor : int8_t {
    Blue,
    Red
};

enum class Direction : uint8_t {
    Left,
    Up,
    Right,
    Down,
    None,
};

enum class SoundEffects : uint8_t {
    Both,
    Music,
    SFX,
    None
};

enum class SoundEffect : uint8_t {
    PlayerLaser,
    PlayerBomb,
    Explosion_00,
    Explosion_01,
    Explosion_02,
    RocketLaunch,
    SurfaceToAir,
    FuelUp
};

inline SoundEffects &operator++(SoundEffects &c ) {
    c = static_cast<SoundEffects>( (static_cast<uint8_t>(c) + 1) % 4 );
    return c;
}

inline SoundEffects operator++(SoundEffects &c, int ) {
    SoundEffects result = c;
    ++c;
    return result;
}

inline SoundEffects &operator--(SoundEffects &c ) {
    if (static_cast<uint8_t>(c) > 0) {
        c = static_cast<SoundEffects>( (static_cast<uint8_t>(c) - 1) % 4 );
    }
    else {
        c = static_cast<SoundEffects>( 3 );
    }
    return c;
}

inline SoundEffects operator--(SoundEffects &c, int ) {
    SoundEffects result = c;
    --c;
    return result;
}