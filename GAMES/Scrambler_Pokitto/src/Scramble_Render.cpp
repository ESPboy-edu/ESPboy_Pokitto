#include "Scramble.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::renderScenery() {

    PD::setColor(5);
    PD::drawFastHLine(0, 10, 220);

    for (uint8_t i = 0; i < 220; i++) {

        // Top 

        if (this->gameScreenVars.scenery.top[i] > this->gameScreenVars.viewY + 14 && (this->gameScreenVars.scenery.top[i] <= this->gameScreenVars.viewY + Constants::Screen_Height)) {

            PD::setColor(15);
            PD::drawFastVLine(i, 14, this->gameScreenVars.scenery.top[i] - this->gameScreenVars.viewY - 14);
            PD::setColor(3);
            PD::drawFastVLine(i, this->gameScreenVars.scenery.top[i] - this->gameScreenVars.viewY - 1, 1);

        }


        // Bottom

        if (this->gameScreenVars.scenery.top[i] + this->gameScreenVars.scenery.bot[i] <= this->gameScreenVars.viewY + Constants::Screen_Height - 14) {

            uint16_t bottom = this->gameScreenVars.scenery.top[i] + this->gameScreenVars.scenery.bot[i] - this->gameScreenVars.viewY;

            PD::setColor(15);
            PD::drawFastVLine(i, bottom, Constants::Screen_Height - 14 - bottom);
            PD::setColor(3);
            PD::drawFastVLine(i, bottom, 1);

        }

    }

}

void Game::renderHUD() {

    PD::drawBitmap(0, 0, Images::HUD);

    PD::drawBitmap(105, 3, Images::Lives[this->player.getLives() > 0]);
    PD::drawBitmap(118, 3, Images::Lives[this->player.getLives() > 1]);
    PD::drawBitmap(131, 3, Images::Lives[this->player.getLives() > 2]);


    // Rneder fuel left ..
    
    {
        const uint8_t colors[] = { 8, 8, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };

        for (uint8_t i = 0; i < (this->player.getFuel() * 3) / 10; i = i + 3) {

            if (i <= (this->player.getFuel() * 3) / 10) {

                if (this->player.getFuel() > 30 || PC::frameCount % 64 < 32) { 

                    PD::setColor(colors[i / 3]);

                }

            }

            PD::fillRect(31 + i, 3, 2, 7);

        }
    
    }


    // Render score ..
    {
        uint8_t digits[6] = {};
        extractDigits(digits, this->gameScreenVars.score);

        uint8_t location = 197;

        for (uint8_t j = 0; j < 6; ++j, location -= 6) {

            PD::drawBitmap(location, 3, Images::Numbers[digits[j]]);

        }

    }


    PD::drawBitmap(0, 160, Images::HUD_Bottom);


    // Render stages ..
    {
        uint8_t digits[3] = {};
        extractDigits(digits, this->gameScreenVars.stage);

        uint8_t location = 194;

        for (uint8_t j = 0; j < 3; ++j, location -= 6) {

            PD::drawBitmap(location, 165, Images::Numbers[digits[j]]);

        }

    }


    // Rneder stage progress left ..

    for (uint8_t i = 0; i < 93; i = i + 3) {

        if (this->gameScreenVars.stageCount * 3 < i) {

            PD::setColor(5);

        }
        else {

            switch (i / 3) {

                case 0 ... 5: 
                case 11 ... 15: 
                case 21 ... 25: 
                    // PD::setColor(12);
                    PD::setColor(13);
                    break;

                case 6 ... 10: 
                case 16 ... 20: 
                case 26 ... 31: 
                    // PD::setColor(8);
                    PD::setColor(6);
                    break;

            }

        }

        PD::fillRect(50 + i, 165, 2, 7);

    }

}


