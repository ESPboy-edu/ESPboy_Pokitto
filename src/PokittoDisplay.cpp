/**************************************************************************/
/*!
    @file     PokittoDisplay.cpp
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


/* THE SEGMENT BELOW PERTAINS TO CIRCLE DRAWING FUNCTIONS ONLY
*
This is the core graphics library for all our displays, providing a common
set of graphics primitives (points, lines, circles, etc.).  It needs to be
paired with a hardware-specific library for each display device we carry
(to handle the lower-level functions).
Adafruit invests time and resources providing this open source code, please
support Adafruit & open-source hardware by purchasing products from Adafruit!
Copyright (c) 2013 Adafruit Industries.  All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cstddef>
#include <algorithm>

#include "PokittoDisplay.h"
#include "Pokitto_settings.h"
#include "PokittoCore.h"
//#include "PokittoSound.h"
#include "ESPboyInit.h"

extern ESPboyInit myESPboy;
#define X_OFFSET 9
#define Y_OFFSET 20



void CheckStack(){};
void ShowCrashScreenAndWait( const char* texLine1, const char* texLine2, const char* texLine3, const char* texLine4, const char* texLine5 ) {};



using core = Pokitto::Core;
//using _pdsound = Pokitto::Sound;
using namespace Pokitto;

void lcdPrepareRefresh(){};

void lcdInit(){
  //myESPboy.tft.fillScreen(TFT_GREEN);
  //delay(50);
  myESPboy.tft.fillScreen(TFT_BLACK);
};

void lcdFillSurface(uint16_t c){
   myESPboy.tft.fillScreen(TFT_BLACK);
};

void lcdPixel(int16_t x, int16_t y, uint16_t color){
   myESPboy.tft.drawPixel(x+X_OFFSET, y+Y_OFFSET, color);
};


void lcdRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
   myESPboy.tft.drawRect(x0+X_OFFSET, y0+Y_OFFSET, x1, y1, color);
};


void lcdTile(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t* gfx){myESPboy.tft.drawString("NO TAS mode yet",0,0);};
void lcdRefreshMixMode(const uint8_t *screenBuffer, const uint16_t * palettePointer, const uint8_t * scanType){myESPboy.tft.drawString("NO MixMode yet",0,0);};
void lcdRefreshMode64( const uint8_t *scrbuf, const uint16_t* paletteptr ){myESPboy.tft.drawString("NO Mode64 yet",0,0);};



//220x176 clipping to 128x128
#define DX PROJ_MODE16_OFFSET_X
#define DY PROJ_MODE16_OFFSET_Y

void IRAM_ATTR lcdRefreshMode16(const uint8_t *scrbuf, const uint16_t* paletteptr){
   static uint16_t bufLine[128] __attribute__ ((aligned));
   uint8_t readByte;
   uint16_t addr;

  myESPboy.tft.setAddrWindow(0, 0, 128, 128);

  for (uint8_t yyy=0; yyy<128; yyy++){
      addr=(DY+yyy)*220+DX;
    for(int xxx=0; xxx<128; xxx++){
      readByte=scrbuf[addr/2];
      if(addr%2)bufLine[xxx] = paletteptr[readByte&15];
      else bufLine[xxx] = paletteptr[readByte>>4];
      addr++;
    }
    myESPboy.tft.pushColors(bufLine, 128);
  }
};


//220x176 fast rescale to 128x128
void IRAM_ATTR lcdRefreshMode15(const uint8_t *scrbuf, const uint16_t* paletteptr){
  
  static uint16_t *bufLine = NULL;
  static bool initFlag = false;
  
  if(initFlag == false){
    initFlag = true;
    bufLine = new uint16_t[128];
  };
  
  myESPboy.tft.setAddrWindow(0, 0, 128, 128);
  
  for (auto yyy=0; yyy<128; yyy++){
    uint32_t xxd = ((yyy*176)>>7) * 220;
    for(auto xxx = 0; xxx<128; xxx++){
      uint32_t addr = xxd + ((xxx*220)>>7);
      uint8_t readByte = scrbuf[addr>>1];
      if(addr%2)bufLine[xxx] = paletteptr[readByte&15];
      else bufLine[xxx] = paletteptr[readByte>>4];
    }
    myESPboy.tft.pushColors(bufLine, 128);
  }
};


//110x88
void IRAM_ATTR lcdRefreshMode13(const uint8_t *scrbuf, const uint16_t* paletteptr, uint8_t offset){
   static uint16_t *bufLine = NULL;
   static bool initFlag = false;  
   if(initFlag == false){
     initFlag = true;
     bufLine = new uint16_t[LCDWIDTH];
  };
   uint16_t addr=0;
   myESPboy.tft.setAddrWindow(X_OFFSET, Y_OFFSET, LCDWIDTH, LCDHEIGHT);
    for(uint8_t y=0; y<LCDHEIGHT; y++){
     for(uint8_t x=0; x<LCDWIDTH; x++)
       bufLine[x]=paletteptr[scrbuf[addr++]];
     myESPboy.tft.pushColors(bufLine, Display::width);}
};


//110x88
void IRAM_ATTR lcdRefreshMode2(const uint8_t* scrbuf, const uint16_t* paletteptr ){
   static uint16_t *bufLine = NULL;
   static bool initFlag = false;  
   if(initFlag == false){
     initFlag = true;
     bufLine = new uint16_t[LCDWIDTH];
  };
   uint8_t readByte;
   uint16_t addr=0;
   myESPboy.tft.setAddrWindow(X_OFFSET, Y_OFFSET, LCDWIDTH, LCDHEIGHT);
    for(uint8_t y=0; y<LCDHEIGHT; y++){
     for(uint8_t x=0; x<LCDWIDTH; x+=2){
       readByte=scrbuf[addr++];
       bufLine[x]=paletteptr[readByte>>4];
       bufLine[x+1]=paletteptr[readByte&15];
     }
     myESPboy.tft.pushColors(bufLine, Display::width);
   }
};


uint8_t* Display::m_scrbuf;
uint8_t Display::m_mode;
uint8_t Display::palOffset;
uint8_t Display::fontSize=1;
int16_t Display::cursorX, Display::cursorY;
uint8_t Display::m_w, Display::m_h;
uint8_t Display::fontWidth, Display::fontHeight;
bool Display::textWrap=true;
#if (PROJ_SCREENMODE == MIXMODE)
    uint8_t Display::subMode; // for mixed mode switching
    uint8_t Display::scanType[88]; // for mixed screen mode
#endif

uint8_t Display::persistence = 0;
uint16_t Display::color = 1;
uint16_t Display::bgcolor = 0;
uint16_t Display::invisiblecolor = 17;
uint16_t Display::directcolor=0xFFFF;
uint16_t Display::directbgcolor=0x0;
bool Display::directtextrotated=false;

uint16_t* Display::paletteptr;
uint16_t Display::palette[PALETTE_SIZE];
const unsigned char* Display::font;
int8_t Display::adjustCharStep = 1;
int8_t Display::adjustLineStep = 1;
bool Display::fixedWidthFont = false, Display::flipFontVertical = false;
uint8_t Display::m_colordepth = PROJ_COLORDEPTH;
uint8_t Display::width = LCDWIDTH;
uint8_t Display::height = LCDHEIGHT;

#if PROJ_SCREENMODE != TASMODE
//uint8_t __attribute__ ((aligned)) Display::screenbuffer[POK_SCREENBUFFERSIZE]; // maximum resolution
#endif // TASMODE

uint16_t Display::getWidth() {
    return width;
}

uint32_t Display::getNumberOfColors() {
    return 1<<PROJ_COLORDEPTH;
}

uint16_t Display::getHeight() {
    return height;
}

uint8_t Display::getColorDepth() {
    return m_colordepth;
}

void Display::setColorDepth(uint8_t v) {
    if (v > PROJ_COLORDEPTH) v=PROJ_COLORDEPTH;
    m_colordepth = v;
}

void Display::clearLCD() {
    lcdFillSurface(0);
    setCursor(0,0); // old basic computer style
}

void Display::fillLCD(uint16_t c) {
    lcdFillSurface(c);
}

void Display::directPixel(int16_t x, int16_t y, uint16_t color) {
    if ((invisiblecolor < PALETTE_SIZE) && (invisiblecolor < 16) && (color == palette[invisiblecolor])) return;
    lcdPixel(x,y,color);
}

void Display::directTile(int16_t x, int16_t y, int16_t x2, int16_t y2, uint16_t* gfx) {
    lcdTile(x,y,x2,y2,gfx);
}

void Display::directRectangle(int16_t x, int16_t y,int16_t x2, int16_t y2, uint16_t color) {
    lcdRectangle(x,y,x2,y2,color);
}

void Display::begin() {
#if PROJ_SCREENMODE != TASMODE
    m_scrbuf = screenbuffer;
#endif
    setDefaultPalette();
    m_mode = 0; // direct printing on by default
    m_w = POK_LCD_W;
    m_h = POK_LCD_H;
    setFont(DEFAULT_FONT);
    invisiblecolor=17;
    bgcolor=0;
    if (PROJ_COLORDEPTH) m_colordepth = PROJ_COLORDEPTH;
    else m_colordepth = 4;
    lcdInit();
}

void Display::setCursor(int16_t x,int16_t y) {
    cursorX = x;
    cursorY = y;
}

/**
 * Update the display.
 * The update rect is used for drawing only part of the screen buffer to LCD. Because of speed optimizations, the
 * x, y, and width of the update rect must be dividable by 4 pixels, and the height must be dividable by 8 pixels.
 * Note: The update rect is currently used for 220x176, 4 colors, screen mode only.
 * @param useDirectMode True, if only direct screen drawing is used. False, if the screen buffer is drawn. Note: If sprites are enabled, they are drawn in both modes.
 * @param updRectX The update rect.
 * @param updRectY The update rect.
 * @param updRectW The update rect.
 * @param updRectH The update rect.
 */
