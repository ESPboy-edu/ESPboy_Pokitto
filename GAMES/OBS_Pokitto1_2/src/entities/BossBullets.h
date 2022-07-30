
#pragma once

#include "Bullet.h"

class BossBullets {

    public:

        Bullet bullets[Constants::Boss_Bullet_Count];

    public:
        
        void reset() {

            for (Bullet &bullet : this->bullets) {

                bullet.reset();

            }

        }

        uint8_t getInactiveBullet() {

            for (uint8_t i = 0; i < Constants::Boss_Bullet_Count; i++) {

                Bullet &bullet = this->bullets[i];

                if (!bullet.getActive()) {

                    return i;

                }

            }

            return Constants::Bullet_None;

        }

};
