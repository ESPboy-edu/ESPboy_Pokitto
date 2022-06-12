#include "AstarokGame.h"

#include "utils/Enums.h"
#include "utils/GameCookie.h"


void AstarokGame::renderSign() {
    
    PD::drawBitmap(22, 18, Images::SignPost_Large);
    PD::setColor(0xc1, 0x67);

    switch (this->mapNumber) {

        case 1:
            PD::setCursor(33, 31);
            PD::print("Forward is");
            PD::setCursor(33, 38);
            PD::print("the way of");
            PD::setCursor(27, 45);
            PD::print("the champion!");
            break;            

        case 2:
            PD::setCursor(29, 31);
            PD::print(" You've gone");
            PD::setCursor(29, 38);
            PD::print("underground,");
            PD::setCursor(29, 45);
            PD::print("  look out!");
            break;

        case 3:
            PD::setCursor(29, 31);
            PD::print("You are back");
            PD::setCursor(29, 38);
            PD::print("above ground");
            PD::setCursor(29, 45);
            PD::print("-keep going!");
            break;

        case 4:
            PD::setCursor(29, 31);
            PD::print(" Welcome to");
            PD::setCursor(29, 38);
            PD::print(" level 004.");
            PD::setCursor(29, 45);
            PD::print(" Good luck!");
            break;

        case 5:
            PD::setCursor(27, 31);
            PD::print("  The levels");
            PD::setCursor(27, 38);
            PD::print("get harder as");
            PD::setCursor(27, 45);
            PD::print("you progress!");
            break;

        case 6:
            PD::setCursor(29, 31);
            PD::print("The enemies");
            PD::setCursor(29, 38);
            PD::print("get a little");
            PD::setCursor(29, 45);
            PD::print("bit smarter!");
            break;

        case 7:
            PD::setCursor(27, 31);
            PD::print(" Beat others");
            PD::setCursor(27, 38);
            PD::print("to become the");
            PD::setCursor(27, 45);
            PD::print("  champion!");
            break;   

        default:

            switch ((this->mapNumber - 7) % 4) {

                case 0:        
                    PD::setCursor(29, 31);
                    PD::print(" Welcome to");
                    PD::setCursor(29, 38);
                    PD::print(" level ");

                    if (this->mapNumber < 100) PD::print("0");
                    if (this->mapNumber < 10)  PD::print("0");
                    PD::print(this->mapNumber);
                    PD::print(".");
                    PD::setCursor(29, 45);
                    PD::print(" Good luck!");
                    break;

                case 1:
                    PD::setCursor(30, 31);
                    PD::print("You must be");
                    PD::setCursor(34, 38);
                    PD::print("tired but");
                    PD::setCursor(27, 45);
                    PD::print("keep running!");
                    break;   

                case 2:
                    PD::setCursor(29, 31);
                    PD::print("Amazing job.");
                    PD::setCursor(34, 38);
                    PD::print("You could");
                    PD::setCursor(29, 45);
                    PD::print("be champion!");
                    break; 

                case 4:
                    PD::setCursor(29, 31);
                    PD::print("Can you hear");
                    PD::setCursor(27, 38);
                    PD::print("the town folk");
                    PD::setCursor(35, 45);
                    PD::print("cheering?");
                    break;   

            }

            break;
        

    }

    PD::setColor(0, 0);

}

void AstarokGame::renderTrialOver() {

    PD::drawBitmap(6, 20, Images::GameOver);

}

void AstarokGame::renderPause() {

    if (this->pause) {

        PD::drawBitmap(20, 20, Images::Pause);

        PD::setColor(0);
        PD::fillRect(88, 79, 22, 10);

        switch (this->cookie->sfx) {

            case SoundSettings::Music:
                PD::drawBitmap(89, 80, Images::Sound_Music_White);
                break;

            case SoundSettings::SFX:
                PD::drawBitmap(89, 80, Images::Sound_SFX_White);
                break;

            case SoundSettings::Both:
                PD::drawBitmap(89, 80, Images::Sound_Both_White);
                break;

            default:
                PD::drawBitmap(89, 80, Images::Sound_None_White);
                break;

        }

        if (PC::buttons.pressed(BTN_UP) || PC::buttons.pressed(BTN_DOWN)) {
            
            if (PC::buttons.pressed(BTN_UP)) {

                this->cookie->sfx--;
                this->cookie->saveCookie();

                if (this->cookie->sfx != SoundSettings::Both && this->cookie->sfx != SoundSettings::Music) {

                    this->sounds->muteTheme();
                    
                }
                else {

                    this->sounds->playTheme(PC::frameCount % 2, this->cookie->sfx);

                }

            }

            if (PC::buttons.pressed(BTN_DOWN)) {

                this->cookie->sfx++;
                this->cookie->saveCookie();

                if (this->cookie->sfx != SoundSettings::Both && this->cookie->sfx != SoundSettings::Music) {

                    this->sounds->muteTheme();
                    
                }
                else {

                    this->sounds->playTheme(PC::frameCount % 2, this->cookie->sfx);
                    
                }
                
            }

        }

    }

}

