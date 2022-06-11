#include "Pokitto.h"
#include "Game.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


                              // A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z  0, 1  2  3  4  5  6  7  8  9 
PROGMEM const uint8_t charWidths[36] = { 4, 4, 4, 4, 4, 4, 5, 5, 1, 4, 5, 4, 6, 5, 4, 4, 5, 4, 4, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };

void Game::highScore() {


    // Handle player actions ..

    if (this->highScoreVariables.entryIdx == NO_HIGH_SCORE_EDIT) {

        if (PC::buttons.pressed(BTN_A)) {

            this->gameState = GameState::MainMenu; 
            this->titleScreenVars.mode = TitleScreenMode::SelectOption;
            this->map.setLevel(0); 
            this->points = 0; 

        }

    }
    else {

        if (PC::buttons.pressed(BTN_LEFT) && this->highScoreVariables.charIdx > 0) {
            this->highScoreVariables.charIdx--;
        }

        if (PC::buttons.pressed(BTN_RIGHT) && this->highScoreVariables.charIdx < 2) {
            this->highScoreVariables.charIdx++;
        }
            
        if (PC::buttons.pressed(BTN_UP) || (PC::buttons.repeat(BTN_UP, 1) && PC::frameCount % 4 == 0)) {

            switch (this->cookieHighScore->score_Char[this->highScoreVariables.entryIdx][this->highScoreVariables.charIdx]) {

                case 'A' ... 'Y':
                case '0' ... '8':
                    this->cookieHighScore->score_Char[this->highScoreVariables.entryIdx][this->highScoreVariables.charIdx] = this->cookieHighScore->score_Char[this->highScoreVariables.entryIdx][this->highScoreVariables.charIdx] + 1;
                    break;

                case 'Z':
                    this->cookieHighScore->score_Char[this->highScoreVariables.entryIdx][this->highScoreVariables.charIdx] = '0';
                    break;

                case '9':
                    this->cookieHighScore->score_Char[this->highScoreVariables.entryIdx][this->highScoreVariables.charIdx] = 'A';
                    break;

            }

        }

        if (PC::buttons.pressed(BTN_DOWN) || (PC::buttons.repeat(BTN_DOWN, 1) && PC::frameCount % 4 == 0)) {

            switch (this->cookieHighScore->score_Char[this->highScoreVariables.entryIdx][this->highScoreVariables.charIdx]) {

                case 'B' ... 'Z':
                case '1' ... '9':
                    this->cookieHighScore->score_Char[this->highScoreVariables.entryIdx][this->highScoreVariables.charIdx] = this->cookieHighScore->score_Char[this->highScoreVariables.entryIdx][this->highScoreVariables.charIdx] - 1;
                    break;

                case 'A':
                    this->cookieHighScore->score_Char[this->highScoreVariables.entryIdx][this->highScoreVariables.charIdx] = '9';
                    break;

                case '0':
                    this->cookieHighScore->score_Char[this->highScoreVariables.entryIdx][this->highScoreVariables.charIdx] = 'Z';
                    break;

            }

        }

        if (PC::buttons.pressed(BTN_A)) {

            this->cookieHighScore->scoreHell[this->highScoreVariables.entryIdx] = this->cookieSaveGame->gameC;
            this->cookieHighScore->saveCookie();
            this->highScoreVariables.entryIdx = NO_HIGH_SCORE_EDIT;

        }

    }


    // Render screen ..

    this->renderEnvironment(!this->map.isBossLevel() && !this->map.isAltarLevel(), 0, 0);
    this->renderHud();

    PD::fillScreen(15);
    PD::setColor(15);
    PD::drawBitmap(0, 0, Images::LevelSplash_UpperLeft);
    PD::drawBitmap(0, 16, Images::LevelSplash_Left);
    PD::drawBitmap(10, 2, Images::LevelSplash_Top);
    PD::drawBitmapXFlipped(54, 2, Images::LevelSplash_Top);
    PD::drawBitmap(100, 0, Images::LevelSplash_UpperRight);
    PD::drawBitmap(100, 16, Images::LevelSplash_Right);
    PD::drawBitmap(10, 78, Images::LevelSplash_Bottom);
    PD::setColor(4, 15);
    
    PD::setCursor(24, 21);
    PD::print("High Scores");

    for (uint8_t y = 0; y < 5; y++) {

        uint8_t charPos = 13;

        for (uint8_t x = 0; x < 3; x++) {

            uint8_t charWidth = 0;

            switch (this->cookieHighScore->score_Char[y][x]) {

                case 'A' ... 'Z':
                    charWidth = charWidths[this->cookieHighScore->score_Char[y][x] - 65];
                    break;

                case '0' ... '9':
                    charWidth = charWidths[this->cookieHighScore->score_Char[y][x] - 48 + 26];
                    break;

            }
            
            PD::setCursor(charPos, 31 + (y * 9));
            PD::print(this->cookieHighScore->score_Char[y][x]);

            if (x == this->highScoreVariables.charIdx && y == this->highScoreVariables.entryIdx && PC::frameCount % 48 < 24) {

                PD::setColor(2);//9);
                PD::drawLine(charPos, 30 + (y * 9), charPos + charWidth, 30 + (y * 9));
                PD::drawLine(charPos, 38 + (y * 9), charPos + charWidth, 38 + (y * 9));
                PD::setColor(4, 15);

            }

            charPos = charPos + charWidth + 2;
            
        }

        if (this->cookieHighScore->scoreHell[y] == true) {
            PD::drawBitmap(charPos, 32 + (y * 9), Images::Asterisk);
        }

        PD::setCursor(41, 31 + (y * 9));
        PD::print("L");
        this->printPaddedNumber(this->cookieHighScore->level[y], 2);

        PD::setCursor(70, 31 + (y * 9));
        this->printPaddedNumber(this->cookieHighScore->score[y], 4);

    }

}
