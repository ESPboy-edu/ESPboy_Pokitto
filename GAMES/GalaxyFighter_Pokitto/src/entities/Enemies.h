#pragma once

#include "Pokitto.h"
#include "Enemy.h"
#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "../utils/Structs.h"

class Enemies {

    public:

        Enemies();

        void pulseFormation();
        void populateFormation(const FormationData *formation, bool upgradeEnemies);
        void updatePositions(bool alternateFrame);
        void reset();
            
        bool launchEnemies(uint32_t enemyPosition, EnemyFormation enemyFormation, bool flipHorizontal, uint8_t sequenceIndex);       // 0 = All Positions, 1 = LHS Positions, 2 = RHS Positions.
        bool allEnemiesDead();
        bool allSequencesComplete();
        void disableAllEnemies();

        uint32_t getNumberOfActiveEnemies();
        uint32_t canTransformEnemy(uint32_t enemyPosition);

        Enemy * getEnemy(uint32_t index);
        Enemy * getEnemyToShootBullet();

    private:

        Enemy enemies[ENEMY_COUNT];

        uint8_t pulseIndex = 0;
        PulseDirection pulseDirection = PulseDirection::Outward;

};
