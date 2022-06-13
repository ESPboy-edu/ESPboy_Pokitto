#include "Enemies.h"

#include "../utils/Constants.h"
#include "../utils/Structs.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"
#include "../data/Sequences.h"

Enemies::Enemies() { 
}

void Enemies::reset() {
    
    for (uint32_t x = 0; x < ENEMY_COUNT; x++) {

        Enemy &enemy = this->enemies[x]; 
        //enemy.setEnabled(false);
        enemy.reset();
    }

    
}

const float pulseOffsetX[] PROGMEM = { 0, 0.25, 0.5, 0.75, 1, 1.25, 1.5, 1.75 };
const float pulseOffsetY[] PROGMEM = { 0, 0.33, 0.66, 0.99, 1, 1.33, 1.66, 2 };

void Enemies::pulseFormation() {

    switch (this->pulseDirection) {

        case PulseDirection::Outward:
            this->pulseIndex++;
            if (this->pulseIndex == 7) pulseDirection = PulseDirection::Inward;
            break;

        case PulseDirection::Inward:
            this->pulseIndex--;
            if (this->pulseIndex == 0) pulseDirection = PulseDirection::Outward;
            break;  

    }

    for (uint8_t y = 0; y < ENEMY_ROW_COUNT; y++) {

        for (uint8_t x = 0; x < ENEMY_COL_COUNT; x++) {
           
            Enemy &enemy = this->enemies[(y * ENEMY_COL_COUNT) + x]; 
            enemy.setX_Formation(static_cast<int16_t>(SCREEN_WIDTH_HALF + ((x - (ENEMY_COL_COUNT / 2)) * HORIZ_SPACING) + ((x - (ENEMY_COL_COUNT / 2)) * pulseOffsetX[pulseIndex])));
            enemy.setY_Formation(static_cast<int16_t>(ENEMY_TOP_OFFSET + (y > 0 ? 2 : 0) + (y * VERT_SPACING) + pulseOffsetY[pulseIndex]));

        }
        
    }

}

void Enemies::populateFormation(const FormationData *formation, bool upgradeEnemies) {

    uint32_t formationLen = 0;
    this->pulseIndex = 0;
    this->pulseDirection = PulseDirection::Outward;

    for (uint32_t i = 0; i < ENEMY_COUNT; i++) {

        Enemy &enemy = this->enemies[i];
        enemy.setX(0);
        enemy.setY(0);
        enemy.setGridPosition(0);
        enemy.setSequence(nullptr);
        enemy.setEnabled(false);

        #ifdef DEBUG
        enemy.setEnemyIndex(i);
        #endif

    }

    while (true) {
    
        FormationData formationData = formation[formationLen];


        // Have we reached the end of the formation?

        if (formationData.enemyType == EnemyType::None) break;


        // Upgrade enemy types?

        if (upgradeEnemies) {

            if (formationData.enemyType == EnemyType::Butterfly) formationData.enemyType = EnemyType::Butterfly_Boss;
        }


        // Otherwise populate the enemy details ..

        formationLen++;

        for (uint32_t i = formationData.gridPosition; i < formationData.gridPosition + formationData.repeat; i++) {

            Enemy &enemy = this->enemies[i];
            enemy.setFormationData(formationData);
            enemy.setSequence(nullptr);


            // Do not enable the first three enemies as these are reserved for transforms ..

            if (i >= 3) {

                enemy.setEnabled(true);

            }
    
    
            // If no position has been specified, position the enemy on the grid ..
    
            if (formationData.x == 0 && formationData.y == 0) {
    
                uint32_t y = formationData.gridPosition / ENEMY_COL_COUNT;
                uint32_t x = (i % ENEMY_COL_COUNT);
    
                enemy.setY(ENEMY_TOP_OFFSET + (y > 0 ? 2 : 0) + (y * VERT_SPACING) + pulseOffsetY[pulseIndex]);
                enemy.setX(SCREEN_WIDTH_HALF + ((x - (ENEMY_COL_COUNT / 2)) * HORIZ_SPACING));

            }
            
        }

    }

}