void Display::update(bool useDirectDrawMode) {
    if (!useDirectDrawMode)
	    #if POK_SCREENMODE == MIXMODE
		  lcdRefreshMixMode(m_scrbuf, paletteptr, scanType);
	    #else
		  lcdRefresh(m_scrbuf, useDirectDrawMode);
	    #endif
  

    #ifndef PERSISTENCE
    if (!persistence)
        clear();
    #endif
}

void Display::printFPS(){
  String toPrint;
  toPrint= (String)((int)core.fps_counter) + "    ";
  myESPboy.tft.drawString(toPrint,0,0);
}



void Display::directBitmap(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t depth, uint8_t scale) {
    uint8_t w = *bitmap;
	uint8_t h = *(bitmap + 1);
	bitmap = bitmap + 2; //add an offset to the pointer to start after the width and height
    int16_t i, j;
    int8_t byteNum, bitNum, byteWidth = (w + 7) >> 3;

    if (depth == 1) {
        for (i = 0; i < w; i++) {
            byteNum = i / 8;
            bitNum = i % 8;
            for (j = 0; j < h; j++) {
                if (*(bitmap + j * byteWidth + byteNum) & (0x80 >> bitNum)) { //0x80 = B10000000
                    if (scale==1) directPixel(x + i, y + j,directcolor);
                    else {
                        directPixel(x + i + i, y + j + j,directcolor);
                        directPixel(x + 1 + i + i, y + j + j,directcolor);
                        directPixel(x + i + i, y + j + j + 1,directcolor);
                        directPixel(x + i + i + 1 , y + j + j + 1,directcolor);
                    }
                }
            }
        }
    } else if (depth == 4) {
        for (j = 0; j < h; j+=1) {
            for (i = 0; i < w; i+=2) {
                uint16_t col = paletteptr[*bitmap>>4]; //higher nibble
                if (scale==2) {
                        directPixel(x + (i<<1), y + (j<<1),col);
                        directPixel(x + (i<<1) + 1, y + (j<<1),col);
                        directPixel(x + (i<<1) + 1, y + (j<<1) + 1,col);
                        directPixel(x + (i<<1), y + (j<<1) + 1,col);
                } else directPixel(x + i, y + j,col);
                col = paletteptr[*bitmap&0xF]; // lower nibble
                if (scale==2) {
                        directPixel(x + (i<<1) + 2, y + (j<<1),col);
                        directPixel(x + (i<<1) + 1 + 2, y + (j<<1),col);
                        directPixel(x + (i<<1) + 1 + 2, y + (j<<1) + 1,col);
                        directPixel(x + (i<<1) + 2 , y + (j<<1) + 1,col);
                } else directPixel(x + i + 1, y + j,col);
                bitmap++;
            }
        }
    }
    else if (depth == 8) {
        for (j = 0; j < h; j+=1) {
            for (i = 0; i < w; i++) {
                uint16_t col = paletteptr[*bitmap];
                if (scale==2) {
                        directPixel(x + (i<<1), y + (j<<1),col);
                        directPixel(x + (i<<1) + 1, y + (j<<1),col);
                        directPixel(x + (i<<1) + 1, y + (j<<1) + 1,col);
                        directPixel(x + (i<<1), y + (j<<1) + 1,col);
                } else directPixel(x + i, y + j,col);
                bitmap++;
            }
        }
    }
}

