#pragma once

#include "Pokitto.h"
#include "Sprite.h"
#include "Player.h"
#include "../../My_settings.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;



PROGMEM const uint8_t spriteWidths[] =  { 
    10, /* Coin */
    10, /* SackOfCash */
    10, /* Bread */
    10, /* Key */
    10, /* Chicken */
    8,  /* Floater */
    12, /* Eye */
    8,  /* Spider */
    8,  /* Bat */
    12, /* Tools */
    10,  /* Tonic */
    16, /* BigSpider */
    14, /* IceSpell */
    14, /* GreenSpell */
    14, /* RedSpell */
    14, /* MauveSpell */
     8, /* Skeleton */
    16, /* SpikeLHS */
    16, /* SpikeRHS */
    16, /* FireTOP */
    16, /* FireBOT */
    12, /* Snake */
    16, /* Chest */
    10, /* Necromancer */
    10, /* Hobgoblin */
    10, /* Guide01 */
    10, /* Guide02 */
    10, /* Guide03 */
    10, /* Guide04 */
    10, /* Guide05 */
    10, /* Guide06 */
    10, /* Guide07 */
    10, /* Guide08 */
    10, /* Guide09 */
    10, /* Guide10 */
    10, /* Guide11 */
    10, /* Guide12 */
    10, /* Guide13 */
    10, /* Guide14 */
    10, /* Guide15 */
    24, /* Bull */
    24, /* Beholder */
    24, /* Cyclop */
};

PROGMEM const uint8_t spriteHeights[] = { 
    10, /* Coin */
    10, /* SackOfCash */
    10, /* Bread */
    10, /* Key */
    8,  /* Chicken */
    8,  /* Floater */  
    12,  /* Eye */
    8,  /* Spider */
    8,  /* Bat */
    12, /* Tools */
    10,  /* Tonic */
    16, /* BigSpider */
    14, /* IceSpell */
    14,  /* GreenSpell */
    14,  /* RedSpell */
    14, /* MauveSpell */
    12, /* Skeleton */
    16, /* SpikeLHS note its actually 17 */
    16, /* SpikeRHS */
    16, /* FireTOP */
    16, /* FireBOT */
    12, /* Snake */
    16, /* Chest */
    12, /* Necromancer */
    12, /* Hobgoblin */
    12, /* Guide01 */
    12, /* Guide02 */
    12, /* Guide03 */
    12, /* Guide04 */
    12, /* Guide05 */
    12, /* Guide06 */
    12, /* Guide07 */
    12, /* Guide08 */
    12, /* Guide09 */
    12, /* Guide10 */
    12, /* Guide11 */
    12, /* Guide12 */
    12, /* Guide13 */
    12, /* Guide14 */
    12, /* Guide15 */
    24, /* Bull */
    24, /* Beholder */
    24, /* Cyclop */
};

        
PROGMEM const int8_t spriteOffsets[] = { 
    -5, -5,  /* Coin */
    -5, -5,  /* SackOfCash */
    -5, -5,  /* Bread */
    -5, -4,  /* Key */
    -5, -5,  /* Chicken */
    -3, -3,  /* Floater */  
    -6, -6,  /* Eye */
    -4, -4,  /* Spider */
    -4, -4,  /* Bat */
    -5, -5,  /* Tools */
    -5, -5,  /* Tonic */
    -8, -8,  /* BigSpider */
    -7, -6,  /* IceSpell */
    -7, -6,  /* GreenSpell */
    -7, -6,  /* RedSpell */
    -7, -6,  /* MauveSpell */
    -6, -6,  /* Skeleton */
    -8, -8,  /* SpikeLHS */
    -8, -8,  /* SpikeRHS */
    -8, -8,  /* FireTOP */
    -8, -8,  /* FireBOT */
    -4, -6,  /* Snake */
    -8, -8,  /* Chest */
    -6, -6,  /* Necromancer */
    -6, -6,  /* Hobgoblin */
    -5, -6,  /* Guide01 */
    -5, -6,  /* Guide02 */
    -5, -6,  /* Guide03 */
    -5, -6,  /* Guide04 */
    -5, -6,  /* Guide05 */
    -5, -6,  /* Guide06 */
    -5, -6,  /* Guide07 */
    -5, -6,  /* Guide08 */
    -5, -6,  /* Guide09 */
    -5, -6,  /* Guide10 */
    -5, -6,  /* Guide11 */
    -5, -6,  /* Guide12 */
    -5, -6,  /* Guide13 */
    -5, -6,  /* Guide14 */
    -5, -6,  /* Guide15 */
    -12, -12,  /* Bull */
    -12, -12,  /* Beholder */
    -12, -12,  /* Cyclop */
};

