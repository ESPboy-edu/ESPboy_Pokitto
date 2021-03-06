/**************************************************************************/
/*!
    @file     PokittoCore.h
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

#ifndef POKITTOCORE_H
#define POKITTOCORE_H

#include "PokittoFonts.h"
#include "PokittoPalettes.h"
#include "PokittoDisplay.h"
#include "PokittoButtons.h"
#include "PokittoSound.h"


namespace Pokitto {

/** Core class.
 *  The Core class is a class consisting of static data and methods.
 *  It handles the lowlevel hardware functions of the Pokitto.
 *  It is declared as static to prevent several instances running at same time.
 * Example:
 * @code
 * // A simple "Hello World!" program with Pokitto
 *
 * #include "Pokitto.h"
 *
 * Pokitto::Core myApp;
 *
 * int main() {
 *     myApp.begin(); // This starts up the console (the display, buttons etc.)
 *     while(myApp.isRunning()) {
 *         if(myApp.Update()) {
 *             myApp.display.print("Hello World!");
 *         }
 *     }
 * }
 * @endcode
 */

class Core
{
public:
  //static Backlight backlight;
  static Buttons buttons;
  #if (POK_ENABLE_SOUND == 1)
  //static Sound sound;
  #endif
  static Display display;

  // EXCECUTION CONTROL
public:
  static void (*updateHook)(bool);
  /** Initialize runtime (use this one) */
  static void begin();
  /** Initialize runtime (deprecated, avoid) */
  static void init();
  /** Initialize runtime with options (deprecated, avoid) */
  static void init(uint8_t);
  /** Return run state (1 = running, 0 = shutting down) */
  static bool isRunning();
  /** Stop running */
  static void quit();
//protected:
  /** run_state is true as long as program is running */
  static bool run_state;
  static void setFrameRate(uint8_t fps);
  static uint8_t getFrameRate();
  static bool update(bool useDirectMode=false, uint8_t updRectX=0, uint8_t updRectY=0, uint8_t updRectW=LCDWIDTH, uint8_t updRectH=LCDHEIGHT);
    

public:
  // INITIALIZATION
  /** Initialize display */
  static void initDisplay();
  /** Initialize random generator */
  static void initRandom();
  /** Initialize GPIO */
  static void initGPIO();
  /** Initialize LCD */
  static void initLCD();
  /** Initialize Audio */
  static void initAudio();


  // DISPLAY
public:
  /** Initialize backlight */
  static void initBacklight();

  // TIMEKEEPING
public:
  /** Initialize runtime clock */
  static void initClock();
  /** Get value of time elapsed during program in milliseconds */
  static uint32_t getTime();
  /** Get value of time elapsed during program in microseconds */
  static uint32_t getTime_us();
  /** Wait for n milliseconds */
  static void wait(uint16_t);
  /** FPS */
  static uint32_t fps_counter;
  static bool fps_counter_updated;
protected:
  /** Time of next refresh */
  static uint32_t refreshtime;

  // DIRECT TO SCREEN
public:
  /** Display Pokitto logo */
  static void showLogo();
  static void showWarning();
  static void setVolLimit();

// BUTTON INPUT HANDLING
public:
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

  // AUDIO RELATED
  static uint8_t ampIsOn();
  static void ampEnable(uint8_t);
  static uint8_t soundbyte;

protected:
    static uint8_t timePerFrame;
    static uint32_t nextFrameMillis;
    static void updatePopup();
    static const char* popupText;
    static uint8_t popupTimeLeft;
    static void displayBattery();
    static uint16_t frameDurationMicros;
    static uint32_t frameStartMicros, frameEndMicros;
    static uint8_t startMenuTimer;
    static uint32_t fps_refreshtime;

  // GB RELATED
public:
    static void readSettings();
    static void titleScreen(const char* name, const uint8_t *logo);
    static void titleScreen(const char* name);
    static void titleScreen(const uint8_t* logo);
    static void titleScreen();
    static uint32_t frameCount;
    static void pickRandomSeed();
    static bool collidePointRect(int16_t x1, int16_t y1 ,int16_t x2 ,int16_t y2, int16_t w, int16_t h);
	static bool collideRectRect(int16_t x1, int16_t y1, int16_t w1, int16_t h1 ,int16_t x2 ,int16_t y2, int16_t w2, int16_t h2);
    static bool collideBitmapBitmap(int16_t x1, int16_t y1, const uint8_t* b1, int16_t x2, int16_t y2, const uint8_t* b2);

};

// this is the instance used by the system
extern Core core;


}

#endif // POKITTOCORE_H


