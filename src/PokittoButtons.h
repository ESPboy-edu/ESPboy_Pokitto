/**************************************************************************/
/*!
    @file     PokittoButtons.h
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


#ifndef POKITTOBUTTONS_H
#define POKITTOBUTTONS_H

#include <stdint.h>
#include "Pokitto_settings.h"

#define NUM_BTN 7

#define UPBIT    0
#define DOWNBIT  1
#define LEFTBIT  2
#define RIGHTBIT 3
#define ABIT     4
#define BBIT     5
#define CBIT     6

#define BTN_UP      1
#define BTN_RIGHT   2
#define BTN_DOWN    3
#define BTN_LEFT    0
#define BTN_A       4
#define BTN_B       5
#define BTN_C       6

#define PAD_LEFT        0x01
#define PAD_UP          0x02
#define PAD_DOWN        0x04
#define PAD_RIGHT       0x08
#define PAD_ACT         0x10
#define PAD_ESC         0x20
#define PAD_LFT         0x40
#define PAD_RGT         0x80
#define PAD_ANY         0xff

namespace Pokitto {

class Buttons {
public:
    // Original functions
    static uint8_t buttons_state, buttons_held, buttons_released;
    static void initButtons();
    static void pollButtons();
    
    static uint8_t leftBtn();
    static uint8_t rightBtn();
    static uint8_t upBtn();
    static uint8_t downBtn();
    static uint8_t aBtn();
    static uint8_t bBtn();
    static uint8_t cBtn();
    static uint8_t leftHeld();
    static uint8_t rightHeld();
    static uint8_t upHeld();
    static uint8_t downHeld();
    static uint8_t aHeld();
    static uint8_t bHeld();
    static uint8_t cHeld();

    static uint8_t leftReleased();
    static uint8_t rightReleased();
    static uint8_t upReleased();
    static uint8_t downReleased();
    static uint8_t aReleased();
    static uint8_t bReleased();
    static uint8_t cReleased();

    static void begin(){}
    static void update();
    static bool pressed(uint8_t button);
    static bool released(uint8_t button);
    static bool held(uint8_t button, uint8_t time = 2);
    static bool repeat(uint8_t button, uint8_t period = 2);
    static uint8_t timeHeld(uint8_t button);
    static uint8_t pins[NUM_BTN];

    static uint8_t states[NUM_BTN];
    static uint8_t heldStates[NUM_BTN]; // additional, not GB based
};

}

#endif // POKITTOBUTTONS_H






