/**************************************************************************/
/*!
    @file     Pokitto_settings.h
    @author   Jonne Valola

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2016, Jonne Valola
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#pragma once
#include <stdint.h>

#include "My_settings.h"

#define POK_DISPLAYLOGO  1
#define POK_ENABLE_REFRESHWITHWAIT 0 // choose whether waiting in application refreshes display or not
#define POK_AUD_FREQ 16000


/** SCREEN CONFIGURATION **/
#define PROJ_PERSISTENCE true
inline constexpr bool POK_PERSISTENCE = PROJ_PERSISTENCE;

#define PROJ_CLEAR_SCREEN 0
inline constexpr uint32_t POK_CLEAR_SCREEN = PROJ_CLEAR_SCREEN;

#define PROJ_FPS 60
inline constexpr uint32_t POK_FPS = PROJ_FPS;
inline constexpr uint32_t POK_FRAMEDURATION = 1000 / PROJ_FPS;

inline constexpr uint32_t R_MASK = 0xF800;
inline constexpr uint32_t G_MASK = 0x07E0;
inline constexpr uint32_t B_MASK = 0x001F;

inline constexpr uint32_t POK_LCD_W = 220;
inline constexpr uint32_t POK_LCD_H = 176;

#define MODE_NOBUFFER            0
#define MODE_HI_4COLOR           1
#define MODE_FAST_16COLOR        2
#define MODE13                   13
#define MODE15                   15
#define MIXMODE                  32
#define TASMODE                  42
#define TASMODELOW               43
#define MODE64                   64

/** SCREENMODE - USE THIS SELECTION FOR YOUR PROJECT **/
#ifndef PROJ_SCREENMODE
    #if defined(PROJ_HIRES) &&  PROJ_HIRES > 0
        #define PROJ_SCREENMODE MODE_HI_4COLOR
    #elif defined(PROJ_HICOLOR) && PROJ_HICOLOR > 0
        #define PROJ_SCREENMODE MODE13
    #elif defined(PROJ_TASMODE) && PROJ_TASMODE > 0
        #define PROJ_SCREENMODE TASMODE
    #elif defined(PROJ_TASMODELOW) && PROJ_TASMODELOW > 0
        #define PROJ_SCREENMODE TASMODELOW
    #elif defined(PROJ_MODE13) && PROJ_MODE13 > 0
        #define PROJ_SCREENMODE MODE13
    #elif defined(PROJ_MODE15) && PROJ_MODE15 > 0
        #define PROJ_SCREENMODE MODE15
    #elif defined(PROJ_MIXMODE) && PROJ_MIXMODE > 0
        #define PROJ_SCREENMODE MIXMODE
    #elif defined(PROJ_MODE64) && PROJ_MODE64 > 0
        #define PROJ_SCREENMODE MODE64
    #else
        #define PROJ_SCREENMODE MODE_FAST_16COLOR
    #endif
#endif // POK_TILEDMODE


#if PROJ_SCREENMODE == MODE_NOBUFFER
    #define PROJ_SCREENBUFFERSIZE BUFSIZE_NOBUFFER
    #define PROJ_COLORDEPTH 8
#endif

#if PROJ_SCREENMODE == TASMODELOW
    #undef PROJ_SCREENMODE
    #define PROJ_SCREENMODE TASMODE
    #define PROJ_SCREENBUFFERSIZE BUFSIZE_TASMODELOW
    #define PROJ_LCDWIDTH 110
    #define PROJ_LCDHEIGHT 88
#endif

#if PROJ_SCREENMODE == TASMODE
    #ifndef PROJ_SCREENBUFFERSIZE
        #define PROJ_SCREENBUFFERSIZE BUFSIZE_TASMODE
    #endif
    #define PROJ_COLORDEPTH 8
    #ifndef PROJ_MAX_SPRITES
        #define PROJ_MAX_SPRITES 100
    #endif
    #ifndef PROJ_TILE_W
        #define PROJ_TILE_W 16
    #endif // PROJ_TILEWIDTH
    #ifndef PROJ_TILE_H
        #define PROJ_TILE_H 16
    #endif // PROJ_TILEHEIGHT
    #if !defined(PROJ_LCDHEIGHT)
        #define PROJ_LCDWIDTH 220
        #define PROJ_LCDHEIGHT 176
    #endif
    #if !defined(PROJ_LINE_FILLERS)
        #define PROJ_LINE_FILLERS       \
                    TAS::BGTileFiller,  \
                    TAS::SpriteFiller,  \
                    TAS::NOPFiller,     \
                    TAS::NOPFiller
    #endif
    inline constexpr uint32_t POK_TILE_W = PROJ_TILE_W;
    inline constexpr uint32_t POK_TILE_H = PROJ_TILE_H;
