#include "Pokitto.h"
#include "Game.h"
#include "images/Images.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::setup(GameCookie *cookie) {

	this->cookie = cookie;

}


void Game::loop(){

    

    PD::clear();
    PC::buttons.pollButtons();




    // == Camera Shake Department ===

    if (this->shake.count > 0) {

        this->shake.count--;

        switch (this->shake.explosionSize) {

            case ExplosionSize::Small:
                this->shake.yOffset = random(-1, 2);
                this->shake.xOffset = 0;
                break;

            case ExplosionSize::Medium:
                this->shake.yOffset = random(-1, 2);
                this->shake.xOffset = random(-1, 2);
                break;

            case ExplosionSize::Large:
                this->shake.xOffset = random(-2, 3);
                this->shake.yOffset = random(-2, 3);
                break;

        }

    }
    else {

        this->shake.explosionSize = ExplosionSize::None;
        this->shake.yOffset = 0;
        this->shake.xOffset = 0;

    }



    // Game state ..

    switch (this->gameState) {

        case GameState::SplashScreen:

            this->doSplashScreen(); 
            break;

        case GameState::Title:

            this->doTitle(); 
            break;

        case GameState::Play_Init:
            this->resetGame();
            this->playTheme(this->cookie->track);
            [[fallthrough]]

        case GameState::Play:


            // Update game speed ..

            #define GAME_SPEED_INC_HARD 800
            #define GAME_SPEED_INC_EASY 1600

            if (this->level == Level::Easy) {
                gameSpeed = (currentScore < (GAME_SPEED_INC_EASY * 6) ? 28 - ((currentScore / GAME_SPEED_INC_EASY) * 4) : 4);
            }   
            else {          
                gameSpeed = (currentScore < (GAME_SPEED_INC_HARD * 6) ? 28 - ((currentScore / GAME_SPEED_INC_HARD) * 4) : 4);
            }

            drawDropped();


            if (this->scoringRowCount > 0) {

                this->scoringRowCount--;
                
                switch (this->scoringRowCount) {

                    case 0:
                        {
                            uint8_t col = this->launchNewColumn();

                            if (this->gameBoard[col][1] != BoardType::None) {

                                this->gameBoard[col][0] = this->convertNewToExisting(this->gameBoard[col][0]);
                                partStopped(col, 0);
                                if (this->scoringRowCount!= SCORING_ROW_COUNT_PART_STOPPED) {
                                    this->scoringRowCount = SCORING_ROW_COUNT_SCORING_COMBO;
                                }
                                else {
                                    this->gameState = GameState::End;
                                }

                            }

                        }
                        break;

                    case SCORING_ROW_COUNT_PART_STOPPED:

                        this->clearMarkedBlocks();

                        if (markScoringRows()) {
                            this->scoringRowCount = SCORING_ROW_COUNT_SCORING_COMBO;
                        }
                        break;

                }

            }



            if (!this->moveCycle()) {

                if (cycleCount >= gameSpeed || ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 1) && cycleCount >= 2))) {
                    this->boardCycle();
                    cycleCount = 0;
                } 
                else {
                    cycleCount++;
                }

            }

            this->drawScore(true, false);
            this->drawTrack();
            this->drawFrame();
            this->drawNextColumn();
            this->drawBoard();

            break;

        case GameState::End:
            this->doGameEnd();
            break;

        case GameState::HighScore_Init:
            //Audio::stop();
            this->doHighScore_Init();
            break;

        case GameState::HighScore:
            this->doHighScore();
            break;

        case GameState::Pause_Init:
            this->doPause_Init();
            break;

        case GameState::Pause:
            this->doPause();
            break;

    }

    renderParticles();

}
