#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"

class SplashScreenState {

	private:
		uint8_t counter = 0;

	public:
		void activate();
		GameStateType update(GameStateType currentState);
		void render();

};