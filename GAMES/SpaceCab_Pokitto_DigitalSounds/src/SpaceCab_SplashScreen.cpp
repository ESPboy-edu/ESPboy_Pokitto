#include "SpaceCab.h"
#include "Pokitto.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
//using PS = Pokitto::Sound;



// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::initSplash() {

    splashScreenVariables.reset();
    PC::buttons.pollButtons();

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::renderSplash() { 

    auto justPressed = PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B) || PC::buttons.pressed(BTN_C);

    if (justPressed > 0) {

        this->state = GameState::TitleScreen_Init; 

    }
    
    if (PC::frameCount % 24 == 0) {

        splashScreenVariables.counter++;
        
        if (splashScreenVariables.counter == 4) {
            
            splashScreenVariables.counter = 0;
            
        }
        
    }
    

    //  Render the state ..

    PD::drawBitmap(22, 27, Images::Ppot_Full);
    PD::drawBitmap(32, 38, Images::Ppot[splashScreenVariables.counter]);

    if (splashScreenVariables.counter < 2) PD::drawBitmap(81, 36, Images::Ppot_Arrow);

}