int Display::directChar(int16_t x, int16_t y, uint16_t index){
    uint8_t fontW = font[0];
    uint8_t fontH = font[1];

    uint8_t hbytes = (fontH + 7)>>3;

    if( fontSize != 2 ) fontSize = 1;

    const uint8_t* bitmap = font + 4 + index*(1 + fontW*hbytes); //add an offset to the pointer
    int charW = *bitmap; //first byte of char is char width
    ++bitmap;

    for (int i = 0; i < charW; ++i) {
        for(int byteNum = 0; byteNum < hbytes; ++byteNum) {
            uint8_t bitcolumn = *bitmap;
            ++bitmap;
            int endRow = (8 + 8*byteNum < fontH) ? (8 + 8*byteNum) : fontH;
            for (int j = 8*byteNum; j < endRow; ++j) {
                uint16_t c = (bitcolumn&1) ? directcolor : directbgcolor;
                if(c != invisiblecolor) {
                    if (fontSize==2) {
                        directPixel(x + (i<<1)  , y + (j<<1), c);
                        directPixel(x + (i<<1)+1, y + (j<<1), c);
                        directPixel(x + (i<<1)  , y + (j<<1)+1, c);
                        directPixel(x + (i<<1)+1, y + (j<<1)+1, c);
                    } else {
                        if(directtextrotated) directPixel(y + fontH - j - 1, x + i, c);
                        else directPixel(x + i, y + j, c);
                    }

                }
                bitcolumn>>=1;
            }
        }
    }
    return fontSize*(charW + adjustCharStep); // for character stepping
}


