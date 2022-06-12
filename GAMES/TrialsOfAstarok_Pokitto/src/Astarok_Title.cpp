#include "Astarok.h"

void Game::drawBackground() {

    PD::drawBitmap(-5, 12, Images::Underground_Brick);
    PD::drawBitmap(97, 12, Images::Underground_Brick);

    PD::drawBitmap(-5, 62, Images::Underground_Brick);
    PD::drawBitmap(97, 62, Images::Underground_Brick);

    PD::drawBitmap(2, 37, Images::Torch[Utils::getFrameCount(16) / 4]);
    PD::drawBitmap(103, 37, Images::Torch[Utils::getFrameCount(16) / 4]);

}

void Game::titleScreen() {

    PD::setColor(0, 0);
    PD::drawBitmap(15, 16, Images::Title);
    PD::drawBitmap(26, 12, Images::Underground_Chain);
    PD::drawBitmap(81, 12, Images::Underground_Chain);    
    drawBackground();

    switch (titleScreenVars.index) {

        case TitleScreenMode::Play:
            PD::drawBitmap(26, 71, Images::Title_Highlight);
            break;

        case TitleScreenMode::HighScore:
            PD::drawBitmap(56, 71, Images::Title_Highlight);
            break;

        default: break;

    }

    switch (this->cookie->sfx) {

        case SoundSettings::Music:
            PD::drawBitmap(89, 79, titleScreenVars.index == TitleScreenMode::SoundEffects ? Images::Sound_Music_White: Images::Sound_Music_Inactive);
            break;

        case SoundSettings::SFX:
            PD::drawBitmap(89, 79, titleScreenVars.index == TitleScreenMode::SoundEffects ? Images::Sound_SFX_White: Images::Sound_SFX_Inactive);
            break;

        case SoundSettings::Both:
            PD::drawBitmap(89, 79, titleScreenVars.index == TitleScreenMode::SoundEffects? Images::Sound_Both_White: Images::Sound_Both_Inactive);
            break;

        default:
            PD::drawBitmap(89, 79, titleScreenVars.index == TitleScreenMode::SoundEffects ? Images::Sound_None_White: Images::Sound_None_Inactive);
            break;

    }


    if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {

        switch (titleScreenVars.index) {

            case TitleScreenMode::Play:
                this->gameState = GameState::IntroText_Init;
                break;

            case TitleScreenMode::HighScore:
                gameState = GameState::HighScore_NoFlash;
                break;

        }

    }


    if (titleScreenVars.index == TitleScreenMode::SoundEffects && (PC::buttons.pressed(BTN_UP) || PC::buttons.pressed(BTN_DOWN))) {
        
        if (PC::buttons.pressed(BTN_UP)) {

            this->cookie->sfx--;
            this->cookie->saveCookie();

            if (this->cookie->sfx != SoundSettings::Both && this->cookie->sfx != SoundSettings::Music) {

                this->sounds.muteTheme();
                
            }
            else {

                this->sounds.playTheme(2, this->cookie->sfx);

            }

        }

        if (PC::buttons.pressed(BTN_DOWN)) {

            this->cookie->sfx++;
            this->cookie->saveCookie();

            if (this->cookie->sfx != SoundSettings::Both && this->cookie->sfx != SoundSettings::Music) {

                this->sounds.muteTheme();
                
            }
            else {

                this->sounds.playTheme(2, this->cookie->sfx);
                
            }
            
        }

    }

    if (PC::buttons.pressed(BTN_LEFT)) {
        sounds.playSoundEffect(Sounds::Effects::ButtonPress, cookie->sfx);
        if (titleScreenVars.index > TitleScreenMode::Play) {
            titleScreenVars.index--;
        }

    }

    if (PC::buttons.pressed(BTN_RIGHT)) {
        sounds.playSoundEffect(Sounds::Effects::ButtonPress, cookie->sfx);
        if (titleScreenVars.index < TitleScreenMode::SoundEffects) {
            titleScreenVars.index++;
        }

    }

}