void Game::renderEnemies() {

    for (uint8_t i = 0; i < Constants::Enemy_Count; i++) {

        Enemy &enemy = this->enemies.enemies[i];

        if (enemy.getActive()) {

            if (enemy.getX() >= this->gameScreenVars.distance - Constants::Enemy_Max_Width && enemy.getX() < this->gameScreenVars.distance + 220) {

                switch (enemy.getEnemyType()) {

                    case EnemyType::Rocket:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::Rocket);

                        if (enemy.getInFlight()) {
                            PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance + 3, enemy.getY() - this->gameScreenVars.viewY + 16, Images::Flame[PC::frameCount % 16 / 4]);
                        }
                        break;

                    case EnemyType::FuelDepot:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::FuelDepot);
                        break;

                    case EnemyType::GroundPod:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::GroundPod);
                        break;

                    case EnemyType::SurfaceAir:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::SurfaceToAir[static_cast<uint8_t>(enemy.getDirection())]);
                        break;

                    case EnemyType::Mine:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::Mine);
                        break;

                    case EnemyType::City_00:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::City_00);
                        break;

                    case EnemyType::City_01:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::City_01);
                        break;

                    case EnemyType::City_02:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::City_02);
                        break;

                    case EnemyType::FuelCan:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::FuelCan);
                        break;

                    case EnemyType::Eighter:
                    case EnemyType::Circler:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::Eighter[PC::frameCount % 32 / 8]);
                        break;
                        

                }

            }

        }

    }

}


void Game::renderPlayerBullets() {


    // Render player bullets ..
    
    for (Bullet &bullet : bullets.bullets) {
                                
        if (bullet.getActive()) {
                
            if (bullet.getMuzzleIndex() > 1) {

                PD::drawBitmap(bullet.getX() - this->gameScreenVars.distance, bullet.getY() - this->gameScreenVars.viewY, Images::Muzzle[3 - (bullet.getMuzzleIndex() / 2)]);

            }
            else {

                PD::drawBitmap(bullet.getX() - this->gameScreenVars.distance, bullet.getY() - this->gameScreenVars.viewY, Images::Bullet);

            }

        }

    }

}


void Game::renderPlayerBombs() {


    // Render player bombs ..
    
    for (Bullet &bomb : bullets.bombs) {
                                
        if (bomb.getActive()) {
                
            if (bomb.getMuzzleIndex() > 1) {

                PD::drawBitmap(bomb.getX() - this->gameScreenVars.distance, bomb.getY() - this->gameScreenVars.viewY, Images::Muzzle[3 - (bomb.getMuzzleIndex() / 2)]);

            }
            else {

                PD::drawBitmap(bomb.getX() - this->gameScreenVars.distance, bomb.getY() - this->gameScreenVars.viewY, Images::Bomb);

            }

        }

    }

}


void Game::renderEnemyBullets() {


    // Render enemy bullets ..
    
    for (Bullet &bullet : bullets.enemyBullets) {
                                
        if (bullet.getActive()) {
                
            if (bullet.getMuzzleIndex() > 1) {

                PD::drawBitmap(bullet.getX() - this->gameScreenVars.distance - 2, bullet.getY() - this->gameScreenVars.viewY - 2, Images::Muzzle[3 - (bullet.getMuzzleIndex() / 2)]);

            }
            else {

                PD::drawBitmap(bullet.getX() - this->gameScreenVars.distance, bullet.getY() - this->gameScreenVars.viewY, Images::EnemyBullet);

            }

        }

    }

}


void Game::renderStars(bool incOffset) {

    const uint8_t colors[] = {1, 5, 6 };

    // Render enemy bullets ..
    
    for (uint8_t i = 0; i < Constants::Star_Count; i++) {

        Star &star = this->stars.stars[i];

        if ((PC::frameCount + i) % 8 > 1) {

            PD::setColor(colors[i % 3]);
            PD::drawPixel(star.getX(), star.getY() - (incOffset ? this->gameScreenVars.viewY : 0));

        }

    }

}

