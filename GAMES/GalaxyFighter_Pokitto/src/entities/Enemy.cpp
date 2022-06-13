

#include "Enemy.h"

#include "../utils/Constants.h"
#include "../utils/Utils.h"
#include "../data/Formations.h"

Enemy::Enemy() { }

void Enemy::reset() {

    this->x = 0;
    this->y = 0;
    this->x_Formation = 0;
    this->y_Formation = 0;
    this->x_Orig = 0;
    this->y_Orig = 0;
    this->xDelta = 0;

    this->gridPosition = -1;           
    this->enemyType = EnemyType::Butterfly;       
    this->sequenceCounter = 0;
    this->imageIndex = 0;
    this->repeat = 0;
    this->health = 0;

    this->enabled = false;   
    this->visible = false;
    this->moveToGrid = false;     
    this->rotateToUpright = false;
    this->rotateFactor = 0;    
    this->flipHorizontal = false;  
    this->explosionCounter = 0;   
    this->wrapHorizontally = false;
    this->poofIndex = 0;
    this->enemyHasBeenCaptured = false;
    this->wasInSequence = false;

    this->tractorEnabled = false;
    this->tractor = 0;
    this->tractorHighlight = 0;

}


float Enemy::getX() {
    
    return this->x;

}

float Enemy::getXDelta() {

    if (this->xDelta > 1.25)   return 1.25 * (this->flipHorizontal ? -1 : 1);
    if (this->xDelta < -1.25)  return -1.25 * (this->flipHorizontal ? -1 : 1);

    return this->xDelta * (this->flipHorizontal ? -1 : 1);

}

float Enemy::getY() {
    
    return this->y;

}

int16_t Enemy::getX_Formation() {
    
    return this->x_Formation;

}

int16_t Enemy::getY_Formation() {
    
    return this->y_Formation;

}

int8_t Enemy::getGridPosition() {
    
    return this->gridPosition;

}

EnemyType Enemy::getEnemyType() {

    if (this->enemyType == EnemyType::Player && this->poofIndex >= 4) {
        return EnemyType::Cyan;
    }

    return this->enemyType;

}

uint8_t Enemy::getImageIndex() {

    if (this->imageIndex <= 12) {
        return this->imageIndex;
    }
    else {
        return 24 - this->imageIndex;
    }

}

uint8_t Enemy::getImageIndex_Raw() {

    return this->imageIndex;

}

SequenceType Enemy::getSequenceType() {

    return this->sequenceType;

}

bool Enemy::getImageFlip() {
    
    if (!flipHorizontal) {
        return (this->imageIndex > 12);
    }
    else {
        return (this->imageIndex <= 12);
    }

}

uint8_t Enemy::getRepeat() {
    
    return this->repeat;

}

uint32_t Enemy::getWidth() {

    return 14; //TODO: Fix widths / heights

}

uint32_t Enemy::getHeight() {

    return 14;

}

uint8_t Enemy::getPoofIndex() {

    return this->poofIndex;

}

bool Enemy::isEnabled() {
    return this->enabled;
}

bool Enemy::isVisible() {
    
    return this->visible && (this->explosionCounter < 5);

}

bool Enemy::isTractorEnabled() {

    return this->tractorEnabled;
    
}

bool Enemy::getEnemyHasBeenCaptured() {

    return this->enemyHasBeenCaptured;
    
}

uint8_t Enemy::getTractorImage() {

    return this->tractor;

}

uint8_t Enemy::getTractorImageHighlight() {

    return this->tractorHighlight;

}

CapturedPlayer Enemy::getCapturedPlayer() {

    return this->capturedPlayer;

}

const SequenceData * Enemy::getSequence() {

    return this->sequence;

}

uint8_t Enemy::getHealth() {

    return this->health;

}

void Enemy::setX(float x) {

    this->x = x;
    this->x_Orig = x;

}

void Enemy::setY(float y) {

    this->y = y;
    this->y_Orig = y;

}

