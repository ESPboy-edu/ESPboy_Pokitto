#include "Invader.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::setup(GameCookie *cookie) {

    this->cookie = cookie;
    this->gameVars.cookie = cookie;

}

void Game::loop() {

    PD::clear();
    PC::buttons.pollButtons();

    switch (this->gameVars.gameState) {

        case GameState::Splash_Init:
            splashScreen_Init();
            splashScreen();
            break;

        case GameState::Splash:
            splashScreen();
            break;

        case GameState::Title_Init:
            title_Init();
            title();
            break;

        case GameState::Title:
            title();
            break;


        case GameState::Game_Init:

            game_Init();
            game();
            break;

        case GameState::Game:

            game();
            break;

        case GameState::TugOfWar_Init:

            tugOfWar_Init();
            tugOfWar();
            break;

        case GameState::TugOfWar:

            tugOfWar();
            break;
            
        case GameState::GameOver_Init:

            gameOver_Init();
            gameOver();
            break;

        case GameState::GameOver:

            gameOver();
            break;

    }

}

