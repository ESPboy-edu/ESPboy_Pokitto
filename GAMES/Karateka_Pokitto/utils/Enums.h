#pragma once

#define IMMEDIATE_ACTION_V_FREQUENT               2
#define IMMEDIATE_ACTION_FREQUENT                 3
#define IMMEDIATE_ACTION_NORMAL                   7
#define IMMEDIATE_ACTION_INFREQUENT               10

#define RETREAT_ACTION_FREQUENT                   4
#define RETREAT_ACTION_NORMAL                     7
#define RETREAT_ACTION_INFREQUENT                 10

#define ACTION_NO_PREF                            0
#define ACTION_KICK_PREF                          1
#define ACTION_PUNCH_PREF                         2

#define MOVE_FWD_V_FREQUENT                       3
#define MOVE_FWD_FREQUENT                         5
#define MOVE_FWD_NORMAL                           8
#define MOVE_FWD_INFREQUENT                       12

#define GAME_STATE_FOLLOW_SEQUENCE                0
#define GAME_STATE_TITLE_SCENE_INIT               19
#define GAME_STATE_TITLE_SCENE                    1
#define GAME_STATE_CASTLE_SCENE                   2
#define GAME_STATE_EMPEROR_INIT                   3
#define GAME_STATE_EMPEROR                        4
#define GAME_STATE_PLAY_INIT                      5
#define GAME_STATE_PLAY                           7
#define GAME_STATE_ENEMY_APPROACH_INIT            8
#define GAME_STATE_ENEMY_APPROACH                 9
#define GAME_STATE_EAGLE_APPROACH_INIT            10
#define GAME_STATE_EAGLE_APPROACH                 11
#define GAME_STATE_THE_END                        12
#define GAME_STATE_GO_THROUGH_GATE                13
#define GAME_STATE_ENTRANCE                       14
#define GAME_STATE_ENTRANCE_INIT                  15
#define GAME_STATE_PRINCESS_BANISHMENT            16
#define GAME_STATE_PRINCESS_SITTING               17
#define GAME_STATE_FINAL_SCENE                    18
#define GAME_STATE_FINAL_SCENE_INIT               248
#define GAME_STATE_SPLASH_SCREEN                  255
#define GAME_STATE_SPLASH_SCREEN_INIT             251
#define GAME_STATE_INTRO_TEXT                     254
#define GAME_STATE_INTRO_TEXT_INIT                253
#define GAME_STATE_CASTLE_SCENE_INIT              252
#define GAME_STATE_EXTRO_TEXT                     250
#define GAME_STATE_EXTRO_TEXT_INIT                249
#define GAME_STATE_INSTRUCTIONS_INIT              247
#define GAME_STATE_INSTRUCTIONS                   246

#define COOKIE_INITIALISED                        37
#define XPOSOVERALL_NO_CHANGE                     127
#define EAGLE_WING_UP                             0
#define EAGLE_WING_DOWN                           1
#define EAGLE_WING_FRAME_MAX                      2

enum class ImageName : uint8_t {
    Title,
    Castle,
    PPOT,
    Mountain,
    Dojo
};

enum class EntityType : uint8_t {
    None,
    EnemyOne,
    EnemyTwo,
    EnemyThree,
    Emperor,
    Eagle,
    Door,           // A door?  Why not ..
    Princess,
    Player,
};

enum class Movement : uint8_t {
    None,
    Sidle_Forward_Tiny,
    Sidle_Forward_SML,
    Sidle_Forward_MED,
    Sidle_Forward_LRG,
    Sidle_Forward_Unknown,
    Running_Forward,
    Sidle_Backward
};

enum class SoundTheme : uint8_t {
    IntroPrincessToCell,
    IntroPrincessCrying,
    PrincessKillsPlayer,
    PrincessNormalEnding,
    PrincessNormalEndingShort,
    StartOfScene,
    TheEnd,
    DefeatEmperor,      
    DefeatEnemy,  
    PrincessLookingUp,  
    SendOutGuard,   
    BreakingDoor,
    None,
};

enum class SoundEffect : uint8_t {
    EagleApproaching,   // 08
    EagleAttacking,     // 09
    Kick,               // 10
    Kiai,               // 11
    Punch,              // 12
    PlayerFootsteps,    // 13
    EnemyFootsteps,     // 14
    MissedPunch,        // 15
    None,             
};


enum class GameState : uint8_t {
    SplashScreen,
    Game, 
};

enum class Direction : uint8_t {
    Up,
    Right,
    Down,
    Left 
};

enum class Background : uint8_t {
    Inside,
    Outside,
    Dungeon,
    Instructions
};

