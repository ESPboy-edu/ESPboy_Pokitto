#pragma once

#include "Pokitto.h"
#include "Enums.h"
#include "Structs.h"
// #include "../sounds/Sounds.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PS = Pokitto::Sound;

namespace Utils {

    static uint32_t hash(uint32_t &value)
    {
      value ^= (value << 13);
      value ^= (value >> 17);
      value ^= (value << 5);
      return value;
    }

    static inline bool collide(Rect rect1, Rect rect2) {
        return !(rect2.x                >= rect1.x + rect1.width  ||
                 rect2.x + rect2.width  <= rect1.x                ||
                 rect2.y                >= rect1.y + rect1.height ||
                 rect2.y + rect2.height <= rect1.y);
    }
    
    
    // This gets the length of an array at compile time
    template< typename T, size_t N > constexpr size_t ArrayLength(T (&)[N]) {
        return N;
    }
    
    
    static inline uint16_t getFrameCount() {
    
        return Pokitto::Core::frameCount;
    
    }
    
    static inline uint16_t getFrameCount(uint16_t mod) {
    
        return (Pokitto::Core::frameCount % mod);
    
    }
    
    static inline bool getFrameCountHalf(uint16_t mod) {
    
        return ((Pokitto::Core::frameCount % mod) > (mod /2));
    
    }
    
    static inline bool isFrameCount(uint16_t mod) {
    
        return ((Pokitto::Core::frameCount % mod) == 0);
    
    }
    
    static inline bool isFrameCount(uint16_t mod, uint16_t val) {
        
        return ((Pokitto::Core::frameCount % mod) == val);
    
    }
    
    
    static inline void drawDottedColumn(uint8_t x, uint8_t sy, uint8_t ey) {
        
        for (uint8_t y = sy; y <= ey; y = y + 2) {
            
            PD::drawPixel(x, y);
        }
    
    }
    
    static inline void drawDottedRow(uint8_t sx, uint8_t ex, uint8_t y) {
        
        for (uint8_t x = sx; x <= ex; x = x + 2) {
            
            PD::drawPixel(x, y);
        }
    
    }
    
    
    /* ----------------------------------------------------------------------------
     *  Return the upper 4 bits of a byte.
     */
    static uint8_t leftValue(uint8_t val) {
    
      return val >> 4; 
          
    }
    
    
    /* ----------------------------------------------------------------------------
     *  Return the lower 4 bits of a byte.
     */
    static uint8_t rightValue(uint8_t val) {
    
      return val & 0x0F; 
          
    }
    
    // ---------------------------------------------------------------------------------
    // Extract individual digits of a uint8_t
    //
    template< size_t size >
    void extractDigits(uint8_t (&buffer)[size], uint8_t value) {
    
      for (uint8_t i = 0; i < size; ++i) {
        buffer[i] = value % 10;
        value /= 10;
      }
    
    }
    
    // ---------------------------------------------------------------------------------
    // Extract individual digits of a uint16_t
    //
    template< size_t size >
    void extractDigits(uint8_t (&buffer)[size], uint16_t value) {
    
      for(uint8_t i = 0; i < size; ++i) {
        buffer[i] = value % 10;
        value /= 10;
      }
    
    }

}