void Enemy::setX_Formation(int16_t x) {

    this->x_Formation = x;

}

void Enemy::setY_Formation(int16_t y) {

    this->y_Formation = y;

}

void Enemy::setGridPosition(int8_t gridPosition) {

    this->gridPosition = gridPosition;

}

void Enemy::setEnemyHasBeenCaptured(bool enemyHasBeenCaptured) {

    this->enemyHasBeenCaptured = enemyHasBeenCaptured;

}

void Enemy::setEnemyType(EnemyType enemyType) {
    
    //                         Butterfly  Butterfly_Boss, Bee  Purple, Cyan  Scorpion, Midori, Galaxian, Tonbo, Momiji, Enterprise, Player
    const uint32_t health[]  = { 1,         2,              1,   2,      2,    1,        1,      1,        1,     1,       1,         1 }; 

    this->health = health[static_cast<uint8_t>(enemyType)];
    this->enemyType = enemyType;

}

void Enemy::setImageIndex(uint8_t imageIndex) {

    this->imageIndex = imageIndex;

}

void Enemy::setSequence(uint8_t sequenceIndex) {

    #ifdef DEBUG
    this->setSequenceIndex(sequenceIndex);
    #endif

    this->setSequence(Formations::sequences[sequenceIndex]);

}

void Enemy::setSequence(const SequenceData * sequence) {

    this->sequence = sequence;
    this->sequenceCounter = 0;
    this->repeat = 0;
    this->poofIndex = 0;
    this->enemyHasBeenCaptured = false;
    this->wasInSequence = false;

    if (sequence != nullptr) {
        this->visible = true;
        this->explosionCounter = 0;
    }

}

void Enemy::setRepeat(uint8_t repeat) {

    this->repeat = repeat;

}

void Enemy::setPoofIndex(uint32_t poofIndex) {

    this->poofIndex = poofIndex;

}

void Enemy::setFormationData(FormationData formationData) {
    
    this->gridPosition = formationData.gridPosition;
    this->setEnemyType(formationData.enemyType);
    this->x = formationData.x;
    this->y = formationData.y;
    this->x_Orig = formationData.x;
    this->y_Orig = formationData.y;

            
    if (formationData.x <= -20 || formationData.x >= SCREEN_WIDTH || formationData.y <= -20 or formationData.y >= PD::height) {
        
        this->visible = false;
        
    }
    else {

        this->visible = true;
        
    }
    
}

void Enemy::setEnabled(bool enabled) {

    #ifdef DEBUG
        if (enabled && this->enemyIndex < 3) {
            printf("Enemy.setEnabled() seq: %i, enemyIdx: %i\n", this->sequenceIndex, this->enemyIndex);
        }
    #endif

    this->enabled = enabled;

    if (!enabled) {

        this->enemyHasBeenCaptured = false;

    }

}

void Enemy::setVisible(bool visible) {

    this->visible = visible;

}

void Enemy::setCapturedPlayer(CapturedPlayer capturedPlayer) {

    this->capturedPlayer = capturedPlayer;

}

void Enemy::setFlipHorizontal(bool flipHorizontal) {

    this->flipHorizontal = flipHorizontal;
    
}


bool Enemy::inSequence() {

    return (this->sequence != nullptr);

}

bool Enemy::isUprightPosition() {

    return (this->imageIndex % 6 == 0);

}

bool Enemy::isExploding() {

    return (this->explosionCounter > 0);

}

uint32_t Enemy::getExplosionImageIndex() {
    
    return (this->explosionCounter - 1) / 3;

}

uint32_t Enemy::getExplosionImageOffset() {
    
    const uint32_t offsets[] = { 10, 8, 6, 0, 0 };

    return offsets[(this->explosionCounter - 1) / 3];

}