void Display::clear() {
#if PROJ_SCREENMODE != TASMODE
    uint8_t c=0;
    c = bgcolor & (PALETTE_SIZE-1) ; //don't let palette go out of bounds
    if (m_colordepth==1 && bgcolor) {
        c = 0xFF; // bgcolor !=0, set all pixels
    } else if (m_colordepth==2) {
        c = bgcolor & 0x3;
        c = c | (c << 2);
        c = c | (c << 4);
    } else if (m_colordepth==4) {
        c = (c & 0x0F) | (c << 4);
    }

    memset((void*)m_scrbuf, c, POK_SCREENBUFFERSIZE);
    setCursor(0,0);
#endif
}

void Display::scroll(int16_t pixelrows) {
    uint16_t index = 0, index2=0,oc;
    if (pixelrows==0) return;
    if (pixelrows >= height) pixelrows=height-1;
    if (m_colordepth == 4) index2 = pixelrows*width/2;
    else if (m_colordepth == 2) index2 = pixelrows*width/4;
    else return;
    oc = color;
    color = bgcolor;
    if (pixelrows>0) {
        for (uint16_t y=0;y<height-pixelrows;y++) {
            for (uint16_t x=0;x<(width/8)*m_colordepth;x++)
                m_scrbuf[index++]=m_scrbuf[index2++];
        }
        fillRect(0,cursorY,width,height);
    } else {
        for (uint16_t y=pixelrows;y<height;y++) {
            for (uint16_t x=0;x<(width*m_colordepth)/8;x++)
                m_scrbuf[index2++]=m_scrbuf[index++];
        }
        fillRect(0,0,width,pixelrows);
    }
    color=oc;
}

void Display::fillScreen(uint16_t c) {
    #if PROJ_SCREENMODE != TASMODE
    c = c & (PALETTE_SIZE-1) ; //don't let palette go out of bounds
    if (m_colordepth==1 && c) c=0xFF; // set all pixels
    else if (m_colordepth==2) {
        c = c & 0x3;
        c = c | (c << 2);
        c = c | (c << 4);
    } else if (m_colordepth==4){
        c = (c & 0x0F) | (c << 4);
    }
    memset((void*)m_scrbuf, c, POK_SCREENBUFFERSIZE);
    #endif
}

void Display::setDefaultPalette() {
    #if PICOPALETTE
        loadRGBPalette(palettePico);
    #else
        loadRGBPalette(POK_DEFAULT_PALETTE);
    #endif //PICOPALETTE
}

void Display::setColor(uint8_t c) {
    color = c & ((1<<PROJ_COLORDEPTH)-1); // cut out colors that go above palette limit
}

