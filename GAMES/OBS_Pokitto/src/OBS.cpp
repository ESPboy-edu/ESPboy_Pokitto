#include "OBS.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::setup(GameCookie *cookie) {

    this->cookie = cookie;

}

void Game::loop() {

    PD::clear();
    PC::buttons.pollButtons();

    switch (this->gameState) {

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
        case GameState::Score:

            game();
            break;
            
    }

}

