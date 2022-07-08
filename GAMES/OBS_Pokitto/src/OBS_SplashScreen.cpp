#include "OBS.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::splashScreen_Init() {

    this->gameState = GameState::Splash;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::splashScreen() { 

    auto justPressed = PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B) || PC::buttons.pressed(BTN_C);

    if (justPressed > 0) {

        this->gameState = GameState::Title_Init; 

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
