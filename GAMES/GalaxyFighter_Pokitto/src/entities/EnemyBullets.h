#pragma once

#include "Pokitto.h"
#include "EnemyBullet.h"
#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "../utils/Structs.h"

class EnemyBullets {

    public:

        EnemyBullets();

        EnemyBullet * getFirstDisabledBullet();        
        uint8_t getEnabledBulletCount();        
        EnemyBullet * getBullet(uint8_t index);        
        
        void updatePositions();
        void reset();
        void decDelayCountdown();
        
    private:

        EnemyBullet bullets[ENEMY_NO_OF_BULLETS];
        uint8_t enemyBulletCountdown_Delay;
        
};