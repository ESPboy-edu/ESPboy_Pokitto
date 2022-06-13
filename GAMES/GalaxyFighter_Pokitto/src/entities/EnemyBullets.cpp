#include "EnemyBullets.h"

#include "../utils/Constants.h"
#include "../utils/Structs.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"

using PD = Pokitto::Display;

EnemyBullets::EnemyBullets() {} 

void EnemyBullets::decDelayCountdown() {
        
    if (this->enemyBulletCountdown_Delay > ENEMY_BULLET_COUNTDOWN_DELAY_MIN)  {

        this->enemyBulletCountdown_Delay = this->enemyBulletCountdown_Delay - ENEMY_BULLET_COUNTDOWN_DELAY_DEC;

    }

}


void EnemyBullets::reset() {
    
    this->enemyBulletCountdown_Delay = ENEMY_BULLET_COUNTDOWN_DELAY_MAX;

    for (uint32_t x = 0; x< ENEMY_NO_OF_BULLETS; x++) {
        
        this->bullets[x].setEnabled(false);

    }

}


EnemyBullet * EnemyBullets::getBullet(uint8_t index) {
    
    return &this->bullets[index];
    
}

EnemyBullet * EnemyBullets::getFirstDisabledBullet() {
    
    for (uint32_t x = 0; x < ENEMY_NO_OF_BULLETS; x++) {
        
        if (!this->bullets[x].isEnabled()) {

            return &this->bullets[x];
            
        }
        
    }
    
    return nullptr;
    
}

uint8_t EnemyBullets::getEnabledBulletCount() {
    
    uint8_t count = 0;
    
    for (uint32_t x = 0; x< ENEMY_NO_OF_BULLETS; x++) {
        
        if (this->bullets[x].isEnabled()) count++;
    }
    
    return count;
    
}   

void EnemyBullets::updatePositions() {
    
    for (uint32_t x = 0; x < ENEMY_NO_OF_BULLETS; x++) {
        
        EnemyBullet & bullet = this->bullets[x];
        
        if (bullet.isEnabled()) {
            
            bullet.setY(bullet.getY() + 2);
            bullet.setX(bullet.getX() + bullet.getXDelta());
            
            if (bullet.getY() > PD::height) {
                
                bullet.setEnabled(false);
                
            }

        }

    }
    
}