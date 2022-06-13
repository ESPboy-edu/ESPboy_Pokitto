#include "TitleScreenState.h"

#include "../images/Images.h"
#include "../sounds/Sounds.h"
#include "../utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
//using PS = Pokitto::Sound;

constexpr const static uint8_t UPLOAD_DELAY = 16;




// ----------------------------------------------------------------------------
//  Initialise state ..
//
void TitleScreenState::activate() {

    this->counter = 20;
    this->stateToggle = 300;
    this->viewState = ViewState::Normal;
	this->initStarField();
    PD::invisiblecolor = 4;
    
}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
GameStateType TitleScreenState::update(GameStateType currentState, GameCookie *cookie) {

    this->updateStarField(1);
  
    if (this->counter > 0) {
        
        this->counter--;
        
    }
    else {
     
        if (viewState == ViewState::StartGame) {

            currentState = GameStateType::PlayGame_Activate; 
            
        }
        
    }
  


    // Update highlight ..
    
    if (Utils::getFrameCount(5) == 0) {

        this->titleSeq++;

        if (this->titleSeq > 16) this->titleSeq = 0;

    }


    // Update states ..
    
    switch (this->viewState) {

        case ViewState::Marquee:

            if (Utils::getFrameCount(2) == 0) {

                this->marquee++;
                if (this->marquee > 950) {
                    
                    this->marquee = 0;
                    this->stateToggle = 300;
                    this->viewState = ViewState::Normal;

                }

            }

            break;

        case ViewState::Normal:

            this->stateToggle--;

            if (this->stateToggle == 0) {
                
                this->marquee = 0;
                this->viewState = ViewState::Marquee;

            }

            break;

    }


    
	// Handle other input ..

	if (PC::buttons.pressed(BTN_A)) {
	    
	    if (this->viewState == ViewState::Normal || this->viewState == ViewState::Marquee) {
	        
            this->viewState = ViewState::StartGame;
            this->counter = 79;
            Audio::SFX8Source::play<0>(sfx_Coin, sfx_Coin_length);
            //PS::playSFX(Sounds::sfx_Coin, Sounds::sfx_Coin_length);
            
	    }
	    else {

            currentState = GameStateType::PlayGame_Activate; 
            
	    }

	}

	if (PC::buttons.pressed(BTN_B)) {

        cookie->setLastScore(0);
        currentState = GameStateType::HighScore_Activate; 
        
    }

    return currentState;

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void TitleScreenState::render(GameCookie *cookie) {

    PD::clear();

    
    // Render star field ..
    
    this->renderStarField(1);
    
    PD::drawBitmap(20, 30, Images::Title_Full);

    switch (this->titleSeq) {

        case 1:
            PD::drawBitmap(24, 38, Images::Title_00);
            break;

        case 2:
            PD::drawBitmap(30, 44, Images::Title_01);
            break;

        case 3:
            PD::drawBitmap(55, 39, Images::Title_02);
            break;

        case 4:
            PD::drawBitmap(72, 53, Images::Title_03);
            break;

        case 5:
            PD::drawBitmap(113, 54, Images::Title_04);
            break;

    }

    if ((this->viewState == ViewState::Normal && this->counter == 0) || (this->viewState == ViewState::StartGame && ((this->counter / 20) % 2) == 1)) {
        
        PD::setCursor(47, 130);
        PD::setColor(6);
        PD::print("INSERT CREDITS");
        
    }

    if (this->viewState == ViewState::Marquee) {

        const char highScores[] = { 'H', 'I', 'G', 'H', ' ', 'S', 'C', 'O', 'R', 'E', 'S' };
        uint8_t x = 0;

        uint8_t marqueeOffset = this->marquee % 10;
        uint8_t marquee10 = this->marquee / 10;

        PD::setCursor(47 - (this->marquee % 10), 130);
        PD::setColor(6);

        for (uint8_t i = marquee10; i < marquee10 + 16; i++) {

            switch (i) {

                case 16 ... 19:
                    PD::setColor(6);
                    this->printSingleChar(highScores[i - 16]);
                    break;

                case 21 ... 26:
                    PD::setColor(6);
                    this->printSingleChar(highScores[i - 16]);
                    break;

                // Player 0

                case 29 ... 31:
                    PD::setColor(6);
                    this->printChar(cookie->initials[0][i - 29]);
                    break;

                case 33 ... 40:
                    {
                        PD::setColor(8);
                        uint8_t digits[8] = {};
                        Utils::extractDigits(digits, cookie->score[0]);
                        this->printNumber(digits[40 - i]);
                    }
                    break;

                // Player 1

                case 42 ... 44:
                    PD::setColor(6);
                    this->printChar(cookie->initials[1][i - 42]);
                    break;

                case 46 ... 53:
                    {
                        PD::setColor(8);
                        uint8_t digits[8] = {};
                        Utils::extractDigits(digits, cookie->score[1]);
                        this->printNumber(digits[53 - i]);
                    }
                    break;

                // Player 2

                case 55 ... 57:
                    PD::setColor(6);
                    this->printChar(cookie->initials[2][i - 55]);
                    break;

                case 59 ... 66:
                    {
                        PD::setColor(8);
                        uint8_t digits[8] = {};
                        Utils::extractDigits(digits, cookie->score[2]);
                        this->printNumber(digits[66 - i]);
                    }
                    break;

                // Player 3

                case 68 ... 70:
                    PD::setColor(6);
                    this->printChar(cookie->initials[3][i - 68]);
                    break;

                case 72 ... 79:
                    {
                        PD::setColor(8);
                        uint8_t digits[8] = {};
                        Utils::extractDigits(digits, cookie->score[3]);
                        this->printNumber(digits[79 - i]);
                    }
                    break;

                // Player 4

                case 81 ... 83:
                    PD::setColor(6);
                    this->printChar(cookie->initials[4][i - 81]);
                    break;

                case 85 ... 92:
                    {
                        PD::setColor(8);
                        uint8_t digits[8] = {};
                        Utils::extractDigits(digits, cookie->score[4]);
                        this->printNumber(digits[92 - i]);
                    }
                    break;                    

                default:
                    PD::setColor(0);
                    PD::print('-');
                    break;

            }

        }


        PD::setColor(0);
        PD::fillRect(36, 130, 10, 10);
        PD::fillRect(174, 130, 15, 10);
    }
    
}


void TitleScreenState::printSingleChar(char theChar) {

    char output[] = { ' ', '\0' };
    memcpy(&output, &theChar, 1);
    PD::print(&output[0]);
    
}

void TitleScreenState::printChar(uint8_t charIndex) {

    switch (charIndex) {

        case 1 ... 26:
            charIndex = charIndex + 64;
            break;

        case 27 ... 36:
            charIndex = charIndex + 21;
            break;

        case 37:
            charIndex = 46;
            break;
        
    }

    char output[] = { ' ', '\0' };
    memcpy(&output, &charIndex, 1);
    PD::print(&output[0]);
    
}


void TitleScreenState::printNumber(uint8_t number) {

    number = number + 48;

    char output[] = { ' ', '\0' };
    memcpy(&output, &number, 1);
    PD::print(&output[0]);
    
}
