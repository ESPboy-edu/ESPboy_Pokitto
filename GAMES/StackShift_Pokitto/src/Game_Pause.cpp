#include "Game.h"
#include "images/Images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

constexpr const static uint8_t UPLOAD_DELAY = 16;

int16_t xCass = 0;
int16_t yCass = 0;
int16_t pathIdx[3];
int16_t pathDir = 0;
int16_t pathCounter = 0;

const PROGMEM uint8_t xPath[84] = {  0,  2,  4,  6,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82,  
                            82, 80, 78, 76, 74, 72, 70, 68, 66, 64, 62, 60, 58, 56, 54, 52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10,  8,  6,  4,  2,  0 };

const PROGMEM uint8_t yPath[84] = { 10, 12, 14, 14, 15, 16, 16, 17, 17, 17, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 18, 18, 18, 18, 18, 17, 17, 17, 16, 16, 15, 14, 14, 12, 
                            10,  8,  6,  6,  5,  4,  4,  3,  3,  3,  2,  2,  2,  2,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  3,  3,  3,  4,  4,  5,  6,  6,  8 };

const PROGMEM uint8_t zPath[84] = {  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
                             2,  2,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1,  1,  1,  1,  1,  };


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::doPause_Init() {
	
    this->gameState = GameState::Pause;
    this->cursor = this->cookie->track;

    switch (this->cookie->track) {

        case 1:
            pathIdx[0] = 49;
            pathIdx[1] = pathIdx[0] - 28;
            pathIdx[2] = pathIdx[0] + 28;
            break;

        case 2:
            pathIdx[1] = 49;
            pathIdx[2] = pathIdx[1] - 28;
            pathIdx[0] = pathIdx[1] + 28;
            break;

        case 0:
            pathIdx[2] = 49;
            pathIdx[0] = pathIdx[2] - 28;
            pathIdx[1] = pathIdx[2] + 28;
            break;

    }

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::doPause() {
	
    if (xCass == 0 && pathCounter == 0) {

        if (PC::buttons.pressed(BTN_LEFT)) {

            pathDir = -1;
            pathCounter = 28;

        }

        if (PC::buttons.pressed(BTN_RIGHT)) {

            pathDir = 1;
            pathCounter = 28;

        }

        if (PC::buttons.pressed(BTN_C)) {
            this->gameState = GameState::Play;
        }

        if (PC::buttons.pressed(BTN_A)) {

            if (this->cookie->sfx == SoundEffects::None) {

                this->cookie->sfx = SoundEffects::Music;
                xCass = 79;
                yCass = 93;

            }
            else if (this->cookie->sfx == SoundEffects::SFX) {

                this->cookie->sfx = SoundEffects::Both;
                xCass = 79;
                yCass = 93;

            }
            else if (this->cookie->track != this->cursor) {

                xCass = 79;
                yCass = 93;

            }

        }

    }

    if (pathCounter > 0) {

        pathCounter--;

        for (uint8_t i = 0; i < 3; i++) {

            pathIdx[i] = pathIdx[i] + pathDir;

            if (pathIdx[i] < 0) {
                pathIdx[i] = pathIdx[i] + 84;
            }

            if (pathIdx[i] >= 84) {
                pathIdx[i] = pathIdx[i] - 84;
            }

        }

        if (pathCounter == 0) {

            this->cursor = this->cursor + pathDir;

            if (this->cursor == 255) this->cursor = 2;
            if (this->cursor == 3) this->cursor = 0;
            
        }

    }


    if (xCass > 0) {

        switch (xCass) {

            case 0 ... 162:
                xCass = xCass + 4;
                break;

            case 163:
                xCass = xCass + 2;
                break;

            case 164 ... 165:
                xCass = xCass + 1;
                break;

        }

        switch (yCass) {

            case 3:
                yCass = yCass - 1;
                break;

            case 4 ... 6:
                yCass = yCass - 2;
                break;

            case 7 ... 255:
                yCass = yCass - 4;
                break;

        }

        if (yCass == 2 && xCass == 166) {
            
            xCass = 0;

            this->cookie->track = this->cursor;
            this->cookie->saveCookie();
            this->playTheme(this->cookie->track);

        }

    }


    // ----------------------------------------------------------------------------
    //  Render the state .. 

    this->drawScore(true, true);
    this->drawFrame();
    this->drawTrack();

    PD::drawBitmap(95, 46, Images::PausePlay);

    if (pathCounter == 0) {

        PD::drawBitmap(40, 86, Images::ArrowLeft);
        PD::drawBitmap(168, 86, Images::ArrowRight);

    }

    for (uint8_t z = 0; z < 3; z++) {

        for (uint8_t i = 0; i < 3; i++) {

            if (zPath[pathIdx[i]] == z) {

                if (xCass > 0 && i == this->cursor) {

                    PD::drawBitmap(xCass, yCass, Images::Tapes_Shadow[this->cursor]);

                }
                else {

                    PD::drawBitmap(41 + xPath[pathIdx[i]], 70 + yPath[pathIdx[i]], Images::Tapes_Shadow[i]);

                }

            }

        }

    }

}
