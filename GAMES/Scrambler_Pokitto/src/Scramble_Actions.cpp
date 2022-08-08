#include "Scramble.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::playerActions() {


    // Move Up and Down ..

    switch (this->player.getYDirection()) {

        case Direction::None:

            if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 1)) {

                this->player.decY(1, PC::frameCount, Constants::Player_Inertia);

                if (this->player.getY() - this->gameScreenVars.viewY < 70) {
                    this->gameScreenVars.viewY = this->gameScreenVars.viewY - 1;
                }

            }

            if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 1)) {

                this->player.incY(1, PC::frameCount, Constants::Player_Inertia);

                if (this->player.getY() - this->gameScreenVars.viewY > 176 - 90) {
                    this->gameScreenVars.viewY = this->gameScreenVars.viewY + 1;
                }

            }

            break;

        case Direction::Up:

            if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, (this->player.getYDelay() / 2))) {

                if (this->player.getYDelay() == 1) {

                    this->player.decY(2, PC::frameCount);

                    if (this->player.getY() - this->gameScreenVars.viewY < 70) {
                        this->gameScreenVars.viewY = this->gameScreenVars.viewY - 2;
                    }

                }
                else {

                    this->player.decY(1, PC::frameCount);

                    if (this->player.getY() - this->gameScreenVars.viewY < 70) {
                        this->gameScreenVars.viewY = this->gameScreenVars.viewY - 1;
                    }

                }

            }

            else if (PC::buttons.repeat(BTN_UP, 1)) { }

            else if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 1)) {
                
                this->player.incY(1, PC::frameCount, Constants::Player_Inertia);

                if (this->player.getY() - this->gameScreenVars.viewY > 176 - 90) {
                    this->gameScreenVars.viewY = this->gameScreenVars.viewY + 1;
                }

            }

            else if (this->player.getYDelay() <= Constants::Player_Inertia) {

                if (this->player.getYDelay() == 1) { this->player.setYDelay(2); }

                if (this->player.movePlayerY(PC::frameCount)) {

                    this->player.decY(1, PC::frameCount, this->player.getYDelay() * 2, true);

                    if (this->player.getY() - this->gameScreenVars.viewY < 70) {
                        this->gameScreenVars.viewY = this->gameScreenVars.viewY - 1;
                    }

                }

            }

            break;

        case Direction::Down:

            if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, (this->player.getYDelay() / 2))) {

                if (this->player.getYDelay() == 1) {

                    this->player.incY(2, PC::frameCount);

                    if (this->player.getY() - this->gameScreenVars.viewY > 176 - 90) {
                        this->gameScreenVars.viewY = this->gameScreenVars.viewY + 2;
                    }

                }
                else {

                    this->player.incY(1, PC::frameCount);

                    if (this->player.getY() - this->gameScreenVars.viewY > 176 - 90) {
                        this->gameScreenVars.viewY = this->gameScreenVars.viewY + 1;
                    }

                }

            }

            else if (PC::buttons.repeat(BTN_DOWN, 1)) { }
            
            else if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 1)) {

                this->player.decY(1, PC::frameCount, Constants::Player_Inertia);

                if (this->player.getY() - this->gameScreenVars.viewY < 70) {
                    this->gameScreenVars.viewY = this->gameScreenVars.viewY - 1;
                }

            }

            else if (this->player.getYDelay() <= Constants::Player_Inertia) {

                if (this->player.getYDelay() == 1) { this->player.setYDelay(2); }

                if (this->player.movePlayerY(PC::frameCount)) {

                    this->player.incY(1, PC::frameCount, this->player.getYDelay() * 2, true);

                    if (this->player.getY() - this->gameScreenVars.viewY > 176 - 90) {
                        this->gameScreenVars.viewY = this->gameScreenVars.viewY + 1;
                    }

                }

            }

            break;

    }



    // Move Left and Right ..
    
    switch (this->player.getXDirection()) {

        case Direction::None:

            if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1)) {

                if (this->player.getX() - this->gameScreenVars.distance > 1) {
                    this->player.decX(1, PC::frameCount, Constants::Player_Inertia);
                }

            }

            if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1)) {

                if (this->player.getX() - this->gameScreenVars.distance < 220 - Constants::Player_Width) {
                    this->player.incX(1, PC::frameCount, Constants::Player_Inertia);
                }

            }

            break;

        case Direction::Left:

            if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, (this->player.getXDelay() / 2))) {

                if (this->player.getX() - this->gameScreenVars.distance > 1) {
                    this->player.decX(this->player.getXDelay() == 1 ? 1 : 0, PC::frameCount);
                }

            }

            else if (PC::buttons.repeat(BTN_LEFT, 1)) { }

            else if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1)) {
                
                if (this->player.getX() - this->gameScreenVars.distance < Constants::Player_X_Max) {
                    this->player.incX(1, PC::frameCount);
                }

            }

            else if (this->player.getXDelay() <= Constants::Player_Inertia) {

                if (this->player.getXDelay() == 1) { this->player.setXDelay(2); }

                if (this->player.movePlayerX(PC::frameCount)) {

                    if (this->player.getX() - this->gameScreenVars.distance < Constants::Player_X_Max) {
                        this->player.incX(1, PC::frameCount, this->player.getXDelay() * 2, true);
                    }

                }

            }

            break;

        case Direction::Right:

            if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, (this->player.getXDelay() / 2))) {

                if (this->player.getX() - this->gameScreenVars.distance < Constants::Player_X_Max) {
                    this->player.incX(this->player.getXDelay() == 1 ? 2 : 1, PC::frameCount);
                }

            }

            else if (PC::buttons.repeat(BTN_RIGHT, 1)) { }
            
            else if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1)) {

                if (this->player.getX() - this->gameScreenVars.distance > 1) {
                    this->player.decX(1, PC::frameCount);
                }

            }

            else if (this->player.getXDelay() <= Constants::Player_Inertia) {

                if (this->player.getXDelay() == 1) { this->player.setXDelay(2); }

                if (this->player.movePlayerX(PC::frameCount)) {

                    if (this->player.getX() - this->gameScreenVars.distance < Constants::Player_X_Max) {
                        this->player.incX(1, PC::frameCount, this->player.getXDelay() * 2, true);
                    }

                }

            }

            break;

    }


    // Player shoots bullet ..

    if (PC::buttons.pressed(BTN_A)) {

        uint8_t bulletIdx = bullets.getInactivePlayerBullet();

        if (bulletIdx != Constants::Bullet_None) {

            Bullet &bullet = bullets.bullets[bulletIdx];
            bullet.setActive(true);
            bullet.setBulletType(BulletType::PlayerBullet);
            bullet.setX(this->player.getX() + Constants::Player_Width + 4);
            bullet.setY(this->player.getY() + 4);
            bullet.setMuzzleIndex(8);

            #ifdef SOUNDS
                playSoundEffect(SoundEffect::PlayerLaser);
            #endif

        }

    }


    // Player drops bomb ..

    if (PC::buttons.pressed(BTN_B)) {

        uint8_t bombIdx = bullets.getInactiveBomb();

        if (bombIdx != Constants::Bomb_None) {

            Bullet &bomb = bullets.bombs[bombIdx];
            bomb.setActive(true);
            bomb.setBulletType(BulletType::PlayerBomb);
            bomb.setX(this->player.getX() + (Constants::Player_Width / 2) - 3);
            bomb.setY(this->player.getY() + Constants::Player_Height + 2);
            bomb.setMuzzleIndex(8);
            bomb.setXInertia(1);

            #ifdef SOUNDS
                playSoundEffect(SoundEffect::PlayerBomb);
            #endif

        }

    }

}