void Display::setColor(uint8_t c,uint8_t bgc){
    color = c & ((1<<PROJ_COLORDEPTH)-1); // cut out colors that go above palette limit
    bgcolor = bgc & ((1<<PROJ_COLORDEPTH)-1); // cut out colors that go above palette limit
}

void Display::setInvisibleColor(uint16_t c){
    invisiblecolor = c; // invisible color can have values beyond 255 for identification purposes
}

uint8_t Display::getColor() {
    return color;
}

uint8_t Display::getBgColor() {
    return bgcolor;
}

uint16_t Display::getInvisibleColor() {
    return invisiblecolor;
}

void Display::drawFastVLine(int16_t x, int16_t y, int16_t h){
    if (h<0) {y += h; h = -h;}
    drawColumn(x,y,y+h);
}

void Display::drawFastHLine(int16_t x, int16_t y, int16_t w){
    if (w<0) {x += w; w = -w;}
    drawRow(x,x+w-1,y);
}

void Display::fillRect(int16_t x, int16_t y, int16_t w, int16_t h) {
    fillRectangle(x,y,w,h);
}

void Display::drawRect(int16_t x, int16_t y, int16_t w, int16_t h) {
    drawRectangle(x,y,w,h);
}

void Display::fillTriangle(int16_t x0, int16_t y0,
        int16_t x1, int16_t y1,
        int16_t x2, int16_t y2) {

    int a, b, y, last, tmp;

    a = getWidth();
    b = getHeight();
    if (x0 < 0 && x1 < 0 && x2 < 0) return;
    if (x0 >= a && x1 > a && x2 > a) return;
    if (y0 < 0 && y1 < 0 && y2 < 0) return;
    if (y0 >= b && y1 > b && y2 > b) return;

    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1) {
        tmp = y0;
        y0 = y1;
        y1 = tmp;
        tmp = x0;
        x0 = x1;
        x1 = tmp;
    }
    if (y1 > y2) {
        tmp = y2;
        y2 = y1;
        y1 = tmp;
        tmp = x2;
        x2 = x1;
        x1 = tmp;
    }
    if (y0 > y1) {
        tmp = y0;
        y0 = y1;
        y1 = tmp;
        tmp = x0;
        x0 = x1;
        x1 = tmp;
    }

    if (y0 == y2) { // Handle awkward all-on-same-line case as its own thing
        a = b = x0;
        if (x1 < a) a = x1;
        else if (x1 > b) b = x1;
        if (x2 < a) a = x2;
        else if (x2 > b) b = x2;
        drawFastHLine(a, y0, b - a + 1);
        return;
    }

    int dx01 = x1 - x0,
        dx02 = x2 - x0,
        dy02 = (1 << 16) / (y2 - y0),
        dx12 = x2 - x1,
        sa = 0,
        sb = 0;

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y1 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y0=y1
    // (flat-topped triangle).
    if (y1 == y2) last = y1; // Include y1 scanline
    else last = y1 - 1; // Skip it

    y = y0;

    if (y0 != y1) {
        int dy01 = (1 << 16) / (y1 - y0);

        for (y = y0; y <= last; y++) {
            a = x0 + ((sa * dy01) >> 16);
            b = x0 + ((sb * dy02) >> 16);
            sa += dx01;
            sb += dx02;
            /* longhand:
               a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
               b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
            */
            if (a > b) {
                tmp = a;
                a = b;
                b = tmp;
            }
            drawFastHLine(a, y, b - a);
        }
    }

    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    if (y1 != y2) {
        int dy12 = (1 << 16) / (y2 - y1);

        sa = dx12 * (y - y1);
        sb = dx02 * (y - y0);
        for (; y <= y2; y++) {
            a = x1 + ((sa * dy12) >> 16);
            b = x0 + ((sb * dy02) >> 16);
            sa += dx12;
            sb += dx02;

            if (a > b) {
                tmp = a;
                a = b;
                b = tmp;
            }
            drawFastHLine(a, y, b - a);
        }
    }
}

void Display::setFont(const unsigned char * f) {
	font = f;
	fontWidth = *(font)+1;
	fontHeight = *(font + 1)+1;
}

void Display::drawBitmap(int16_t x, int16_t y, const uint8_t * bitmap, uint8_t frameIndex)
{
	using std::size_t;
	constexpr size_t widthIndex = 0;
	constexpr size_t heightIndex = 1;
	constexpr size_t dataIndex = 2;
	constexpr size_t bitsPerByte = 8;
	const size_t width = bitmap[widthIndex];
	const size_t height = bitmap[heightIndex];
	const size_t frameSize = ((width * height) / (bitsPerByte / Display::m_colordepth));

	Display::drawBitmapData(x, y, width, height, &bitmap[dataIndex + (frameIndex * frameSize)]);
}

