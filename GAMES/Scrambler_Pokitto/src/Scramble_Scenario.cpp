#include "Scramble.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::scenario_Init() {

    this->gameState = GameState::Scenario;

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::scenario() {

    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameState::Game_Init;

    }         

    if (PC::buttons.pressed(BTN_B)) { 

        this->gameState = GameState::Title_Init;

    }         


    this->stars.moveY();


    // Move title up ..

    if (this->titleScreenVars.charsY[0] > 0) {

        for (uint8_t i = 0; i < 9; i++) {

            this->titleScreenVars.charsY[i] = this->titleScreenVars.charsY[i] - 2;

        }

    }
    else {

        if (this->titleScreenVars.scenarioCounter <= 106) {
            this->titleScreenVars.scenarioCounter++;
        }

    }



    // Render page ..

    this->renderStars(false);

    PD::setColor(6);



    // Title underline ..

    if (this->titleScreenVars.counter > 4) {

        for (uint16_t i = 110 - 2 - this->titleScreenVars.counter; i < 110 + this->titleScreenVars.counter; i = i + 3) {
            PD::drawBitmap(i, 31 + this->titleScreenVars.charsY[0], Images::Title_Mid);
        }

    }

    PD::drawBitmap(110 - 4 - this->titleScreenVars.counter, 31 + this->titleScreenVars.charsY[0], Images::Title_Left);
    PD::drawBitmap(110 + this->titleScreenVars.counter, 31 + this->titleScreenVars.charsY[0], Images::Title_Right);

    for (uint8_t i = 0; i < 9; i++) {

        PD::drawBitmap(this->titleScreenVars.charsX[i] + 19, this->titleScreenVars.charsY[i] + 1, Images::TitleLetters[this->titleScreenVars.charsIdx[i]]);

    }

    #define SHADOW 2
    #define HIGHLIGHT 7
    
    if (this->titleScreenVars.charsY[0] == 0) {

        if (this->titleScreenVars.scenarioCounter > 0) {

            PD::setColor(SHADOW, 14);
            PD::setCursor(60, 62);
            PD::print("-- Score Table --");
            PD::setColor(HIGHLIGHT, 14);
            PD::setCursor(60, 61);
            PD::print("-- Score Table --");

        }

        if (this->titleScreenVars.scenarioCounter > 10 + 32) {

            PD::drawBitmap(24, 80, Images::Rocket);
            PD::drawBitmap(27, 96, Images::Flame[PC::frameCount % 16 / 4]);
            PD::setColor(SHADOW, 14);
            PD::setCursor(50, 85);
            PD::print(".. 20 Pts");
            PD::setColor(HIGHLIGHT, 14);
            PD::setCursor(50, 84);
            PD::print(".. 20 Pts");


            PD::drawBitmap(120, 80, Images::Eighter[PC::frameCount % 16 / 4]);
            PD::setColor(SHADOW, 14);
            PD::setCursor(150, 85);
            PD::print(".. 20 Pts");
            PD::setColor(HIGHLIGHT, 14);
            PD::setCursor(150, 84);
            PD::print(".. 20 Pts");

        }

        if (this->titleScreenVars.scenarioCounter > 10 + (2 * 32)) {

            PD::drawBitmap(20, 110, Images::Mine);
            PD::setColor(SHADOW, 14);
            PD::setCursor(50, 115);
            PD::print(".. 25 Pts");
            PD::setColor(HIGHLIGHT, 14);
            PD::setCursor(50, 114);
            PD::print(".. 25 Pts");

            PD::drawBitmap(114, 110, Images::SurfaceToAir[PC::frameCount % 128 / 32]);
            PD::setColor(SHADOW, 14);
            PD::setCursor(150, 115);
            PD::print(".. 100 Pts");
            PD::setColor(HIGHLIGHT, 14);
            PD::setCursor(150, 114);
            PD::print(".. 100 Pts");

        }

        if (this->titleScreenVars.scenarioCounter > 10 + (3 * 32)) {

            PD::drawBitmap(20, 140, Images::GroundPod);
            PD::setColor(SHADOW, 14);
            PD::setCursor(50, 145);
            PD::print(".. 75 Pts");
            PD::setColor(HIGHLIGHT, 14);
            PD::setCursor(50, 144);
            PD::print(".. 75 Pts");

            PD::drawBitmap(114, 140, Images::FuelDepot_Sml);
            PD::setColor(SHADOW, 14);
            PD::setCursor(150, 145);
            PD::print(".. 100 Pts");
            PD::setCursor(150, 154);
            PD::print("    + Fuel");
            PD::setColor(HIGHLIGHT, 14);
            PD::setCursor(150, 144);
            PD::print(".. 100 Pts");
            PD::setCursor(150, 153);
            PD::print("    + Fuel");

        }

        PD::setColor(0, 0);

    }

}