#define ANIMATION_NUMBER_OF_FRAMES                5
#define ANIMATION_FLASHING_TRIANGLES              12

#define MAIN_SCENE_X_SIDLING_1_DELTA              1
#define MAIN_SCENE_X_SIDLING_2_DELTA              2
#define MAIN_SCENE_X_SIDLING_4_DELTA              4
#define MAIN_SCENE_X_EAGLE_FLYING_DELTA           6

#define PLAYER_KICK_ACTIONS_MIN 50
#define PLAYER_KICK_ACTIONS_MAX 90

//4
#define MAIN_SCENE_IMG_WIDTH                      48

#define STANCE_DEFAULT                            0
#define STANCE_DEFAULT_LEAN_BACK                  1
#define STANCE_KICK_READY                         2
#define STANCE_DEFAULT_LEAN_FORWARD               3
#define STANCE_KICK_STANDING_TRANSITION           4
#define STANCE_KICK_MED_END                       5
#define STANCE_KICK_LOW_END                       6
#define STANCE_KICK_HIGH_END                      7

#define STANCE_PUNCH_MED_RH_END                   8
#define STANCE_PUNCH_MED_LH_END                   9 
#define STANCE_PUNCH_HIGH_RH_END                  10
#define STANCE_PUNCH_HIGH_LH_END                  11
#define STANCE_PUNCH_LOW_RH_END                   12
#define STANCE_PUNCH_LOW_LH_END                   13
#define STANCE_PUNCH_READY                        14

#define STANCE_STANDING_UPRIGHT                   15

#define STANCE_SIDLING_1                          16
#define STANCE_SIDLING_2                          17
#define STANCE_SIDLING_3                          18
#define STANCE_SIDLING_4                          19
#define STANCE_SIDLING_5                          20
#define STANCE_SIDLING_6                          21
#define STANCE_SIDLING_7                          22

#define STANCE_RUNNING_1                          23
#define STANCE_RUNNING_2                          24
#define STANCE_RUNNING_3                          25
#define STANCE_RUNNING_4                          26
#define STANCE_RUNNING_5                          27
#define STANCE_RUNNING_6                          28
#define STANCE_RUNNING_7                          29
#define STANCE_RUNNING_8                          30
#define STANCE_RUNNING_STRAIGHTEN_UP              31
#define STANCE_RUNNING_LF_END                     STANCE_RUNNING_3
#define STANCE_RUNNING_RF_END                     STANCE_RUNNING_6

/* The following are not mapped for a player */
#define STANCE_STANDING_UPRIGHT_REV               32




#define STANCE_RUNNING_1_REV                      33
#define STANCE_RUNNING_2_REV                      34
#define STANCE_RUNNING_3_REV                      35
#define STANCE_RUNNING_4_REV                      36
#define STANCE_RUNNING_5_REV                      37
#define STANCE_RUNNING_6_REV                      38
#define STANCE_RUNNING_7_REV                      39
#define STANCE_RUNNING_8_REV                      40
#define STANCE_RUNNING_STRAIGHTEN_UP_REV          41
#define STANCE_RUNNING_LF_END_REV                 STANCE_RUNNING_3_REV
#define STANCE_RUNNING_RF_END_REV                 STANCE_RUNNING_6_REV
/* .. only for enemies */


#define STANCE_BOW_1                              42
#define STANCE_BOW_2                              43

#define STANCE_DEATH_1                            44
#define STANCE_DEATH_2                            45
#define STANCE_DEATH_3                            46
#define STANCE_DEATH_4                            47
#define STANCE_DEATH_5                            48
#define STANCE_DEATH_6                            49

#define STANCE_ENTRANCE_1                         50
#define STANCE_ENTRANCE_2                         51
#define STANCE_ENTRANCE_3                         52
#define STANCE_ENTRANCE_4                         53
#define STANCE_ENTRANCE_5                         54
#define STANCE_ENTRANCE_6                         55

#define STANCE_EAGLE_1                            56
#define STANCE_EAGLE_2                            57
#define STANCE_EAGLE_3                            58
#define STANCE_EAGLE_4                            59

#define STANCE_EAGLE_1_REV                        60
#define STANCE_EAGLE_2_REV                        61
#define STANCE_EAGLE_3_REV                        62
#define STANCE_EAGLE_4_REV                        63

#define STANCE_PRINCESS_SITTING                   64
#define STANCE_PRINCESS_STANDING                  65
#define STANCE_PRINCESS_KISSING                   66
#define STANCE_PRINCESS_STANDING_REV              72

