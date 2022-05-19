/**************************************************************************/
/*!
    @file     PokittoButtons.cpp
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

#include "PokittoCore.h"
#include "ESPboyInit.h"

extern ESPboyInit myESPboy;

using namespace Pokitto;

uint8_t Buttons::pins[NUM_BTN];
uint8_t Buttons::heldStates[NUM_BTN];
uint8_t Buttons::states[NUM_BTN];
uint8_t Buttons::buttons_state;
uint8_t Buttons::buttons_held;
uint8_t Buttons::buttons_released; // from LSB up,down,left,right,a,b,c
//uint16_t Buttons::cHWLongPress = 3000;//CHWLONGPRESSTIMEOUT;


void Buttons::initButtons(){};

void Buttons::update() {
    pollButtons();
        /** HARDWARE CODE **/
    for (uint8_t thisButton = 0; thisButton < NUM_BTN; thisButton++) {
        if (heldStates[thisButton]) { //if button pressed
            states[thisButton]++; //increase button hold time
            if (states[thisButton]==0xFF) states[thisButton]=2; // PREVENT WRAPAROUND!!!!
        } else {
            if (states[thisButton] == 0)//button idle
                continue;
            if (states[thisButton] == 0xFF)//if previously released
                states[thisButton] = 0; //set to idle
            else
                states[thisButton] = 0xFF; //button just released
        }
        }
}

/*
 * Returns true when 'button' is pressed.
 * The button has to be released for it to be triggered again.
 */
bool Buttons::pressed(uint8_t button) {
    if (states[button] == 1)
        return true;
    else
        return false;
}

/*
 * return true if 'button' is released
 */
bool Buttons::released(uint8_t button) {
    if (states[button] == 0xFF) {
        states[button] = 0; // prevent continuous released state!
        return true;
    }
    else
        return false;
}

/**
 * returns true ONCE when 'button' is held for 'time' frames
 * @param button The button's ID
 * @param time How much frames button must be held, between 1 and 254.
 * @return true when 'button' is held for 'time' frames
 */
bool Buttons::held(uint8_t button, uint8_t time){
    if(states[button] == (time+1))
        return true;
    else
        return false;
}

/**
 * returns true every 'period' frames when 'button' is held
 * @param button The button's ID
 * @param period How much frames button must be held, between 1 and 254.
 * @return true if the button is held for the given time
 */
bool Buttons::repeat(uint8_t button, uint8_t period) {
    if (period <= 1) {
        if ((states[button] != 0xFF) && (states[button]))
            return true;
    } else {
        if ((states[button] != 0xFF) && ((states[button] % period) == 1))
            return true;
    }
    return false;
}

/**
 *
 * @param button The button's ID
 * @return The number of frames during which the button has been held.
 */
uint8_t Buttons::timeHeld(uint8_t button){
    if(states[button] != 0xFF)
        return states[button];
    else
        return 0;

}

void Buttons::pollButtons() {
    uint8_t buttons_state_old = buttons_state;
    buttons_state = 0; // clear all
    uint8_t getPressedButtons = myESPboy.getKeys();
    for (uint8_t i=0; i<NUM_BTN;i++) heldStates[i]=0;
    
    if (getPressedButtons&PAD_UP) {buttons_state |= (1<<UPBIT); heldStates[BTN_UP]=1;}
    if (getPressedButtons&PAD_DOWN) {buttons_state |= (1<<DOWNBIT); heldStates[BTN_DOWN]=1;}
    if (getPressedButtons&PAD_LEFT) {buttons_state |= (1<<LEFTBIT); heldStates[BTN_LEFT]=1;}
    if (getPressedButtons&PAD_RIGHT) {buttons_state |= (1<<RIGHTBIT); heldStates[BTN_RIGHT]=1;}
    if (getPressedButtons&PAD_ACT) {buttons_state |= (1<<ABIT); heldStates[BTN_A]=1;}
    if (getPressedButtons&PAD_ESC) {buttons_state |= (1<<BBIT); heldStates[BTN_B]=1;}
    if (getPressedButtons&PAD_RGT || getPressedButtons&PAD_LFT) {buttons_state |= (1<<CBIT); heldStates[BTN_C]=1;}
    buttons_held = buttons_state & buttons_state_old; // only if both 1, end result is 1
    buttons_released = ~buttons_state & buttons_state_old; // if now zero, then 1 AND previous 1 = 1
}

uint8_t Buttons::aBtn() {
    return heldStates[BTN_A];
}


uint8_t Buttons::bBtn() {
    return heldStates[BTN_B];
}

uint8_t Buttons::cBtn() {
    return heldStates[BTN_C];
}

uint8_t Buttons::leftBtn() {
    return heldStates[BTN_LEFT];
}

uint8_t Buttons::rightBtn() {
    return heldStates[BTN_RIGHT];
}

uint8_t Buttons::upBtn() {
    return heldStates[BTN_UP];
}

uint8_t Buttons::downBtn() {
    return heldStates[BTN_DOWN];
}

uint8_t Buttons::upHeld() { return (uint8_t) Buttons::held(BTN_UP);}
uint8_t Buttons::downHeld() { return (uint8_t) Buttons::held(BTN_DOWN);}
uint8_t Buttons::leftHeld() { return (uint8_t) Buttons::held(BTN_LEFT);}
uint8_t Buttons::rightHeld() { return (uint8_t) Buttons::held(BTN_RIGHT);}
uint8_t Buttons::aHeld() { return (uint8_t) Buttons::held(BTN_A);}
uint8_t Buttons::bHeld() { return (uint8_t) Buttons::held(BTN_B);}
uint8_t Buttons::cHeld() { return (uint8_t) Buttons::held(BTN_C);}

uint8_t Buttons::upReleased() { return (uint8_t) Buttons::released(BTN_UP);}
uint8_t Buttons::downReleased() { return (uint8_t) Buttons::released(BTN_DOWN);}
uint8_t Buttons::leftReleased() { return (uint8_t) Buttons::released(BTN_LEFT);}
uint8_t Buttons::rightReleased() { return (uint8_t) Buttons::released(BTN_RIGHT);}
uint8_t Buttons::aReleased() { return (uint8_t) Buttons::released(BTN_A);}
uint8_t Buttons::bReleased() { return (uint8_t) Buttons::released(BTN_B);}
uint8_t Buttons::cReleased() { return (uint8_t) Buttons::released(BTN_C);}

//** EOF **//
