#include "Pokitto.h"
#include "Game.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::showGameSavedMessage() {


    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) {

        PD::setColor(0);
        gameState = GameState::Game; 

    }



    // Rnder screen ..

    PD::fillScreen(0);
    this->renderEnvironment(!this->map.isBossLevel() && !this->map.isAltarLevel(), 0, 0);
    this->renderHud();

    PD::setColor(15);
    PD::fillRect(14, 27, 87, 24);
    PD::drawBitmap(8, 22, Images::AltarTOP_Wide); 
    PD::drawBitmap(8, 29, Images::MessagePanelLHS); 
    PD::drawBitmap(98, 29, Images::MessagePanelRHS); 
    PD::drawBitmap(8, 50, Images::AltarBOT_Wide); 
    PD::setColor(4, 15);
    PD::setFont(font3x5);


    PD::setCursor(19, 30);
    PD::print("Game Saved. Resuming");
    PD::setCursor(19, 37);
    PD::print("will take you to the");
    PD::setCursor(19, 44);
    PD::print("START of the level.");

    PD::setFont(fontKoubit);

}
