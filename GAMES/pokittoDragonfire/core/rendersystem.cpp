#include "rendersystem.h"

#include "../core/rendering/tiny4x7h.h"
#include "../core/palettes.h"

#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>

static bool initialized = false;

int RenderSystem::getLineLength(const char *line, int fontSize)
{
    int width = 0;
    for(char c : std::string(line)) {
        uint8_t index = uint8_t(c);
        if (index == 195) continue;
        if (index > 128) index += 64;
        index -= TinyUnicode5x8[2];
        const uint8_t* bitmap = TinyUnicode5x8;
        uint8_t w = *bitmap;
        uint8_t h = *(bitmap + 1);
        uint8_t hbytes=0, xtra=1;
        if (h==8 || h==16) xtra=0; //don't add if exactly on byte limit
        hbytes=(h>>3)+xtra; //GLCD fonts are arranged w+1 times h/8 bytes
        //bitmap = bitmap + 3 + index * h * ((w>>3)+xtra); //add an offset to the pointer (fonts !)
        bitmap = bitmap + 4 + index * (w * hbytes + 1); //add an offset to the pointer (fonts !)
        int8_t numBytes = *bitmap++; //first byte of char is the width in bytes

        int adjustCharStep = index == 0 ? 0 : 1;
        width += (numBytes+adjustCharStep)*fontSize;
    }
    return width;
}

#include "Pokitto.h"
#include "../core/pokittolibextensions.h"
#include "../core/pokittolibextensions.cpp"

Pokitto::Core game;

uint32_t RenderSystem::getTimeMs()
{
    return initialized ? game.getTime() : 0;
}

void RenderSystem::setPalette(const uint16_t *ptr)
{
    game.display.load565Palette(ptr);
}

void RenderSystem::initialize()
{
    game.begin();
    game.display.textWrap = false;
    game.display.persistence = true;
    game.display.load565Palette(default_palette);
    game.display.setInvisibleColor(0);
    game.display.setColor(3, 0);
    game.display.font = TinyUnicode5x8;
    initialized = true;
}

bool RenderSystem::running()
{
    return game.isRunning();
}

bool RenderSystem::update()
{
    return game.update();
}

void RenderSystem::pixel(int x, int y, uint8_t color)
{
    game.display.drawPixel(x, y, color);
}

void RenderSystem::sprite(int x, int y, const uint8_t * sprite, int transparent_color, bool flip) {
    if (flip || transparent_color >= 0) {
        Pokitto::DisplayExtensions::drawBitmap(x, y, sprite, transparent_color, flip);
    } else {
        Pokitto::DisplayExtensions::drawTile(x, y, sprite[0], sprite[1], sprite + 2);
    }
}

void RenderSystem::drawLine(int x0, int y0, int x1, int y1, uint8_t color)
{
    game.display.setColor(color);
    game.display.drawLine(x0, y0, x1, y1);
}

void RenderSystem::drawRect(int x0, int y0, int w, int h, uint8_t color)
{
    game.display.setColor(color);
    game.display.fillRect(x0, y0, w, std::max(h-1,std::min(h,1))); // PokittoLib implementation is wrong
}

void RenderSystem::drawCircle(int x, int y, int r, int color)
{
    game.display.setColor(color);
    game.display.drawCircle(x,y,r);
}

void RenderSystem::clear(uint8_t idx) {
    game.display.bgcolor = idx;
    if (game.display.persistence) {
        uint8_t * m_buffer = game.display.getBuffer();
        std::fill(m_buffer, m_buffer + 110 * 176, idx);
    }
}

int printChar(int x, int y, uint8_t index, uint8_t color, uint8_t fontSize) {
    if (index == 195) return x;
    if (index > 128) index += 64;
    index -= TinyUnicode5x8Slim[2];
    const uint8_t* bitmap = TinyUnicode5x8;
    uint8_t w = *bitmap;
    uint8_t h = *(bitmap + 1);
    uint8_t hbytes=0, xtra=1;
    if (h==8 || h==16) xtra=0; //don't add if exactly on byte limit
    hbytes=(h>>3)+xtra; //GLCD fonts are arranged w+1 times h/8 bytes
    //bitmap = bitmap + 3 + index * h * ((w>>3)+xtra); //add an offset to the pointer (fonts !)
    bitmap = bitmap + 4 + index * (w * hbytes + 1); //add an offset to the pointer (fonts !)
    //int8_t i, j, byteNum, bitNum, byteWidth = (w + 7) >> 3;
    int8_t i, j, numBytes;
    numBytes = *bitmap++; //first byte of char is the width in bytes
    // GLCD fonts are arranged LSB = topmost pixel of char, so its easy to just shift through the column
    uint16_t bitcolumn; //16 bits for 2x8 bit high characters

    for (i = 0; i < numBytes; i++) {
            bitcolumn = *bitmap++;
            if (hbytes == 2) bitcolumn |= (*bitmap++)<<8; // add second byte for 16 bit high fonts
            for (j = 0; j < h; j++) {
                if (bitcolumn&0x1) {
                    if (fontSize==2) {
                        RenderSystem::pixel(x + (i<<1)  , y + (j<<1),color);
                        RenderSystem::pixel(x + (i<<1)+1, y + (j<<1),color);
                        RenderSystem::pixel(x + (i<<1)  , y + (j<<1)+1,color);
                        RenderSystem::pixel(x + (i<<1)+1, y + (j<<1)+1,color);
                    } else {
                        RenderSystem::pixel(x + i, y + j,color);
                    }

                }
                bitcolumn>>=1;
            }
    }
    int adjustCharStep = index == 0 ? 0 : 1;
    return x + (numBytes+adjustCharStep)*fontSize; // for character stepping
}

void RenderSystem::print(int x, int y, const char *line, uint8_t color, uint8_t size, uint8_t)
{
    std::string l(line);
    for (auto c : l) {
        x = printChar(x, y, c, color, size);
    }
}
