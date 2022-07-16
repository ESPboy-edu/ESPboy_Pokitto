#include "Invader.h"
#include "images/Images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title_Init() {

    this->gameVars.gameState = GameState::Title;
    this->titleScreenVars.reset(this->cookie->gameRotation);

    #ifdef SOUNDS
        playTheme(Theme::Main);
    #endif

    this->titleScreenVars.levels = 0;

    for (uint8_t i = 0; i < 3; i++) {
        if (this->cookie->getLevel(i) == 1) this->titleScreenVars.levels++;
    }

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title() {

    renderScenery(GameMode::Single, false);
    renderHighScore(this->cookie->gameMode, false);
    
    if (PC::buttons.pressed(BTN_B)) {

        this->gameVars.gameState = GameState::Title_Init;
        this->cookie->saveRotation(this->cookie->gameRotation == GameRotation::Landscape ? GameRotation::Portrait : GameRotation::Landscape);

    }

    uint8_t frame = (PC::frameCount % 12) < 6 ? 0: 1;

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            PD::drawBitmap(this->titleScreenVars.counter, 21, Images::Portrait::MOTHERSHIP_SIZE_PORTRAIT::Mothership_Title[frame]);

            switch (this->titleScreenVars.counter) {

                case 79:
                    renderPlayerSelection(true);
                    renderInvaderSign();
                    break;

                case 80 ... 87:
                    renderPlayerSelection(true);
                    renderInvaderSign();
                    this->titleScreenVars.counter++;
                    break;

                case 88 ... 95:
                    renderPlayerSelection(false);
                    renderInvaderSign();
                    this->titleScreenVars.counter++;
                    break;

                case 96 ... 110:
                    renderPlayerSelection(false);
                    this->titleScreenVars.counter++;
                    break;

                case 111:

                    this->cookie->saveCookie();
                    
                    switch (this->cookie->gameMode) {

                        case GameMode::Single ... GameMode::Double:
                            this->gameVars.gameState = GameState::Game_Init;
                            break;

                        case GameMode::TugOfWar:
                            this->gameVars.gameState = GameState::TugOfWar_Init;
                            break;

                    }

                    break;
                    
            }

            if (PC::buttons.pressed(BTN_RIGHT) && this->cookie->gameMode != GameMode::Single) { 

                this->cookie->gameMode--;
                this->cookie->saveCookie();
            
            }

            if (PC::buttons.pressed(BTN_LEFT) && static_cast<uint8_t>(this->cookie->gameMode) < this->titleScreenVars.levels) { 

                this->cookie->gameMode++;
                this->cookie->saveCookie();

            }

            if (PC::buttons.pressed(BTN_A) && this->titleScreenVars.counter == 79) {

                this->titleScreenVars.counter = 80;

            }

            if (PC::buttons.pressed(BTN_UP)) { 

                this->cookie->sfx--;
                this->cookie->saveCookie();
                this->titleScreenVars.soundCounter = 64;

                if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

                    this->muteTheme();
                    
                }
                else {

                    this->playTheme(Theme::Main);

                }

            }

            if (PC::buttons.pressed(BTN_DOWN)) { 

                this->cookie->sfx++;
                this->cookie->saveCookie();
                this->titleScreenVars.soundCounter = 64;

                if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

                    this->muteTheme();
                    
                }
                else {

                    this->playTheme(Theme::Main);

                }

            }

            break;

        case GameRotation::Landscape:

            PD::drawBitmap(5, 6 + this->titleScreenVars.counter, Images::Landscape::MOTHERSHIP_SIZE_PORTRAIT::Mothership_Title[frame]);

            switch (this->titleScreenVars.counter) {

                case 0:
                    renderPlayerSelection(true);
                    renderInvaderSign();
                    break;

                case -8 ... -1:
                    renderPlayerSelection(true);
                    renderInvaderSign();
                    this->titleScreenVars.counter--;
                    break;

                case -18 ... -9:
                    renderPlayerSelection(false);
                    renderInvaderSign();
                    this->titleScreenVars.counter--;
                    break;

                case -38 ... -19:
                    renderPlayerSelection(false);
                    this->titleScreenVars.counter--;
                    break;

                case -39:

                    switch (this->cookie->gameMode) {

                        case GameMode::Single ... GameMode::Double:
                            this->gameVars.gameState = GameState::Game_Init;
                            break;

                        case GameMode::TugOfWar:

                            if (this->cookie->gameRotation == GameRotation::Landscape) {
                                this->cookie->gameRotation = this->cookie->gameRotation == GameRotation::Landscape ? GameRotation::Portrait : GameRotation::Landscape;
                                this->gameVars.gameState = GameState::Title_Init;
                                this->cookie->saveRotation(this->cookie->gameRotation);
                            }
                            
                            this->gameVars.gameState = GameState::TugOfWar_Init;
                            break;

                    }

                    break;
                    
            }

            if (PC::buttons.pressed(BTN_UP) && this->cookie->gameMode != GameMode::Single) { 

                this->cookie->gameMode--;
                this->cookie->saveCookie();

            }

            if (PC::buttons.pressed(BTN_DOWN) && static_cast<uint8_t>(this->cookie->gameMode) < this->titleScreenVars.levels) { 

                this->cookie->gameMode++;
                this->cookie->saveCookie();

            }

            if (PC::buttons.pressed(BTN_LEFT)) { 

                this->cookie->sfx--;
                this->cookie->saveCookie();
                this->titleScreenVars.soundCounter = 64;

                if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

                    this->muteTheme();
                    
                }
                else {

                    //this->playTheme();

                }

            }

            if (PC::buttons.pressed(BTN_RIGHT)) { 

                this->cookie->sfx++;
                this->cookie->saveCookie();
                this->titleScreenVars.soundCounter = 64;

                if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

                    this->muteTheme();
                    
                }
                else {

                    //this->playTheme();

                }

            }

            if (PC::buttons.pressed(BTN_A) && this->titleScreenVars.counter == 0) { 

                this->titleScreenVars.counter = -1;

            }

            break;

    }

}

