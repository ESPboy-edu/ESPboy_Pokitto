
#pragma once

#include "Enemy.h"

class Enemies {

    public:

        Enemy enemies[Constants::Enemy_Count];

    public:
        
        void reset() {

            for (Enemy &enemy : this->enemies) {

                enemy.reset();

            }

        }

        uint8_t getInactiveEnemy() {

            for (uint8_t i = 0; i < Constants::Enemy_Count; i++) {

                Enemy &enemy = this->enemies[i];

                if (!enemy.getActive()) {

                    return i;

                }

            }

            return Constants::Enemy_None;

        }

        uint8_t getInactiveEnemyCount() {

            uint8_t enemyCount = 0;

            for (uint8_t i = 0; i < Constants::Enemy_Count; i++) {

                Enemy &enemy = this->enemies[i];

                if (!enemy.getActive()) {

                    enemyCount++;

                }

            }

            return enemyCount;

        }

};
