#include "Invader.h"
#include "sounds/Sounds.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::gameOver_Init() {

    this->gameVars.gameState = GameState::GameOver;
    gameOverScreenVars.reset();

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:
            gameOverScreenVars.counter = 130;
            break;

        case GameRotation::Landscape:
            gameOverScreenVars.counter = -20;
            break;

    }

    uint16_t oldScore = this->cookie->getScore(this->cookie->gameMode);
    uint16_t score = (this->cookie->gameMode == GameMode::Single ? player1.getScore() : player1.getScore() > player2.getScore() ? player1.getScore() : player2.getScore());

    if (score > 80) {

        if (this->cookie->getLevel(0) == 0) {

            this->cookie->saveLevel(0, 1);

        }
        else if (score > 160) {

            if (this->cookie->getLevel(1) == 0) {

                this->cookie->saveLevel(1, 1);
                
            }

        }

    }


    if (this->cookie->gameMode == GameMode::Double) {

        gameOverScreenVars.flashPlayer1 = player1.getScore() > player2.getScore();
        gameOverScreenVars.flashPlayer2 = player2.getScore() > player1.getScore();
        
    }
    
    if (oldScore < score) {

        if (this->cookie->gameMode == GameMode::Single) {
            gameOverScreenVars.flashPlayer1 = true;
        }

        gameOverScreenVars.newHighScore = true;
        this->cookie->saveScore(this->cookie->gameMode, score);

    }

    #ifdef SOUNDS
        playTheme(Theme::Game_Over);
    #endif

}   


void Game::gameOver() {


    // Move mothership ..

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            if (gameOverScreenVars.counter > 58) {

                gameOverScreenVars.counter--;

            }

            break;

        case GameRotation::Landscape:

            if (gameOverScreenVars.counter < 4) {

                gameOverScreenVars.counter++;

            }

            break;

    }


    // Handle User Input -----------------------------------------------------

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameVars.gameState = GameState::Title_Init;

    }


    // Render screen ---------------------------------------------------------------------

    renderScores(gameOverScreenVars.flashPlayer1, gameOverScreenVars.flashPlayer2);
    renderScenery(this->cookie->gameMode, true);
    renderStars(this->cookie->gameMode, this->cookie->gameRotation);

    uint8_t frame = (PC::frameCount % 12) < 6 ? 0 : 1;

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            PD::drawBitmap(gameOverScreenVars.counter, 21, Images::Portrait::MOTHERSHIP_SIZE_PORTRAIT::Mothership_Title[frame]);

            if (gameOverScreenVars.counter == 58) {

                PD::drawBitmap(38, 29, Images::Portrait::GameOver);
                
                if (!gameOverScreenVars.newHighScore || ((PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2))) {
                    renderHighScore(this->cookie->gameMode, false);
                }

            }
            break;

        case GameRotation::Landscape:

            PD::drawBitmap(32, gameOverScreenVars.counter, Images::Landscape::MOTHERSHIP_SIZE_LANDSCAPE::Mothership_Title[frame]);

            if (gameOverScreenVars.counter == 4) {

                PD::drawBitmap(23, 38, Images::Landscape::GameOver);
                
                if (!gameOverScreenVars.newHighScore || (PC::frameCount % Constants::FlashSpeed) < (Constants::FlashSpeed / 2)) {
                    renderHighScore(this->cookie->gameMode, true);
                }

            }
            break;

    }

}
