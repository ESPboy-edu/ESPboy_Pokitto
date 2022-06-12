#pragma once

#include "Constants.h"
#include "Enums.h"

struct Point {
    int16_t x;
    int16_t y;
};

struct Rect {
    int16_t x;
    int16_t y;
    uint8_t width;
    uint8_t height;
};

struct Slot {

    char seeds[7];
    uint16_t score;

    void reset() {
        this->seeds[0] = 0;
        this->seeds[1] = 0;
        this->seeds[2] = 0;
        this->seeds[3] = 0;
        this->seeds[4] = 0;
        this->seeds[5] = 0;
        this->seeds[6] = 0;
        this->score = 0;
    }

};

struct MemoryGameVars {

    uint8_t runes[18];
    uint8_t spinIndex[18];
    MemoryGameStatus status[18]; 

    uint8_t selections[2];
    uint8_t flashCounter = 0;
    uint8_t moves = 3;
    
    Point cursor = { 0, 0 };

    void reset() {

        for (uint8_t i = 0; i < 18; i++) {

            this->runes[i] = 255;
            this->spinIndex[i] = 0;
            this->status[i] = MemoryGameStatus::Hide;

        }

        for (uint8_t i = 0; i < 18; i++) {

            while (true) {

                uint8_t j = random(0, 18);

                if (this->runes[j] == 255) {
                    this->runes[j] = i < 12 ? i % 6 : (i - 12) % 3;
                    break;
                }

            }

        }

        this->cursor.x = 0;
        this->cursor.y = 0;

        this->selections[0] = 255;
        this->selections[1] = 255;

        this->moves = 3;

    }


    void decSpinIndex() {

        for (uint8_t i = 0; i < 18; i++) {
                
            if (this->spinIndex[i] > 0) {

                this->spinIndex[i]--;

                if (this->spinIndex[i] == 0) {

                    this->status[i] = MemoryGameStatus::Hide;
                }
                else if (this->spinIndex[i] == 8) {

                    this->status[i] = MemoryGameStatus::Show;
                    this->spinIndex[i] = 0;
                } 
                
            }

        }

        if (this->flashCounter > 0) {
            
            this->flashCounter--;

            if (this->flashCounter == 0) {

                if (this->runes[this->selections[0]] == this->runes[this->selections[1]]) {

                    this->status[this->selections[0]] = MemoryGameStatus::Delete;
                    this->status[this->selections[1]] = MemoryGameStatus::Delete;

                    for (uint8_t i = 0; i < 18; i++) {

                        if (this->status[i] != MemoryGameStatus::Delete) {

                            this->cursor.x = i % 6;
                            this->cursor.y = i / 6;
                            break;

                        }

                    }
                    
                }
                else {

                    this->spinIndex[this->selections[0]] = 8;
                    this->spinIndex[this->selections[1]] = 8;
                    this->status[this->selections[0]] = MemoryGameStatus::Hide;
                    this->status[this->selections[1]] = MemoryGameStatus::Hide;
                    this->moves--;

                }

                this->selections[0] = 255;
                this->selections[1] = 255;

            }

        }
        
    }

    bool isGameOver() {

        if (this->moves == 0) return true;
        
        for (uint8_t i = 0; i < 18; i++) {

            if (this->status[i] != MemoryGameStatus::Delete) {

                return false;

            }

        }

        return true;

    }


    bool isTileSpinning() {
        
        for (uint8_t i = 0; i < 18; i++) {

            if (this->spinIndex[i] > 0) {

                return true;

            }

        }

        return false;

    }

};

struct PlayerSelectVars {

    uint8_t index = 0;
    uint8_t counter = 0;
    int8_t vy = 0;
    uint8_t y = 0;

    uint8_t maleIdle = 0;
    uint8_t femaleIdle = 0;

    void reset(Sex sex) {

        this->index = sex == Sex::Male ? 0 : 1;
        this->counter = 0;
        this->maleIdle = 2;
        this->femaleIdle = 0;

    }

};

struct SplashScreenVars {

    uint8_t counter = 0;

};

struct TitleScreenVars {

    TitleScreenMode index = TitleScreenMode::Play;

    void reset() {

        this->index = TitleScreenMode::Play;

    }

};

struct IntroTextVars {

    uint8_t panel = 0;
    uint8_t index = 0;
    bool skipTypewriter = false;

    void reset() {

        this->panel = 0;
        this->index = 0;
        this->skipTypewriter = false;

    }

};

struct HighScoreVars {

    char seeds[5];
    uint16_t score;
    uint8_t index = 0;
    uint8_t slot = Constants::No_Slot;
    uint8_t resetCounter = 0;
    uint8_t spinIndex;
    uint8_t spinCountdown;

    void reset() {

        this->index = 0;
        this->resetCounter = 0;
        this->slot = Constants::No_Slot;
        this->spinCountdown = 100;

    }

    void decSpinIndex() {

        if (this->spinIndex > 0) {

            this->spinIndex--;
            
        }

        this->spinCountdown--;
        
    }

};

struct SeedVars {

    uint8_t seed[5];
    uint8_t index;
    uint8_t spinIndex;
    uint8_t arrowUp;
    uint8_t arrowDown;

    void incValue() {

        if (this->seed[this->index] == 5) {

            this->seed[this->index] = 0;
            
        }
        else {

            this->seed[this->index]++;

        }

        this->spinIndex = 17;
        
    }

    void decValue() {

        if (this->seed[this->index] == 0) {

            this->seed[this->index] = 5;
            
        }
        else {

            this->seed[this->index]--;

        }

        this->spinIndex = 17;
        
    }

    bool incIndex() {

        if (this->index < 4) {

            this->index++;
            return true;

        }

        return false;
        
    }

    bool decIndex() {

        if (this->index > 0) {

            this->index--;
            return true;
            
        }

        return false;
        
    }

    void decSpinIndex() {

        if (this->spinIndex > 0) {

            this->spinIndex--;
            
        }
        
    }

    void reset() {

        this->arrowDown = 0;
        this->arrowUp = 0;
        this->index = 0;
        this->spinIndex = 0;
        
    }

    uint16_t getSeedValue() {

        return (this->seed[0] * 1296 + 
                this->seed[1] * 216 +
                this->seed[2] * 36 +
                this->seed[3] * 6 +
                this->seed[4]) + 1;
               
    }

};