void Game::renderGameOver() {


    // Increase underline ..

    if (this->gameScreenVars.gameOver_Counter < 87) {
        this->gameScreenVars.gameOver_Counter = this->gameScreenVars.gameOver_Counter + 4;
    }

    if (this->gameScreenVars.gameOver_Counter > 4) {

        for (uint16_t i = 110 - 2 - this->gameScreenVars.gameOver_Counter; i < 110 + this->gameScreenVars.gameOver_Counter; i = i + 3) {
            PD::drawBitmap(i, 93, Images::Title_Mid);
        }

    }

    PD::drawBitmap(110 - 4 - this->gameScreenVars.gameOver_Counter, 93, Images::Title_Left);
    PD::drawBitmap(110 + this->gameScreenVars.gameOver_Counter, 93, Images::Title_Right);

    for (uint8_t i = 0; i < 8; i++) {

        PD::drawBitmap(this->gameScreenVars.gameOver_CharsX[i] + 22, this->gameScreenVars.gameOver_CharsY[i] + 5, Images::TitleLetters[this->gameScreenVars.gameOver_CharsIdx[i]]);

    }

    this->gameScreenVars.incGameOverLetters();
    
}

void Game::renderStageComplete() {



    // Render stage complete ..

    if (this->gameScreenVars.stageTransition > 0) {

    //printf("(stageTransition %i, stageCompT %i, stageLineCounter %i) \n", this->gameScreenVars.stageTransition, this->gameScreenVars.stageCompT, this->gameScreenVars.stageLineCounter);


        switch (static_cast<uint16_t>(TransitionMode::Sequence_End) - this->gameScreenVars.stageTransition) {

            case static_cast<uint16_t>(TransitionMode::LineEntry_Start) ... static_cast<uint16_t>(TransitionMode::LineEntry_End):
                this->gameScreenVars.stageLineCounter = this->gameScreenVars.stageLineCounter + 4;
                break;

            case static_cast<uint16_t>(TransitionMode::TextEntry_Start) ... static_cast<uint16_t>(TransitionMode::TextEntry_End):
                this->gameScreenVars.stageCompT = this->gameScreenVars.stageCompT + 4;
                break;

            case static_cast<uint16_t>(TransitionMode::TextExit_Start) ... static_cast<uint16_t>(TransitionMode::TextExit_End):
                this->gameScreenVars.stageCompT = this->gameScreenVars.stageCompT + 4;
                break;

            case static_cast<uint16_t>(TransitionMode::LineExit_Start) ... static_cast<uint16_t>(TransitionMode::LineExit_End) - 2:
                this->gameScreenVars.stageLineCounter = this->gameScreenVars.stageLineCounter - 4;
                break;

            case static_cast<uint16_t>(TransitionMode::LineExit_End) - 1 ... static_cast<uint16_t>(TransitionMode::LineExit_End):
                this->gameScreenVars.stageLineCounter = this->gameScreenVars.stageLineCounter - 4;
                this->gameScreenVars.resetAnimation(GameState::Game);
                this->gameScreenVars.stage++;
                this->gameScreenVars.stageCount = 31;
                break;

            default:
                break;

        }


        // Stage Complete underline ..

        if (static_cast<uint16_t>(TransitionMode::Sequence_End) - this->gameScreenVars.stageTransition >= static_cast<uint16_t>(TransitionMode::LineEntry_Start) &
            static_cast<uint16_t>(TransitionMode::Sequence_End) - this->gameScreenVars.stageTransition <= static_cast<uint16_t>(TransitionMode::LineExit_End)) {

            if (this->gameScreenVars.stageLineCounter > 4) {

                for (uint16_t i = 110 - 2 - this->gameScreenVars.stageLineCounter; i < 110 + this->gameScreenVars.stageLineCounter; i = i + 3) {
                    PD::drawBitmap(i, 86, Images::Title_Mid);
                }

            }

            PD::drawBitmap(110 - 4 - this->gameScreenVars.stageLineCounter, 86, Images::Title_Left);
            PD::drawBitmap(110 + this->gameScreenVars.stageLineCounter, 86, Images::Title_Right);

        }


        // Stage

        int16_t x = this->gameScreenVars.stageCompT;
        
        for (uint8_t i = 0; i < 5; i++) {

            x = x + this->gameScreenVars.stageCompT_CharsX[i];
            PD::drawBitmap(x, 56, Images::TitleLetters[this->gameScreenVars.stageCompT_CharsIdx[i]]);

        }

        // Complete

        x = 86 - this->gameScreenVars.stageCompT;
        
        for (uint8_t i = 0; i < 8; i++) {

            x = x + this->gameScreenVars.stageCompB_CharsX[i];
            PD::drawBitmap(x, 96, Images::TitleLetters[this->gameScreenVars.stageCompB_CharsIdx[i]]);

        }

    }

}

