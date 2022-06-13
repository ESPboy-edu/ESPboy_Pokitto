#pragma once

#include "Pokitto.h"

#include "../utils/Constants.h"
#include "../utils/Enums.h"

class Player {

    public:

        Player();

        const uint8_t width = 15;
        const uint8_t height = 16;


        // Properties ..

        uint8_t getX();
        uint8_t getY();
        uint8_t getWidth();
        uint8_t getHeight();
        uint8_t getHealth();
        uint8_t getLives();
        bool isEnabled();
        bool isJustHit();
        Side getJustHitSide();

        void setX(uint8_t x);
        void setY(uint8_t y);
        void setHealth(uint8_t health);
        void setLives(uint8_t lives);
        void setEnabled(bool enabled);
        void setJustHitSide(Side justHitSide);


        // Methods ..

        void decX();
        void incX();

        bool move();
        void decelerate();
        void decHealth(bool twinPlayers, uint8_t amount);
        void decLives();
        void incLives();
        bool isExploding();
        void reset(bool startOfGame);

        uint8_t getExplosionImageIndex();
        uint8_t getExplosionImageOffset();
        uint8_t getImage();
        bool getImageFlip();
    
    protected:

        uint8_t x;
        uint8_t y;
        int32_t xInertia;
        uint8_t health;
        uint8_t enabled;
        bool twinPlayers;

        uint8_t justHit;
        uint8_t lives;

        uint8_t explosionCounter;           // Explosion counter - 0 not exploding, 1-3, 4-6, 7-9, 10-12 are graphics indexes 0 - 3.
        Side justHitSide;                   // When in twin player mode, which side did the hit occur on?
 
};

