#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Enums.h"
#include "Structs.h"


class GameCookie : public Pokitto::Cookie {

	public:

		uint8_t initialised;
		SoundSettings sfx;
		uint8_t seeds[5];
		Slot slots[Constants::NumberOfScores];
		Sex sex = Sex::Male;

	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;
			this->sfx = SoundSettings::Both;

			for (uint8_t i = 0; i < 5; i++) {
				seeds[i] = 0;
			}
			
			for (uint8_t i = 0; i < Constants::NumberOfScores; i++) {
				slots[i].reset();
				slots[i].score = 5 - i;
			}

			this->sex = Sex::Male;
			this->saveCookie();

		}

};