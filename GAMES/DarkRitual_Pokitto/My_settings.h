#pragma once

#define PROJ_BUTTONS_POLLING_ONLY

#define PROJ_HIGH_RAM HIGH_RAM_MUSIC
//#define PROJ_AUD_FREQ 16000

//#define DEBUG


//--------------------------------------------
// Confgurable Settings
//--------------------------------------------


// Health ..

#define HEALTH_INC_BREAD                20
#define HEALTH_INC_CHICKEN              35
#define HEALTH_INC_TONIC                50
#define HEALTH_DEC_SPIDERS_WEB          1       // Health decrement when running through a spider's web.
#define HEALTH_DEC_EYES                 5
#define HEALTH_DEC_SPIDER               2
#define HEALTH_DEC_BIGSPIDER            6
#define HEALTH_DEC_BAT                  1
#define HEALTH_DEC_SKELETON             3
#define HEALTH_DEC_SNAKE                3
#define HEALTH_DEC_NECROMANCER          3
#define HEALTH_DEC_HOBGOBLIN            3
#define HEALTH_DEC_SPIKE_FIRE           2
#define HEALTH_DEC_CHEST                5
#define HEALTH_DEC_BOSS                 10
#define HEALTH_DEC_CYCLOP               8

// Enemy Starting Health ..

#define HEALTH_NONE                     0
#define HEALTH_BAT                      20
#define HEALTH_EYE                      40
#define HEALTH_SKELETON                 40
#define HEALTH_SNAKE                    20
#define HEALTH_SPIDER                   30
#define HEALTH_LARGESPIDER              50
#define HEALTH_NECROMANCER              60
#define HEALTH_HOBGOBLIN                50
#define HEALTH_CHEST                    30
#define HEALTH_BOSS                     120
#define HEALTH_CYCLOP                   120

// Enemy damage ..

#define DAMAGE_FIREBALL                 10
#define DAMAGE_ICESPELL                 10
#define DAMAGE_GREENSPELL               20
#define DAMAGE_REDSPELL                 30
#define DAMAGE_BULLET                   15
#define DAMAGE_SPIKE_FIRE               5

// Other settings ..

#define ICE_SPELL_DELAY                 360
#define ICE_SPELL_DELAY_INC             30
#define WALK_SLOW_FRAME_COUNT           3

#define PLAYER_BULLET_MAX               6
#define ENEMY_BULLET_MAX                10
#define BOSS_BULLET_MAX                 8


// Random offerings ..

#define BARREL_RANDOM_NOTHING           120
#define BARREL_RANDOM_COIN              BARREL_RANDOM_NOTHING + 30
#define BARREL_RANDOM_SACK              BARREL_RANDOM_COIN + 5
#define BARREL_RANDOM_BREAD             BARREL_RANDOM_SACK + 5
#define BARREL_RANDOM_CHICKEN           BARREL_RANDOM_BREAD + 5

#define CHEST_RANDOM_COIN               70
#define CHEST_RANDOM_SACK               CHEST_RANDOM_COIN + 10
#define CHEST_RANDOM_BREAD              CHEST_RANDOM_SACK + 10
#define CHEST_RANDOM_CHICKEN            CHEST_RANDOM_BREAD + 10
#define CHEST_RANDOM_TONIC              CHEST_RANDOM_CHICKEN + 10
#define CHEST_RANDOM_ICE                CHEST_RANDOM_TONIC + 5
#define CHEST_RANDOM_GREEN              CHEST_RANDOM_ICE + 5
#define CHEST_RANDOM_RED                CHEST_RANDOM_GREEN + 5
#define CHEST_RANDOM_MAUVE              CHEST_RANDOM_RED + 5
#define CHEST_RANDOM_END                CHEST_RANDOM_MAUVE + 5


// Number of inventory items (note random(min, max)) ..

#define INVENTORY_BREAD_MIN             2
#define INVENTORY_BREAD_MAX             6
#define INVENTORY_CHICKEN_MIN           2
#define INVENTORY_CHICKEN_MAX           6
#define INVENTORY_KEY_MIN               2
#define INVENTORY_KEY_MAX               6
#define INVENTORY_TOOLS_MIN             1
#define INVENTORY_TOOLS_MAX             3
#define INVENTORY_TONIC_MIN             1
#define INVENTORY_TONIC_MAX             4
#define INVENTORY_ICE_SPELL_MIN         0
#define INVENTORY_ICE_SPELL_MAX         3
#define INVENTORY_GREEN_SPELL_MIN       0
#define INVENTORY_GREEN_SPELL_MAX       3
#define INVENTORY_RED_SPELL_MIN         0
#define INVENTORY_RED_SPELL_MAX         3
#define INVENTORY_MAUVE_SPELL_MIN       0
#define INVENTORY_MAUVE_SPELL_MAX       3


