#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../utils/Structs.h"
#include "../utils/Constants.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

class BaseState {

    protected:

		void updateStarField(uint8_t speed);
		void initStarField();
		void renderStarField(uint8_t speed);
		void playSFX_ByPriority( const uint8_t *sfx, uint32_t length, uint8_t priority);
		
	protected:
   
		int16_t stars[STAR_COUNT];
		SoundFX soundFX;
		SoundSD soundSD;
		
};