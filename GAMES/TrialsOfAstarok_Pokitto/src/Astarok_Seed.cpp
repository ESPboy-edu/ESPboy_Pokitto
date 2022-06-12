#include "Astarok.h"

void Game::seed_Init() {

    seedVars.reset();

    for (uint8_t i = 0; i < 5; i++) {
        seedVars.seed[i] = cookie->seeds[i];
    }
    
    gameState = GameState::Seed;

}

void Game::seed() {

    PD::drawBitmap(-5, 12, Images::Underground_Brick);
    PD::drawBitmap(97, 12, Images::Underground_Brick);

    PD::drawBitmap(-5, 65, Images::Underground_Brick);
    PD::drawBitmap(97, 65, Images::Underground_Brick);

    PD::drawBitmap(2, 37, Images::Torch[Utils::getFrameCount(16) / 4]);
    PD::drawBitmap(103, 37, Images::Torch[Utils::getFrameCount(16) / 4]);

    
    PD::drawBitmap(25, 16, Images::EnterRunes_Text);
    PD::drawBitmap(15, 31, Images::EnterRunes_00);
    PD::drawBitmap(15, 57, Images::EnterRunes_02);
    PD::drawBitmap(88, 31, Images::EnterRunes_01);
    PD::drawBitmap(88, 57, Images::EnterRunes_03);

    PD::setColor(0xf8);
    PD::drawFastHLine(21, 31, 67);
    PD::drawFastHLine(21, 64, 67);
    PD::drawFastHLine(17, 66, 75);

    for (uint8_t i = 0; i < 5; i++) {

        if (i == seedVars.index && seedVars.spinIndex > 0) {
            PD::drawBitmap(21 + (i* 14), 41, Images::Rune_Frame[16 - seedVars.spinIndex]);
        }
        else {
            PD::drawBitmap(21 + (i* 14), 41, Images::Rune_Frame_00);
            PD::drawBitmap(24 + (i* 14), 45, Images::Runes[seedVars.seed[i]]);
        }

    }

    PD::drawBitmap(24 + (seedVars.index * 14), 36, Images::ArrowUp);
    PD::drawBitmap(24 + (seedVars.index* 14), 57, Images::ArrowDown);

    if (seedVars.spinIndex == 0) {

        if (PC::buttons.pressed(BTN_UP)) {
            seedVars.incValue();
            cookie->seeds[seedVars.index] = seedVars.seed[seedVars.index];
            this->sounds.playSoundEffect(Sounds::Effects::ButtonPress, this->cookie->sfx);
        }

        if (PC::buttons.pressed(BTN_DOWN)) { 
            seedVars.decValue();
            cookie->seeds[seedVars.index] = seedVars.seed[seedVars.index];
            this->sounds.playSoundEffect(Sounds::Effects::ButtonPress, this->cookie->sfx);
        }

        if (PC::buttons.pressed(BTN_LEFT)) { 
            if (seedVars.decIndex()) this->sounds.playSoundEffect(Sounds::Effects::ButtonPress, this->cookie->sfx);

        }

        if (PC::buttons.pressed(BTN_RIGHT)) { 
            if (seedVars.incIndex()) this->sounds.playSoundEffect(Sounds::Effects::ButtonPress, this->cookie->sfx);
        }

        if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {

            cookie->saveCookie();

            game.seed = seedVars.getSeedValue();
            for (uint8_t a = 0; a < Constants::GameSeeds; a++ ) {
                game.seeds[a] = Utils::hash(game.seed);
            }

            gameState = GameState::PlayerSelect_Init;

        }

    }

    seedVars.decSpinIndex();

}

