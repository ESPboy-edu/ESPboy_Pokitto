#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Enums.h"


class GameCookie : public Pokitto::Cookie {

	public:

		uint8_t initialised;
		SoundEffects sfx = SoundEffects::Both;
		uint32_t score[5] = { 500, 400, 300, 200, 100 };
		uint8_t initials[5][3] = { 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5 };
		uint32_t lastScore = 0;
		uint32_t lastScoreIndex = 0;


	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;
			this->sfx = SoundEffects::Both;

			this->score[0] = 1250;
			this->score[1] = 980;
			this->score[2] = 530;
			this->score[3] = 450;
			this->score[4] = 210;

			for (uint8_t x = 0; x < 5; x++) {

				for (uint8_t y = 0; y < 3; y++) {
					this->initials[x][y] = x + 1;
				}

			}

			this->lastScore = 0;
			this->lastScoreIndex = 0;

			this->saveCookie();

		}
		

		uint32_t getScoreIndex() {

			return lastScoreIndex;

		}


		uint32_t setLastScore(uint32_t score) {

            uint32_t index = Constants::No_Score;
            
			for (uint32_t x = 0; x < 5; x++) {

				if (score >= this->score[x]) {
				    
				    index = x;
				    break;
				    
				}

			}

			if (index != Constants::No_Score) {

			    for (int32_t x = 3; x >= index; x--) {
			        
			        this->score[x + 1] = this->score[x];
			        this->initials[x + 1][0] = this->initials[x][0];
			        this->initials[x + 1][1] = this->initials[x][1];
			        this->initials[x + 1][2] = this->initials[x][2];
			        
			    }

				this->score[index] = score;
				this->initials[index][0] = 0;
				this->initials[index][1] = 0;
				this->initials[index][2] = 0;

			}

			this->lastScore = score;
			this->lastScoreIndex = index;

			return index;

		}

};