#include "Scramble.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title_Init() {

    this->gameState = GameState::Title;
    this->playTheme(Themes::Main);

    this->titleScreenVars.reset();
    this->stars.reset();
    // this->gamePlay.setCounter(0);

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title() {

    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        this->titleScreenVars.setLettersToTop();
        this->titleScreenVars.counter = 87;
        this->gameState = GameState::Scenario_Init;

    }         

    if (PC::buttons.pressed(BTN_B)) { 

        uint32_t index = cookie->setLastScore(0);
        this->gameState = GameState::HighScore_Init;

    }         

    if (PC::buttons.pressed(BTN_UP)) {

        this->cookie->sfx--;
        this->cookie->saveCookie();

        if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

            this->muteTheme();
            
        }
        else {

            this->playTheme(Themes::Main);

        }

    }

    if (PC::buttons.pressed(BTN_DOWN)) {

        this->cookie->sfx++;
        this->cookie->saveCookie();

        if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

            this->muteTheme();
            
        }
        else {

            this->playTheme(Themes::Main);
            
        }
        
    }


    // Create explosions ..

    if (PC::frameCount % 60 == 0 && this->titleScreenVars.counter >= 87) {

        this->explode(random(16, 200) + this->gameScreenVars.distance, random(55, 55 + 37) + this->gameScreenVars.viewY, static_cast<ExplosionSize>(random(1, 4)), this->gameScreenVars.getColor());

    }

    this->stars.moveY();



    // Increase counters ..

    if (this->titleScreenVars.counter < 87) {
        this->titleScreenVars.counter = this->titleScreenVars.counter + 4;
    }


    // Render page ..

    this->renderStars(false);


    // Title underline ..

    if (this->titleScreenVars.counter > 4) {

        for (uint16_t i = 110 - 2 - this->titleScreenVars.counter; i < 110 + this->titleScreenVars.counter; i = i + 3) {
            PD::drawBitmap(i, 86, Images::Title_Mid);
        }

    }

    PD::drawBitmap(110 - 4 - this->titleScreenVars.counter, 86, Images::Title_Left);
    PD::drawBitmap(110 + this->titleScreenVars.counter, 86, Images::Title_Right);

    for (uint8_t i = 0; i < 9; i++) {

        PD::drawBitmap(this->titleScreenVars.charsX[i] + 19, this->titleScreenVars.charsY[i] - 2, Images::TitleLetters[this->titleScreenVars.charsIdx[i]]);

    }

    this->titleScreenVars.incLetters();



    switch (this->cookie->sfx) {

        case SoundEffects::Music:
            PD::drawBitmap(186, 164, Images::Sound_Music);
            break;

        case SoundEffects::SFX:
            PD::drawBitmap(186, 164, Images::Sound_SFX);
            break;

        case SoundEffects::Both:
            PD::drawBitmap(186, 164, Images::Sound_Both);
            break;

        default:
            PD::drawBitmap(186, 164, Images::Sound_None);
            break;

    }


    // Render shockwaves and particles ..

    this->renderShockwave(this->gameScreenVars.distance, this->gameScreenVars.viewY);
    this->renderParticles(this->gameScreenVars.distance, this->gameScreenVars.viewY);

}
