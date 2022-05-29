#pragma once

#include "Constants.h"

    
// uint8_t fadeWidth;

 struct Rect {
     
    int16_t x;      
    int16_t y;      
    uint8_t width;  
    uint8_t height; 
    Rect() = default;

    constexpr Rect(int16_t x, int16_t y, uint8_t width, uint8_t height) : x(x), y(y), width(width), height(height) { }

 };


// Extract individual digits of a uint8_t -------------------------------------

template< size_t size > void extractDigits(uint8_t (&buffer)[size], uint8_t value) {

    for(uint8_t i = 0; i < size; ++i) {
        buffer[i] = value % 10;
        value /= 10;
    }

}

// Extract individual digits of a uint16_t
template< size_t size > void extractDigits(uint8_t (&buffer)[size], uint16_t value) {

    for(uint8_t i = 0; i < size; ++i) {
        buffer[i] = value % 10;
        value /= 10;
    }
    
}



// ----------------------------------------------------------------------------
//    A better absolute as it uses less memory than the standard one .. 
//
template<typename T> T absT(const T & v) {
    
    return (v < 0) ? -v : v;

}


// ----------------------------------------------------------------------------
//    Return the absolute difference between values .. 
//
template<typename T> T diffT(const T & v, const T & u) {
    
    return (v < u) ? u - v : v - u;

}