#define STANCE_SIDLING_1_1                        67
#define STANCE_SIDLING_1_2                        68
#define STANCE_SIDLING_2_1                        69

#define STANCE_BOW_1_REV                          70
#define STANCE_BOW_2_REV                          71
#define STANCE_VICTORY_1                          72
#define STANCE_VICTORY_2                          73

#define ACTION_MIN_KICK                           ACTION_MED_KICK
#define ACTION_MED_KICK                           0
#define ACTION_LOW_KICK                           1
#define ACTION_HIGH_KICK                          2
#define ACTION_MAX_KICK                           ACTION_HIGH_KICK
#define ACTION_MIN_PUNCH                          ACTION_MED_PUNCH
#define ACTION_MED_PUNCH                          3
#define ACTION_HIGH_PUNCH                         4
#define ACTION_LOW_PUNCH                          5
#define ACTION_MAX_PUNCH                          ACTION_LOW_PUNCH
#define ACTION_MAX                                ACTION_LOW_PUNCH
#define ACTION_RETURN_TO_DEFAULT                  6
#define ACTION_RETURN_TO_ACTION_READY             7
#define ACTION_NO_ACTION                          8

#define DISTANCE_TOO_CLOSE                        30
#define DISTANCE_TOO_FAR                          90

#define DISTANCE_BETWEEN_LRG                      90
#define DISTANCE_BETWEEN_MED                      80
#define DISTANCE_BETWEEN_SML                      70
#define DISTANCE_BETWEEN_TINY                     60

#define DISTANCE_MINIMUM_MOVE                     25

#define CHANCE_PERFORM_ACTION                     0
#define CHANCE_PERFORM_ACTION_REGARDLESS_MAX      6
#define CHANCE_MOVE_ENEMY_MAX                     10
 
#define EMPEROR_MODE_INIT                         0
#define EMPEROR_MODE_PAUSE_1                      1
#define EMPEROR_LIFT_ARM                          2
#define EMPEROR_MODE_PAUSE_2                      3
#define EMPEROR_MODE_BOW                          4
#define EMPEROR_MODE_PAUSE_3                      5
#define EMPEROR_MODE_FIGHTER_LEAVE                6

#define EAGLE_MODE_NONE                           0
#define EAGLE_MODE_FLY_INIT                       1
#define EAGLE_MODE_FLY_TOWARDS                    2
#define EAGLE_MODE_ATTACK_1                       3
#define EAGLE_MODE_ATTACK_2                       4
#define EAGLE_MODE_ATTACK_3                       5
#define EAGLE_MODE_FLY_AWAY                       6
#define EAGLE_MODE_DONE                           7

#define EAGLE_LEVEL_LOW                           50
#define EAGLE_LEVEL_MED                           37
#define EAGLE_LEVEL_HIGH                          29
#define EAGLE_LEVEL_NONE                          0

#define EAGLE_LEVEL_LOW_HEALTH                    30
#define EAGLE_LEVEL_MED_HEALTH                    30
#define EAGLE_LEVEL_HIGH_HEALTH                   50

#define HEALTH_UNIT                               16
#define HEALTH_MAX_POINTS                         200
#define HEALTH_STARTING_POINTS                    140
#define HEALTH_REGAIN_POINTS                      3
#define HEALTH_REGAIN_LIMIT                       150

#define DAMAGE_1_POINT                            1
#define DAMAGE_2_POINT                            2
#define DAMAGE_3_POINT                            3
#define DAMAGE_MAX_POINTS                         0

#define ARCH_LEFT_HAND_1                          1
#define ARCH_RIGHT_HAND_1                         2
#define ARCH_LEFT_HAND_2                          3
#define ARCH_RIGHT_HAND_2                         4
#define ARCH_LEFT_HAND_3                          5
#define ARCH_RIGHT_HAND_3                         6
#define ARCH_LEFT_HAND_4                          7
#define ARCH_RIGHT_HAND_4                         8
#define ARCH_LEFT_HAND_GATE                       9
#define ARCH_RIGHT_HAND_GATE                      10
#define ARCH_LEFT_HAND_ENTR                       11
#define ARCH_RIGHT_HAND_ENTR                      12
#define ARCH_LEFT_HAND_DBLD                       13
#define ARCH_RIGHT_HAND_DBLD                      14
#define ARCH_LEFT_STAIRS                          15

#define FINAL_SCENE_INACTIVE                      0
#define FINAL_SCENE_INIT                          1
#define FINAL_SCENE_PAUSE                         2
#define FINAL_SCENE_PAUSE_2                       3
#define FINAL_SCENE_KISSING                       4
#define FINAL_SCENE_BREAK_UP                      5