uint32_t Enemy::killEnemy() {

    if (this->explosionCounter == 0) this->explosionCounter = 1;
    if (this->enemyType == EnemyType::Cyan) this->enemyType = EnemyType::Purple;

    if (this->health > 0) this->health--;

    return this->getScore();
    
}

void Enemy::updatePosition(bool alternateFrame) {
    
    if (this->explosionCounter > 0) {

        this->explosionCounter++;
        if (explosionCounter == 2) Utils::playMusicStream(SDStream::Explosion);
        if (this->health > 0 && this->explosionCounter == 5) {

            this->explosionCounter = 0;
            
        }

        if (this->explosionCounter == 16) {

            this->enabled = false;
            this->explosionCounter = 0;
            this->tractorEnabled = false;
            this->tractor = 0;
            this->capturedPlayer = CapturedPlayer::None;
            this->wasInSequence = !(this->sequence == nullptr);
            this->sequence = nullptr;
            this->enemyHasBeenCaptured = false;

        }
        
        return;        
        
    }
        
    if (this->sequence != nullptr) {
        
        if (this->repeat > 0) {

            if (this->rotateToUpright) {

                if (alternateFrame) {
        
                    this->repeat--;
                    this->imageIndex = this->imageIndex + this->rotateFactor;
                    if (this->imageIndex == 24) this->imageIndex = 0;

                }
    
            }
            else {
                            
                this->repeat--;

            }
            
        }
        else {
            
            this->wrapHorizontally = false;
            this->moveToGrid = false;
            this->rotateToUpright = false;
            this->sequenceData = this->sequence[this->sequenceCounter];
            this->xDelta = this->sequenceData.x;
            this->sequenceCounter++;
            this->sequenceType = this->sequenceData.patternType;

            switch (this->sequenceData.patternType) {
                
                case SequenceType::Normal:
                
                    imageIndex = this->sequenceData.imageIndex;
                    this->repeat = sequenceData.repeat;
                    
                    break;
                    
                case SequenceType::PosAbsolute:
                
                    imageIndex = this->sequenceData.imageIndex;

                    if (!flipHorizontal) {
                        this->x = this->sequenceData.x;
                        this->y = this->sequenceData.y;
                    }
                    else {
                        this->x = SCREEN_WIDTH_HALF - this->sequenceData.x;
                        this->y = this->sequenceData.y;
                    }
                    
                    this->sequenceData.x = 0;
                    this->sequenceData.y = 0;

                    return;
                    
                case SequenceType::PosRelative:
                
                    imageIndex = this->sequenceData.imageIndex;

                    if (!flipHorizontal) {
                        this->x = this->x + this->sequenceData.x;
                        this->y = this->y + this->sequenceData.y;
                    }
                    else {
                        this->x = this->x - this->sequenceData.x;
                        this->y = this->y - this->sequenceData.y;
                    }
                    
                    this->sequenceData.x = 0;
                    this->sequenceData.y = 0;

                    return;
                    
                case SequenceType::PosOffset:
                
                    imageIndex = this->sequenceData.imageIndex;

                    if (!flipHorizontal) {
                        this->x = this->x_Orig + this->sequenceData.x;
                        this->y = this->y_Orig + this->sequenceData.y;
                    }
                    else {
                        this->x = this->x_Orig + this->sequenceData.x;
                        this->y = this->y_Orig + this->sequenceData.y;
                    }
                    
                    this->sequenceData.x = 0;
                    this->sequenceData.y = 0;

                    return;
                    
                case SequenceType::RotateToUpright:

                    this->rotateToUpright = true;

                    if (this->imageIndex > 12) {
                        this->repeat = 24 - imageIndex;
                        this->rotateFactor = 1;
                    } 
                    else {
                        this->repeat = imageIndex;
                        this->rotateFactor = -1;
                    }

                    return;
                  
                case SequenceType::MoveToGridPos:
                    {
                        imageIndex = this->sequenceData.imageIndex;

                        float deltaX = this->x - this->x_Formation;
                        float deltaY = this->y - this->y_Formation;

                        uint8_t incX = Utils::absT(deltaX / (this->sequenceData.x + 1));
                        uint8_t incY = Utils::absT(deltaY / (this->sequenceData.y + 1));

                        this->repeat = (incX > incY ? incX : incY);
                        this->moveToGrid = true;
                        this->xDelta = deltaX;
                        
                        
                        // Work out which image to use ..
                        
                        getImageIndexFromGrad(deltaX, deltaY);

                        if (!flipHorizontal) {

                            sequenceData.x = -(deltaX / this->repeat);
                            sequenceData.y = -(deltaY / this->repeat);

                        }
                        else {

                            sequenceData.x = (deltaX / this->repeat);
                            sequenceData.y = -(deltaY / this->repeat);

                        }

                    }
                    
                    break;

                case SequenceType::WrapHorizontally:

                    imageIndex = this->sequenceData.imageIndex;
                    this->repeat = sequenceData.repeat;
                    this->wrapHorizontally = true;
                    
                    break;
                    
                case SequenceType::Disable:
                
                    this->enabled = false;

                    break;
                    
                case SequenceType::Tractor0:

                    this->tractorEnabled = false;

                    if (this->capturedPlayer == CapturedPlayer::Initial && this->enemyHasBeenCaptured) {

                        this->capturedPlayer = CapturedPlayer::Below;

                    }

                    break;
                    
                case SequenceType::Tractor1 ... SequenceType::Tractor5:

                    if (this->capturedPlayer != CapturedPlayer::Joined) {

                        this->tractor = static_cast<uint8_t>(this->sequenceData.patternType) - static_cast<uint8_t>(SequenceType::Tractor1);
                        this->tractorHighlight = 5;
                        this->repeat = sequenceData.repeat;
                        this->tractorEnabled = true;

                    }

                    break;
                    
                case SequenceType::MoveCapturedAbove:

                    if (this->capturedPlayer == CapturedPlayer::Below) {

                        this->capturedPlayer = CapturedPlayer::Above;

                    }
                    else {

                        this->poofIndex = 0;
                        this->sequenceCounter = 0;
                        this->wasInSequence = !(this->sequence == nullptr);
                        this->sequence = nullptr;
                        this->imageIndex = 0;
                        this->xDelta = 0;

                    }

                    break;
                    
                case SequenceType::TransformToBOSS_00:

                    this->poofIndex = 0;
                    break;
                    
                case SequenceType::TransformToBOSS_01 ... SequenceType::TransformToBOSS_07:

                    this->poofIndex = static_cast<uint32_t>(this->sequenceData.patternType) - static_cast<uint32_t>(SequenceType::TransformToBOSS_00);
                    this->repeat = sequenceData.repeat;
                    break;
                    
                case SequenceType::TransformToBOSS_Cyan:

                    this->poofIndex = 0;
                    this->setEnemyType(EnemyType::Cyan);
                    this->setEnabled(true);
                    this->sequenceCounter = 0;
                    this->wasInSequence = !(this->sequence == nullptr);
                    this->sequence = nullptr;
                    this->imageIndex = 0;
                    this->xDelta = 0;
                    break;
                    
                case SequenceType::End:
                
                    this->sequenceCounter = 0;
                    this->wasInSequence = !(this->sequence == nullptr);
                    this->sequence = nullptr;
                    this->imageIndex = 0;
                    this->xDelta = 0;

                    break;

            }

        }


        // Update the tractor beam highlight ..

        if (this->sequenceType == SequenceType::Tractor5 && repeat % 5 == 0) {

            if (this->tractorHighlight > 0) {
                this->tractorHighlight--;
            }
            else {
                this->tractorHighlight = 4;
            }

        }


        // if this is the last step of a 'moveToGrid' sequence then make sure the enemy is snapped to the grid ..

        if (this->repeat == 0 && this->moveToGrid) {

            this->x = this->x_Formation;
            this->y = this->y_Formation;

        }
        else {


            // Otherwise just move the enemy ..

            if (!flipHorizontal) {

                this->x = this->x + this->sequenceData.x;
                this->y = this->y + this->sequenceData.y;

            }
            else {

                this->x = this->x - this->sequenceData.x;
                this->y = this->y + this->sequenceData.y;

            }


            // Have we wrapped horizontally?

            if (this->wrapHorizontally) {

                if (this->x < -20) { 
                    
                    this-> x = 200; 
                    this->wrapHorizontally = false;
                    
                }
                else if (this->x > 200) {

                    this-> x = -20; 
                    this->wrapHorizontally = false;

                }

            }

        }

    }
    
}

