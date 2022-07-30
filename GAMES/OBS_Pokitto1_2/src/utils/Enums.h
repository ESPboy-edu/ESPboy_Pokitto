#pragma once

#define SOUNDS
#define COOKIE_INITIALISED 39

enum class GameState : uint8_t {
    Splash_Init, // 0
    Splash,
    Title_Init,
    Title,
    Game_Init,
    Game,
    Game_EnemyLeaving,
    Game_AsteroidLeaving,
    Game_BossEntering,
    Game_Boss,
    Game_BossLeaving,
    Score,
    GameOver_Init,
    GameOver,
};

enum class SoundEffects : uint8_t {
    Both,
    Music,
    SFX,
    None
};

enum class SoundEffect : uint8_t {
    Laser,
    Mini_Explosion,
    Player_Hit,
    Game_Over,
    KeyPress,
    Health
};

enum class Theme : uint8_t {
    Main,
    Boss,
    BossExplosion
};
    
enum class Direction : int8_t {
	Up = -1,
	None = 0,
	Down = 1,
    UpLeft,
    Left,
    DownLeft,
};
     
enum class Motion : uint8_t {
	Slow,
	Fast
};
 
enum class Path : uint8_t {
    Small,
	Medium,
	Large,
};

enum class HitObject : int8_t {
    None,
	LargeAsteroid,
	Enemy,
    Player,
    Boss,
    BossBullet
};

enum class TitleMode : int8_t {
    OBS,
	Scroll_One,
	Scenario,
	Scroll_Two,
	Entrance,
};

enum class ExplosionSize : int8_t {
    Small,
    Medium,
    Large
};

enum class ExplosionColor : int8_t {
    Blue,
    Red
};

enum class BossColor : int8_t {
    Green,
    Blue,    
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
