#pragma once

#include "Pokitto.h"
//#include <LibAudio>
//#include "../../libs/LibAudio/LibAudio.h"
#include "../utils/Enums.h"
#include "Sprites_Consts.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;



class Sprite {

    public:

        Sprite() {};

        uint16_t getX();
        uint16_t getY();
        uint8_t getWidth();
        uint8_t getHeight();
        int8_t getXOffset();
        int8_t getYOffset();
        int8_t getFrame();
        uint8_t getQuantity();
        uint8_t getPuffIndex();
        Object getType();
        Object getCarrying();
        int16_t getHealth();
        int16_t getHealthOrig();
        bool getGuideText();
        SpriteStatus getActive();
        bool getRenderHealthBar();
        uint8_t getCountdown();
        bool getPreventImmediatePickup();

        void setActive(SpriteStatus value);
        void setFrame(int8_t frame);
        void setQuantity(uint8_t quantity);
        void setX(uint16_t x);
        void setY(uint16_t y);
        void setType(Object type);
        void setCarrying(Object carrying);
        void setCountdown(uint8_t countdown);
        void setPreventImmediatePickup(bool value);
        void setDirection(Direction direction);
        void setGuideText(bool guideText);
        void setWidth(uint8_t value);
        void setHeight(uint8_t value);
        void setPuffIndex(uint8_t value);

        void decCountdown();
        Rect getRect();
        void update();
        void setPosition(uint16_t x, uint16_t y);
        void setSprite(uint16_t x, uint16_t y, uint8_t health, Object type, SpriteStatus active, bool enablePuff);
        bool decHealth(Object weapon); // returns is dead
        Direction getDirection();

        void incFrame();
        bool isEnemy();
        bool isBoss();
        bool isSolidSprite();
        bool isCarryable();

    private:

        int8_t xOffset;
        int8_t yOffset;
        uint16_t x;
        uint16_t y;
        uint8_t width;
        uint8_t height;
        int16_t health;
        int16_t healthOrig;
        Object type;
        Object carrying = Object::None;
        int8_t frame;
        uint8_t countdown = 50;
        SpriteStatus active;
        bool guideText;
        uint8_t quantity;

        int8_t lastMoveX;
        int8_t lastMoveY;
        bool preventImmediatePickup;
        uint8_t renderHealthBar;
        uint8_t puffIndex = 0;

};


