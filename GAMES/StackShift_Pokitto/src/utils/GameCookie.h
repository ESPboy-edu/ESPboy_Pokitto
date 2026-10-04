#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Consts.h"

class GameCookie : public Pokitto::Cookie {

	public:
                // ВАЖНО: 32-битные массивы идут первыми для выравнивания в памяти
		uint32_t score[2][5] = { 50, 40, 30, 20, 10, 100, 80, 60, 40, 20 };
		char initials[2][5][3] = { 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5 };
		uint32_t lastScore = 0;
		uint32_t lastScoreIndex = 0;
		SoundEffects sfx = SoundEffects::Both;
		uint8_t track = 0;
		uint8_t initialised; // Перенесено в конец

	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;
			this->sfx = SoundEffects::Both;

			this->score[0][0] = 50;
			this->score[0][1] = 40;
			this->score[0][2] = 30;
			this->score[0][3] = 20;
			this->score[0][4] = 10;

			this->score[1][0] = 100;
			this->score[1][1] = 80;
			this->score[1][2] = 60;
			this->score[1][3] = 40;
			this->score[1][4] = 20;

			for (uint8_t z = 0; z < 2; z++) {
				for (uint8_t x = 0; x < 5; x++) {
					for (uint8_t y = 0; y < 3; y++) {
						this->initials[z][x][y] = x + 1;
					}
				}
			}

			this->lastScore = 0;
			this->lastScoreIndex = 0;
			this->track = 0;
			this->saveCookie();
		}
		
		uint32_t getScoreIndex() {
			return lastScoreIndex;
		}

		void setScoreIndex(uint32_t val) {
			lastScoreIndex = val;
		}

uint32_t setLastScore(Level level, uint32_t score) {

            // ИСПРАВЛЕНИЕ: меняем uint32_t на int32_t, чтобы избежать 
            // бага при сравнении x >= index, когда x уходит в минус
            int32_t index = NO_SCORE;

			for (int32_t x = 0; x < 5; x++) {
				if (score >= this->score[static_cast<uint8_t>(level)][x]) {
				    index = x;
				    break;
				}
			}

			if (index != NO_SCORE) {
			    for (int32_t x = 3; x >= index; x--) {
			        this->score[static_cast<uint8_t>(level)][x + 1] = this->score[static_cast<uint8_t>(level)][x];
			        this->initials[static_cast<uint8_t>(level)][x + 1][0] = this->initials[static_cast<uint8_t>(level)][x][0];
			        this->initials[static_cast<uint8_t>(level)][x + 1][1] = this->initials[static_cast<uint8_t>(level)][x][1];
			        this->initials[static_cast<uint8_t>(level)][x + 1][2] = this->initials[static_cast<uint8_t>(level)][x][2];
			    }

				this->score[static_cast<uint8_t>(level)][index] = score;
				this->initials[static_cast<uint8_t>(level)][index][0] = 0;
				this->initials[static_cast<uint8_t>(level)][index][1] = 0;
				this->initials[static_cast<uint8_t>(level)][index][2] = 0;
			}

			this->lastScore = score;
			this->lastScoreIndex = index;

			return index;
		}

};