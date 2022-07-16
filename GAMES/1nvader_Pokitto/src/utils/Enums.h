#pragma once

#define SOUNDS
#define COOKIE_INITIALISED 39

enum class SoundEffects : uint8_t {
    Both,
    Music,
    SFX,
    None
};

enum class Theme : uint8_t {
    Game_Over,
    Hover,
    Main
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

enum class TitleScreenMode : uint8_t {
    NewGame,
    LevelSelect,
    SoundEffects
};

inline TitleScreenMode &operator++(TitleScreenMode &c ) {
    c = static_cast<TitleScreenMode>( (static_cast<uint8_t>(c) + 1) % 4 );
    return c;
}

inline TitleScreenMode operator++(TitleScreenMode &c, int ) {
    TitleScreenMode result = c;
    ++c;
    return result;
}

inline TitleScreenMode &operator--(TitleScreenMode &c ) {
    if (static_cast<uint8_t>(c) > 0) {
        c = static_cast<TitleScreenMode>( (static_cast<uint8_t>(c) - 1) % 4 );
    }
    else {
        c = static_cast<TitleScreenMode>( 3 );
    }
    return c;
}

inline TitleScreenMode operator--(TitleScreenMode &c, int ) {
    TitleScreenMode result = c;
    --c;
    return result;
}

enum class SoundEffect : uint8_t {
    Laser,
    Mini_Explosion,
    Level_Cleared,
    Bomb_HitGround,
    Player_Hit,
    Drop_Bomb,
};

enum class EnemyType : uint8_t {
    Single,
    Double,
};