#include "Astarok.h"

//#include "AstarokGame.h"
#include "images/Images.h"
#include "utils/Constants.h"
#include "utils/Enums.h"
#include "utils/Structs.h"
#include "font/Font4x6.h"
//#include "sounds/Sounds.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

AstarokGame game();
GameState gameState = GameState::SplashScreen_Init;

void Game::setup(GameCookie *cookie) {

    this->cookie = cookie;
    this->game.sounds = &this->sounds;
    this->game.cookie = this->cookie;

    //this->sounds.connectVolumeControl(1);

}

void Game::loop() {

    PC::buttons.pollButtons();

    switch (this->gameState) {

        case GameState::SplashScreen_Init:

            PD::clear();
            splashScreen_Init();
            [[fallthrough]]

        case GameState::SplashScreen:

            PD::clear();
            splashScreen();
            break;

        case GameState::Title_Init:

            sounds.playTheme(2, this->cookie->sfx, true, true);
            PD::clear();
            this->gameState = GameState::Title;
            [[fallthrough]]

        case GameState::Title:

            PD::clear();
            titleScreen();
            break;

        case GameState::IntroText_Init:

            PD::clear();
            introText_Init();
            [[fallthrough]]

        case GameState::IntroText:

            PD::clear();
            introText();
            break;

        case GameState::Seed_Init:

            PD::clear();
            seed_Init();
            [[fallthrough]]

        case GameState::Seed:

            PD::clear();
            seed();
            break;

        case GameState::PlayerSelect_Init:

            PD::clear();
            playerSelect_Init();
            [[fallthrough]]

        case GameState::PlayerSelect:

            PD::clear();
            playerSelect();
            break;

        case GameState::MemoryGame_Init:

            PD::clear();
            memoryGame_Init();
            [[fallthrough]]

        case GameState::MemoryGame:

            PD::clear();
            memoryGame();
            break;

        case GameState::Game_Init:

            PD::clear();
            this->game.newGame();
            this->gameState = GameState::Game_Play;
            sounds.muteTheme();
            [[fallthrough]]

        case GameState::Game_Play:

            if (game.mapNumber % 2) {
                PD::setColor(0xd6);
                PD::fillRect(0, 0, 110, 44);
                PD::setColor(0x07);
                PD::fillRect(0, 44, 110, 44);
            }
            else {
                PD::clear();
            }

            game.cycle(this->gameState);
            game.draw();

            if (game.event == EventType::Death) {
                game.renderTrialOver();
            }

            break;

        case GameState::Game_Mini:

            if (game.mapNumber % 2) {
                PD::setColor(0xd6);
                PD::fillRect(0, 0, 110, 44);
                PD::setColor(0x07);
                PD::fillRect(0, 44, 110, 44);
            }
            else {
                PD::clear();
            }

            game.draw();
            game.playMiniGame(this->gameState);
            break;

        case GameState::Display_Sign:

            if (game.mapNumber % 2) {
                PD::setColor(0xd6);
                PD::fillRect(0, 0, 110, 44);
                PD::setColor(0x07);
                PD::fillRect(0, 44, 110, 44);
            }
            else {
                PD::clear();
            }

            game.draw();
            game.displaySign(this->gameState);
            game.renderSign();
            break;

        case GameState::HighScore_Check:

            PD::clear();
            
            highScoreVars.reset();
            checkHighScoreSlot(game.score + game.player.x / Constants::TileSize);

            if (highScoreVars.slot != Constants::No_Slot) {
                PC::frameCount = 0;
                this->gameState = GameState::HighScore_Flash;
            } 
            else {
                this->gameState = GameState::HighScore_NoFlash;
            }

            highScores();
            break;

        case GameState::HighScore_Flash:
        case GameState::HighScore_NoFlash:

            PD::clear();
            highScores();
            break;

    }

    //sounds.updateFades();

}