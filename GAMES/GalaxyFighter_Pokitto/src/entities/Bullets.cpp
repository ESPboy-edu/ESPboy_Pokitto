#include "Bullets.h"

#include "../utils/Constants.h"
#include "../utils/Structs.h"
#include "../utils/Enums.h"

Bullets::Bullets() {} 


void Bullets::reset() {
    
    for (uint32_t x = 0; x < (PLAYER_NO_OF_BULLETS * 2); x++) {
        
        this->bullets[x].setEnabled(false);
    }

}
    
Bullet * Bullets::getBullet(uint8_t index) {
    
    return &this->bullets[index];
    
}

uint32_t Bullets::getFirstDisabledBullet(uint32_t bulletsInPlay) {
    
    for (uint32_t x = 0; x < bulletsInPlay; x++) {
        
        if (!this->bullets[x].isEnabled() && !this->bullets[x + PLAYER_NO_OF_BULLETS].isEnabled()) return x;

    }
    
    return NO_BULLET;
    
}

uint32_t Bullets::getEnabledBulletCount() {
    
    uint32_t count = 0;
    
    for (uint32_t x = 0; x < PLAYER_NO_OF_BULLETS; x++) {
        
        if (this->bullets[x].isEnabled() || this->bullets[x + PLAYER_NO_OF_BULLETS].isEnabled()) count++;
    }
    
    return count;
    
}   

void Bullets::updatePositions() {
    
    for (uint32_t x = 0; x < (PLAYER_NO_OF_BULLETS * 2); x++) {
        
        Bullet & bullet = this->bullets[x];
        
        if (bullet.isEnabled()) {
            
            if (bullet.getY() > 2) {
            
                bullet.setY(bullet.getY() - 2);

            }
            else {
                
                bullet.setEnabled(false);
                
            }

        }

    }
    
}