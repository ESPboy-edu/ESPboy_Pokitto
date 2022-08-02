#ifndef POKITTOLIBEXTENSIONS_H
#define POKITTOLIBEXTENSIONS_H

#include <cstdint>

namespace Pokitto {

    class DisplayExtensions {

    public:

        static void drawTile(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t* tile);

        static void fillRect(int x, int y, int w, int h, uint8_t color);

        static void drawBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int transparent_color = -1, bool flip = false);

    };
}

#endif // POKITTOLIBEXTENSIONS_H
