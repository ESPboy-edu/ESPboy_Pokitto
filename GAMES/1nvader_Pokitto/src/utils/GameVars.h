#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "GameCookie.h"
#include "Constants.h"
#include "Enums.h"


class GameVars {

	public:

		uint8_t counter = Constants::MothershipCounterMax;
		uint8_t wave = 0; 

		uint16_t bombCounter;
		uint8_t waveCounter;
		bool waveCleared;
		
		GameCookie *cookie;
        GameState gameState = GameState::Splash_Init;

	public:

        uint8_t getCounter()                                { return this->counter; }
        void setCounter(uint8_t val)                        { this->counter = val; }


        bool decCounter() {

            this->counter--;

            if (this->counter == 0) {
                this->counter = 80;
                this->wave++;
                return true;
            }
            
            return false;
            
        }

		bool launchRedMothership() {

			switch (this->counter) {

				case 71 ... 80:
					return false;

				case 2 ... 70:
					return random(0, (this->counter / 2)) == 0;

				default:
					return false;
					
			}

		}

};