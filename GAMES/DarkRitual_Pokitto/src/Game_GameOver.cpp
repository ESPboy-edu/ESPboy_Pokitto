#include "Pokitto.h"
#include "Game.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::death() {

    this->renderEnvironment(!this->map.isBossLevel() && !this->map.isAltarLevel(), 0, 0);
    this->renderHud();

    PD::setColor(15);
    PD::fillScreen(15);
    PD::drawBitmap(0, 0, Images::LevelSplash_UpperLeft);
    PD::drawBitmap(0, 16, Images::LevelSplash_Left);
    PD::drawBitmap(10, 0, Images::GameOver);
    PD::drawBitmap(100, 0, Images::LevelSplash_UpperRight);
    PD::drawBitmap(100, 16, Images::LevelSplash_Right);
    PD::drawBitmap(10, 78, Images::LevelSplash_Bottom);
    PD::setColor(4, 15);
    PD::setCursor(14,26);

    uint32_t pts = this->printLevelSummary(34, 0);


    if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {

        this->highScoreOrNot(pts);
        //sound.noTone(); 
        gameState = GameState::HighScore; 

    }

}

uint32_t Game::printLevelSummary(uint8_t yOffset, uint16_t timer) {

    uint32_t padd = player.getCoins() * 5;    
    uint32_t killp = player.getKills() * 10;
    uint32_t cult = player.getCultists() * 20;
    uint32_t pts = padd + killp + + cult + timer;

    PD::setColor(4, 14);
    PD::setCursor(9, yOffset);
    PD::print("Kills");
    PD::drawBitmap(37, yOffset + 1, Images::Colon);
    PD::setCursor(48, yOffset);
    this->printPaddedNumber(player.getKills(), 2);
    PD::setCursor(64, yOffset);
    PD::print("=");
    PD::setCursor(73, yOffset);
    this->printPaddedNumber(killp, 4);

    yOffset = yOffset + 7;

    PD::setCursor(9, yOffset);
    PD::print("Cults");
    PD::drawBitmap(41, yOffset + 1, Images::Colon);
    PD::setCursor(48, yOffset);
    this->printPaddedNumber(player.getCultists(), 2);
    PD::setCursor(64, yOffset);
    PD::print("=");
    PD::setCursor(73, yOffset);
    this->printPaddedNumber(cult, 4);

    yOffset = yOffset + 7;
    
    PD::setCursor(9, yOffset);
    PD::print("Coins");
    PD::drawBitmap(37, yOffset + 1, Images::Colon);
    PD::setCursor(48, yOffset);
    this->printPaddedNumber(player.getCoins(), 2);
    PD::setCursor(64, yOffset);
    PD::print("=");
    PD::setCursor(73, yOffset);
    this->printPaddedNumber(padd, 4);

    yOffset = yOffset + 7;
    
    PD::setCursor(9, yOffset);
    PD::print("Time Bonus");
    PD::drawBitmap(68, yOffset + 1, Images::Colon);
    PD::setCursor(73, yOffset);
    this->printPaddedNumber(timer, 4);

    yOffset = yOffset + 7;
    
    PD::setCursor(9, yOffset);
    PD::print("Level Pts");
    PD::drawBitmap(62, yOffset + 1, Images::Colon);
    PD::setCursor(73, yOffset);
    this->printPaddedNumber(pts, 4);

    yOffset = yOffset + 7;

    PD::setCursor(9, yOffset);
    PD::print("Total Pts");
    PD::drawBitmap(63, yOffset + 1, Images::Colon);
    PD::setCursor(73, yOffset);
    this->printPaddedNumber(this->points + pts, 4);

    return pts;

}

void Game::highScoreOrNot(uint8_t pts) {

    // Work out whether we have a high score or not?

    uint8_t i = 0;
    bool found = false;

    for (i = 0; i < 5; i++) {

        if (this->cookieHighScore->score[i] < this->points + pts) {
            
            found = true;
            break;

        }

    }

    if (found) {

        for (int8_t j = 3; j >= i; j--) {

            this->cookieHighScore->score[j + 1] = this->cookieHighScore->score[j];
            this->cookieHighScore->level[j + 1] = this->cookieHighScore->level[j];
            this->cookieHighScore->score_Char[j + 1][0] = this->cookieHighScore->score_Char[j][0];
            this->cookieHighScore->score_Char[j + 1][1] = this->cookieHighScore->score_Char[j][1];
            this->cookieHighScore->score_Char[j + 1][2] = this->cookieHighScore->score_Char[j][2];

        }

        this->highScoreVariables.charIdx = 0;
        this->highScoreVariables.entryIdx = i;

        this->cookieHighScore->score_Char[i][0] = 'A';
        this->cookieHighScore->score_Char[i][1] = 'A';
        this->cookieHighScore->score_Char[i][2] = 'A';
        this->cookieHighScore->score[i] = static_cast<uint16_t>(this->points + pts);
        this->cookieHighScore->level[i] = static_cast<uint8_t>(map.getLevel());

    }
    else {

        this->highScoreVariables.entryIdx = 255;

    }

}