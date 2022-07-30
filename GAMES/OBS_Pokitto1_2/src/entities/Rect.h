#pragma once

class Rect {

    public:

        int16_t x;      
        int16_t y;      
        uint8_t width;  
        uint8_t height; 

        Rect() = default;

        constexpr Rect(int16_t x, int16_t y, uint8_t width, uint8_t height)
            : x(x), y(y), width(width), height(height)
        {   }

 };