void Display::drawBitmap(int16_t x, int16_t y, const uint8_t* bitmap)
{
    if (bitmap == NULL){
       Serial.println("NULLPRTR! in PokittoDisplay.cpp line 630 drawBitmapData(x, y, w, h, bitmap)");
       return;}
    int16_t w = *bitmap;
    int16_t h = *(bitmap + 1);
    //add an offset to the pointer to start after the width and height
    bitmap = bitmap + 2;
    drawBitmapData(x, y, w, h, bitmap);
}

void Display::drawBitmapData(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t* bitmap) {
    /** visibility check */
    if (bitmap == NULL) return;
    if (y<-h || y>=height) return; //invisible
    if (x<-w || x>=width) return;  //invisible
    if (m_colordepth==2) drawBitmapData2BPP(x, y, w, h, bitmap);
    if (m_colordepth==4) drawBitmapData4BPP(x, y, w, h, bitmap);
    if (m_colordepth==8) drawBitmapData8BPP(x, y, w, h, bitmap);
}

void Display::drawBitmapDataXFlipped(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t* bitmap)
{
    /** visibility check */
    if (y<-h || y>height) return; //invisible
    if (x<-w || x>width) return;  //invisible
    /** 2 bpp mode */
    if (m_colordepth==2) drawBitmapDataXFlipped2BPP(x, y, w, h, bitmap);
    else if (m_colordepth==4) drawBitmapDataXFlipped4BPP(x, y, w, h, bitmap);
    /** 8 bpp mode */
    else if (m_colordepth==8) drawBitmapDataXFlipped8BPP(x, y, w, h, bitmap);

}

void Display::drawBitmapXFlipped(int16_t x, int16_t y, const uint8_t* bitmap)
{
    drawBitmapDataXFlipped(x, y, bitmap[0], bitmap[1], bitmap + 2);
}

void Display::drawBitmapYFlipped(int16_t x, int16_t y, const uint8_t* bitmap)
{
    drawBitmapDataYFlipped(x, y, bitmap[0], bitmap[1], bitmap + 2);
}

void Display::drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t rotation, uint8_t flip) {
#if PROJ_GAMEBUINO == 0
    if (!flip)
        drawBitmap(x,y,bitmap);
    else if(flip == FLIPH)
        drawBitmapXFlipped(x,y,bitmap);
    else if(flip == FLIPV)
        drawBitmapYFlipped(x,y,bitmap);
#else
	if((rotation == NOROT) && (flip == NOFLIP)){
		drawBitmap(x,y,bitmap); //use the faster algorithm
		return;
	}
	uint8_t w = bitmap[0];
	uint8_t h = bitmap[1];
	bitmap = bitmap + 2; //add an offset to the pointer to start after the width and height
    int8_t i, j, //coordinates in the raw bitmap
            k, l, //coordinates in the rotated/flipped bitmap
            byteNum, bitNum, byteWidth = (w + 7) >> 3;

    rotation %= 4;

    for (i = 0; i < w; i++) {
        byteNum = i / 8;
        bitNum = i % 8;
        for (j = 0; j < h; j++) {
            if (bitmap[j * byteWidth + byteNum] & (B10000000 >> bitNum)) {
                switch (rotation) {
                    case NOROT: //no rotation
                        k = i;
                        l = j;
                        break;
                    case ROTCCW: //90° counter-clockwise
                        k = j;
                        l = w - i - 1;
                        break;
                    case ROT180: //180°
                        k = w - i - 1;
                        l = h - j - 1;
                        break;
                    case ROTCW: //90° clockwise
                        k = h - j - 1;
                        l = i;
                        break;
                }
                if (flip) {
                    flip %= 4;
                    if (flip & B00000001) { //horizontal flip
                        k = w - k;
                    }
                    if (flip & B00000010) { //vertical flip
                        l = h - l;
                    }
                }
                k += x; //place the bitmap on the screen
                l += y;
                drawPixel(k, l);
            }
        }
    }
#endif //PROJ_GAMEBUINO

}

uint8_t* Display::getBuffer() {
    return m_scrbuf;
}