void AstarokGame::drawMobs() {

    for (AISprite &obj : this->mobs) {

        if (obj.getActive() || obj.explodeCounter > 16) {

            if (obj.getRightX() - this->camera.x > 0 && obj.x - this->camera.x < 128) {
                obj.draw();
            }

        }

        if (obj.explodeCounter > 0) {

            PD::drawBitmap(obj.x - this->camera.x - 2, obj.y - this->camera.y - 2, 
                           Images::Puffs[(((21 - obj.explodeCounter) / 3) * 2) + (this->mapNumber % 2 ? 1 : 0)]); 

        }

    }

}

void AstarokGame::drawHUD() {

    int16_t tmpScore = this->score + this->player.x / Constants::TileSize; 
    if (tmpScore < 0) tmpScore = 0;

    uint8_t digits[5] = {};
    Utils::extractDigits(digits, static_cast<uint16_t>(tmpScore));

    PD::setColor(0);
    PD::fillRect(0, 0, 53, 8);

    if (this->mapNumber % 2 == MapLevel::AboveGround) {

        PD::drawBitmap(1, 1, Images::Heart[this->lives >= 1 ? Hearts::FilledIn : Hearts::Outline]);
        PD::drawBitmap(9, 1, Images::Heart[this->lives >= 2 ? Hearts::FilledIn : Hearts::Outline]);
        PD::drawBitmap(17, 1, Images::Heart[this->lives >= 3 ? Hearts::FilledIn : Hearts::Outline]);

        for (uint8_t x = 5; x > 0; x--) {
            PD::drawBitmap(27 + ((5 - x) * 5), 1, Images::Numbers[digits[x - 1]]);
        }

    }
    else {

        PD::drawBitmap(1, 1, Images::Heart[this->lives >= 1 ? Hearts::FilledIn : Hearts::Outline]);
        PD::drawBitmap(9, 1, Images::Heart[this->lives >= 2 ? Hearts::FilledIn : Hearts::Outline]);
        PD::drawBitmap(17, 1, Images::Heart[this->lives >= 3 ? Hearts::FilledIn : Hearts::Outline]);

        for (uint8_t x = 5; x > 0; x--) {
            PD::drawBitmap(27 + ((5 - x) * 5), 1, Images::Numbers[digits[x - 1]]);
        }

    }

}

void AstarokGame::drawMap_Background() {

    int16_t backgroundXOffset = (this->camera.x / 4) % 110;
    int16_t backgroundYOffset = this->camera.y / 12;


    // Render backgrounds ..

    if (this->mapNumber % 2 == MapLevel::AboveGround) {

        for (uint8_t i = 0; i < 2; i++) {
            PD::drawBitmap((i * 110) - backgroundXOffset, backgroundYOffset + 8, Images::Sky_Background);
        }

    }
    else {

        for (uint16_t i = 0; i <= 220; i += 110) {

            PD::drawBitmap(i + 2 - backgroundXOffset, backgroundYOffset, Images::Underground_Chain);
            PD::drawBitmap(i + 57 - backgroundXOffset, backgroundYOffset, Images::Underground_Chain);
            PD::drawBitmap(i + 13 - backgroundXOffset, backgroundYOffset + 4, Images::Underground_Brick);
            PD::drawBitmap(i + 63 - backgroundXOffset, backgroundYOffset + 22, Images::Underground_Brick);
            PD::drawBitmap(i + 29 - backgroundXOffset, backgroundYOffset, Images::Torch[Utils::getFrameCount(16) / 4]);
            PD::drawBitmap(i + 80 - backgroundXOffset, backgroundYOffset + 26, Images::Torch[Utils::getFrameCount(16) / 4]);

        }

    }


    // Render interactive tiles ..

    for (int16_t x = (this->camera.x / Constants::TileSize) - 12; x < (this->camera.x / Constants::TileSize) + 17; x++) {

        for (int16_t y = this->camera.y / Constants::TileSize; y < (this->camera.y / Constants::TileSize) + 9; y++) {

            InteractiveObject *obj = this->level.getObject(x, y);

            if (obj != nullptr) {
                    
                switch (obj->getType()) {

                    case ObjectTypes::AboveGroundExit:
                        if (obj->getActive() || obj->explodeCounter > 16) {
                            PD::drawBitmap(x * Constants::TileSize - this->camera.x - 36, y * Constants::TileSize - this->camera.y - 24, Images::Outside_Exit_00);
                        }
                        break;

                    case ObjectTypes::UnderGroundExit:
                        if (obj->getActive() || obj->explodeCounter > 16) {
                            PD::drawBitmap(x * Constants::TileSize - this->camera.x - 13, y * Constants::TileSize - this->camera.y - 4, Images::Underground_Exit_00);
                        }
                        break;

                    case ObjectTypes::Sign:
                        if (obj->getActive() || obj->explodeCounter > 16) {
                            PD::drawBitmap(x * Constants::TileSize - this->camera.x - 4, y * Constants::TileSize - this->camera.y - 4, Images::SignPost[this->mapNumber % 2]);
                        }
                        break;

                    case ObjectTypes::Coin:
                        if (obj->getActive() || obj->explodeCounter > 16) {
                            PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, Images::Coins[Utils::getFrameCount(16) / 4]);
                        }
                        break;

                    case ObjectTypes::Chest_Closed:
                        if (obj->getActive() || obj->explodeCounter > 16) {
                            PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y - 3, Images::Chest_Closed);
                        }
                        break;

                    case ObjectTypes::Chest_Open:
                        if (obj->getActive() || obj->explodeCounter > 16) {
                            PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y - 2, Images::Chest_Open);
                        }
                        break;

                    case ObjectTypes::MemoryMan:
                        if (obj->getActive() || obj->explodeCounter > 16) {
                            PD::drawBitmap(x * Constants::TileSize - this->camera.x - 2, y * Constants::TileSize - this->camera.y - 5, Images::MemoryMan);
                        }
                        break;

                    default: break;
                        if (obj->getActive() || obj->explodeCounter > 16) {
                            PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y - 5, Images::Default);
                        }

                }

                if (obj->explodeCounter > 0) {

                    PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, 
                                Images::Puffs[(((21 - obj->explodeCounter) / 3) * 2) + (this->mapNumber % 2 ? 1 : 0)]); 

                }

            }

        }

    }

}


