#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Constants.h"


class GameCookie : public Pokitto::Cookie {

	public:

		uint8_t initialised;
		uint16_t score[5] = 	  { 50, 40, 30, 20, 10, };
		char initials[5][3] =  	  { 65, 65, 65, 66, 66, 66, 67, 67, 67, 68, 68, 68, 69, 69, 69, };
		uint16_t lastScore = 0;
		uint16_t lastScoreIndex = 0;

	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;

			this->score[0] = 50;
			this->score[1] = 40;
			this->score[2] = 30;
			this->score[3] = 20;
			this->score[4] = 10;

			for (uint8_t x = 0; x < 5; x++) {

				for (uint8_t y = 0; y < 3; y++) {

					this->initials[x][y] = x + 65;

				}

			}

			this->lastScore = 0;
			this->lastScoreIndex = 0;
			this->saveCookie();

		}
		
		uint32_t getScoreIndex() {

			return lastScoreIndex;

		}

		void setScoreIndex(uint32_t val) {

			lastScoreIndex = val;

		}

		uint16_t setLastScore(uint32_t score) {

            uint16_t index = NO_SCORE;

			for (uint16_t x = 0; x < 5; x++) {

				if (score >= this->score[x]) {
				    
				    index = x;
				    break;
				    
				}

			}

			if (index != NO_SCORE) {

			    for (int32_t x = 3; x >= index; x--) {
			        
			        this->score[x + 1] = this->score[x];
			        this->initials[x + 1][0] = this->initials[x][0];
			        this->initials[x + 1][1] = this->initials[x][1];
			        this->initials[x + 1][2] = this->initials[x][2];
			        
			    }

				this->score[index] = score;
				this->initials[index][0] = 65;
				this->initials[index][1] = 65;
				this->initials[index][2] = 65;

			}

			this->lastScore = score;
			this->lastScoreIndex = index;

			return index;

		}

};