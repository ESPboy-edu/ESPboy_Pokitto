#pragma once

enum class GameStateType : uint32_t {
	SplashScreen_Activate,
	SplashScreen,
	TitleScreen_Activate,
	TitleScreen,
	PlayGame_Activate,
	PlayGame,
	HighScore_Activate,
	HighScore
};

enum class StageType : uint32_t {
	Normal,
	Challenge
};

enum class EnemyType : uint32_t {
	Butterfly,
    Butterfly_Boss,
	Bee,
	Purple,
	Cyan,
	Scorpion,
    Midori,
    Galaxian,
    Tonbo,
    Momiji,
    Enterprise,
    Player,
    Count,
    PlaceHolder = Count,
	None
};

enum class EnemyFormation : uint32_t {
	Single,
	Two,
	Four
};

enum class LevelType : uint8_t {
    SetFormation,
    LaunchSequence,
    LaunchSequenceTractor,
    LaunchSequence_Rand_1,
    LaunchSequence_Rand_2,
    LaunchSequence_Rand_4,
    Delay,
    DelayUntilAllFinished,
    StartPulse,
    RepeatStart,
    RepeatEnd,
    Transform,
    TransformLaunchSequence,
    DisableAll,
    End
};

enum class SequenceType : uint8_t {
    Normal,
    PosAbsolute,
    PosOffset,
    PosRelative,
    MoveToGridPos,
    RotateToUpright,
    WrapHorizontally,
    Tractor0,
    Tractor1,
    Tractor2,
    Tractor3,
    Tractor4,
    Tractor5,
    MoveCapturedAbove,
    TransformToBOSS_00,
    TransformToBOSS_01,
    TransformToBOSS_02,
    TransformToBOSS_03,
    TransformToBOSS_04,
    TransformToBOSS_05,
    TransformToBOSS_06,
    TransformToBOSS_07,
    TransformToBOSS_Cyan,
    Disable,
    End
    };

enum class PulseDirection : uint32_t {
    Inward,
    Outward,
};

enum class LevelStartType : uint32_t {
    None,
    StartOfGame_Init,
    StartOfGame,
    StartNextLevel,
    NewLife_Init,			// Delays until the explosion sound is complete.
    NewLife_Sounds,			// Starts the 'New Life'sound and waits.
    NewLife_Delay,			// Small delay until game starts.
    NewLife,
    ChallengeResults, 
    EndOfGame
};

enum class SDStream : uint32_t {
    None,
    StageIntro,
    ScoreTop,
    ScoreOther,
    ChallengeStart,
    ChallengeFinish,
    ChallengePerfect,
    FighterCaptured,
    FighterRescued,
    FighterDestroyed,
    Explosion
};

enum class CapturedPlayer : uint32_t {
    None,
    Initial,
    Below,
    Above,
    Joining,
    Joined,
    Dying,
    Dead,
    Complete
};

enum class Side : uint32_t {
    None,
    Left,
    Right
};

enum class BulletType : uint32_t {
    Small = 2,
    Medium = 3,
    Large = 4
};