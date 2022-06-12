#include "Astarok.h"


// Returns the new slot the provided high score should occupy ..
void Game::checkHighScoreSlot(uint16_t score) {

    uint16_t tmpScore = 0;

    for (uint8_t i = 0; i < Constants::NumberOfScores; i++) {

        Slot slot = this->cookie->slots[i];

        if (slot.score < score) {
            
            highScoreVars.slot = i;
            highScoreVars.score = game.score + game.player.x / Constants::TileSize;

            for (uint8_t i = 0; i < 5; i++) {
                highScoreVars.seeds[i] = seedVars.seed[i];
            }
            
            writeHighScoreEntry(highScoreVars);
            this->sounds.playTheme(3, cookie->sfx);
            return;

        }

    }

    highScoreVars.slot = Constants::No_Slot;

}

void Game::writeHighScoreEntry(HighScoreVars &highScoreVars) {


    // Move the scores down one ..

    for (uint8_t j = Constants::NumberOfScores - 1; j > highScoreVars.slot; j--) {          

        Slot &slot1 = this->cookie->slots[j - 1];
        Slot &slot2 = this->cookie->slots[j];

        for (uint8_t k = 0; k < 5; k++) {

            slot2.seeds[k] = slot1.seeds[k];

        }

        slot2.score = slot1.score;

    }


    // Write score and initials to the nominated slot ..

    Slot &slot = this->cookie->slots[highScoreVars.slot];
    slot.reset();
    slot.score = highScoreVars.score;

    for (uint8_t i = 0; i < 5; i++) {
        slot.seeds[i] = seedVars.seed[i];
    }

    this->cookie->saveCookie();

}

void Game::highScores() {

    uint16_t score;

    // Rnadomly spin a rune ..

    if (gameState == GameState::HighScore_NoFlash && highScoreVars.spinCountdown == 0) {

        highScoreVars.index = Utils::hash(game.seed) % 14;
        highScoreVars.spinIndex = 16;
        highScoreVars.spinCountdown = 100;

    }


    // Render screen ..

    PD::drawBitmap(21, 0, Images::Underground_Chain);
    PD::drawBitmap(85, 0, Images::Underground_Chain);
    PD::drawBitmap(21, 8, Images::Underground_Chain);
    PD::drawBitmap(85, 8, Images::Underground_Chain);
    PD::drawBitmap(29, 5, Images::TopThree);

    PD::drawBitmap(3, 1, Images::Intro_Brick_00);
    PD::drawBitmap(94, 1, Images::Intro_Brick_01);

    PD::drawBitmap(9, 6, Images::Torch[Utils::getFrameCount(16) / 4]);
    PD::drawBitmap(95, 6, Images::Torch[Utils::getFrameCount(16) / 4]);
    PD::drawBitmap(92, 81, Images::Version);


    for (uint8_t i = 0; i < Constants::NumberOfScores; i++) {

        // If we are not editing this slot, the render it normally ..
        
        if (gameState == GameState::HighScore_NoFlash || i != highScoreVars.slot || Utils::getFrameCountHalf(32)) {

            Slot slot = this->cookie->slots[i];

            for (uint8_t j = 0; j < 5; j++) {

                if ((i * 5) + j == highScoreVars.index && highScoreVars.spinIndex > 0) {
                    PD::drawBitmap(7 + (j * 14), 26 + (i * 17), Images::Rune_Frame[16 - highScoreVars.spinIndex]);
                }
                else {
                    PD::drawBitmap(7 + (j * 14), 26 + (i * 17), Images::Rune_Frame_00);
                    PD::drawBitmap(10 + (j * 14), 26 + (i * 17) + 4, Images::Runes[slot.seeds[j]]);
                }

            }

            // Render score always ..

            uint8_t digits[5] = {};
            Utils::extractDigits(digits, slot.score);
            
            for (uint8_t j = 0; j < 5; j++) {
                PD::drawBitmap(75 + ((5 - j) * 5), 26 + (i * 17) + 4, Images::Numbers[digits[j]]);
            }

        }

    }


    // Handle player input ..

    if ((PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1)) && (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1))) {
        
        highScoreVars.resetCounter++;

        if (highScoreVars.resetCounter == 64) {
            this->cookie->initialize();
            highScoreVars.resetCounter = 0;
        }

    }
    else if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {

        gameState = GameState::Title_Init;
        highScoreVars.resetCounter = 0;

    }
    else {

        highScoreVars.resetCounter = 0;

    }

    if (PC::frameCount >= 126 && gameState == GameState::HighScore_Flash) gameState = GameState::HighScore_NoFlash;
    highScoreVars.decSpinIndex();

}
