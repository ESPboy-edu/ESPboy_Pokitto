#include "Game.h"
#include "Pokitto.h"
#include "images/images.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;



// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::doTitle() { 

    if (this->splashScreenVariables.buttonCounter == 0 && PC::buttons.pressed(BTN_LEFT) && this->titleCursor > 0) {

        this->titleCursor--;

    }

    if (this->splashScreenVariables.buttonCounter == 0 && PC::buttons.pressed(BTN_RIGHT) && this->titleCursor  < 3) {

        this->titleCursor++;

    }


    if (this->splashScreenVariables.buttonCounter > 0 ? false : (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B))) {

        switch (this->titleCursor) {

            case 0:
                this->level = Level::Easy;
                this->gameState = GameState::Play_Init;
                break;

            case 1:
                this->level = Level::Hard;
                this->gameState = GameState::Play_Init;
                break;

            case 2:
                this->cookie->setScoreIndex(NO_SCORE);
                this->gameState = GameState::HighScore_Init;
                break;

            case 3:
                this->cookie->sfx++;
                this->cookie->saveCookie();
                break;

        }
                            

    }
   

    if (Utils::isFrameCount(46)) this->launchHighScoreParticles();

    PD::drawBitmap(1, 30, Images::Title);


    PD::drawBitmap(98, 30, Images::Title_Anim[(PC::frameCount / 9) % 4]);

    PD::setColor(this->titleCursor == 0 ? 7 : 5, 0);
    PD::setCursor(12, 142);
    PD::print("EASY");

    PD::setColor(this->titleCursor == 1 ? 7 : 5, 0);
    PD::setCursor(58, 142);
    PD::print("HARD");

    PD::setColor(this->titleCursor == 2 ? 7 : 5, 0);
    PD::setCursor(105, 142);
    PD::print("SCORES");

    PD::setColor(this->titleCursor == 3 ? 7 : 5, 0);

    switch (this->cookie->sfx) {

        case SoundEffects::Music:
            PD::setCursor(166, 142);
            PD::print("MUSIC");
            break;

        case SoundEffects::SFX:
            PD::setCursor(174, 142);
            PD::print("SFX");
            break;

        case SoundEffects::Both:
            PD::setCursor(170, 142);
            PD::print("BOTH");
            break;

        default:
            PD::setCursor(170, 142);
            PD::print("NONE");
            break;
    }

    constexpr uint8_t xPos[] = { 26, 71, 127, 184 };
    PD::drawBitmap(xPos[this->titleCursor], 130, Images::Symbols[static_cast<uint8_t>(BoardType::Existing_Red)][0]);

    this->renderParticles();

}
