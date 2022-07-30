#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Constants.h"
#include "Enums.h"


class GameCookie : public Pokitto::Cookie {

	public:

		uint8_t initialised;
		SoundEffects sfx;
		uint16_t score[3];

	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;
			this->sfx = SoundEffects::Both;

			this->score[0]= 3;
			this->score[1]= 2;
			this->score[2]= 1;

			this->saveCookie();

		}

		void reset() {

			this->score[0]= 3;
			this->score[1]= 2;
			this->score[2]= 1;

			this->saveCookie();

		}

		uint8_t saveScore(uint16_t newScore) {

			if (newScore > this->score[0]) {

				this->score[2] = this->score[1];
				this->score[1] = this->score[0];
				this->score[0] = newScore;
				this->saveCookie();
				return 0;

			}

			if (newScore > this->score[1]) {

				this->score[2] = this->score[1];
				this->score[1] = newScore;
				this->saveCookie();
				return 1;

			}

			if (newScore > this->score[2]) {

				this->score[2] = newScore;
				this->saveCookie();
				return 2;
				
			}

			return 255;

		}



};