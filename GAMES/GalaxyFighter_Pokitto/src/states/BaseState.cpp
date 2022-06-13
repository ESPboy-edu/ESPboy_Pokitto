#include "BaseState.h"

#include "Pokitto.h"
#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "../utils/Structs.h"
#include "../utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
//using PS = Pokitto::Sound;

// ----------------------------------------------------------------------------
//  Update star field .. 
//
void BaseState::updateStarField(uint8_t speed) {

    for (uint32_t x=0; x < STAR_COUNT; x++) {
        
        this->stars[x] = this->stars[x] + speed;
        if (this->stars[x] > 180) this->stars[x] = -(rand() % 120) - (50 * (speed / 20));
        
    }

}


// ----------------------------------------------------------------------------
//  Update star field .. 
//
void BaseState::initStarField() {

    // Populate star field ..

    for (uint32_t x = 0; x < STAR_COUNT; x++) {
        
        this->stars[x] = rand() % 220 - 50;
        
    }

}

// ----------------------------------------------------------------------------
//  Render the star field .. 
//
void BaseState::renderStarField(uint8_t speed) {

    for (uint32_t x = 0; x < STAR_COUNT; x++) {
        
        if (x % 2 == 0) {
            PD::setColor(6);
        }
        else {
            PD::setColor(5); 
        }

        if (speed == 1) {
          PD::drawPixel(x * STAR_SPACING, this->stars[x]);
        }
        else {
          PD::drawColumn(x * STAR_SPACING, this->stars[x], this->stars[x] + speed - 1);
        }

    }

}


// ----------------------------------------------------------------------------
//  Play a sound effect if a higher priority one is not playing .. 
//
void BaseState::playSFX_ByPriority(const uint8_t *sfx, uint32_t length, uint8_t priority) {
    Utils::playPlay(sfx, length);
   /*
    if (this->soundFX.active) = true;
    if (!this->soundFX.active || this->soundFX.priority < priority) {

        //#ifdef INCLUDE_SOUND
        this->soundFX.active = true;
        this->soundFX.priority = priority;
        Utils::playPlay(sfx, length);
        //PS::playSFX(sfx, length);
        //#endif

    }
   */
}