PROGMEM const uint8_t object_DamageOnPlayer[] = {
    0,                      /* Coin */
    0,                      /* SackOfCash */
    0,                      /* Bread */
    0,                      /* Key */
    0,                      /* Chicken */
    0,                      /* Floater */  
    HEALTH_DEC_EYES,        /* Eye */
    HEALTH_DEC_SPIDER,      /* Spider */
    HEALTH_DEC_BAT,         /* Bat */
    0,                      /* Tools */
    0,                      /* Tonic */
    HEALTH_DEC_BIGSPIDER,   /* BigSpider */
    0,                      /* IceSpell */
    0,                      /* GreenSpell */
    0,                      /* RedSpell */
    0,                      /* MauveSpell */
    HEALTH_DEC_SKELETON,    /* Skeleton */
    HEALTH_DEC_SPIKE_FIRE,  /* SpikeLHS */
    HEALTH_DEC_SPIKE_FIRE,  /* SpikeRHS */
    HEALTH_DEC_SPIKE_FIRE,  /* FireTOP */
    HEALTH_DEC_SPIKE_FIRE,  /* FireBOT */
    HEALTH_DEC_SNAKE,       /* Snake */
    0,                      /* Chest */
    HEALTH_DEC_NECROMANCER, /* Necromancer */
    HEALTH_DEC_HOBGOBLIN,   /* Hobgoblin */
    0,                      /* Guide01 */
    0,                      /* Guide02 */
    0,                      /* Guide03 */
    0,                      /* Guide04 */
    0,                      /* Guide05 */
    0,                      /* Guide06 */
    0,                      /* Guide07 */
    0,                      /* Guide08 */ 
    0,                      /* Guide09 */ 
    0,                      /* Guide10 */ 
    0,                      /* Guide11 */ 
    0,                      /* Guide12 */ 
    0,                      /* Guide13 */ 
    0,                      /* Guide14 */ 
    0,                      /* Guide15 */ 
    0,                      /* Bull */ 
    HEALTH_DEC_BOSS,        /* Beholder */ 
    HEALTH_DEC_CYCLOP,      /* Cyclop */ 
};

PROGMEM const char object_Desc_00[] = "Coin";
PROGMEM const char object_Desc_01[] = "Sack of Coins";
PROGMEM const char object_Desc_02[] = "Bread";
PROGMEM const char object_Desc_03[] = "Key";
PROGMEM const char object_Desc_04[] = "Chicken";
PROGMEM const char object_Desc_05[] = "Floater";
PROGMEM const char object_Desc_06[] = "Eye";
PROGMEM const char object_Desc_07[] = "Spider";
PROGMEM const char object_Desc_08[] = "Bat";
PROGMEM const char object_Desc_09[] = "Tools";
PROGMEM const char object_Desc_10[] = "Tonic";
PROGMEM const char object_Desc_11[] = "Big Spider";
PROGMEM const char object_Desc_12[] = "Ice Spell";
PROGMEM const char object_Desc_13[] = "Tox Spell";
PROGMEM const char object_Desc_14[] = "HRT Spell";
PROGMEM const char object_Desc_15[] = "Pow Spell";
PROGMEM const char object_Desc_16[] = "Skeleton";
PROGMEM const char object_Desc_17[] = "Spike LHS";
PROGMEM const char object_Desc_18[] = "Spike RHS";
PROGMEM const char object_Desc_19[] = "Flame TOP";
PROGMEM const char object_Desc_20[] = "Flame BOT";
PROGMEM const char object_Desc_21[] = "Snake";
PROGMEM const char object_Desc_22[] = "Chest";
PROGMEM const char object_Desc_23[] = "Necromancer";
PROGMEM const char object_Desc_24[] = "Hobgoblin";
PROGMEM const char object_Desc_25[] = "Guide 01";
PROGMEM const char object_Desc_26[] = "Guide 02";
PROGMEM const char object_Desc_27[] = "Guide 03";
PROGMEM const char object_Desc_28[] = "Guide 04";
PROGMEM const char object_Desc_29[] = "Guide 05";
PROGMEM const char object_Desc_30[] = "Guide 06";
PROGMEM const char object_Desc_31[] = "Guide 07";
PROGMEM const char object_Desc_32[] = "Guide 08";
PROGMEM const char object_Desc_33[] = "Guide 09";
PROGMEM const char object_Desc_34[] = "Guide 10";
PROGMEM const char object_Desc_35[] = "Guide 11";
PROGMEM const char object_Desc_36[] = "Guide 12";
PROGMEM const char object_Desc_37[] = "Guide 13";
PROGMEM const char object_Desc_38[] = "Guide 14";
PROGMEM const char object_Desc_39[] = "Guide 15";
PROGMEM const char object_Desc_40[] = "Bull";
PROGMEM const char object_Desc_41[] = "Beholder";
PROGMEM const char object_Desc_42[] = "Cyclop";

PROGMEM const char * const object_Descs[] = { 
    object_Desc_00,
    object_Desc_01,
    object_Desc_02,
    object_Desc_03,
    object_Desc_04,
    object_Desc_05,
    object_Desc_06,
    object_Desc_07,
    object_Desc_08,
    object_Desc_09,
    object_Desc_10,
    object_Desc_11,
    object_Desc_12,
    object_Desc_13,
    object_Desc_14,
    object_Desc_15,
    object_Desc_16,
    object_Desc_17,
    object_Desc_18,
    object_Desc_19,
    object_Desc_20,
    object_Desc_21,
    object_Desc_22,
    object_Desc_23,
    object_Desc_24,
    object_Desc_25,
    object_Desc_26,
    object_Desc_27,
    object_Desc_28,
    object_Desc_29,
    object_Desc_30,
    object_Desc_31,
    object_Desc_32,
    object_Desc_33,
    object_Desc_34,
    object_Desc_35,
    object_Desc_36,
    object_Desc_37,
    object_Desc_38,
    object_Desc_39,
    object_Desc_40,
    object_Desc_41,
    object_Desc_42,
};

                                // 0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4   
PROGMEM const uint8_t spike_frameIdx[] =  {0, 2, 4, 6, 8, 8, 8, 8, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 3, 2, 1, 1, 0 };
PROGMEM const uint8_t fire_frameIdx[] =   {0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 2, 2, 2, 2 };
