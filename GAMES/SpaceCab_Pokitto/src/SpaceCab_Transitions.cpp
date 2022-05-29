#include "SpaceCab.h"
#include "Utils/Vector2.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

constexpr Vector2 centreScreen = Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

PROGMEM const Vector2 offsets[MAX_STARS] = {
	Vector2(1.0000, 0.0000),
	Vector2(0.9239, 0.3827),
	Vector2(0.7071, 0.7071),
	Vector2(0.3827, 0.9239),
	Vector2(0.0000, 1.0000),
	Vector2(-0.3827, 0.9239),
	Vector2(-0.7071, 0.7071),
	Vector2(-0.9239, 0.3827),
	Vector2(-1.0000, 0.0000),
	Vector2(-0.9239, -0.3827),
	Vector2(-0.7071, -0.7071),
	Vector2(-0.3827, -0.9239),
	Vector2(0.0000, -1.0000),
	Vector2(0.3827, -0.9239),
	Vector2(0.7071, -0.7071),
	Vector2(0.9239, -0.3827),
	Vector2(1.3827, 0.0000),
	Vector2(0.9239, 0.3827),
	Vector2(0.7071, 0.7071),
	Vector2(0.3827, 0.9239),
	Vector2(0.0000, 1.0000),
	Vector2(-0.3827, 0.9239),
	Vector2(-0.7071, 0.7071),
	Vector2(-0.9239, 0.3827),
	Vector2(-1.0000, 0.3827),
	Vector2(-0.9239, -0.3827),
	Vector2(-0.7071, -0.7071),
	Vector2(-0.3827, -0.9239),
	Vector2(0.0000, -1.0000),
	Vector2(0.9239, -0.9239),
	Vector2(0.7071, -0.7071),
	Vector2(0.9239, -0.3827),
};

void Game::initialiseStars(void) {

	for(uint8_t i = 0; i < MAX_STARS; ++i) this->gamePlayVariables.stars[i] = centreScreen;
	this->gamePlayVariables.starsInitialised = true;

}

void Game::resetStars(void) {
	this->gamePlayVariables.starsInitialised = false;
}

void Game::updateStarfield(void) {

	for(uint8_t i = 0; i < MAX_STARS; ++i) {

		this->gamePlayVariables.stars[i].x += offsets[i].x;
		this->gamePlayVariables.stars[i].y += offsets[i].y;

		if (i > MAX_STARS / 2) {
			this->gamePlayVariables.stars[i].x += offsets[i].x;
		}

		if (i % 3 == 0) {
			this->gamePlayVariables.stars[i].y += offsets[i].y;
		}

		if (this->gamePlayVariables.stars[i].x < 0 || this->gamePlayVariables.stars[i].y < 0 || this->gamePlayVariables.stars[i].x > SCREEN_WIDTH || this->gamePlayVariables.stars[i].y > SCREEN_HEIGHT) this->gamePlayVariables.stars[i] = centreScreen;

	}

}

void Game::drawStarfield() {

	for(uint8_t i = 0; i < MAX_STARS; ++i) {
		PD::drawPixel(static_cast<int8_t>(this->gamePlayVariables.stars[i].x), static_cast<int8_t>(this->gamePlayVariables.stars[i].y));
  	}
  
}

void Game::drawLevelStart(Level &level) {

	if (!this->gamePlayVariables.starsInitialised) initialiseStars();

	this->updateStarfield();
	this->drawStarfield();

	PD::setColor(0, 0);
	PD::fillRect(19, 31, 72, 17); 
	PD::setColor(9, 0);
	PD::drawFastHLine(20, 32, 70); 
	PD::drawFastHLine(20, 45, 70);

	PD::setCursor(55 - (level.getLevelNameOffset() / 2), 36);
	PD::setColor(6, 14);
	PD::print(level.getLevelName());
	PD::setColor(6, 0);

    if (PC::buttons.pressed(BTN_A)) {

		this->state = GameState::PlayGame_InitLevel; 

	}

}

void Game::drawMaxLevelCompleted() {

	if (!this->gamePlayVariables.starsInitialised) initialiseStars();

	this->updateStarfield();
	this->drawStarfield();

	PD::setColor(0, 0);
	PD::fillRect(15, 27, 80, 30); //black
	PD::setColor(9, 0);
	PD::drawFastHLine(16, 28, 78); 
	PD::drawFastHLine(16, 58, 78); 

	PD::setColor(6, 0);
	PD::setCursor(40, 33);
	PD::print("You completed");
	PD::setCursor(46, 43);
	PD::print("all levels!");
	PD::drawBitmap(15, 39, Images::EndOfGameBadge);

    if (PC::buttons.pressed(BTN_A)) {

		this->state = GameState::GameOver_Init; 

	}

}
