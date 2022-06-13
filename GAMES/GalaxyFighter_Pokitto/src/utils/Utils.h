#pragma once

#include "Pokitto.h"
#include "Constants.h"
#include "Enums.h"
#include "sfx.h"
#include "../../libs/LibAudio/LibAudio.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
//using PS = Pokitto::Sound;


struct Rect {
    int16_t x;
    int16_t y;
    uint8_t width;
    uint8_t height;
};

namespace Utils {

    static inline bool sfxOver() {

  //      return ( PS::sfxDataPtr >= PS::sfxEndPtr );

    return(1);//RS
    }
    
    static inline void printffloat(float d) {
        
        int a = static_cast<int>(d);
        int b = static_cast<int>((d * 1000)) % 1000;
        
        printf("%i.%i", a, b);
        
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
        
        for (uint32_t y = sy; y <= ey; y = y + 2) {
            
            PD::drawPixel(x, y);
        }
    
    }
    
    static inline void drawDottedRow(uint8_t sx, uint8_t ex, uint8_t y) {
        
        for (uint32_t x = sx; x <= ex; x = x + 2) {
            
            PD::drawPixel(x, y);
        }
    
    }
    
    
    // ----------------------------------------------------------------------------
    //  A better absolute as it uses less memory than the standard one .. 
    //
    template<typename T> T absT(const T & v) {
      
      return (v < 0) ? -v : v;
    
    }
    
    
    // ---------------------------------------------------------------------------------
    // Extract individual digits of a uint16_t
    //
    template< size_t size >
    void extractDigits(uint8_t (&buffer)[size], uint16_t value) {
    
      for (uint32_t i = 0; i < size; ++i) {
        buffer[i] = value % 10;
        value /= 10;
      }
    
    }
    
    
    // ---------------------------------------------------------------------------------
    // Extract individual digits of a uint32_t
    //
    template< size_t size >
    void extractDigits(uint8_t (&buffer)[size], uint32_t value) {
    
      for(uint8_t i = 0; i < size; ++i) {
        buffer[i] = value % 10;
        value /= 10;
      }
    
    }
    

    static void playPlay(const uint8_t *arrfx, const uint16_t len) {
      static uint8_t chan=1;
      chan++;
      if(chan>MAXCHANNELS-1) chan=1;

      switch(chan){
        case 0: Audio::SFX8Source::play<0>(arrfx, len); break;
        case 1: Audio::SFX8Source::play<1>(arrfx, len); break;
        case 2: Audio::SFX8Source::play<2>(arrfx, len); break;
        case 3: Audio::SFX8Source::play<3>(arrfx, len); break;
        case 4: Audio::SFX8Source::play<4>(arrfx, len); break;
      };
    };



    // ----------------------------------------------------------------------------
    //  Start a stream from the SD card .. 
    //

    static void playMusicStream(SDStream stream) {

       // #ifdef INCLUDE_SOUND_FROM_SD
        switch (stream) {

            case SDStream::StageIntro:
                Audio::play<0>(sfx1); 
                //PS::playMusicStream("music/galaxy1.raw", 0);
                break;

            case SDStream::ScoreTop:
                Audio::play<0>(sfx6); 
                //PS::playMusicStream("music/galaxy2.raw", 0);
                break;

            case SDStream::ScoreOther:
                Audio::play<0>(sfx5); 
                //PS::playMusicStream("music/galaxy3.raw", 0);
                break;

            case SDStream::ChallengeStart:
                Audio::play<0>(sfx4); 
                //PS::playMusicStream("music/galaxy4.raw", 0);
                break;

            case SDStream::ChallengeFinish:
                Audio::play<0>(sfx5); 
                //PS::playMusicStream("music/galaxy5.raw", 0);
                break;

            case SDStream::ChallengePerfect:
                Audio::play<0>(sfx6); 
                //PS::playMusicStream("music/galaxy6.raw", 0);
                break;

            case SDStream::FighterCaptured:
                Audio::play<0>(sfx7); 
                //PS::playMusicStream("music/galaxy7.raw", 0);
                break;

            case SDStream::FighterRescued:
                Audio::play<0>(sfx5); 
                //PS::playMusicStream("music/galaxy5.raw", 0);
                break;

            case SDStream::FighterDestroyed:
                Audio::play<0>(sfx6); 
                //PS::playMusicStream("music/galaxy6.raw", 0);
                break;

            case SDStream::Explosion:
                Audio::play<0>(sfxA); 
                //PS::playMusicStream("music/galaxyA.raw", 0);
                break;


        }
      //  #endif

    }
}