void AstarokGame::drawMap_Background_2() {

    // Rneder water ..

    if (this->mapNumber % 2 == MapLevel::AboveGround) {

        for (int8_t i = -(PC::frameCount % 16) / 4; i < 110; i = i + 24) {
            PD::drawBitmap(i, 182 - this->camera.y, Images::Water);
        }

    }


    // Render tiles last ..

    for (int16_t x = (this->camera.x / Constants::TileSize) - 12; x < (this->camera.x / Constants::TileSize) + 17; x++) {

        for (int16_t y = this->camera.y / Constants::TileSize; y < (this->camera.y / Constants::TileSize) + 9; y++) {

            if (this->level.isTile(x, y)) {

                if (y == 15 || this->level.isTile(x, y + 1)) {

                    PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, Images::Tile_Brick[this->mapNumber % 2 == MapLevel::AboveGround]);

                }
                else {
                    PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y, Images::Platform[this->mapNumber % 2 == MapLevel::AboveGround]);

                }

            }

        }

    }

}

void AstarokGame::drawMap_Foreground() {

    for (int16_t x = this->camera.x / Constants::TileSize; x < (this->camera.x / Constants::TileSize) + 17; x++) {

        for (int16_t y = this->camera.y / Constants::TileSize; y < (this->camera.y / Constants::TileSize) + 9; y++) {

            if (!this->level.isTile(x, y)) {

                ObjectTypes tile = static_cast<ObjectTypes>(this->level.checkObject(x, y));

                switch (tile) {

                    case ObjectTypes::AboveGroundExit:
                        PD::drawBitmap(x * Constants::TileSize - this->camera.x - 10, y * Constants::TileSize - this->camera.y - 24, Images::Outside_Exit_01);
                        break;

                    case ObjectTypes::UnderGroundExit:
                        PD::drawBitmap(x * Constants::TileSize - this->camera.x, y * Constants::TileSize - this->camera.y - 4, Images::Underground_Exit_01);
                        break;

                    default: break;

                }

            }

        }

    }

}

void AstarokGame::drawPlayer() {


    // Render player ..

    switch (this->event) {

        case EventType::StartLevel:

            if (this->eventCounter < 12) { // Do not display for first half of puff cycle.
                this->player.draw();
            }

            break;

        case EventType::Death_Init:
        case EventType::Death:
        case EventType::Playing:   
        case EventType::Flash:   
            if (!(this->eventCounter % 2)) this->player.draw();
            break;

        default:
            this->player.draw();
            break;

    }


    // Render entrance puff of smoke ..

    if (this->event == EventType::StartLevel) { 

        PD::drawBitmap(this->player.x - this->camera.x - 2, this->player.y - this->camera.y - 4, 
                       Images::Puffs[(((21 - this->eventCounter) / 3) * 2) + (this->mapNumber % 2 ? 1 : 0)]); 

    }

}

void AstarokGame::draw() {

    drawMap_Background(); 
    drawMobs(); 
    drawMap_Background_2(); 
    drawPlayer(); 
    drawMap_Foreground(); 
    drawHUD();
    renderPause();


    // Particles?

    for (uint8_t i = 0; i < Constants::ParticlesMax; i++) {

        this->particles[i].update();

        if (this->particles[i].render()) { // the dot should be rendered

            uint8_t pSize = particles[i].getColor();

            switch (pSize) {

                case 0:
                    PD::drawBitmap(this->particles[i].getX(), this->particles[i].getY(), Images::Pixel_01);
                    break;

                case 1:
                    PD::drawBitmap(this->particles[i].getX(), this->particles[i].getY(), Images::Pixel_02);
                    break;

                case 2:
                    PD::drawBitmap(this->particles[i].getX(), this->particles[i].getY(), Images::Pixel_03);
                    break;

            } 

        }

    }

}
