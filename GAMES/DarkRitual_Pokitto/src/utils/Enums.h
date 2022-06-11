#pragma once

enum class SpriteStatus : uint8_t {
    Inactive,
    Active,
    Dying
};

enum class SoundTheme : uint8_t {
    Main,
    Hell,
    Shop,
    Shop_Hell,
    Boss,
    Boss_Hell,
    EOG,
    EOG_Hell,
    Unknown
};

enum class SoundEffect : uint8_t {
    LeverPull,
    OpenChest,
    CannotPickUp,
    PickUpCoin,
    Death1,
    Death3,
    Damage,
    CastSpell,
    PressPlate,
    BarrelExploding,
    MainTheme,
    BossTheme,
    ShopTheme,
    Win
};

enum class GameMode : uint8_t {
    Normal,
    Help,
    Resume,
};

enum class WalkType : uint8_t {
    Stop,
    Normal,
    Slow,
};

enum class TitleScreenOption : uint8_t {
    Resume,
    Start,
    HighScore,
    Help
};

inline TitleScreenOption &operator++(TitleScreenOption &c ) {
    c = static_cast<TitleScreenOption>( static_cast<uint8_t>(c) + 1 );
    return c;
}

inline TitleScreenOption operator++(TitleScreenOption &c, int ) {
    TitleScreenOption result = c;
    ++c;
    return result;
}

inline TitleScreenOption &operator--(TitleScreenOption &c ) {
    c = static_cast<TitleScreenOption>( static_cast<uint8_t>(c) - 1 );
    return c;
}

inline TitleScreenOption operator--(TitleScreenOption &c, int ) {
    TitleScreenOption result = c;
    --c;
    return result;
}

enum class TitleScreenMode : uint8_t {
    SelectOption,
    Introduction
};

enum Object {
    Coin = 0,
    SackOCash = 1,
    Bread = 2,
    Key = 3,
    Chicken = 4, 
    Eye = 6,
    Spider = 7, 
    Bat = 8,
    Tools = 9,
    Tonic = 10,
    BigSpider = 11, 
    IceSpell = 12,
    GreenSpell = 13,
    RedSpell = 14,
    MauveSpell = 15,
    Skeleton = 16,
    SpikeLHS = 17,
    SpikeRHS = 18,
    FireTOP = 19,
    FireBOT = 20,
    Snake = 21,
    Chest = 22,
    Necromancer = 23,
    Hobgoblin = 24,
    Guide01 = 25,
    Guide02 = 26,
    Guide03 = 27,
    Guide04 = 28,
    Guide05 = 29,
    Guide06 = 30,
    Guide07 = 31,
    Guide08 = 32,
    Guide09 = 33,
    Guide10 = 34,
    Guide11 = 35,
    Guide12 = 36,
    Guide13 = 37,
    Guide14 = 38,
    Guide15 = 39,
    Beholder = 41,
    Cyclop = 42,
    Sparks = 252,
    SpiderWeb = 253,
    FireBall = 254,
    None = 255,
};

enum class SpriteType : uint8_t {
    Player_1 = 0,
    Player_2,
    Player_3,
    Coin_1 = 12,
    Coin_2,
    Coin_3,
    Coin_4,
    Coin_5,
    Coin_6,
    BulletUp = 18,
    BulletDown,
    BulletRight,
    BulletLeft,    
};

enum class GameState : uint8_t {
    SplashScreen,
    MainMenu, 
    Settings, 
    Game_Init_Music,
    Game, 
    LoadMap,
    EndOfLevel, 
    Dead, 
    WinState_Init,
    WinState,
    Inventory,
    MapDetails,
    Shop_Init_Music,
    Shop,
    HighScore,
    AltarPieceAchieved,
    Guide,
    NeedRune,
    Puzzle_Init_Game,
    Puzzle_No_Selection,
    Puzzle_Node_Selected,
    Puzzle_Game_Over,
    GameSaved,
};