void Game::renderStageStart() {



    // Render stage start ..

    if (this->gameScreenVars.stageTransition > 0) {

    //printf("(stageTransition %i, stageCompT %i, stageLineCounter %i) \n", this->gameScreenVars.stageTransition, this->gameScreenVars.stageCompT, this->gameScreenVars.stageLineCounter);


        switch (static_cast<uint16_t>(GameStartMode::Sequence_End) - this->gameScreenVars.stageTransition) {

            case static_cast<uint16_t>(GameStartMode::LineEntry_Start) ... static_cast<uint16_t>(GameStartMode::LineEntry_End):
                this->gameScreenVars.stageLineCounter = this->gameScreenVars.stageLineCounter + 4;
                break;

            case static_cast<uint16_t>(GameStartMode::TextEntry_Start) ... static_cast<uint16_t>(GameStartMode::TextEntry_End):
                this->gameScreenVars.stageCompT = this->gameScreenVars.stageCompT + 4;
                break;

            case static_cast<uint16_t>(GameStartMode::TextExit_Start) ... static_cast<uint16_t>(GameStartMode::TextExit_End):
                this->gameScreenVars.stageCompT = this->gameScreenVars.stageCompT + 4;
                break;

            case static_cast<uint16_t>(GameStartMode::LineExit_Start) ... static_cast<uint16_t>(GameStartMode::LineExit_End) - 2:
                this->gameScreenVars.stageLineCounter = this->gameScreenVars.stageLineCounter - 4;
                break;

            case static_cast<uint16_t>(GameStartMode::LineExit_End) - 1 ... static_cast<uint16_t>(GameStartMode::LineExit_End):
                this->gameScreenVars.stageLineCounter = this->gameScreenVars.stageLineCounter - 4;
                this->gameScreenVars.resetAnimation(GameState::Game);
                this->gameScreenVars.stageCount = 31;
                break;

            default:
                break;

        }


        // Stage Complete underline ..

        if (static_cast<uint16_t>(GameStartMode::Sequence_End) - this->gameScreenVars.stageTransition >= static_cast<uint16_t>(GameStartMode::LineEntry_Start) &
            static_cast<uint16_t>(GameStartMode::Sequence_End) - this->gameScreenVars.stageTransition <= static_cast<uint16_t>(GameStartMode::LineExit_End)) {

            if (this->gameScreenVars.stageLineCounter > 4) {

                for (uint16_t i = 110 - 2 - this->gameScreenVars.stageLineCounter; i < 110 + this->gameScreenVars.stageLineCounter; i = i + 3) {
                    PD::drawBitmap(i, 86, Images::Title_Mid);
                }

            }

            PD::drawBitmap(110 - 4 - this->gameScreenVars.stageLineCounter, 86, Images::Title_Left);
            PD::drawBitmap(110 + this->gameScreenVars.stageLineCounter, 86, Images::Title_Right);

        }


        // Start

        if (this->gameScreenVars.stageTransition > 54) {
                
            int16_t x = this->gameScreenVars.stageCompT - 1;
            
            for (uint8_t i = 0; i < 5; i++) {

                x = x + this->gameScreenVars.startGameT_CharsX[i] + 3;
                PD::drawBitmap(x, 56, Images::TitleLetters[this->gameScreenVars.startGameT_CharsIdx[i]]);

            }

            // Scramabling

            x = 73 - this->gameScreenVars.stageCompT;
            
            for (uint8_t i = 0; i < 10; i++) {

                x = x + this->gameScreenVars.startGameB_CharsX[i];
                PD::drawBitmap(x, 96, Images::TitleLetters[this->gameScreenVars.startGameB_CharsIdx[i]]);

            }

        }

    }
    else {

        this->gameState = GameState::Game;

    }

}