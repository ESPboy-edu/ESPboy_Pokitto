#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Structs.h"
#include "Enums.h"

class GameCookieSaveGame : public Pokitto::Cookie {
    
    public:
    
    	uint8_t initialised;

        PlayerStatus playerStatus;
        uint8_t levelNo = 0;
        uint8_t definedMapLevel = 0;
        bool gameC = false;
        

	public:

		void initialise() {

			this->initialised = COOKIE_INITIALISED;
            this->levelNo = 255;
			this->saveCookie();

		}

        void updateStatus(uint8_t level, uint8_t definedMapLevel, PlayerStatus playerStatus) {

            this->levelNo = level;
            this->definedMapLevel = definedMapLevel;
            this->playerStatus = playerStatus;

        }

        uint8_t getLevel() {

            return this->levelNo;
            
        }

        uint8_t getDefinedMapLevel() {

            return this->definedMapLevel;
            
        }

        PlayerStatus getPlayerStatus() {

            return this->playerStatus;
            
        }

};
