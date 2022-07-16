#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Constants.h"
#include "Enums.h"


class GameCookie : public Pokitto::Cookie {

	public:

		uint8_t initialised;
		uint16_t highScore[3];
		GameMode gameMode;
		GameRotation gameRotation;
		uint8_t levelLock[3];
		SoundEffects sfx;

	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;
			this->sfx = SoundEffects::Both;
			
			this->highScore[0] = 0;
			this->highScore[1] = 0;
			this->highScore[2] = 0;
			this->gameMode = GameMode::Single;
			this->gameRotation = GameRotation::Landscape;
			this->levelLock[0] = 0;	//SJH
			this->levelLock[1] = 0;	//SJH
			this->levelLock[2] = 0;

			this->saveCookie();

		}


		/* -----------------------------------------------------------------------------
		*   Get score. 
		*/
		uint16_t getScore(GameMode mode) {

			return this->highScore[static_cast<uint8_t>(mode)];

		}


		/* -----------------------------------------------------------------------------
		*   Save score ..
		*/
		void saveScore(GameMode mode, uint16_t score) {

			uint16_t oldScore = this->getScore(mode);
	
			if (oldScore < score) {

				this->highScore[static_cast<uint8_t>(mode)] = score;
				this->saveCookie();

			}

		}


		/* -----------------------------------------------------------------------------
		*   Get mode. 
		*/
		GameMode getMode() {

			return this->gameMode;

		}


		/* -----------------------------------------------------------------------------
		*   Save mode ..
		*/
		void saveMode(GameMode mode) {

			if (mode != this->gameMode) {

				this->gameMode = mode;
				this->saveCookie();

			}

		}


		/* -----------------------------------------------------------------------------
		*   Get rotation. 
		*/
		GameRotation getRotation() {

			return this->gameRotation;

		}


		/* -----------------------------------------------------------------------------
		*   Save rotation ..
		*/
		void saveRotation(GameRotation rotation) {

			if (rotation != this->gameRotation) {

				this->gameRotation = rotation;
				this->saveCookie();

			}
			
		}

		/* -----------------------------------------------------------------------------
		*   Get level. 
		*/
		uint8_t getLevel(uint8_t level) {

			return this->levelLock[level];

		}


		/* -----------------------------------------------------------------------------
		*   Save level ..
		*/
		void saveLevel(uint8_t level, uint8_t value) {

			if (this->levelLock[level] != value) {

				this->levelLock[level] = value;
				this->saveCookie();

			}

		}

};

