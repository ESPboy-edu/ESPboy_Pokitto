#ifndef __SYSTEM
#define __SYSTEM

#include <cstdint>

struct RenderSystem
{

public:
    static void initialize();
    static uint32_t getTimeMs();
    static bool running();
    static bool update();
    static void setPalette(const uint16_t * ptr);
    static void clear(uint8_t idx);

    static int getLineLength(const char * line, int fontSize = 1);
    static void print(int x, int y, const char * line, uint8_t color, uint8_t size = 1, uint8_t bgcol = 0);

    static void sprite(int x, int y, const uint8_t * sprite, int transparent_color = -1, bool flip = false);

    static void pixel(int x, int y, uint8_t color);
    static void drawLine(int x0, int y0, int x1, int y1, uint8_t color);
    static void drawRect(int x0, int y0, int w, int h, uint8_t color);
    static void drawCircle(int x, int y, int r, int color);
};

#endif
