#pragma once

struct SplashScreenVariables {

    uint8_t counter = 0;
    uint8_t buttonCounter = 0;

};

struct TitleScreenVars {

    int16_t counter = 0;
    uint8_t levels = 0;
    uint16_t soundCounter = 0;

    void reset(GameRotation gameRotation) {
        
        switch (gameRotation) {

            case GameRotation::Portrait:
            
                this->counter = 79;
                break;

            case GameRotation::Landscape:
            
                this->counter = 0;
                break;

        }

    }

};

struct GameOverScreenVars {

    int16_t counter = 0;
    bool newHighScore = false;
    bool flashPlayer1 = false;
    bool flashPlayer2 = false;

    void reset() {

        this->counter = 128;
        newHighScore = false;
        flashPlayer1 = false;
        flashPlayer2 = false;

    }

};

struct Rect {
   int16_t x;      
   int16_t y;      
   uint8_t width;  
   uint8_t height; 
   Rect() = default;
  
   constexpr Rect(int16_t x, int16_t y, uint8_t width, uint8_t height)
     : x(x), y(y), width(width), height(height)
   {   }
 };