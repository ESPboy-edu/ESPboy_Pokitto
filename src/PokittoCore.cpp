/**************************************************************************/
/*!
    @file     PokittoCore.cpp
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

#include "Pokitto_settings.h"
#include "PokittoCore.h"

#include "PokittoFonts.h"
#include "PokittoTimer.h"
#include "PokittoLogos.h"
#include <stdlib.h>
#include "ESPboyInit.h"


ESPboyInit myESPboy;
//ESPboyTerminalGUI *terminalGUIobj = NULL;
//ESPboyOTA2 *OTA2obj = NULL;

using namespace Pokitto;

void (*Core::updateHook)(bool) = +[](bool){};

bool Core::run_state; // this definition needed

uint8_t Core::timePerFrame;
uint32_t Core::frameCount;

/** Components */
Buttons Core::buttons;
#if (POK_ENABLE_SOUND == 1)
//Sound Core::sound;
#endif
Display Core::display;

extern uint8_t *Display::screenbuffer;

void Core::begin() {
    myESPboy.begin("Pokitto");
/*  
      //Check OTA2
  if (myESPboy.getKeys()&PAD_ACT || myESPboy.getKeys()&PAD_ESC) { 
     terminalGUIobj = new ESPboyTerminalGUI(&myESPboy.tft, &myESPboy.mcp);
     OTA2obj = new ESPboyOTA2(terminalGUIobj);
  }
 */     
   #if PROJ_SCREENMODE != TASMODE
     Display::screenbuffer = new uint8_t[POK_SCREENBUFFERSIZE]; // maximum resolution
   #endif // TASMODE    
    init(); // original functions
    display.begin();
    timePerFrame = POK_FRAMEDURATION;
	//read default settings from flash memory (set using settings.hex)
	readSettings();
	showLogo();
    display.clearLCD();
}

void Core::init() {
    run_state = true;
    display.enableDirectPrinting(false);
    display.setFont(DEFAULT_FONT);
    //initClock();
    //initGPIO();
    //initButtons();
    //initRandom();
    //initAudio();
    //initDisplay();
}

void Core::init(uint8_t switches) {
    run_state = true;
    display.enableDirectPrinting(false);
    display.setFont(DEFAULT_FONT);
    //initClock();
    //initGPIO();
    //initButtons();
    //initRandom();
    //initAudio();
    //initDisplay();
}

void Core::initButtons() {
    //Pokitto::initButtons();
}

bool Core::isRunning() {
    return run_state;
}

void Core::initDisplay() {
}

void Core::showLogo() {
// 128x43
    myESPboy.tft.fillScreen(TFT_BLACK);
    myESPboy.tft.drawXBitmap(0, 40, Pokitto_logo, 128, 43, TFT_GREEN, TFT_BLACK);      
	delay(2000);
}


void Core::wait(uint16_t tme){
delay(tme);
}


void Core::readSettings() {}
void Core::titleScreen(const char* name){}
void Core::titleScreen(const uint8_t* logo){}
void Core::titleScreen(){}
void Core::titleScreen(const char*  name, const uint8_t *logo){}


/**
 * Update all the subsystems, like graphics, audio, events, etc.
 * Note: the update rect is used for drawing only part of the screen buffer to LCD. Because of speed optimizations,
 * the x, y, and width of the update rect must be dividable by 4 pixels, and the height must be dividable by 8 pixels.
 * The update rect is currently used for 220x176, 4 colors, screen mode only.
 * @param useDirectMode True, if only direct screen drawing is used. False, if the screen buffer is drawn. Note: If sprites are enabled, they are drawn in both modes.
 * @param updRectX The update rect.
 * @param updRectY The update rect.
 * @param updRectW The update rect.
 * @param updRectH The update rect.
 */
 
 
 uint32_t Core::getTime(){return (millis());};
 uint32_t Core::getTime_us(){return (micros());};
 
bool Core::update(bool useDirectMode, uint8_t updRectX, uint8_t updRectY, uint8_t updRectW, uint8_t updRectH) {
    static uint32_t prevTime;
	if (getTime()-prevTime > timePerFrame) { //if time to render a new frame is reached and the frame end has ran once
		updateHook(true);
		frameCount++;
		buttons.update();
	    //#if (POK_ENABLE_SOUND == 1)
		//	sound.updateTrack();
		//	sound.updatePattern();
		//	sound.updateNote();
		//#endif
		//display.update();

        // FPS counter
		#if defined(PROJ_USE_FPS_COUNTER) ||  defined(PROJ_SHOW_FPS_COUNTER)
		  String toPrint = (String)(1000/(getTime()-prevTime)) + "   ";
		  myESPboy.tft.drawString(toPrint,0,0);
        #endif
         prevTime = getTime();
	     return true;}
	else{
	     updateHook(false);
	     return false;
     }
     return false; 
}



void Core::setFrameRate(uint8_t fps) {
	timePerFrame = 1000 / fps;}

uint8_t Core::getFrameRate() {
	return 1000 / timePerFrame;}

void Core::pickRandomSeed(){
        //initRandom();
        }


bool Core::collidePointRect(int16_t x1, int16_t y1 ,int16_t x2 ,int16_t y2, int16_t w, int16_t h){
	if((x1>=x2)&&(x1<x2+w))
	if((y1>=y2)&&(y1<y2+h))
	return true;
	return false;
}

bool Core::collideRectRect(int16_t x1, int16_t y1, int16_t w1, int16_t h1 ,int16_t x2 ,int16_t y2, int16_t w2, int16_t h2){
  return !( x2     >=  x1+w1  ||
            x2+w2  <=  x1     ||
            y2     >=  y1+h1  ||
            y2+h2  <=  y1     );
}

bool Core::collideBitmapBitmap(int16_t x1, int16_t y1, const uint8_t* b1, int16_t x2, int16_t y2, const uint8_t* b2){
  int16_t w1 = pgm_read_byte(b1);
  int16_t h1 = pgm_read_byte(b1 + 1);
  int16_t w2 = pgm_read_byte(b2);
  int16_t h2 = pgm_read_byte(b2 + 1);

  if(collideRectRect(x1, y1, w1, h1, x2, y2, w2, h2) == false){
    return false;
  }

  int16_t xmin = (x1>=x2)? 0 : x2-x1;
  int16_t ymin = (y1>=y2)? 0 : y2-y1;
  int16_t xmax = (x1+w1>=x2+w2)? x2+w2-x1 : w1;
  int16_t ymax = (y1+h1>=y2+h2)? y2+h2-y1 : h1;
  for(uint8_t y = ymin; y < ymax; y++){
    for(uint8_t x = xmin; x < xmax; x++){
      if(display.getBitmapPixel(b1, x, y) && display.getBitmapPixel(b2, x1+x-x2, y1+y-y2)){
        return true;
      }
    }
  }
  return false;
}


//** EOF **//








