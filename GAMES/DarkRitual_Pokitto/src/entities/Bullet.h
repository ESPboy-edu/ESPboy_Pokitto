#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../utils/Structs.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


class Bullet {

    public:

        Bullet() {}  

        bool getActive();
        uint16_t getX();
        uint16_t getY();
        uint8_t getWidth();
        uint8_t getHeight();
        uint8_t getFrame();
        uint8_t getCountdown();
        Object getWeapon();
        Direction getDirection();

        void setX(uint16_t x);
        void setY(uint16_t y);
        void setActive(bool active);
        void setWeapon(Object weapon);
        void setDirection(Direction direction);

        void setBullet(uint16_t x, uint16_t y, Direction direction, Object weapon, uint8_t lifeCountdown);

        void update();
        void kill();
        Rect getRect();

    private:

        void updatePosition();

    private:

        uint16_t x;
        uint16_t y;
        Direction direction;
        bool active;
        uint8_t frame;
        Object weapon;
        uint8_t lifeCountdown;           // Life countdown for web, etc

};