#endif


#if PROJ_SCREENMODE == MODE_FAST_16COLOR
    #define PROJ_SCREENBUFFERSIZE BUFSIZE_FAST_16COLOR
    #define PROJ_COLORDEPTH 4
    #define PROJ_LCDWIDTH 110
    #define PROJ_LCDHEIGHT 88
#endif

#if PROJ_SCREENMODE == MODE13
    #define PROJ_SCREENBUFFERSIZE BUFSIZE_MODE13
    #define PROJ_COLORDEPTH 8
    #define PROJ_LCDWIDTH 110
    #define PROJ_LCDHEIGHT 88
#endif

#if PROJ_SCREENMODE == MODE15
    #define PROJ_SCREENBUFFERSIZE BUFSIZE_MODE15
    #define PROJ_COLORDEPTH 4
#endif

#if PROJ_SCREENMODE == MIXMODE
    #define PROJ_SCREENBUFFERSIZE BUFSIZE_MIXMODE
    #define PROJ_COLORDEPTH 8
    #define PROJ_LCDWIDTH 110
    #define PROJ_LCDHEIGHT 88
#endif

#if PROJ_SCREENMODE == MODE64
    #define PROJ_SCREENBUFFERSIZE BUFSIZE_MODE64
    #define PROJ_COLORDEPTH 8
    #define PROJ_LCDWIDTH 110
    #define PROJ_LCDHEIGHT 176
#endif

#if PROJ_SCREENMODE == MODE_HI_4COLOR || !defined(PROJ_SCREENBUFFERSIZE)
    #define PROJ_SCREENBUFFERSIZE BUFSIZE_HI_4COLOR
    #define PROJ_COLORDEPTH 2
#endif

#ifndef PROJ_LCDWIDTH
    #define PROJ_LCDWIDTH POK_LCD_W
#endif
inline constexpr uint32_t LCDWIDTH = PROJ_LCDWIDTH;

#ifndef PROJ_LCDHEIGHT
    #define PROJ_LCDHEIGHT POK_LCD_H
#endif
inline constexpr uint32_t LCDHEIGHT = PROJ_LCDHEIGHT;

/** AUTOMATIC COLOR DEPTH SETTING - DO NOT CHANGE **/
#ifndef PROJ_COLORDEPTH
    #define PROJ_COLORDEPTH 4
#endif // PROJ_COLORDEPTH
inline constexpr uint32_t POK_COLORDEPTH = PROJ_COLORDEPTH;

inline constexpr uint32_t BUFSIZE_NOBUFFER = 0;
inline constexpr uint32_t BUFSIZE_TASMODE = 220;
inline constexpr uint32_t BUFSIZE_TASMODELOW = 110;
inline constexpr uint32_t BUFSIZE_HI_4COLOR = ((POK_LCD_H+1)*POK_LCD_W)*POK_COLORDEPTH/8;
inline constexpr uint32_t BUFSIZE_FAST_16COLOR = (((POK_LCD_H/2)+1)*POK_LCD_W/2)*POK_COLORDEPTH/8;
inline constexpr uint32_t BUFSIZE_MODE13 = 110*88;
inline constexpr uint32_t BUFSIZE_MODE15 = 0x4BA0;
inline constexpr uint32_t BUFSIZE_MODE64 = 220*88;
inline constexpr uint32_t BUFSIZE_MIXMODE = 110*88;

#ifndef PROJ_SCREENBUFFERSIZE
    #define PROJ_SCREENBUFFERSIZE 0
#endif
inline constexpr uint32_t POK_SCREENBUFFERSIZE = PROJ_SCREENBUFFERSIZE;

inline constexpr uint32_t XCENTER = LCDWIDTH / 2;
inline constexpr uint32_t YCENTER = LCDHEIGHT / 2;

#ifndef PROJ_PALETTE_SIZE
	#if (PROJ_SCREENMODE == MIXMODE)
		#define PROJ_PALETTE_SIZE 276;
	#else
		#define PROJ_PALETTE_SIZE 1<<PROJ_COLORDEPTH
	#endif
#endif

inline constexpr uint32_t PALETTE_SIZE = PROJ_PALETTE_SIZE;

/** SCROLL TEXT VS. WRAP AROUND WHEN PRINTING **/
#if PROJ_NO_AUTO_SCROLL
#define SCROLL_TEXT 0
#else
#define SCROLL_TEXT 1
#endif

/** AUDIO **/

/** LOADER UPDATE MECHANISM **/