#define INVENTORY_BREAD_PRICE           6
#define INVENTORY_CHICKEN_PRICE         10
#define INVENTORY_KEY_PRICE             15
#define INVENTORY_TOOLS_PRICE           15
#define INVENTORY_TONIC_PRICE           20
#define INVENTORY_ICE_SPELL_PRICE       20
#define INVENTORY_GREEN_SPELL_PRICE     25
#define INVENTORY_RED_SPELL_PRICE       35
#define INVENTORY_MAUVE_SPELL_PRICE     50

#define SPELL_BULLETS_MIN               10
#define SPELL_BULLETS_MAX               20


//--------------------------------------------
// Do not touch!
//--------------------------------------------

#define MAX_INVENTORY_COUNT             5       // NUmber of items the player can hold, two of one type counts as two.

#define MAPS_RANDOM_COUNT               24
#define CENTERX                         55
#define CENTERY                         36

#define TILE_WIDTH                      16
#define TILE_HEIGHT                     16
#define TILE_SIZE                       16

#define PLAYER_WIDTH                    12
#define PLAYER_WIDTH_HALF               6
#define PLAYER_HEIGHT                   12
#define PLAYER_HEIGHT_HALF              6
#define PLAYER_DEAD_DELAY               -100

#define MAXOBJECT                       200
#define MAXENVIROMENT                   150

#define MAP_SIZE_X                      45
#define MAP_SIZE_Y                      45
#define MAP_SIZE                        (MAP_SIZE_X * MAP_SIZE_Y)

#define NO_SLOT_FOUND                   255
#define NO_SPRITE_FOUND                 255
#define NO_HIGH_SCORE_EDIT              255
#define NO_INACTIVE_BULLET_FOUND        255
#define MAX_INVENTORY_ITEMS             5                   // Number of item types the player can hold
#define RANDOM_TILE_SIZE                9
#define HEALTH_BAR_DELAY                8
#define END_OF_OPTIONS                  255

#define TIMER_STEP                      24
#define LEVEL_START_DELAY               60
#define COOKIE_INITIALISED              28
#define SHOP_PURCHASE_DELAY             48

#define ENEMY_BULLET_DELAY_MIN          20
#define ENEMY_BULLET_DELAY_MAX          40

#define LAUNCH_SKELETON_DELAY_MIN       60
#define LAUNCH_SKELETON_DELAY_MAX       100
#define LAUNCH_SPIDER_DELAY_MIN         60
#define LAUNCH_SPIDER_DELAY_MAX         100
#define LAUNCH_CYCLOPS_DELAY_MIN        70
#define LAUNCH_CYCLOPS_DELAY_MAX        120


#define BULLET_FIREBALL_FRAMES          20
#define BULLET_ICESPELL_FRAMES          20
#define BULLET_GREENRED_FRAMES          20


// Web bullet travel details ..

#define BULLET_WEB_FRAMES               40       // Number of frames to travel
#define BULLET_WEB_FRAMES_DIV1          BULLET_WEB_FRAMES - 6 
#define BULLET_WEB_FRAMES_DIV2          BULLET_WEB_FRAMES_DIV1 - 6 
#define BULLET_WEB_FRAMES_DIV3          9
#define BULLET_WEB_FRAMES_DIV4          6
#define BULLET_WEB_FRAMES_DIV5          3

#define CYCLOP_SPARK_FRAMES             15       // Number of frames to travel


// Frame constants 

#define PUFF_FRAME_MAX                  20
#define SKELETON_FRAME_MAX              48
#define NECROMANCER_FRAME_MAX           40
#define CYCLOPS_FRAME_MAX               40

#define CHANGE_STATE_DELAY              24


/* -------------------------------------------------------------------------------
Bit 7       Blank segment.
Bit 6       Any Segment from the nominated Type.
Bit 5       Specify a specific segment (over two bytes, sgement type, index)
Bit 4 .. 0  Segment specification (range 0 - 31).
*/

#define BLANK_SEG   128
#define ANY_SEG     64
#define THIS_SEG    32
#define SEG_00      0
#define SEG_01      1
#define SEG_02      2
#define SEG_03      3
#define SEG_04      4
#define SEG_05      5
#define SEG_06      6
#define SEG_07      7
#define SEG_08      8
#define SEG_09      9
#define SEG_10      10
#define SEG_11      11
#define SEG_12      12
#define SEG_13      13
#define SEG_14      14
#define SEG_15      15