Enemy * Enemies::getEnemy(uint32_t index) {
    
    return &this->enemies[index];
    
}


void Enemies::updatePositions(bool alternateFrame) {

    for (uint32_t x = 0; x < ENEMY_COUNT; x++) {

        Enemy &enemy = this->enemies[x];
        enemy.updatePosition(alternateFrame);
        
    }

}


Enemy * Enemies::getEnemyToShootBullet() {

    uint8_t inSequence[50];
    uint8_t stationary[50];

    uint32_t inSequence_Count = 0;
    uint32_t stationary_Count = 0;

    for (uint32_t x = 0; x < ENEMY_COUNT; x++) {

        Enemy &enemy = this->enemies[x];
        if (enemy.isVisible() && enemy.isEnabled() && !enemy.isTractorEnabled()) {

            if (enemy.inSequence()) {

                inSequence[inSequence_Count] = x;
                inSequence_Count++;

            }
            else {

                stationary[stationary_Count] = x;
                stationary_Count++;

            }

        }
        
    }


    if (inSequence_Count > 0 && stationary_Count > 0) {

        if (rand() % 5 == 0) {
            return &this->enemies[stationary[rand() % stationary_Count]];
        }
        else { 
            return &this->enemies[inSequence[rand() % inSequence_Count]];
        }

    }
    else {

        if (inSequence_Count > 0) {
            return &this->enemies[inSequence[rand() % inSequence_Count]];
        }
        else if (stationary_Count > 0) {
            return &this->enemies[stationary[rand() % stationary_Count]];
        }

    }

    return nullptr;

}

