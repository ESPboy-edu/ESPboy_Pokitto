#pragma once

#include "Pokitto.h"
#include "Enums.h"

struct LevelData {
    
    LevelType levelType;
    uint8_t enemyIndex;
    uint8_t index;
    bool flipHorizontal;
    uint8_t delay;

};

struct FormationData {
    
    int8_t gridPosition;  
    int16_t x;
    int16_t y;
    EnemyType enemyType;
    uint8_t repeat;
    
};


struct SequenceData {
    
    SequenceType patternType;
    uint16_t repeat = 0;
    float x = 0;
    float y = 0;
    uint8_t imageIndex;
    
};


struct Transform {
    
    bool activated = false;
    uint8_t counter = 0;
    uint8_t deaths = 0;
    uint8_t rewardImageCounter = 0;		// Counter showing reward ..
    uint8_t rewardImageIndex = 0;		// Image to show - Scorpion = 0, Midori = 1, Galaxian = 2 ..
    int16_t rewardImageX = 0;		
    int16_t rewardImageY = 0;		

};

struct Challenge {
    
    uint8_t level;
    uint32_t score = 0;
    uint32_t hitsOverall = 0;
    int8_t sequence = -1;
    uint8_t hitsThisSequence = 0;
    uint8_t rewardImageCounter = 0;		// Counter showing reward ..
    uint8_t rewardImageIndex = 0;		// Image to show - Scorpion = 0, Midori = 1, Galaxian = 2 ..
    int16_t rewardImageX = 0;		
    int16_t rewardImageY = 0;	
    uint8_t enemiesInWave = 0;	
    uint8_t enemiesOverall = 0;	

    void clear(bool retainLevel) {

        this->sequence = -1;
        this->score = 0;
        this->hitsOverall = 0;
        this->hitsThisSequence = 0;
        this->enemiesOverall = 0;

        if (!retainLevel) {
            level = 0;
        }

    }

    uint32_t getNumberOfHits() {

        return this->hitsOverall;

    }

    uint32_t getNumberOfEnemies() {

        return this->enemiesOverall;

    }

    uint32_t getScore() {

        return this->score;

    }

    void incDeaths() {
        
        this->hitsThisSequence++;
        this->hitsOverall++;
        this->score = this->score + 100;
        
    }

    void decScore() {
        
        if (this->score > 0) this->score = this->score - 100;
        
    }

};

struct SoundFX {
    
    bool active = false;
    uint8_t priority = 0;

};

struct SoundSD {
    
    bool active = false;
    uint32_t length = 0;

};


		