void Game::renderPlayerSelection(bool renderPlayerSelection) {

    uint8_t frame = Constants::Arrow_Frames[(PC::frameCount % 48) / 12];

    switch (this->cookie->gameRotation) {

        case GameRotation::Portrait:

            if (!renderPlayerSelection) return;

            PD::drawBitmap(54 - (static_cast<uint8_t>(this->cookie->gameMode) * 8), 17, Images::Portrait::DownArrow[frame]);
            PD::drawBitmap(54, 25, this->cookie->gameMode == GameMode::Single ? Images::Portrait::SurvivalMode : Images::Portrait::SurvivalMode_Grey);
            PD::drawBitmap(46, 25, this->cookie->gameMode == GameMode::Double ? Images::Portrait::VSMode : Images::Portrait::VSMode_Grey);
            PD::drawBitmap(38, 25, this->cookie->gameMode == GameMode::TugOfWar ? Images::Portrait::TugOfWarMode : Images::Portrait::TugOfWarMode_Grey);

            if (this->cookie->getLevel(0) == 0) PD::drawBitmap(46, 17, Images::Portrait::Lock);
            if (this->cookie->getLevel(1) == 0) PD::drawBitmap(38, 17, Images::Portrait::Lock);

            if (this->titleScreenVars.soundCounter == 0) {

                PD::drawBitmap(28, 32, Images::Portrait::Rotate);

            }
            else {

                switch (this->cookie->sfx) {

                    case SoundEffects::Both:
                        PD::drawBitmap(27, 36, Images::Portrait::Sound_Both_White);
                        break;

                    case SoundEffects::None:
                        PD::drawBitmap(27, 36, Images::Portrait::Sound_None_White);
                        break;

                    case SoundEffects::SFX:
                        PD::drawBitmap(27, 36, Images::Portrait::Sound_SFX_White);
                        break;

                    case SoundEffects::Music:
                        PD::drawBitmap(27, 36, Images::Portrait::Sound_Music_White);
                        break;

                    
                }
                
                this->titleScreenVars.soundCounter--;

            }

            break;

        case GameRotation::Landscape:

            if (!renderPlayerSelection) return;

            PD::drawBitmap(56, 22 + (static_cast<uint8_t>(this->cookie->gameMode) * 9), Images::Landscape::LeftArrow[frame]);
            PD::drawBitmap(64, 22, this->cookie->gameMode == GameMode::Single ? Images::Landscape::SurvivalMode : Images::Landscape::SurvivalMode_Grey);
            PD::drawBitmap(64, 31, this->cookie->gameMode == GameMode::Double ? Images::Landscape::VSMode : Images::Landscape::VSMode_Grey);
            PD::drawBitmap(64, 40, this->cookie->gameMode == GameMode::TugOfWar ? Images::Landscape::TugOfWarMode : Images::Landscape::TugOfWarMode_Grey);

            if (this->cookie->getLevel(0) == 0) PD::drawBitmap(56, 31, Images::Landscape::Lock);
            if (this->cookie->getLevel(1) == 0) PD::drawBitmap(56, 40, Images::Landscape::Lock);

            if (this->titleScreenVars.soundCounter == 0) {

                PD::drawBitmap(80, 53, Images::Landscape::Rotate);

            }
            else {

                switch (this->cookie->sfx) {

                    case SoundEffects::Both:
                        PD::drawBitmap(82, 53, Images::Landscape::Sound_Both_White);
                        break;

                    case SoundEffects::None:
                        PD::drawBitmap(82, 53, Images::Landscape::Sound_None_White);
                        break;

                    case SoundEffects::SFX:
                        PD::drawBitmap(82, 53, Images::Landscape::Sound_SFX_White);
                        break;

                    case SoundEffects::Music:
                        PD::drawBitmap(82, 53, Images::Landscape::Sound_Music_White);
                        break;

                    
                }
                
                this->titleScreenVars.soundCounter--;

            }


            break;
            
    }

}
