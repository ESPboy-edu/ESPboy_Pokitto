#pragma once

#include "Rect.h"

enum class BulletType : uint8_t {
    PlayerBullet,
    PlayerBomb,
	EnemyBullet,
};

class Bullet : public Point {

    private:

        uint8_t muzzleIndex = 0;
        uint8_t xInertia = 0;
        uint8_t xInertiaCounter = 0;

        BulletType bulletType = BulletType::PlayerBullet;
        Direction direction = Direction::Down;
    
    public:

        uint8_t getMuzzleIndex()                { return this->muzzleIndex; }
        uint8_t getXInertia()                   { return this->xInertia; }
        BulletType getBulletType()              { return this->bulletType; }
        Direction getDirection()                { return this->direction; }

        void setMuzzleIndex(uint8_t val)        { this->muzzleIndex = val; }
        void setXInertia(uint8_t val)           { this->xInertia = val; this->xInertiaCounter = 0; }
        void setBulletType(BulletType val)      { this->bulletType = val; }
        void setDirection(Direction val)        { this->direction= val; }

        void reset() {

            this->setX(-1);
            this->setActive(false);

        }

        void decMuzzleIndex() {

            this->muzzleIndex--;

        }

        Rect getRect() {

            Rect rect = { this->getX() + 1, this->getY() + 1, 1, 1 };

            switch (this->bulletType) {

                case BulletType::PlayerBullet:

                    rect.width = Constants::Player_Bullet_Width;
                    rect.height = Constants::Player_Bullet_Height;
                    return rect;

                case BulletType::PlayerBomb:

                    rect.width = Constants::Player_Bomb_Width;
                    rect.height = Constants::Player_Bomb_Height;
                    return rect;

                case BulletType::EnemyBullet:

                    rect.x = this->getX();
                    rect.y = this->getY();
                    rect.width = Constants::Enemy_Bullet_Width + 2;
                    rect.height = Constants::Enemy_Bullet_Height + 2;
                    return rect;

            }

            return rect; // should never get here!

        }

        void move() {
            
            switch (this->bulletType) {

                case BulletType::PlayerBomb:
                        
                    this->xInertiaCounter ++;

                    switch (this->xInertiaCounter) {

                        case 1 ... 2:
                            this->incX(5);
                            this->incY(1);
                            break;

                        case 3 ... 4:
                            this->incX(4);
                            this->incY(2);
                            break;

                        case 5 ... 6:
                            this->incX(4);
                            this->incY(2);
                            break;

                        default:
                            this->incX(3);
                            this->incY(3);
                            break;
                            
                    }

                    break;

                case BulletType::EnemyBullet:

                    switch (this->direction) {

                        case Direction::Left:
                            this->decX(3);
                            this->decY(3);
                            break;

                        case Direction::Up:
                            this->decY(3);
                            break;

                        case Direction::Right:
                            this->incX(3);
                            this->decY(3);
                            break;
                            
                    }

                    break;

            }

        }


};