uint8_t Display::getBitmapPixel(const uint8_t* bitmap, uint16_t x, uint16_t y) {
    uint16_t w = *bitmap;
    uint8_t sourcebyte = bitmap[2+(y * ((w+7)>>3))+ (x>>3)];
    return sourcebyte & (0x80>>(x&7));
}

int Display::print_char(int16_t x, int16_t y, unsigned char c) {
    c -= font[2];
    if (m_mode) return directChar(x,y,c);
    return bufferChar(x,y,c);
}

void Display::drawChar(int16_t x, int16_t y, unsigned char c, uint8_t size) {
    print_char(x,y,c);
    return;
}

bool Display::isDirectPrintingEnabled() {
    return m_mode;
}

void Display::enableDirectPrinting(uint8_t m) {
    if (m) {
        m_mode=true;
        m_w = POK_LCD_W;
        m_h = POK_LCD_H;
    } else {
        m_mode=false;
        m_w = getWidth();
        m_h = getHeight();
    }
}

void Display::write(uint8_t c) {
	int charstep=0;
	if(font[3]) {
        // only caps in this font
        if (c>=97) c-=32;
	}
	switch(c) {
		case '\0':			//null
			break;
		case '\n':			//line feed
			cursorX = 0;
			inc_txtline();
			break;
		case 8:				//backspace
			cursorX -= font[0];
			charstep=print_char(cursorX,cursorY,' ');
			break;
		case 13:			//carriage return
			cursorX = 0;
			break;
		case 14:			//form feed new page(clear screen)
			//clear_screen();
			break;
		default:
			if (cursorX >= (m_w - font[0])) {
				cursorX = 0;
				if (textWrap) inc_txtline();
				else return; // stop outputting text
				charstep=print_char(cursorX,cursorY,c);
			}
			else
				charstep=print_char(cursorX,cursorY,c);
			#ifndef FULLWIDTHSPACES
			if (c==' ' && adjustCharStep) charstep=(charstep>>1)+1;
			#endif
			cursorX += charstep;
	}
}

void Display::inc_txtline() {
	if (cursorY > m_h - 2*font[1]) //= (height - (font[1]+1)))
		#if SCROLL_TEXT > 0
		scroll(font[1] + adjustLineStep);
		#else
		cursorY = 0;
		#endif
	else
		cursorY += font[1] + adjustLineStep;
}

/* default implementation: may be overridden */
void Display::write(const char *str)
{
  while (*str)
    write(*str++);
}

/* default implementation: may be overridden */
void Display::write(const uint8_t *buffer, uint8_t size)
{
  while (size--)
    write(*buffer++);
}

void Display::print(const char str[])
{
  write(str);
}

void Display::print(char c, int base)
{
  print((long) c, base);
}

void Display::print(unsigned char b, int base)
{
  print((unsigned long) b, base);
}

void Display::print(int n, int base)
{
  print((long) n, base);
}

void Display::print(unsigned int n, int base)
{
  print((unsigned long) n, base);
}

void Display::print(long n, int base)
{
  if (base == 0) {
    write(n);
  } else if (base == 10) {
    if (n < 0) {
      print('-');
      n = -n;
    }
    printNumber(n, 10);
  } else {
    printNumber(n, base);
  }
}

void Display::print(unsigned long n, int base)
{
  if (base == 0) write(n);
  else printNumber(n, base);
}

void Display::print(double n, int digits)
{
  printFloat(n, digits);
}

void Display::println(void)
{
  print('\r');
  print('\n');
}

void Display::println(const char c[])
{
  print(c);
  println();
}

void Display::println(char c, int base)
{
  print(c, base);
  println();
}

void Display::println(unsigned char b, int base)
{
  print(b, base);
  println();
}

void Display::println(int n, int base)
{
  print(n, base);
  println();
}

void Display::println(unsigned int n, int base)
{
  print(n, base);
  println();
}

void Display::println(long n, int base)
{
  print(n, base);
  println();
}

void Display::println(unsigned long n, int base)
{
  print(n, base);
  println();
}

void Display::println(double n, int digits)
{
  print(n, digits);
  println();
}

void Display::set_cursor(int16_t x, int16_t y) {
	cursorX = x;
	cursorY = y;
}

