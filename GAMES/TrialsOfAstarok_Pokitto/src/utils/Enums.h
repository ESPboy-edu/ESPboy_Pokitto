#pragma once

enum class FadeMode : uint8_t {
    None,
    FadeIn,
    FadeOut,
    Transition
};

enum class SoundSettings : uint8_t {
    Both,
    Music,
    SFX,
    None
};

inline SoundSettings &operator++(SoundSettings &c ) {
    c = static_cast<SoundSettings>( (static_cast<uint8_t>(c) + 1) % 4 );
    return c;
}

inline SoundSettings operator++(SoundSettings &c, int) {
    SoundSettings result = c;
    ++c;
    return result;
}

inline SoundSettings &operator--(SoundSettings &c ) {
    if (static_cast<uint8_t>(c) > 0) {
        c = static_cast<SoundSettings>( (static_cast<uint8_t>(c) - 1) % 4 );
    }
    else {
        c = static_cast<SoundSettings>( 3 );
    }
    return c;
}

inline SoundSettings operator--(SoundSettings &c, int) {
    SoundSettings result = c;
    --c;
    return result;
}

enum class SoundEffects : uint8_t {
    Introduction,
    JumpObstacle,
    Jump,
    Pause,
    ThrowKey,
    KongPound,
    Collide,
    Unlock,
    GameOver,
    FreeKong,
    Silence
};

enum GameState {
	SplashScreen_Init,
	SplashScreen,
	Title_Init,
	Title,
    IntroText_Init,
    IntroText,
	Seed_Init,
	Seed,
	PlayerSelect_Init,
	PlayerSelect,
	Game_Init,
	Game_Play,
	Game_Mini,
	MemoryGame_Init,
	MemoryGame,
	HighScore_Check,
	HighScore_Flash,
	HighScore_NoFlash,
    Display_Sign,
};

enum TitleScreenMode {
	Play,
	HighScore,
    SoundEffects
};

inline TitleScreenMode &operator++(TitleScreenMode &c ) {
    c = static_cast<TitleScreenMode>( (static_cast<uint8_t>(c) + 1) % 4 );
    return c;
}

inline TitleScreenMode operator++(TitleScreenMode &c, int) {
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

inline TitleScreenMode operator--(TitleScreenMode &c, int) {
    TitleScreenMode result = c;
    --c;
    return result;
}

enum MapLevel {
	BelowGround,
	AboveGround,
};

enum Hearts {
	FilledIn,
	Outline,
};

enum SpriteDataLayout {
	Type,
	Flags,
	Speed,
	Intelligence,
};

enum Direction { Up, Down, Left, Right, None };

enum ObjectTypes {
  Player = 0,  // Sprites
  Spider,
  Starman,
  Skull,
  Bolt,
  Health = 5,
  QBlock,  // Interactive Tiles
  BQBlock,
  MushBlock,
  Bricks = 9,
  AboveGroundExit,
  UnderGroundExit,
  Sign,
  Fireball,
  Coin,
  Chest_Closed,
  Chest_Open,
  MemoryMan,
};

enum EventType {
  Off = 0,
  Playing,
  Death_Init,
  Death,
  Flash,
  LevelExit,
  StartLevel
};

enum Sex {
  Male = 0,
  Female,
};

enum MemoryGameStatus {
  Hide = 0,
  Show,
  FlashRune,
  Delete,
};    