enum class Direction : uint8_t {
    Up, 
    UpRight, 
    Right, 
    DownRight,
    Down, 
    DownLeft, 
    Left, 
    UpLeft,
    None
};

enum class Axis : uint8_t {
    XAxis,
    YAxis
};

enum class WinScreenMode : uint8_t {
    ShowAnim,
    ShowMessage,
    Score
};

enum MapTiles {
    Empty = 0,
    BlankWall = 1,
    LockedDoor = 2,
    DownStairs = 3,
    Barrel = 4,
    OpenChest = 5,
    OpenDoor = 6,
    FullBlockWall = 7,
    ClosedChest_Key = 8,
    UpStairs = 9,
    SwitchOn = 10,
    SwitchOff = 11,
    TorchWall = 12,
    WindowWall = 13,
    PressPlate_Up = 14,
    SpearDoor = 15,
    ExplosiveBarrel = 16,
    LockedStairs = 17,
    Rubble = 18,
    SwitchBroken = 19,
    Grass = 20,
    StraightRHS = 21,
    StraightTOP = 22,
    StraightLHS = 23,
    StraightBOT = 24,
    TriangleTL = 25,
    TriangleTR = 26,
    TriangleLL = 27,
    TriangleLR = 28,
    CornerFillLR = 29,
    CornerFillLL = 30,
    CornerFillTR = 31,
    CornerFillTL = 32,
    FullSquare = 33,
    CornerLL = 34,
    CornerLR = 35,
    CornerTR = 36,
    CornerTL = 37,
    Fill = 38,
    DoorLHS = 39,
    DoorRHS = 40,
    DoorTOP = 41,
    DoorBOT = 42,
    StraightLR = 43,
    StraightTB = 44,
    EndTRL = 45,
    EndRBL = 46,
    EndTBL = 47,
    EndTRB = 48,
    FillTLTR = 49,
    FillTRBR = 50,
    FillBLBR = 51,
    FillTLBL = 52,
    DoorLHSOpen = 53,
    DoorRHSOpen = 54,
    DoorTOPOpen = 55,
    DoorBOTOpen = 56,
    SpearDoorLHS = 57,
    SpearDoorRHS = 58,
    SpearDoorTOP = 59,
    SpearDoorBOT = 60,
    SpearDoorLHSOpen = 61,
    SpearDoorRHSOpen = 62,
    SpearDoorTOPOpen = 63,
    SpearDoorBOTOpen = 64,
    StraightTorchLHS_F0 = 65,
    StraightTorchRHS_F0 = 66,
    StraightTorchTOP_F0 = 67,
    StraightTorchBOT_F0 = 68,
    StraightTorchLHS_F1 = 69,
    StraightTorchRHS_F1 = 70,
    StraightTorchTOP_F1 = 71,
    StraightTorchBOT_F1 = 72,
    WormHole_F0 = 73,
    WormHole_F1 = 74,
    WormHole_F2 = 75,
    WormHole_F3 = 76,
    Shop00 = 77,
    Shop01 = 78,
    Shop02 = 79,
    Shop03 = 80,
    Shop04 = 81,
    Shop05 = 82,
    SpiderWebTL = 83,
    SpiderWebTR = 84,
    SpiderWebLR = 85,
    SpiderWebLL = 86,
    ClosedChest_Random = 87,
    ClosedChest_Killer = 88,
    PressPlate_Down = 89,
    Altar00 = 90,
    Altar01 = 91,
    Altar02 = 92,
    Altar03 = 93,
    Altar04 = 94,
    Altar05 = 95,
    ClosedChest_Altar = 96,
    SavePost = 97,
    CornerFill = 98,
    ThreeSkulls = 99,
    Shadow = 100,
};

enum class ShopMessage : uint8_t {
    None,
    NotEnoughGold,
    OutOfStock,
    InventoryFull
};

enum class SplashScreenMode : uint8_t {
    PPOT,
    Dreamer
};

enum class InventoryMenuMode : uint8_t {
    Inventory,
    AltarPieces
};


