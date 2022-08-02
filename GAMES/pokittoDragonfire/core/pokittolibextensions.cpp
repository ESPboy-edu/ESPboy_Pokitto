#include "pokittolibextensions.h"

#include <cstring>
#include <algorithm>

#include "PokittoDisplay.h"

namespace Pokitto {

    void DisplayExtensions::drawTile(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t* tile) {
        if (y<-h || y>Display::height) return; //invisible
        if (x<-w || x>Display::width) return;  //invisible
        int screenh = std::min((int)h, Display::height- y);
        int screenw = std::min((int)w, Display::width - x);
        int screenx = x;
        int offsetx = 0;
        if (x < 0) {
            screenx = 0;
            offsetx = -x;
            screenw -= offsetx;
        }
        int screeny = y;
        int offsety = 0;
        if (y < 0) {
            screeny = 0;
            offsety = -y;
        }
        uint8_t* start = Display::getBuffer() + 110 * screeny + screenx;
        uint8_t* end = Display::getBuffer() + 110 * (screeny + screenh) + screenx;
        uint8_t* tloc = const_cast<uint8_t*>(tile) + offsetx + offsety * w;
        for (uint8_t* loc = start; loc != end;  loc += 110) {
          std::memcpy(loc, tloc, screenw);
          tloc += w;
        }
    }

    void DisplayExtensions::fillRect(int x, int y, int w, int h, uint8_t color) {
        if (y<-h || y>Display::height) return; //invisible
        if (x<-w || x>Display::width) return;  //invisible
        int screenh = std::min((int)h, Display::height- y);
        int screenw = std::min((int)w, Display::width - x);
        int screenx = x;
        int offsetx = 0;
        if (x < 0) {
            screenx = 0;
            offsetx = -x;
            screenw -= offsetx;
        }
        int screeny = y;
        int offsety = 0;
        if (y < 0) {
            screeny = 0;
            offsety = -y;
        }
        uint8_t* start = Display::getBuffer() + 110 * screeny + screenx;
        uint8_t* end = Display::getBuffer() + 110 * (screeny + screenh) + screenx;
        for (uint8_t* loc = start; loc != end;  loc += 110) {
          std::memset(loc, color, screenw);
        }
    }

    void DisplayExtensions::drawBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int transparent_color, bool flip)
    {
        int16_t w = *bitmap;
        int16_t h = *(bitmap + 1);
        /** visibility check */
        if (y<-h || y>Display::height) return; //invisible
        if (x<-w || x>Display::width) return;  //invisible
        bitmap = bitmap + 2;
        if (transparent_color >= 0) {
            Display::invisiblecolor = transparent_color;
        }
        if (flip) {
            Display::drawBitmapDataXFlipped(x, y, w, h, bitmap);
        } else {
            Display::drawBitmapData(x, y, w, h, bitmap);
        }
    }
}
