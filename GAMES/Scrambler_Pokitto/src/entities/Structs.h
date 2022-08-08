#pragma once

#include "../utils/Enums.h"
#include "../utils/Utils.h"


struct Scenery {

    int8_t top_Inc;
    int8_t bot_Inc;
    uint8_t top_Counter;
    uint8_t bot_Counter;
    uint16_t top[220];
    uint16_t bot[220];
    uint8_t rand;
    uint8_t countdown;
    
    void reset() {

        for (uint8_t i = 0; i < 220; i++) {

            this->top[i] = 15880;
            this->bot[i] = 240;
            
        }

        this->top_Counter = 1;
        this->bot_Counter = 1;
        this->top_Inc = 0;
        this->bot_Inc = 0;
        this->countdown = 0;

    }

};


struct SplashScreenVariables {

    uint8_t counter = 0;
    uint8_t buttonCounter = 20;

};


struct TitleScreenVariables {

    //                         S   C   R   A   M    B    L    E    R
    const uint8_t charsX[9] = {0, 20, 42, 60, 84, 109, 128, 142, 161 };
    const uint8_t charsIdx[9] = { 11, 2, 10, 0, 8, 1, 7, 3, 10 };

    int8_t counter = -3;
    uint8_t scenarioCounter = 0;
    int8_t charsY[9];
    uint8_t charsYCount[9];

    void incLetters() {

        for (uint8_t i = 0; i < 9; i++) {

            if (this->charsYCount[i] < 55) this->charsYCount[i]++;
            this->charsY[i] = Pathways::TitleSeq[this->charsYCount[i]];

        }

    }

    void reset() {

        this->counter = -3;
        this->scenarioCounter = 0;
        
        for (uint8_t i = 0; i < 9; i++) {
            
            this->charsYCount[i] = random(0, 7);
            this->charsY[i] = Pathways::TitleSeq[this->charsYCount[i]];

        }

    }

    void setLettersToTop() {

        for (uint8_t i = 0; i < 9; i++) {

            this->charsY[i] = Pathways::TitleSeq[55];
            this->charsYCount[i] = 55;

        }

    }

};


struct GameScreenVars {


    //                                     G   A   M   E   O    V    E    R
    const uint8_t gameOver_CharsX[8] =   { 0, 22, 46, 71, 94, 118, 139, 158 };
    const uint8_t gameOver_CharsIdx[8] = { 4,  0,  8,  3,  9,  12,   3,  10 };

    //                                        S   T   A   G   E
    const uint8_t stageCompT_CharsX[5] =   { 0,  19, 18, 24, 22 };
    const uint8_t stageCompT_CharsIdx[5] = { 11, 13,  0,  4,  3 };
    //                                        C  O   M   P   L   E   T   E 
    const uint8_t stageCompB_CharsX[8] =   { 0, 22, 24, 26, 18, 14, 20, 20 };
    const uint8_t stageCompB_CharsIdx[8] = { 2,  9,  8, 14,  7,  3, 13,  3 };

    //                                        S   T   A   R   T
    const uint8_t startGameT_CharsX[5] =   { 0,  16, 14, 22, 15 };
    const uint8_t startGameT_CharsIdx[5] = { 11, 13,  0, 10, 13 };
    //                                        S   C   R   A   M   B   L   I   N   G 
    const uint8_t startGameB_CharsX[10] =  {  0, 20, 22, 18, 24, 25, 19, 14,  6, 19, };
    const uint8_t startGameB_CharsIdx[10] ={ 11,  2, 10,  0,  8,  1,  7,  6, 15,  4 };

    int8_t gameOver_Counter = -3;
    int8_t gameOver_CharsY[8];
    uint8_t gameOver_CharsYCount[8];

    int16_t stageCompT = -142;
    int16_t stageLineCounter = -3;

    uint8_t clearScores = 0;
    uint32_t score = 0;
    int16_t viewY = 15980;
    uint32_t distance = 0;
    uint8_t countdown = 0;

    uint8_t stage = 1;
    uint8_t stageCount = 31;
    uint16_t stageTransition = 0;

    ExplosionColor explosionColor = ExplosionColor::Blue;
    Scenery scenery;

    ExplosionColor getColor() {

        switch (this->explosionColor) {

            case ExplosionColor::Blue:
                this->explosionColor = ExplosionColor::Red;
                break;

            case ExplosionColor::Red:
                this->explosionColor = ExplosionColor::Blue;
                break;
                
        }

        return this->explosionColor;

    }

    void reset(bool startOfGame) {

        this->clearScores = 0;
        this->viewY = 15980;
        this->distance = 0;
        this->countdown = (32 * 4) - 1;

        this->stageCount = 31;
        this->scenery.reset();

        if (startOfGame) {
    
            this->stage = 1;
            this->score = 0;

        }


        // Game Over sequence ..

        this->gameOver_Counter = -3;
        
        for (uint8_t i = 0; i < 8; i++) {
            
            this->gameOver_CharsYCount[i] = random(0, 7);
            this->gameOver_CharsY[i] = Pathways::TitleSeq[this->gameOver_CharsYCount[i]];

        }

    }

    void incGameOverLetters() {

        for (uint8_t i = 0; i < 8; i++) {

            if (this->gameOver_CharsYCount[i] < 55) this->gameOver_CharsYCount[i]++;
            this->gameOver_CharsY[i] = Pathways::TitleSeq[this->gameOver_CharsYCount[i]];

        }

    }

    void resetAnimation(GameState gameState) {

        this->gameOver_Counter = -3;
        this->gameOver_CharsY[8];
        this->gameOver_CharsYCount[8];

        switch (gameState) {

            case GameState::Game_Start:
                this->stageCompT = -154;
                break;

            default:
                this->stageCompT = -142;
                break;

        }
        this->stageLineCounter = -3;

    }

};