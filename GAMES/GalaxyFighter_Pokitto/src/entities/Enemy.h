#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../utils/Structs.h"

class Enemy {

    public:

        Enemy();


        // Properties ..
        
        float getX();
        float getXDelta();
        float getY();
        int16_t getX_Formation();
        int16_t getY_Formation();
        int8_t getGridPosition();
        uint8_t getImageIndex();
        uint8_t getImageIndex_Raw();
        uint8_t getRepeat();
        bool isEnabled();
        bool isVisible();
        bool getEnemyHasBeenCaptured();
        uint8_t getPoofIndex();
        bool isTractorEnabled();
        uint8_t getTractorImage();
        uint8_t getTractorImageHighlight();
        uint8_t getHealth();
        CapturedPlayer getCapturedPlayer();
        EnemyType getEnemyType();
        SequenceType getSequenceType();
        const SequenceData * getSequence();

        #ifdef DEBUG
        uint8_t getEnemyIndex();
        uint8_t getSequenceIndex();
        #endif


        void setX(float x);
        void setY(float y);
        void setX_Formation(int16_t x);
        void setY_Formation(int16_t y);
        void setGridPosition(int8_t gridPosition);
        void setEnemyType(EnemyType enemyType);
        void setImageIndex(uint8_t imageIndex);
        void setSequence(uint8_t sequenceIndex);
        void setSequence(const SequenceData * sequence);
        void setRepeat(uint8_t repeat);
        void setEnabled(bool enabled);
        void setVisible(bool visible);
        void setEnemyHasBeenCaptured(bool enemyHasBeenCaptured);
        void setFlipHorizontal(bool flipHorizontal);
        void setCapturedPlayer(CapturedPlayer capturedPlayer);
        void setPoofIndex(uint32_t poofIndex);

        #ifdef DEBUG
        void setEnemyIndex(uint8_t enemyIndex);
        void setSequenceIndex(uint8_t sequenceIndex);
        #endif

        
        // Methods ..

        void updatePosition(bool alternateFrame);
        void setFormationData(FormationData formationData);
        bool inSequence();
        bool isUprightPosition();
        bool getImageFlip();
        void getImageIndexFromGrad(float deltaX, float deltaY);
        uint32_t getWidth();
        uint32_t getHeight();
        uint32_t getScore();
        bool inSequenceBeforeDeath();
        void reset();

        // Kill the enemy !
        
        uint32_t killEnemy();               // Returns score to add.
        bool isExploding();
        uint32_t getExplosionImageIndex();
        uint32_t getExplosionImageOffset();

    private:

        float x = 0;
        float y = 0;
        int16_t x_Formation = 0;
        int16_t y_Formation = 0;
        float x_Orig = 0;
        float y_Orig = 0;
        float xDelta = 0;                   // Used to store the X delta from the current movement to allow us to have the bullets drop in the same direction.
        
        int8_t gridPosition = -1;           
        EnemyType enemyType = EnemyType::Butterfly;       
        uint16_t sequenceCounter = 0;
        uint8_t imageIndex = 0;
        uint16_t repeat = 0;
        uint8_t health = 0;
        
        bool enabled = false;                  // Is the enemy active in the level?
        bool visible = false;                  // Is the enemy visible?  This will be set to false for enemies starting out of the screen at start of level but will remain true once they become visible.
        uint8_t moveToGrid = false;            // Is the enemy currently executing a moveToGrid sequence?  If so, on the last step, make sure that the enemy is alligned exactly with grid.
        uint8_t rotateToUpright = false;       // Is the enemy currently being rotated to the upright position?
        int8_t rotateFactor = 0;               // If the enemy is currently being rotated, which way? +ve anti-clockwise.
        bool flipHorizontal = false;           // Flip the current sequence horizontally?
        uint8_t explosionCounter = 0;          // Explosion counter - 0 not exploding, 1-3, 4-6, 7-9, 10-12, 13-15 are graphics indexes 0 - 4.
        uint8_t wrapHorizontally = false;      // Wrap around screen when we get to - 20 or 200
        
        SequenceType sequenceType;       
        const SequenceData * sequence;      
        SequenceData sequenceData;

        uint8_t poofIndex = 0;
        CapturedPlayer capturedPlayer;
        bool enemyHasBeenCaptured = false;
        uint8_t wasInSequence = false;

        bool tractorEnabled = false;
        uint8_t tractor = 0;
        uint8_t tractorHighlight = 0;

        #ifdef DEBUG
        uint8_t enemyIndex;
        uint8_t sequenceIndex;
        #endif

};
