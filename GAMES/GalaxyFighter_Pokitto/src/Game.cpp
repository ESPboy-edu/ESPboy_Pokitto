/*
	Copyright (C) 2018 Pharap (@Pharap)

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.

	Modified by Filmote and Vampirics
*/

#include "Game.h"

#include "states/States.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::setup(GameCookie *cookie) {

	this->currentState = GameStateType::SplashScreen_Activate; 
	this->splashScreenState.activate();
	this->cookie = cookie;
	
}

void Game::loop(void) {

    PC::buttons.pollButtons();

	switch (this->currentState) {

		case GameStateType::SplashScreen_Activate:
			this->splashScreenState.activate();
			this->currentState = GameStateType::SplashScreen;
			[[fallthrough]]

		case GameStateType::SplashScreen:
			this->currentState = this->splashScreenState.update(this->currentState);
			this->splashScreenState.render();
			break;

		case GameStateType::TitleScreen_Activate: 
			this->titleScreenState.activate();
			this->currentState = GameStateType::TitleScreen;
			[[fallthrough]]

		case GameStateType::TitleScreen: 
			this->currentState = this->titleScreenState.update(this->currentState, this->cookie);
			this->titleScreenState.render(this->cookie);
			break;

        case GameStateType::PlayGame_Activate: 
			this->playGameState.activate();
			this->currentState = GameStateType::PlayGame;
			[[fallthrough]]

        case GameStateType::PlayGame: 
			this->currentState = this->playGameState.update(this->currentState, this->cookie);
			this->playGameState.render();
			break;

        case GameStateType::HighScore_Activate: 
			this->highScoreState.activate();
			this->currentState = GameStateType::HighScore;
			[[fallthrough]]

        case GameStateType::HighScore: 
			this->currentState = this->highScoreState.update(this->currentState, this->cookie);
			this->highScoreState.render(this->cookie);
			break;

		default: break;	

	}

}