void Enemy::getImageIndexFromGrad(float deltaX, float deltaY) {

    //                                     0 --------- 1 ------ 2 ------ 3 ------ 4 ------ 5 ------ 6 ------ 7 ------ 8 ------ 9 ------ 10 ----- 11 ----- 12 ----- 
    const float grads[] =            { -9999999.0, -7.5958, -2.4142, -1.3032, -0.7673, -0.4142, -0.1317, 0.1317,  0.4142,  0.7673,  1.3032,  2.4142,  7.5957 };
    const uint8_t grads_Positive[] = { 18,         19,      20,      21,      22,      23,      0,       1,       2,       3,       4,       5,       6      };
    const uint8_t grads_Negative[] = { 6,          7,       8,       9,       10,      11,      12,      13,      14,      15,      16,      17,      18     };

    float grad = deltaX / deltaY;    

    if (deltaY >= 0) {

        for (uint32_t i = 13; i > 0; i--) {
            
            if (grad > grads[i - 1]) {
                
                if (!flipHorizontal) {
    
                    this->imageIndex = grads_Positive[i - 1];
                    break;
                    
                }
                else {

                    this->imageIndex = grads_Positive[13 - i];
                    break;
                    
                }

            }
            
        }
            
        
    }
    else {

        for (uint32_t i = 13; i > 0; i--) {
            
            if (grad > grads[i - 1]) {
                
                if (!flipHorizontal) {
                    
                    this->imageIndex = grads_Negative[i - 1];
                    break;
                    
                }
                else {

                    this->imageIndex = grads_Negative[13 - i];
                    break;
                    
                }

            }
            
        }
        
    }
    
}