bool Enemies::launchEnemies(uint32_t enemyPosition, EnemyFormation enemyFormation, bool flipHorizontal, uint8_t sequenceIndex) {

    uint8_t stationary[50];
    uint32_t stationary_Count = 0;

    switch (enemyFormation) {

        case EnemyFormation::Single:
            {
                uint32_t startLoop = 0;
                uint32_t endLoop = ENEMY_COUNT;

                if ((enemyPosition & UPPER_ENEMY_POS) > 0) endLoop = ENEMY_COUNT - (2 * ENEMY_COL_COUNT);
                if ((enemyPosition & LOWER_ENEMY_POS) > 0) startLoop = (2 * ENEMY_COL_COUNT);

                if ((enemyPosition & BOSS_ENEMY_ONLY) > 0)  {
                    
                    if ((enemyPosition & LHS_ENEMY_POS) > 0) {
                        startLoop = ENEMY_BOSS_INDEX_START;
                        endLoop = ENEMY_BOSS_INDEX_END + 2;
                    }
                    else if ((enemyPosition & RHS_ENEMY_POS) > 0) {
                        startLoop = ENEMY_BOSS_INDEX_START + 2;
                        endLoop = ENEMY_BOSS_INDEX_END + 1;
                    }
                    else {
                        startLoop = ENEMY_BOSS_INDEX_START;
                        endLoop = ENEMY_BOSS_INDEX_END + 1;
                    }

                }
                    
                for (uint32_t x = startLoop; x < endLoop; x++) {

                    Enemy &enemy = this->enemies[x];

                    switch (enemyPosition & ALL_LHS_RHS) {

                        case ALL_ENEMY_POS:
                            if (enemy.isVisible() && enemy.isEnabled() && !enemy.inSequence()) {
                                stationary[stationary_Count] = x;
                                stationary_Count++;
                            }
                            break;

                        case LHS_ENEMY_POS:
                            if ((x % ENEMY_COL_COUNT < ENEMY_COL_COUNT / 2) && enemy.isVisible() && enemy.isEnabled() && !enemy.inSequence()) {
                                stationary[stationary_Count] = x;
                                stationary_Count++;
                            }

                            break;

                        case RHS_ENEMY_POS:
                            if ((x % ENEMY_COL_COUNT >= ENEMY_COL_COUNT / 2) && enemy.isVisible() && enemy.isEnabled() && !enemy.inSequence()) {
                                stationary[stationary_Count] = x;
                                stationary_Count++;
                            }

                            break;

                    }
                    
                }

            }

            if (stationary_Count > 0) {

                uint32_t enemyIndex = rand() % stationary_Count;

                Enemy &enemy = this->enemies[stationary[enemyIndex]];
                enemy.setFlipHorizontal(flipHorizontal);
                enemy.setSequence(sequenceIndex);

                return true;

            }

            return false;

        case EnemyFormation::Two:
            {
                uint32_t startLoop = 0;
                uint32_t endLoop = ENEMY_COUNT - 1;

                if ((enemyPosition & UPPER_ENEMY_POS) > 0) endLoop = ENEMY_COUNT - (2 * ENEMY_COL_COUNT) - 1;
                if ((enemyPosition & LOWER_ENEMY_POS) > 0) startLoop = (2 * ENEMY_COL_COUNT);

                if ((enemyPosition & BOSS_ENEMY_ONLY) > 0)  {

                    if ((enemyPosition & LHS_ENEMY_POS) > 0) {
                        startLoop = ENEMY_BOSS_INDEX_START;
                        endLoop = ENEMY_BOSS_INDEX_END + 2;
                    }
                    else if ((enemyPosition & RHS_ENEMY_POS) > 0) {
                        startLoop = ENEMY_BOSS_INDEX_START + 2;
                        endLoop = ENEMY_BOSS_INDEX_END + 1;
                    }
                    else {
                        startLoop = ENEMY_BOSS_INDEX_START;
                        endLoop = ENEMY_BOSS_INDEX_END + 1;
                    }
                    
                }

                for (uint32_t x = startLoop; x < endLoop; x++) {

                    Enemy &enemy1 = this->enemies[x];
                    Enemy &enemy2 = this->enemies[x + 1];

                    switch (enemyPosition & ALL_LHS_RHS) {

                        case ALL_ENEMY_POS:

                            if (x % ENEMY_COL_COUNT < ENEMY_COL_COUNT - 1) {
                                if (enemy1.isVisible() && enemy1.isEnabled() && !enemy1.inSequence() && enemy2.isVisible() && enemy2.isEnabled() && !enemy2.inSequence()) {
                                    stationary[stationary_Count] = x;
                                    stationary_Count++;
                                }
                            }
                            break;

                        case LHS_ENEMY_POS:

                            if (x % ENEMY_COL_COUNT < (ENEMY_COL_COUNT / 2) - 1) {
                                if (enemy1.isVisible() && enemy1.isEnabled() && !enemy1.inSequence() && enemy2.isVisible() && enemy2.isEnabled() && !enemy2.inSequence()) {
                                    stationary[stationary_Count] = x;
                                    stationary_Count++;
                                }
                            }

                            break;

                        case RHS_ENEMY_POS:

                            if ((x % ENEMY_COL_COUNT >= ENEMY_COL_COUNT / 2) && (x % ENEMY_COL_COUNT <= 8)) {
                                if (enemy1.isVisible() && enemy1.isEnabled() && !enemy1.inSequence() && enemy2.isVisible() && enemy2.isEnabled() && !enemy2.inSequence()) {
                                    stationary[stationary_Count] = x;
                                    stationary_Count++;
                                }
                            }

                            break;

                    }
                    
                }

            }

            if (stationary_Count > 0) {

                uint32_t enemyIndex = rand() % stationary_Count;
                Enemy &enemy1 = this->enemies[stationary[enemyIndex]];
                enemy1.setFlipHorizontal(flipHorizontal);
                enemy1.setSequence(sequenceIndex);

                Enemy &enemy2 = this->enemies[stationary[enemyIndex] + 1];
                enemy2.setFlipHorizontal(flipHorizontal);
                enemy2.setSequence(sequenceIndex);

                return true;

            }

            return false;
            
        case EnemyFormation::Four:
            {
                uint8_t startLoop = 0;
                uint8_t endLoop = ENEMY_COUNT - ENEMY_COL_COUNT - 1;

                if ((enemyPosition & UPPER_ENEMY_POS) > 0) endLoop = ENEMY_COUNT - (3 * ENEMY_COL_COUNT) - 1;
                if ((enemyPosition & LOWER_ENEMY_POS) > 0) startLoop = (2 * ENEMY_COL_COUNT);

                if ((enemyPosition & BOSS_ENEMY_ONLY) > 0)  {

                    if ((enemyPosition & LHS_ENEMY_POS) > 0) {
                        startLoop = ENEMY_BOSS_INDEX_START;
                        endLoop = ENEMY_BOSS_INDEX_END + 2;
                    }
                    else if ((enemyPosition & RHS_ENEMY_POS) > 0) {
                        startLoop = ENEMY_BOSS_INDEX_START + 2;
                        endLoop = ENEMY_BOSS_INDEX_END + 1;
                    }
                    else {
                        startLoop = ENEMY_BOSS_INDEX_START;
                        endLoop = ENEMY_BOSS_INDEX_END + 1;
                    }

                }

                for (uint32_t x = startLoop; x < endLoop; x++) {

                    Enemy &enemy1 = this->enemies[x];
                    Enemy &enemy2 = this->enemies[x + 1];
                    Enemy &enemy3 = this->enemies[x + ENEMY_COL_COUNT];
                    Enemy &enemy4 = this->enemies[x + ENEMY_COL_COUNT + 1];

                    switch (enemyPosition & ALL_LHS_RHS) {

                        case ALL_ENEMY_POS:

                            if (x % ENEMY_COL_COUNT < ENEMY_COL_COUNT - 1) {
                                if (enemy1.isVisible() && enemy1.isEnabled() && !enemy1.inSequence() &&
                                    enemy2.isVisible() && enemy2.isEnabled() && !enemy2.inSequence() &&
                                    enemy3.isVisible() && enemy3.isEnabled() && !enemy3.inSequence() &&
                                    enemy4.isVisible() && enemy3.isEnabled() && !enemy4.inSequence()) {
                                    stationary[stationary_Count] = x;
                                    stationary_Count++;
                                }
                            }
                            break;

                        case LHS_ENEMY_POS:

                            if (x % ENEMY_COL_COUNT < (ENEMY_COL_COUNT / 2) - 1) {
                                if (enemy1.isVisible() && enemy1.isEnabled() && !enemy1.inSequence() &&
                                    enemy2.isVisible() && enemy2.isEnabled() && !enemy2.inSequence() &&
                                    enemy3.isVisible() && enemy3.isEnabled() && !enemy3.inSequence() &&
                                    enemy4.isVisible() && enemy3.isEnabled() && !enemy4.inSequence()) {
                                    stationary[stationary_Count] = x;
                                    stationary_Count++;
                                }
                            }

                            break;

                        case RHS_ENEMY_POS:

                            if ((x % ENEMY_COL_COUNT >= ENEMY_COL_COUNT / 2) && (x % ENEMY_COL_COUNT <= ENEMY_COL_COUNT - 2)) {
                                if (enemy1.isVisible() && enemy1.isEnabled() && !enemy1.inSequence() &&
                                    enemy2.isVisible() && enemy2.isEnabled() && !enemy2.inSequence() &&
                                    enemy3.isVisible() && enemy3.isEnabled() && !enemy3.inSequence() &&
                                    enemy4.isVisible() && enemy3.isEnabled() && !enemy4.inSequence()) {
                                    stationary[stationary_Count] = x;
                                    stationary_Count++;
                                }
                            }

                            break;

                    }
                    
                }

            }

            if (stationary_Count > 0) {

                uint8_t enemyIndex = rand() % stationary_Count;
                Enemy &enemy1 = this->enemies[stationary[enemyIndex]];
                enemy1.setFlipHorizontal(flipHorizontal);
                enemy1.setSequence(sequenceIndex);

                Enemy &enemy2 = this->enemies[stationary[enemyIndex] + 1];
                enemy2.setFlipHorizontal(flipHorizontal);
                enemy2.setSequence(sequenceIndex);

                Enemy &enemy3 = this->enemies[stationary[enemyIndex] + ENEMY_COL_COUNT];
                enemy3.setFlipHorizontal(flipHorizontal);
                enemy3.setSequence(sequenceIndex);

                Enemy &enemy4 = this->enemies[stationary[enemyIndex] + ENEMY_COL_COUNT + 1];
                enemy4.setFlipHorizontal(flipHorizontal);
                enemy4.setSequence(sequenceIndex);

                return true;

            }

            return false;
            
    }

    return false;

}


