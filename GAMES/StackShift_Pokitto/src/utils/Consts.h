#pragma once

#define SOUNDS
#define _DEBUG
#define _DEBUG_ROCKS

#define ROCK_POINTS 25
#define NO_SCORE 255
#define BOARD_WIDTH 6
#define BOARD_HEIGHT 15
#define PART_SIZE 11
#define BOARD_X_OFFSET 74
#define BOARD_Y_OFFSET 2
#define PARTICLE_MAX 60
#define numberOfBadWords 10
#define wordBufferLength 10

#define NO_BLOCK_FOUND 255
#define COOKIE_INITIALISED 14

#define ROCK_FREQ_LOW_EASY 20
#define ROCK_FREQ_MED_EASY 15
#define ROCK_FREQ_HIGH_EASY 10

#define ROCK_FREQ_LOW_HARD 10
#define ROCK_FREQ_MED_HARD 8
#define ROCK_FREQ_HIGH_HARD 6

#define SCORING_ROW_COUNT_PART_STOPPED 2
#define SCORING_ROW_COUNT_SCORING_COMBO 12

enum class SoundEffects : uint8_t {
    Both,
    Music,
    SFX,
    None
};

enum class Level : uint8_t {
    Easy,
    Hard
};

enum class SoundTheme : uint8_t {
    Bubble_Short,
    Bubble_Med,
    Bubble_Med2,
    Bubble_Long,
    Chime,
    Unknown
};

enum class Color : uint8_t {
    Green,
    Red,
    Yellow,
    White,
    MauvePink,
    Max = MauvePink
};

enum class ExplosionSize : uint8_t {
    Small,
    Medium,
    Large,
    None
};

enum class ParticleType : uint8_t {
    Zero,
    One,
    Two,
    Score,
};

enum class GameState : uint8_t {
    SplashScreen,
    Title,
    Play_Init,
    Play,
    End,
    HighScore_Init,
    HighScore,
    Pause_Init,
    Pause
};

enum class BoardType : uint8_t {
    Existing_Green,
    Existing_Red,
    Existing_Yellow,
    Existing_Rock, //3
    Existing_First = Existing_Green,
    Existing_Last = Existing_Rock,
    New_Green,
    New_Red,
    New_Yellow,
    New_Rock, //7
    New_First = New_Green,
    New_Last = New_Rock,
    Marked_Green,
    Marked_Red,
    Marked_Yellow,
    Marked_Rock, //1
    Marked_First = Marked_Green,
    Marked_Last = Marked_Rock,
    None,
};

struct SplashScreenVariables {

    uint8_t counter = 0;
    uint8_t buttonCounter = 0;

};

struct Shake {
    ExplosionSize explosionSize = ExplosionSize::None;
    uint8_t count = 0;
    int16_t xOffset = 0;
    int16_t yOffset = 0;
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