#include "Pokitto.h"
#include "Game.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;



void Game::win_Init() {

    const uint8_t delay[] = { 10, 25, 45, 65, 80, 105 };

    for (uint8_t i = 0; i < 6; i++) {

        this->winScreenVars.runeEOG[i].delay = delay[i];
        this->winScreenVars.runeEOG[i].index = 0;

        if (i % 2 == 0) {
            this->winScreenVars.runeEOG[i].x = 46;
            this->winScreenVars.runeEOG[i].direction = Direction::Left;
        }
        else {
            this->winScreenVars.runeEOG[i].x = 38;
            this->winScreenVars.runeEOG[i].direction = Direction::Right;
        }

    }

    this->winScreenVars.counter = 235;
    this->winScreenVars.yPos = 90;
    this->winScreenVars.mode = WinScreenMode::ShowAnim;
    
    this->gameState = GameState::WinState;


    // Start win theme ..

    this->playTheme(SoundTheme::EOG, true);

}

void Game::win() {

    const uint8_t coordsY[] = { 94, 86, 80, 74, 68, 62, 56, 48, 
                                42, 37, 32, 28, 24, 20, 17, 14, 
                                11,  9,  7,  6,  5,  5,  4,  4, 
                                 3,  3,  3,  3,  4,  4,  5,  5, 
                                 6,  7,  9, 11, 14, 17, 20, 24, 
                                28, 32, 37, 43, 48, 56, 62, 68, 
                                72, 67, 62, 57, 53, 49, 45, 42, 
                                39, 36, 33, 31, 29, 28, 27, 27, 
                                26, 26, 26, 26, 27, 27, 28, 29, 
                                31, 33, 36, 39, 42, 45, 49, 53,
                                47, 62, 67, 72, 69, 66, 63, 61,
                                59, 57, 55, 54, 53, 53, 52, 52,
                                53, 53, 54, 55, 57, 59, 61, 63,
                                66, 69, 72, 69, 66, 63, 61, 59 };


    switch (this->winScreenVars.mode) {

        case WinScreenMode::ShowAnim:
            {
                    
                for (uint8_t x = 0; x < 6; x++) {

                    auto &rune = this->winScreenVars.runeEOG[x];

                    if (rune.delay > 0) {

                        rune.delay--;

                    }
                    else {
                        
                        if (rune.index < 109){//75) {
                            if (rune.index % 3 <= 1)
                            rune.x = rune.x + (rune.direction == Direction::Left ? -1 : 1);
                            rune.index++;
                        }

                    }

                }

                PD::drawBitmap(0, 36, Images::WallBackground_Ending);
                PD::drawBitmapXFlipped(110 - 34, 36, Images::WallBackground_Ending);
                this->drawPlayer(21,2);


                if (PC::frameCount % 128 <= 1) {
                    PD::drawBitmap(42, 32, Images::Eyes_Closed);
                }
                else {
                    PD::drawBitmap(42, 32, Images::Eyes_Open);
                }

                for (uint8_t x = 0; x < 6; x++) {

                    auto &rune = this->winScreenVars.runeEOG[x];

                    if (rune.index < 20) {

                        PD::drawBitmap(rune.x, coordsY[rune.index], Images::LargeRunes[x]);

                    }

                }

                PD::drawBitmap(0, 78, Images::OpenBook);
                PD::drawBitmapXFlipped(110 - 56, 78, Images::OpenBook);

                for (uint8_t x = 0; x < 6; x++) {

                    auto &rune = this->winScreenVars.runeEOG[x];

                    if (rune.index >= 20) {

                        PD::drawBitmap(rune.x, coordsY[rune.index], Images::LargeRunes[x]);

                    }

                }

            }

            this->winScreenVars.counter--;
            if (this->winScreenVars.counter == 0 || PC::buttons.pressed(BTN_A)) { 
                this->winScreenVars.counter = 1250;
                this->winScreenVars.mode = WinScreenMode::ShowMessage;
            }
                
            break;

        case WinScreenMode::ShowMessage:

            if (PC::frameCount % 4 == 0) {
                this->winScreenVars.yPos--;
            }

            PD::setColor(6, 0);
            if (this->winScreenVars.yPos > -100) {
                PD::setCursor(6, this->winScreenVars.yPos);
                PD::print("Congratulations!"); 
                PD::setCursor(6, this->winScreenVars.yPos + 15);
                PD::print("You have scoured"); 
                PD::setCursor(2, this->winScreenVars.yPos + 24);
                PD::print("the corners of the"); 
                PD::setCursor(10, this->winScreenVars.yPos + 33);
                PD::print("underworld and "); 
                PD::setCursor(3, this->winScreenVars.yPos + 42);
                PD::print("fought for the six"); 
                PD::setCursor(17, this->winScreenVars.yPos + 51);
                PD::print("sacred runes. "); 
            }

            PD::setCursor(8, this->winScreenVars.yPos + 66);
            PD::print("Presenting them"); 
            PD::setCursor(8, this->winScreenVars.yPos + 75);
            PD::print("at the altar has"); 
            PD::setCursor(7, this->winScreenVars.yPos + 84);
            PD::print("freed your soul - "); 
            PD::setCursor(12, this->winScreenVars.yPos + 93);
            PD::print("you are able to"); 
            PD::setCursor(11, this->winScreenVars.yPos + 102);
            PD::print("return back to"); 
            PD::setCursor(6, this->winScreenVars.yPos + 111);
            PD::print("the world of the "); 
            PD::setCursor(37, this->winScreenVars.yPos + 120);
            PD::print("living."); 
            PD::setCursor(4, this->winScreenVars.yPos + 145);
            PD::print("Dark Ritual - 2020"); 
            PD::setCursor(28, this->winScreenVars.yPos + 159);
            PD::print("Vampirics"); 
            PD::setCursor(32, this->winScreenVars.yPos + 168);
            PD::print("Filmote"); 

            if (this->winScreenVars.yPos < 0) {
                PD::setCursor(17, this->winScreenVars.yPos + 177);
                PD::print("Dreamer2345"); 
                PD::setCursor(10, this->winScreenVars.yPos + 186);
                PD::print("RafaeleSpindola"); 
                PD::setCursor(12, this->winScreenVars.yPos + 195);
                PD::print("Tuxinator2009"); 
                PD::setCursor(12, this->winScreenVars.yPos + 215);
                PD::print("For a challenge"); 
                PD::setCursor(9, this->winScreenVars.yPos + 224);
                PD::print("press and hold 'C'"); 
                PD::setCursor(12, this->winScreenVars.yPos + 233);
                PD::print("when starting a"); 
                PD::setCursor(28, this->winScreenVars.yPos + 242);
                PD::print("new game."); 
            }

            PD::setColor(0, 0);
            PD::fillRect(0, 0, 110, 7);
            PD::drawBitmap(0, 78, Images::OpenBook);
            PD::drawBitmapXFlipped(110 - 56, 78, Images::OpenBook);

            this->winScreenVars.counter--;
            if (this->winScreenVars.counter == 0 || PC::buttons.pressed(BTN_A)) { 
                this->winScreenVars.counter = 300;
                this->winScreenVars.mode = WinScreenMode::Score;
            }
            break;

        case WinScreenMode::Score:
            {
                this->renderEnvironment(!this->map.isBossLevel() && !this->map.isAltarLevel(), 0, 0);
                this->renderHud();
                this->renderLevelSplash();
    
                uint32_t pts = this->printLevelSummary(19, this->map.getTimer()/10);

                if ((PC::frameCount % 800 == 0) || (PC::buttons.pressed(BTN_A))) {  
    
                    this->highScoreOrNot(pts);
                    //sound.noTone(); 
                    gameState = GameState::HighScore; 
    
                }
    
                PD::setColor(0, 0);
            }
            break;

    }

}

void Game::endOfLevel() {

    PD::setColor(15);
    this->renderEnvironment(!this->map.isBossLevel() && !this->map.isAltarLevel(), 0, 0);
    this->renderHud();
    this->renderLevelSplash();

    uint32_t pts = this->printLevelSummary(19, this->map.getTimer()/10);

    if ((PC::frameCount % 800 == 0) || (PC::buttons.pressed(BTN_A))) {  

        if (this->map.getRandomLevel()) { this->map.setRandomLevelIndex(this->map.getRandomLevelIndex() + 1); }
        gameState = GameState::LoadMap;
        this->points += pts;
        
    }

    PD::setColor(0, 0);

}
