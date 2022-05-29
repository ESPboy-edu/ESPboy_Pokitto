#include "SpaceCab.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

#define HIGH_SCORE_VERT_SPACING 8
#define HIGH_SCORE_TOP 35
#define HIGH_SCORE_LETTERS_LEFT 28
#define HIGH_SCORE_NUMBERS_RIGHT 86
#define HIGH_SCORE_HORIZ_SPACING 5



// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::highScore_Init() {

    this->cursor = 0;
    this->state = GameState::HighScore;
    uint32_t index = cookie->getScoreIndex();

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::highScore() {
	
    bool flash = PC::frameCount % 48 < 24;
    uint32_t index = cookie->getScoreIndex();
    
	// Handle other input ..

    if (index != NO_SCORE) {

        if (PC::buttons.pressed(BTN_LEFT) && this->cursor > 0) {
            this->cursor--;
        }

        if (PC::buttons.pressed(BTN_RIGHT) && this->cursor < 2) {
            this->cursor++;
        }

        if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 16)) {

            uint32_t val = cookie->initials[index][this->cursor];
            val++;
            if (val > 90) val = 65;
            cookie->initials[index][this->cursor] = val;
            
        }

        if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 16)) {

            uint32_t val = cookie->initials[index][this->cursor];
            if (val == 64) val = 90;
            val--;
            cookie->initials[index][this->cursor] = val;
            
        }

        if (PC::buttons.pressed(BTN_A)) {

            if (cookie->initials[index][0] != 0 && cookie->initials[index][1] != 0 && cookie->initials[index][2] != 0) {

                cookie->saveCookie();
                cookie->setLastScore(0);

            }
            else if (this->cursor < 2 && cookie->initials[index][this->cursor] != 0 ) {
                this->cursor++;
            }
            
        }

    }
    else {

        if (PC::buttons.pressed(BTN_A)) {
        	this->state = GameState::TitleScreen_Init;
        }
   
    }


    // ----------------------------------------------------------------------------
    //  Render the state .. 

    // for (uint8_t i = 0; i < 110; i = i + 6) {

    //     PD::drawBitmap(i, 0, Images::Checkers);
    //     PD::drawBitmap(i, 82, Images::Checkers);

    // }

    scrollingBackground(true, 1, 0);
    scrollingBackground(false, 77, 1);

    PD::setColor(6, 0);
    PD::drawBitmap(19, 16, Images::HighScore);

    PD::setColor(7, 0);


    // Has a new High Score been set ?
   
    if (index != NO_SCORE) {
    
        uint8_t digits[5] = {};
        extractDigits(digits, cookie->lastScore);


        // Render Highlights on either side of the entry ..
        
        PD::drawBitmap(HIGH_SCORE_LETTERS_LEFT - 8, HIGH_SCORE_TOP + (index * HIGH_SCORE_VERT_SPACING) - 2, Images::HS_Highlight);
        PD::drawBitmap(HIGH_SCORE_NUMBERS_RIGHT + 2, HIGH_SCORE_TOP + (index * HIGH_SCORE_VERT_SPACING) - 2, Images::HS_Highlight);


        // Render score and name entry ..

        for (uint32_t x = 0; x < 3; x++) {
            
            if ((this->cursor == x && flash) || this->cursor != x) {
            
                if (this->cookie->initials[index][x] > 0) {
                    PD::setCursor(HIGH_SCORE_LETTERS_LEFT + (x * HIGH_SCORE_HORIZ_SPACING), HIGH_SCORE_TOP + (index * HIGH_SCORE_VERT_SPACING));
                    PD::print(static_cast<char>(this->cookie->initials[index][x]));
                }
                else {
                    PD::fillRect(HIGH_SCORE_LETTERS_LEFT + (x * HIGH_SCORE_HORIZ_SPACING), HIGH_SCORE_TOP + (index * HIGH_SCORE_VERT_SPACING), 8, 7);
                }
                
            }

        }
        
        for (uint8_t j = 5; j > 0; --j) {
        
            PD::setCursor(HIGH_SCORE_NUMBERS_RIGHT - (j * HIGH_SCORE_HORIZ_SPACING), HIGH_SCORE_TOP + (index * HIGH_SCORE_VERT_SPACING));
            PD::print(digits[j - 1], 10);

        }

    }
       


    // Render remaining scores ..
    
    PD::setColor(6, 0);

    for (uint32_t y = 0; y < 5; y++) {

        //Score

        uint8_t digits[5] = {};
        extractDigits(digits, cookie->score[y]);
        
        if (index != y) {

            for (uint32_t x = 0; x < 3; x++) {
                
                PD::setCursor(HIGH_SCORE_LETTERS_LEFT + (x * HIGH_SCORE_HORIZ_SPACING), HIGH_SCORE_TOP + (y * HIGH_SCORE_VERT_SPACING));
                PD::print(static_cast<char>(cookie->initials[y][x]));

            }

            for (uint8_t j = 5; j > 0; --j) {
            
                PD::setCursor(HIGH_SCORE_NUMBERS_RIGHT - (j * HIGH_SCORE_HORIZ_SPACING), HIGH_SCORE_TOP + (y * HIGH_SCORE_VERT_SPACING));
                PD::print(digits[j - 1] , 10);
            
            }

        }
        
    }

    PD::update();

}
