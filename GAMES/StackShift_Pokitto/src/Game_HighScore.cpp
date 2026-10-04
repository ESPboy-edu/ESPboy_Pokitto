#include "Game.h"
#include "images/Images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

constexpr const static uint8_t UPLOAD_DELAY = 16;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::doHighScore_Init() {
	
    this->cursor = 0;
    this->gameState = GameState::HighScore;
    uint32_t index = cookie->getScoreIndex();

    for (uint8_t x = 0; x < 16; x++) {

        uint8_t rnd = random(0, 13);

        for (uint8_t y = 0; y < 16; y++) {

            if (y >= rnd && y <= rnd + 2) {
                this->scoreGameBoard[x][y] = static_cast<uint8_t>(static_cast<uint8_t>(this->getRandomBoardType(this->level, 0)) << 4) + random(4);
            }
            else {
                this->scoreGameBoard[x][y] = static_cast<uint8_t>(BoardType::None) << 4;
            }
            
        }

    }

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::doHighScore() {
	
    bool flash = Utils::getFrameCountHalf(48);
    uint32_t index = cookie->getScoreIndex();

    const uint8_t frameCount[16] = {4, 5, 7, 4, 6,   5, 7, 6, 5, 6,   4, 5, 6, 4, 5,   6,  };

    for (uint8_t x = 0; x < 16; x++) {

        BoardType bt = static_cast<BoardType>(this->scoreGameBoard[x][15] >> 4);
        uint8_t temp = this->scoreGameBoard[x][15];

        if (Utils::isFrameCount(frameCount[x])) {

            for (uint8_t y = 15; y > 0; y--) {

                this->scoreGameBoard[x][y] = (this->scoreGameBoard[x][y - 1] & 0xf0) + (((this->scoreGameBoard[x][y - 1] & 0x0f) + 1) % 4);
                
            }

            if (bt != BoardType::None) {
                this->scoreGameBoard[x][0] = (static_cast<uint8_t>(this->getRandomBoardType(this->level, 0)) << 4) + random(4);
            }
            else {
                this->scoreGameBoard[x][0] = temp;
            }

        }

    }



	// Handle other input ..

    if (index != NO_SCORE) {

        if (PC::buttons.pressed(BTN_LEFT) && this->cursor > 0) {
            this->cursor--;
        }

        if (PC::buttons.pressed(BTN_RIGHT) && this->cursor < 2) {
            this->cursor++;
        }

        if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 16)) {

            uint32_t val = cookie->initials[static_cast<uint8_t>(this->level)][index][this->cursor];
            val++;
            if (val > 26) val = 1;
            cookie->initials[static_cast<uint8_t>(this->level)][index][this->cursor] = val;
            
        }

        if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 16)) {

            uint32_t val = cookie->initials[static_cast<uint8_t>(this->level)][index][this->cursor];
            if (val == 0) val = 26;
            val--;
            cookie->initials[static_cast<uint8_t>(this->level)][index][this->cursor] = val;
            
        }

        if (PC::buttons.pressed(BTN_A) && cookie->initials[static_cast<uint8_t>(this->level)][index][0] != 0 && cookie->initials[static_cast<uint8_t>(this->level)][index][1] != 0 && cookie->initials[static_cast<uint8_t>(this->level)][index][2] != 0) {

            cookie->saveCookie();
            cookie->setLastScore(this->level, 0);
            
        }

    }
    else {

        if (PC::buttons.pressed(BTN_LEFT) && this->level == Level::Hard) {
            this->level = Level::Easy;
        }

        if (PC::buttons.pressed(BTN_RIGHT) && this->level == Level::Easy) {
            this->level = Level::Hard;
        }

        if (PC::buttons.pressed(BTN_A)) {
        	gameState = GameState::Title;
        }
   
    }


    // ----------------------------------------------------------------------------
    //  Render the state .. 


    for (uint8_t x = 0; x < 16; x++) {

        for (uint8_t y = 0; y < 16; y++) {

            BoardType bt = static_cast<BoardType>(this->scoreGameBoard[x][y] >> 4);

            if (bt != BoardType::None) {

                uint8_t frame = this->scoreGameBoard[x][y] & 0x0F;

                PD::drawBitmap((x * (PART_SIZE + 3)), y * PART_SIZE, Images::GreySymbols[this->getFrameNumber(bt)][frame]);

            }
            
        }

    }



    PD::setColor(6, 0);
    PD::drawBitmap(24, 10, Images::HighScore);


    PD::setCursor(92, 89);
    PD::drawLine(40, 93, 86, 93);
    PD::drawLine(132, 93, 178, 93);

    if (this->level == Level::Easy) {
        PD::print("EASY");
    }
    else {
        PD::print("HARD");
    }

    PD::setColor(7, 0);


    // Has a new High Score been set ?
        
    if (index != NO_SCORE) {
    
        uint8_t digits[5] = {};
        Utils::extractDigits(digits, cookie->lastScore);


        // Render Highlights on either side of the entry ..
        
        PD::drawBitmap(48, 105 + (index * 12), Images::HS_Highlight);
        PD::drawBitmap(170, 105 + (index * 12), Images::HS_Highlight);


        // Render score and name entry ..

        for (uint32_t x = 0; x < 3; x++) {
            
            if ((this->cursor == x && flash) || this->cursor != x) {
            
                if (this->cookie->initials[static_cast<uint8_t>(this->level)][index][x] > 0) {
                    PD::setCursor(60 + (x * 10), 105 + (index * 12));
                    PD::print(static_cast<char>(this->cookie->initials[static_cast<uint8_t>(this->level)][index][x] + 64));
                }
                else {
                    PD::fillRect(60 + (x * 10), 105 + (index * 12), 8, 7);
                }
                
            }

        }
        
        for (uint8_t j = 5; j > 0; --j) {
        
            PD::setCursor(163 - (j * 10), 105 + (index * 12));
            PD::print(digits[j - 1], 10);

        }

    }
    else {
          
        if (Utils::isFrameCount(24)) this->launchHighScoreParticles();
        this->renderParticles();

    }
        


    // Render remaining scores ..
    
    PD::setColor(6, 0);
    for (uint32_t y = 0; y < 5; y++) {
    
        //Score

        uint8_t digits[5] = {};
        Utils::extractDigits(digits, cookie->score[static_cast<uint8_t>(this->level)][y]);
        
        if (index != y) {

            for (uint32_t x = 0; x < 3; x++) {
                
                PD::setCursor(60 + (x * 10), 105 + (y * 12));
                PD::print(static_cast<char>(cookie->initials[static_cast<uint8_t>(this->level)][y][x] + 64));

            }

            for (uint8_t j = 5; j > 0; --j) {
            
                PD::setCursor(163 - (j * 10), 105 + (y * 12));
                PD::print(digits[j - 1] , 10);
            
            }

        }
        
    }

}
