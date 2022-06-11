#include "SpaceCab.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::titleScreen_Init() {
    this->gamePlayVariables.reset();
    this->gamePlayVariables.levelNumber = 0;
    initLevel(this->level, this->player, this->customer, this->gamePlayVariables.levelNumber);
    this->customer.setStartingPosition(0);
    this->customer.setDestinationPosition(1);
    launchCustomer(this->level, this->customer, this->gamePlayVariables.gateToRender, GO_TO_GATE);
    this->player.setFrame(0);
    this->state = GameState::TitleScreen;
    this->prevState = GameState::TitleScreen_Init;
    this->playTheme();

}

void Game::titleScreen(Level &level, Player &player, Customer &customer) {

    int16_t customerXVal = static_cast<uint16_t>(customer.getX() + level.xOffset);
    int16_t customerYVal = static_cast<uint16_t>(customer.getY() + level.yOffset);

    if (this->gamePlayVariables.gotoCounter != 0)   {
        this->gamePlayVariables.gotoCounter--;
    }

    if (this->gamePlayVariables.ouchCounter != 0) { 

        this->gamePlayVariables.ouchCounter--;

        if (this->gamePlayVariables.ouchCounter == 0) {
            this->gamePlayVariables.gateToRender = (this->gamePlayVariables.gateToRender == 0 ? 1 : 0);
            launchCustomer(level, customer, this->gamePlayVariables.gateToRender, GO_TO_GATE);
        }

    }

    drawLevel_Intro(level, this->gamePlayVariables.gateToRender);

    PD::drawBitmap(92 + this->level.getXOffsetDisplay(), 18, Images::SpaceCabLogo);
    PD::drawBitmap(this->level.getXOffsetDisplay(), 26, Images::Scores_Flag);
    PD::drawBitmap(225 + this->level.getXOffsetDisplay(), 26, Images::Design_Flag);

    for (uint8_t y = 37; y < 48; y++) {

        PD::setColor(y % 2 == 0 ? 5 : 6);
        PD::drawFastHLine(5 + this->level.getXOffsetDisplay(), y, 21);

    }

    for (uint8_t y = 37; y < 48; y++) {

        PD::setColor(y % 2 == 0 ? 5 : 6);
        PD::drawFastHLine(230 + this->level.getXOffsetDisplay(), y, 21);

    }

    this->playerDisplay(player);
    this->customerDisplay(level, player, customer, customerXVal, customerYVal);
    this->handleInput(player);
    this->checkCollisionWithCustomer(level, player, customer);
    this->drawGoto(level, player, customer, customerXVal, customerYVal);
    this->drawOuch(customer, customerXVal, customerYVal);


    // Handle the score landing location ..

    bool renderScore = false;
    
    if (player.getX() <= 28) {

        if (player.getY() >= 28 && player.getYDelta() > 0) {
            player.setLandingGearDown(true);
        }

        if ((player.getY() >= 37 && player.getY() <= 39) && player.isCarryingCustomer()) {

            this->playSoundEffect(4);

            for (uint8_t y = 47; y > 36; y--) {
                
                //#ifdef SOUNDS
                Game::playFXS(2, y);
                /*
                    auto note = Audio::Note((y * 2) - 40)
                                        .wave(WSQUARE)
                                        .duration(50)
                                        .volume(75);
                    
                    
                    note.play(2);  
                */
                //#endif
                

                PD::setColor(0);
                PD::drawFastHLine(5 + this->level.getXOffsetDisplay(), y, 21);
                this->playerDisplay(player);

                //PD::update();
                PC::update();
                PD::update();
                PC::wait(150);

            }

            PD::setColor(0, 0);
            cookie->setLastScore(0);
            this->state = GameState::HighScore_Init;

        } 

    } 

    // Handle the design landing location ..

    if (player.getX() >= 68) {

        if (player.getY() >= 28 && player.getYDelta() > 0) {
            player.setLandingGearDown(true);
        } 
/*
        if ((player.getY() >= 37 && player.getY() <= 39) && player.isCarryingCustomer()) {

            // this->playSoundEffect(4);
            
            for (uint8_t y = 47; y > 36; y--) {

                #ifdef SOUNDS                
                    auto note = Audio::Note((y * 2) - 40)
                                        .wave(WSQUARE)
                                        .duration(50)
                                        .volume(75);
                    
                    
                    note.play(2); 
                #endif

                PD::setColor(0);
                PD::drawFastHLine(230 + this->level.getXOffsetDisplay(), y, 21);
                
                this->playerDisplay(player);
                PD::update();
                PC::update();
                PC::wait(150);

            }

            PD::setColor(0, 0);
            this->state = GameState::Designer_Init;
        } 
*/
    }


    // Land on the ground ..

    if (player.getY() >= 41 && player.getYDelta()> 0) {
        player.setLandingGearDown(true);
    } 


    // if (PC::buttons.pressed(BTN_C)) {
    //     this->state = GameState::Designer_Init;
    // }
 
}