bool Enemies::allEnemiesDead() {

    for (uint32_t x = 0; x < ENEMY_COUNT; x++) {
        
        Enemy &enemy = this->enemies[x];
        if (enemy.isEnabled() || enemy.isExploding() || enemy.getSequence() == Formations::sequences[Formations::SEQ_RETURN_TO_FORMATION]) {
            
            return false;
            
        }

    }

    return true;
    
}


void Enemies::disableAllEnemies() {

    for (uint32_t x = 0; x < ENEMY_COUNT; x++) {
        
        Enemy &enemy = this->enemies[x];
        enemy.setEnabled(false);
        enemy.setPoofIndex(0);
        enemy.setSequence(nullptr);

    }
    
}


bool Enemies::allSequencesComplete() {
    
    for (uint32_t x = 0; x < 50; x++) {
        
        Enemy &enemy = this->enemies[x];
        if (enemy.isEnabled() && enemy.isVisible() && enemy.inSequence()) {

            return false;
            
        }
        
    }

    return true;

}


uint32_t Enemies::getNumberOfActiveEnemies() {
    
    uint32_t count = 0;

    for (uint32_t x = 0; x < 50; x++) {
        
        Enemy &enemy = this->enemies[x];
        if (enemy.isEnabled() && !enemy.isExploding()) {
            
            count++;
            
        }
        
    }

    return count;

}

