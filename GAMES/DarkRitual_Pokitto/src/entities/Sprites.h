#pragma once

#include "Pokitto.h"
#include "Sprite.h"
#include "Sprites_Consts.h"
#include "Player.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


class Sprites {

    public:

        Sprites() {};  

        Sprite & getSprite(uint8_t index);
        uint8_t getFirstInactiveSpriteIndex(Object type);
        uint8_t getObjectNum();

        void setObjectNum(uint8_t oNum);

//        void update();
        void render(Player &player, bool renderEnemies);
        void clearPreventImmediatePickup(Player &player);
        void renderHealthBar(uint32_t x, uint32_t y, uint8_t health);
        void renderSprite(Object type, int x, int y);
        void renderSprite(Object type, int x, int y, int8_t xOffset, int8_t yOffset, Direction direction, int8_t frame, uint8_t countdown, bool showEnemies, bool showGuideText, bool renderHealth, int healthValue);

    private:

        Sprite objects[MAXOBJECT];
        uint8_t oNum = 0;

};


