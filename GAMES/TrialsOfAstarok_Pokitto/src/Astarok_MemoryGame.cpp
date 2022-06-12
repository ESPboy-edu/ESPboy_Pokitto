#include "Astarok.h"

void Game::memoryGame_Init() {

    memoryGameVars.reset();
    
    gameState = GameState::MemoryGame;

}

void Game::memoryGame() {


    // Controls

    if (!memoryGameVars.isTileSpinning() && memoryGameVars.flashCounter == 0) {

        if (PC::buttons.pressed(BTN_LEFT) && memoryGameVars.cursor.x > 0) {
            memoryGameVars.cursor.x--;
        }

        if (PC::buttons.pressed(BTN_RIGHT) && memoryGameVars.cursor.x < 5) {
            memoryGameVars.cursor.x++;
        }

        if (PC::buttons.pressed(BTN_UP) && memoryGameVars.cursor.y > 0) {
            memoryGameVars.cursor.y--;
        }

        if (PC::buttons.pressed(BTN_DOWN) && memoryGameVars.cursor.y < 2) {
            memoryGameVars.cursor.y++;
        }

        if (PC::buttons.pressed(BTN_A)) {

            if (memoryGameVars.status[memoryGameVars.cursor.x + (memoryGameVars.cursor.y * 6)] == MemoryGameStatus::Hide) {

                memoryGameVars.spinIndex[memoryGameVars.cursor.x + (memoryGameVars.cursor.y * 6)] = 16;
                
                if (memoryGameVars.selections[0] == 255) {
                    memoryGameVars.selections[0] = memoryGameVars.cursor.x + (memoryGameVars.cursor.y * 6);
                }
                else{
                    memoryGameVars.selections[1] = memoryGameVars.cursor.x + (memoryGameVars.cursor.y * 6);
                }

            }

        }

    }


    if (memoryGameVars.flashCounter == 0 && !memoryGameVars.isTileSpinning()) {

        if (memoryGameVars.selections[1] != 255) {

            memoryGameVars.status[memoryGameVars.selections[0]] = MemoryGameStatus::FlashRune;
            memoryGameVars.status[memoryGameVars.selections[1]] = MemoryGameStatus::FlashRune;

            if (memoryGameVars.runes[memoryGameVars.selections[0]] == memoryGameVars.runes[memoryGameVars.selections[1]]) {

                memoryGameVars.flashCounter = 120;

                game.score = game.score + Constants::Points_Match;
                sounds.playSoundEffect(Sounds::Effects::PickUpCoin, cookie->sfx);

            }
            else {

                memoryGameVars.flashCounter = 72;
                sounds.playSoundEffect(Sounds::Effects::Fail, cookie->sfx);

            }

        }

    }

    PD::drawBitmap(8, 11, Images::Intro_Brick_00);
    PD::drawBitmap(89, 11, Images::Intro_Brick_01);

    PD::drawBitmap(26, 11, Images::Torch[Utils::getFrameCount(16) / 4]);
    PD::drawBitmap(76, 11, Images::Torch[Utils::getFrameCount(16) / 4]);

    
    PD::drawBitmap(38, 0, Images::MemoryGame);

    if (PC::frameCount % 128 < 2) {

        PD::drawBitmap(47, 9, Images::MemoryGame_Blink);

    }

    PD::drawBitmap(8, 30, Images::EnterRunes_00);
    PD::drawBitmap(8, 76, Images::EnterRunes_02);
    PD::drawBitmap(95, 30, Images::EnterRunes_01);
    PD::drawBitmap(95, 76, Images::EnterRunes_03);

    PD::setColor(0xf8);
    PD::drawFastHLine(14, 30, 81);
    PD::drawFastHLine(14, 83, 81);


    for (uint8_t y = 0; y < 3; y++) {

        for (uint8_t x = 0; x < 6; x++) {

            if (memoryGameVars.status[x + (y * 6)] < MemoryGameStatus::FlashRune || ((memoryGameVars.status[x + (y * 6)] == MemoryGameStatus::FlashRune) && (memoryGameVars.flashCounter % 32 >= 16))) {


                if (memoryGameVars.spinIndex[x + (y * 6)] > 0) {
                    PD::drawBitmap(14 + (x * 14), 34 + (y * 16), Images::Rune_Frame[16 - memoryGameVars.spinIndex[x + (y * 6)]]);
                }
                else {
                    PD::drawBitmap(14 + (x * 14), 34 + (y * 16), Images::Rune_Frame_00);

                    if (memoryGameVars.status[x + (y * 6)] != MemoryGameStatus::Hide) {
                        PD::drawBitmap(17 + (x * 14), 38 + (y * 16), Images::Runes[memoryGameVars.runes[x + (y * 6)]]);
                    }

                }

            }

        }


    }

    if (!memoryGameVars.isTileSpinning() && memoryGameVars.flashCounter == 0) {
        PD::drawBitmap(18 + (memoryGameVars.cursor.x * 14), 42 + (memoryGameVars.cursor.y * 16), Images::Cursor);
    }



    // Render HUD

    uint8_t digits[5] = {};
    int16_t tmpScore = game.score + game.player.x / Constants::TileSize; 
    Utils::extractDigits(digits, static_cast<uint16_t>(tmpScore));

    for (uint8_t x = 5; x > 0; x--) {
        PD::drawBitmap(((5 - x) * 5), 1, Images::Numbers[digits[x - 1]]);
    }


    if (memoryGameVars.moves >= 3) { PD::drawBitmap(89, 1, Images::Moves_Empty); }  else { PD::drawBitmap(89, 1, Images::Moves_Full); }
    if (memoryGameVars.moves >= 2) { PD::drawBitmap(96, 1, Images::Moves_Empty); }  else { PD::drawBitmap(96, 1, Images::Moves_Full); }
    if (memoryGameVars.moves >= 1) { PD::drawBitmap(103, 1, Images::Moves_Empty); } else { PD::drawBitmap(103, 1, Images::Moves_Full); }


    // Housekeeping ..

    memoryGameVars.decSpinIndex();

    if (memoryGameVars.isGameOver()) {

        gameState = GameState::Game_Play;
        game.chestObj->deactivate(true);

    }

}