uint32_t Enemy::getScore() {
    
    //                                Red  Blue  Purple, Cyan   Scorpion, Midori, Galaxian
    const uint32_t inFormation[]  = { 80,  50,   150,    150,   160,      160,    160 }; 
    const uint32_t inSequence[]  =  { 160, 100,  400,    400,   160,      160,    160 }; 

    if (this->sequence != nullptr) {

        return inFormation[static_cast<uint8_t>(this->enemyType)];

    }
    else {

        return inSequence[static_cast<uint8_t>(this->enemyType)];

    }

}

bool Enemy::inSequenceBeforeDeath() {

    bool wasInSequence = this->wasInSequence;
    this->wasInSequence = false;

    return wasInSequence;

}

#ifdef DEBUG
uint8_t Enemy::getEnemyIndex() {

    return this->enemyIndex;

}
#endif

#ifdef DEBUG
uint8_t Enemy::getSequenceIndex() {

    return this->sequenceIndex;

}
#endif

#ifdef DEBUG

void Enemy::setEnemyIndex(uint8_t enemyIndex) {

    this->enemyIndex = enemyIndex;

}
#endif

#ifdef DEBUG

void Enemy::setSequenceIndex(uint8_t sequenceIndex) {

    if (sequenceIndex == Formations::SEQ_RETURN_TO_FORMATION) {
        printf("enemy.setSequenceIndex(Formations::SEQ_RETURN_TO_FORMATION)\n");
    }

    this->sequenceIndex = sequenceIndex;

}
#endif