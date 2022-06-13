#pragma once

#include "Pokitto.h"
#include "Bullet.h"
#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "../utils/Structs.h"

class Bullets {

    public:

        Bullets();

        uint32_t getFirstDisabledBullet(uint32_t bulletsInPlay);        
        uint32_t getEnabledBulletCount();        
        Bullet * getBullet(uint8_t index);        
        
        void updatePositions();
        void reset();
                
    private:

        Bullet bullets[PLAYER_NO_OF_BULLETS * 2];
        
};