uint32_t Enemies::canTransformEnemy(uint32_t enemyPosition) {

    uint8_t bee[20];
    uint8_t butterfly[20];
    uint8_t bee_Count = 0;
    uint8_t butterfly_Count = 0;

    uint32_t startLoop = 10;
    uint32_t endLoop = ENEMY_COUNT;

    if ((enemyPosition & UPPER_ENEMY_POS) > 0) endLoop = ENEMY_COUNT - (2 * ENEMY_COL_COUNT);
    if ((enemyPosition & LOWER_ENEMY_POS) > 0) startLoop = (2 * ENEMY_COL_COUNT);

    for (uint32_t x = startLoop; x < endLoop; x++) {

        Enemy &enemy = this->enemies[x];

        switch (enemyPosition) {

            case ALL_ENEMY_POS:
                if (enemy.isVisible() && enemy.isEnabled() && !enemy.inSequence()) {

                    if (x < 30) {
                        butterfly[butterfly_Count] = x;
                        butterfly_Count++;
                    }
                    else {
                        bee[bee_Count] = x;
                        bee_Count++;
                    }

                }
                break;

            case LHS_ENEMY_POS:
                if ((x % ENEMY_COL_COUNT < ENEMY_COL_COUNT / 2) && enemy.isVisible() && enemy.isEnabled() && !enemy.inSequence()) {

                    if (x < 30) {
                        butterfly[butterfly_Count] = x;
                        butterfly_Count++;
                    }
                    else {
                        bee[bee_Count] = x;
                        bee_Count++;
                    }

                }

                break;

            case RHS_ENEMY_POS:
                if ((x % ENEMY_COL_COUNT >= ENEMY_COL_COUNT / 2) && enemy.isVisible() && enemy.isEnabled() && !enemy.inSequence()) {

                    if (x < 30) {
                        butterfly[butterfly_Count] = x;
                        butterfly_Count++;
                    }
                    else {
                        bee[bee_Count] = x;
                        bee_Count++;
                    }

                }

                break;

        }

    }

    // Return a bee if possible, otherwise a butterfly ..

    if (bee_Count > 0) {

        return bee[rand() % bee_Count];

    }
    else if (butterfly_Count > 0) {

        return butterfly[rand() % butterfly_Count];

    }
    else return NO_ENEMY;

}