void Display::print(uint8_t x, uint8_t y, const char str[]) {
	cursorX = x;
	cursorY = y;
	write(str);

}
void Display::print(uint8_t x, uint8_t y, char c, int base) {
	cursorX = x;
	cursorY = y;
	print((long) c, base);
}
void Display::print(uint8_t x, uint8_t y, unsigned char b, int base) {
	cursorX = x;
	cursorY = y;
	print((unsigned long) b, base);
}
void Display::print(uint8_t x, uint8_t y, int n, int base) {
	cursorX = x;
	cursorY = y;
	print((long) n, base);
}
void Display::print(uint8_t x, uint8_t y, unsigned int n, int base) {
	cursorX = x;
	cursorY = y;
	print((unsigned long) n, base);
}
void Display::print(uint8_t x, uint8_t y, long n, int base) {
	cursorX = x;
	cursorY = y;
	print(n,base);
}
void Display::print(uint8_t x, uint8_t y, unsigned long n, int base) {
	cursorX = x;
	cursorY = y;
	print(n,base);
}
void Display::print(uint8_t x, uint8_t y, double n, int digits) {
	cursorX = x;
	cursorY = y;
	print(n,digits);
}

void Display::println(uint8_t x, uint8_t y, const char c[])
{
	cursorX = x;
	cursorY = y;
	print(c);
	println();
}

void Display::println(uint8_t x, uint8_t y, char c, int base)
{
	cursorX = x;
	cursorY = y;
	print(c, base);
	println();
}

void Display::println(uint8_t x, uint8_t y, unsigned char b, int base)
{
	cursorX = x;
	cursorY = y;
	print(b, base);
	println();
}

void Display::println(uint8_t x, uint8_t y, int n, int base)
{
	cursorX = x;
	cursorY = y;
	print(n, base);
	println();
}

void Display::println(uint8_t x, uint8_t y, unsigned int n, int base)
{
	cursorX = x;
	cursorY = y;
	print(n, base);
	println();
}

void Display::println(uint8_t x, uint8_t y, long n, int base)
{
	cursorX = x;
	cursorY = y;
	print(n, base);
	println();
}

void Display::println(uint8_t x, uint8_t y, unsigned long n, int base)
{
	cursorX = x;
	cursorY = y;
	print(n, base);
	println();
}

void Display::println(uint8_t x, uint8_t y, double n, int digits)
{
	cursorX = x;
	cursorY = y;
	print(n, digits);
	println();
}

void Display::printNumber(unsigned long n, uint8_t base)
{
  unsigned char buf[8 * sizeof(long)]; // Assumes 8-bit chars.
  unsigned long i = 0;

  if (n == 0) {
    print('0');
    return;
  }

  while (n > 0) {
    buf[i++] = n % base;
    n /= base;
  }

  for (; i > 0; i--)
    print((char) (buf[i - 1] < 10 ?
      '0' + buf[i - 1] :
      'A' + buf[i - 1] - 10));
}

void Display::printFloat(double number, uint8_t digits)
{
  // Handle negative numbers
  if (number < 0.0)
  {
     print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    print(".");

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    print(toPrint);
    remainder -= toPrint;
  }
}

void Display::lcdRefresh(const unsigned char* scr, bool useDirectDrawMode) {
    if (useDirectDrawMode)
        return;
#if (PROJ_SCREENMODE != MODE_NOBUFFER) && !defined(POK_SIM)
    lcdPrepareRefresh();
#endif
#if PROJ_SCREENMODE == TASMODE
    lcdRefreshTASMode(paletteptr);
    #ifdef POK_SIM
    simulator.refreshDisplay();
    #endif
#endif

#if PROJ_SCREENMODE == MODE_HI_4COLOR
    lcdRefreshMode1(scr, 0, 0, 220, 176, paletteptr);
#endif

#if PROJ_SCREENMODE == MODE13
    lcdRefreshMode13(scr, paletteptr, palOffset);
#endif

#if PROJ_SCREENMODE == MODE15
    lcdRefreshMode15(scr, paletteptr);
#endif

#if PROJ_SCREENMODE == MODE16
    lcdRefreshMode16(scr, paletteptr);
#endif

#if PROJ_SCREENMODE == MIXMODE
    lcdRefreshMixMode(scr, paletteptr, scanType);
#endif

#if PROJ_SCREENMODE == MODE64
    lcdRefreshMode64(scr, paletteptr);
#endif

#if PROJ_SCREENMODE == MODE_FAST_16COLOR
    lcdRefreshMode2((uint8_t*)scr, paletteptr);
#endif

}

void Display::setFrameBufferTo(uint8_t* sb) {
    m_scrbuf = sb;
};



/** Eof */
