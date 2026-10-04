
#include "Pokitto.h"
#include "Game.h"
#include "utils/Consts.h"
#include "images/Images.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::resetGame() {
    
    if (currentScore > highScore) highScore = currentScore;
    currentScore = 0;

    for (uint8_t row = 0; row < BOARD_HEIGHT; row++) {
        for (uint8_t col = 0; col < BOARD_WIDTH; col++) {
            gameBoard[col][row] = BoardType::None;
            gameBoard_Frames[col][row] = 0;
        }
    }

    gameState = GameState::Play;

    this->launchBlocks[2] = this->getRandomBoardType(this->level, 0);
    this->launchBlocks[3] = this->getRandomBoardType(this->level, 0);
    this->launchBlocks[4] = this->getRandomBoardType(this->level, 0);

    this->launchBlocks_Frames[2] = random(4);
    this->launchBlocks_Frames[3] = random(4);
    this->launchBlocks_Frames[4] = random(4);

    launchNewColumn();

    this->gameSpeed = 28;
    this->scoringRowCount = 0;
    this->highScore = this->cookie->score[static_cast<uint8_t>(this->level)][0];



    // this->currentScore = 4000;
    // //fill er up!
    // for (uint8_t row = 7; row < BOARD_HEIGHT; row++) {
    //     for (uint8_t col = 0; col < BOARD_WIDTH; col++) {
    //         gameBoard[col][row] = (BoardType)(((row % 2) + col) % 2 == 0 ? 0 : 1);
    //     }
    // }

// gameBoard[0][14] = BoardType::Existing_Green;
// gameBoard[1][14] = BoardType::Existing_Green;


    // this->launchBlocks[0] = BoardType::New_Green;
    // this->launchBlocks[1] = BoardType::New_Green;
    // this->launchBlocks[2] = BoardType::New_Green;
    // this->launchBlocks[3] = BoardType::New_Green;
    // this->launchBlocks[4] = BoardType::New_Green;



}


void Game::doGameEnd() {

    drawScore(false, false);
    drawFrame();
    drawBoard();


    PD::drawBitmap(23, 34, Images::GameOver);

    if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {
        this->gameState = GameState::HighScore_Init;
        cookie->setLastScore(this->level, this->currentScore);
    }

}
