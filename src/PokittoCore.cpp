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

#include "ESPboyInit.h"
#include "PokittoCore.h"

#include "PokittoFonts.h"
#include "PokittoTimer.h"
#include "PokittoLogos.h"
#include <stdlib.h>


ESPboyInit myESPboy;


//char selectedfile[25];

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

#if PROJ_SCREENMODE != TASMODE
  extern uint8_t *Display::screenbuffer;
#endif


void Core::begin() {
    myESPboy.begin("Pokitto");
    //LittleFS.begin();
  
      
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
    #if PROJ_SCREENMODE == MODE15_240x240
      myESPboy.tft.drawXBitmap((240-128)/2, 80, Pokitto_logo, 128, 43, TFT_GREEN, TFT_BLACK); 
    #else
      myESPboy.tft.drawXBitmap(0, 40, Pokitto_logo, 128, 43, TFT_GREEN, TFT_BLACK);      
	#endif
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


int8_t Core::menu(const char* const* items, uint8_t length) {
if (display.color>3) display.color=1;
#if (ENABLE_GUI > 0)
	display.persistence = false;
	int8_t activeItem = 0;
	int16_t currentY = display.height;
	int16_t targetY = 0, rowh = display.fontHeight + 2;
	boolean exit = false;
	int8_t answer = -1;
	while (isRunning()) {
		if (update()) {
			if (buttons.pressed(BTN_A) || buttons.pressed(BTN_B) || buttons.pressed(BTN_C)) {
				exit = true; //time to exit menu !
				targetY = - display.fontHeight * length - 2; //send the menu out of the screen
				if (buttons.pressed(BTN_A)) {
					answer = activeItem;
					//sound.playOK();
				} else {
					//sound.playCancel();
				}
			}
			if (exit == false) {
				if (buttons.repeat(BTN_DOWN,4)) {
					activeItem++;
					//sound.playTick();
				}
				if (buttons.repeat(BTN_UP,4)) {
					activeItem--;
					//sound.playTick();
				}
				//don't go out of the menu
				if (activeItem == length) activeItem = 0;
				if (activeItem < 0) activeItem = length - 1;

				targetY = -rowh * activeItem + (rowh+4); //center the menu on the active item
			} else { //exit :
				if ((currentY - targetY) <= 1)
				return (answer);
			}
			//draw a fancy menu
			currentY = (currentY + targetY) / 2;
			display.cursorX = 0;
			display.cursorY = currentY;
			display.textWrap = false;
			uint16_t fc,bc;
			fc = display.color;
            bc = display.bgcolor;
			for (byte i = 0; i < length; i++) {
				display.cursorY = currentY + rowh * i;
				if (i == activeItem){
					display.cursorX = 3;

                    //display.fillRoundRect(0, currentY + display.fontHeight * activeItem - 2, LCDWIDTH, (display.fontHeight+3), 3);
                    display.fillRect(0, currentY + rowh * activeItem - 2, LCDWIDTH, (rowh));
                    display.setColor(bc,fc);
				} else display.setColor(fc,bc);

				display.println((char*)*(const unsigned int*)(items+i));
				display.setColor(fc,bc);
			}

		}
	}
#else
	return 0;
#endif
	return 0;
}


void Core::keyboard(char* text, uint8_t length) {
#if (ENABLE_GUI > 0)
	display.persistence = false;
	//memset(text, 0, length); //clear the text
	text[length-1] = '\0';
	//active character in the typing area
	int8_t activeChar = 0;
	//selected char on the keyboard
	int8_t activeX = 0;
	int8_t activeY = 2;
	//position of the keyboard on the screen
	int8_t currentX = LCDWIDTH;
	int8_t currentY = LCDHEIGHT;
	int8_t targetX = 0;
	int8_t targetY = 0;

	while (1) {
		if (update()) {
			//move the character selector
			if (buttons.repeat(BTN_DOWN, 4)) {
				activeY++;
				//sound.playTick();
			}
			if (buttons.repeat(BTN_UP, 4)) {
				activeY--;
				//sound.playTick();
			}
			if (buttons.repeat(BTN_RIGHT, 4)) {
				activeX++;
				//sound.playTick();
			}
			if (buttons.repeat(BTN_LEFT, 4)) {
				activeX--;
				//sound.playTick();
			}
			//don't go out of the keyboard
			if (activeX == KEYBOARD_W) activeX = 0;
			if (activeX < 0) activeX = KEYBOARD_W - 1;
			if (activeY == KEYBOARD_H) activeY = 0;
			if (activeY < 0) activeY = KEYBOARD_H - 1;
			//set the keyboard position on screen
			targetX = -(display.fontWidth+1) * activeX + LCDWIDTH / 2 - 3;
			targetY = -(display.fontHeight+1) * activeY + LCDHEIGHT / 2 - 4 - display.fontHeight;
			//smooth the keyboard displacement
			currentX = (targetX + currentX) / 2;
			currentY = (targetY + currentY) / 2;
			//type character
			if (buttons.pressed(BTN_A)) {
				if (activeChar < (length-1)) {
					byte thisChar = activeX + KEYBOARD_W * activeY;
					if((thisChar == 0)||(thisChar == 10)||(thisChar == 13)) //avoid line feed and carriage return
					continue;
					text[activeChar] = thisChar;
					text[activeChar+1] = '\0';
				}
				activeChar++;
				//sound.playOK();
				if (activeChar > length)
				activeChar = length;
			}
			//erase character
			if (buttons.pressed(BTN_B)) {
				activeChar--;
				//sound.playCancel();
				if (activeChar >= 0)
				text[activeChar] = 0;
				else
				activeChar = 0;
			}
			//leave menu
			if (buttons.pressed(BTN_C)) {
				//sound.playOK();
				while (1) {
					if (update()) {
						//display.setCursor(0,0);
						display.println(("You entered\n"));
						display.print(text);
						display.println(("\n\n\n\x15:okay \x16:edit"));
						if(buttons.pressed(BTN_A)){
							//sound.playOK();
							return;
						}
						if(buttons.pressed(BTN_B)){
							//sound.playCancel();
							break;
						}
					}
				}
			}
			//draw the keyboard
			for (int8_t y = 0; y < KEYBOARD_H; y++) {
				for (int8_t x = 0; x < KEYBOARD_W; x++) {
					display.drawChar(currentX + x * (display.fontWidth+1), currentY + y * (display.fontHeight+1), x + y * KEYBOARD_W, 1);
				}
			}
			//draw instruction
			display.cursorX = currentX-display.fontWidth*6-2;
			display.cursorY = currentY+1*(display.fontHeight+1);
			display.print(("\25type"));

			display.cursorX = currentX-display.fontWidth*6-2;
			display.cursorY = currentY+2*(display.fontHeight+1);
			display.print(("\26back"));

			display.cursorX = currentX-display.fontWidth*6-2;
			display.cursorY = currentY+3*(display.fontHeight+1);
			display.print(("\27save"));

			//erase some pixels around the selected character
			display.setColor(WHITE);
			display.drawFastHLine(currentX + activeX * (display.fontWidth+1) - 1, currentY + activeY * (display.fontHeight+1) - 2, 7);
			//draw the selection rectangle
			display.setColor(BLACK);
			display.drawRoundRect(currentX + activeX * (display.fontWidth+1) - 2, currentY + activeY * (display.fontHeight+1) - 3, (display.fontWidth+2)+(display.fontWidth-1)%2, (display.fontHeight+5), 3);
			//draw keyboard outline
			//display.drawRoundRect(currentX - 6, currentY - 6, KEYBOARD_W * (display.fontWidth+1) + 12, KEYBOARD_H * (display.fontHeight+1) + 12, 8, BLACK);
			//text field
			display.drawFastHLine(0, LCDHEIGHT-display.fontHeight-2, LCDWIDTH);
			display.setColor(WHITE);
			display.fillRect(0, LCDHEIGHT-display.fontHeight-1, LCDWIDTH, display.fontHeight+1);
			//typed text
			display.cursorX = 0;
			display.cursorY = LCDHEIGHT-display.fontHeight;
			display.setColor(BLACK);
			display.print(text);
			//blinking cursor
			if (((frameCount % 8) < 4) && (activeChar < (length-1)))
			display.drawChar(display.fontWidth * activeChar, LCDHEIGHT-display.fontHeight, '_',1);
		}
	}
#endif
}





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








