#include "Pokitto.h"
#include "Bullet.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;



bool Bullet::getActive()                        { return this->active;}
uint16_t Bullet::getX()                         { return this->x;}
uint16_t Bullet::getY()                         { return this->y;}
uint8_t Bullet::getFrame()                      { return this->frame;}
uint8_t Bullet::getCountdown()                  { return this->lifeCountdown;}
Direction Bullet::getDirection()                { return this->direction;}
Object Bullet::getWeapon()                      { return this->weapon;}

void Bullet::setX(uint16_t x)                   { this->x = x;}
void Bullet::setY(uint16_t y)                   { this->y = y;}
void Bullet::setActive(bool active)             { this->active = active;}
void Bullet::setWeapon(Object weapon)           { this->weapon = weapon;}
void Bullet::setDirection(Direction direction)  { this->direction = direction;}

void Bullet::kill()                             { this->active = false;}

uint8_t Bullet::getWidth() {

    switch (this->weapon) {

        case Object::Sparks:

            return 2;

        case Object::FireBall:
        case Object::IceSpell:
        case Object::GreenSpell:
        case Object::RedSpell:
        case Object::MauveSpell:

            return 4;

        case Object::SpiderWeb:

            switch (this->frame) {

                case 0:
                    return 6;

                case 1:
                    return 8;

                case 2 ... 5:
                    return 14;

            }

            break;

        default: return 4;

    } 

    return 4;

}

uint8_t Bullet::getHeight() {

    return this->getWidth();

}


void Bullet::setBullet(uint16_t x, uint16_t y, Direction direction, Object weapon, uint8_t lifeCountdown) { 

    this->x = x; 
    this->y = y; 
    this->direction = direction; 
    this->active = true; 
    this->weapon = weapon; 
    this->frame = 0;

    this->lifeCountdown = lifeCountdown;

}

Rect Bullet::getRect() {

    switch (this->weapon) {

        case Object::Sparks:

            return Rect { this->getX() - 1, this->getY() - 1, 2, 2 };

        case Object::SpiderWeb:
            {
                const uint8_t offsets[6] = { 3, 4, 7, 5, 4, 3 };

                if (this->frame >= 0 && this->frame <= 5) { 

                    uint8_t offset = offsets[this->frame];

                    return Rect { this->getX() - offset, this->getY() - offset, (offset * 2), (offset * 2) };
                }

            }

            return Rect { this->getX() - (this->getWidth() / 2), this->getY() - (this->getHeight() / 2), this->getWidth(), this->getHeight() };


        default:

            return Rect { this->getX() - 2, this->getY() - 2, 4, 4 };

    }

}

void Bullet::update() {

    if (this->getActive()) {

        switch (this->weapon) {

            case Object::FireBall:
            case Object::IceSpell:
            case Object::GreenSpell:
            case Object::RedSpell:
            case Object::MauveSpell:
            case Object::Sparks: 

                this->lifeCountdown--;

                if (this->lifeCountdown == 0) {

                    this->setActive(false);
                    break;

                }
                else {

                    this->frame++;
                    this->frame = this->frame % 4;
                    updatePosition();

                }

                break;

            case Object::SpiderWeb:

                this->lifeCountdown--;

                switch (this->lifeCountdown) {

                    case BULLET_WEB_FRAMES - 1:
                        this->frame = 0;
                        updatePosition();
                        break;

                    case BULLET_WEB_FRAMES_DIV1 + 1 ... BULLET_WEB_FRAMES - 2:
                    case BULLET_WEB_FRAMES_DIV2 + 1 ... BULLET_WEB_FRAMES_DIV1 - 1:
                    case BULLET_WEB_FRAMES_DIV3 + 1 ... BULLET_WEB_FRAMES_DIV2 - 1:
                    case BULLET_WEB_FRAMES_DIV4 + 1 ... BULLET_WEB_FRAMES_DIV3 - 1:
                    case BULLET_WEB_FRAMES_DIV5 + 1 ... BULLET_WEB_FRAMES_DIV4 - 1:
                    case 1 ... BULLET_WEB_FRAMES_DIV5 - 1:
                        updatePosition();
                        break;

                    case BULLET_WEB_FRAMES_DIV1:
                        this->frame = 1;
                        updatePosition();
                        break;

                    case BULLET_WEB_FRAMES_DIV2:
                        this->frame = 2;
                        updatePosition();
                        break;

                    case BULLET_WEB_FRAMES_DIV3:
                        this->frame = 3;
                        updatePosition();
                        break;

                    case BULLET_WEB_FRAMES_DIV4:
                        this->frame = 4;
                        updatePosition();
                        break;

                    case BULLET_WEB_FRAMES_DIV5:
                        this->frame = 5;
                        updatePosition();
                        break;

                    case 0:
                        this->setActive(false);
                        break;

                }

                break;
    
        }

    }

}

void Bullet::updatePosition() {

    const int32_t xOffsets[9] = { 0, 3, 3, 3, 0, -3, -3, -3, 0 };
    const int32_t yOffsets[9] = { -3, -3, 0, 3, 3, 3, 0, -3, 0 };

    this->setX(this->getX() + xOffsets[static_cast<uint8_t>(this->getDirection())]);
    this->setY(this->getY() + yOffsets[static_cast<uint8_t>(this->getDirection())]);

}
