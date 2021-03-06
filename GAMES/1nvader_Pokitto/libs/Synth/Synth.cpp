/**************************************************************************/
/*!
    @file     Synth.cpp
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
#ifndef SYNTH_CPP
#define SYNTH_CPP

#include "Pokitto.h"
#include "stdint.h"

/** COMMON TO BOTH HW AND SIMULATED SOUND **/

bool playing=false; //external to share between player and synth
bool track1on = true, track2on = true, track3on = true, tableRefresh = false;

uint8_t sequencepos=0, tempo = 120;
long writeindex=0, readindex=0;
uint16_t playerpos=0;
uint16_t samplespertick = (float)((60.0f/(float)tempo)*POK_AUD_FREQ)/16;
uint16_t notetick=0; // samplespertick is a calculated value based on song speed. notetick is a counter
long samplesperpattern=0;

uint8_t tick=3; // loops between 3 channels. Tick 3 is used to calculate volume envelopes


SONG song;
OSC osc1,osc2,osc3;
OSC patch[MAXPATCHES];
BLOCK block[MAXBLOCKS];

#endif





