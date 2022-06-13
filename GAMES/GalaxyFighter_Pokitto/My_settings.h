#pragma once

//#define PROJ_SHOW_FPS_COUNTER

#define PROJ_BUTTONS_POLLING_ONLY

#define PROJ_MODE15                 1
#define PROJ_HIGH_RAM               HIGH_RAM_MUSIC
#define PROJ_ENABLE_SFX             1
#define PROJ_AUD_FREQ               8000

#define INCLUDE_SOUND
#define INCLUDE_SOUND_FROM_SD

#ifdef INCLUDE_SOUND_FROM_SD

    #define PROJ_STREAM_LOOP            0
    #define PROJ_ENABLE_SD_MUSIC

#endif

#define _DEBUG
#define _DEBUG_NEVER_DIE