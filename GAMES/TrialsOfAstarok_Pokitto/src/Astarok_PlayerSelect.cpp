#include "Astarok.h"

void Game::playerSelect_Init() {

    playerSelectVars.reset(cookie->sex);
    
    for (uint8_t i = 0; i < 5; i++) {
        seedVars.seed[i] = cookie->seeds[i];
    }
    
    gameState = GameState::PlayerSelect;

}

void Game::playerSelect() {

    PD::drawBitmap(-5, 12, Images::Underground_Brick);
    PD::drawBitmap(97, 12, Images::Underground_Brick);

    PD::drawBitmap(-5, 65, Images::Underground_Brick);
    PD::drawBitmap(97, 65, Images::Underground_Brick);

    PD::drawBitmap(2, 37, Images::Torch[Utils::getFrameCount(16) / 4]);
    PD::drawBitmap(103, 37, Images::Torch[Utils::getFrameCount(16) / 4]);

    
    PD::drawBitmap(21, 16, Images::SelectPlayer);
    PD::drawBitmap(15, 31, Images::EnterRunes_00);
    PD::drawBitmap(15, 57, Images::EnterRunes_02);
    PD::drawBitmap(88, 31, Images::EnterRunes_01);
    PD::drawBitmap(88, 57, Images::EnterRunes_03);

    PD::setColor(0xf8);
    PD::drawFastHLine(21, 31, 67);
    PD::drawFastHLine(21, 64, 67);
    PD::drawFastHLine(17, 66, 75);


    if (playerSelectVars.counter == 0) {

        PD::drawBitmap(35, 41, Images::MalePlayer_Idle[playerSelectVars.maleIdle + 3]);
        PD::drawBitmap(62, 41, Images::FemalePlayer_Idle[playerSelectVars.femaleIdle]);

        if (PC::buttons.pressed(BTN_LEFT) && playerSelectVars.index > 0) {
            
            playerSelectVars.index = 0;
            this->sounds.playSoundEffect(Sounds::Effects::ButtonPress, this->cookie->sfx);
            playerSelectVars.counter = 6;
            playerSelectVars.vy = -3;
            playerSelectVars.y = 41;

        }

        if (PC::buttons.pressed(BTN_RIGHT) && playerSelectVars.index < 1) {
            
            playerSelectVars.index = 1;
            this->sounds.playSoundEffect(Sounds::Effects::ButtonPress, this->cookie->sfx);
            playerSelectVars.counter = 6;
            playerSelectVars.vy = -3;
            playerSelectVars.y = 41;

        }

        if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {

            cookie->sex = static_cast<Sex>(playerSelectVars.index);
            cookie->saveCookie();

            gameState = GameState::Game_Init;

        }

    }
    else {

        PD::drawBitmap(35, playerSelectVars.index == 0 ? playerSelectVars.y : 40, Images::MalePlayer_Jumping[1]);
        PD::drawBitmap(61, playerSelectVars.index == 1 ? playerSelectVars.y : 40, Images::FemalePlayer_Jumping[0]);
        
        if (PC::frameCount % 4 == 0) {

            playerSelectVars.y = playerSelectVars.y + playerSelectVars.vy;
            playerSelectVars.vy++;
            playerSelectVars.counter--;

        }

    }

    PD::drawBitmap(36 + (playerSelectVars.index * 27), 56, Images::PlayerSelector);

    if (PC::frameCount % 24 == 0) {

        playerSelectVars.maleIdle = (playerSelectVars.maleIdle + 1) % 3;
        playerSelectVars.femaleIdle = (playerSelectVars.femaleIdle + 1) % 3;
         
    }

}

