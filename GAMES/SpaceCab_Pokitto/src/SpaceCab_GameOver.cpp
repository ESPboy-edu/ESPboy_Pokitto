#include "SpaceCab.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

void Game::gameoverScreen() {

    scrollingBackground(true, 1, 0);
    scrollingBackground(false, 77, 1);

    PD::setColor(0);
    PD::drawBitmap(17, 20, Images::Gameover);
    PD::setColor(COLOR_LOWLIGHT);
    PD::setCursor(33, 45);
    PD::print("SCORE: ");

    uint8_t digits[5];
    extractDigits(digits, player.getScore());

    for (uint8_t i = 5; i > 0; --i) {
        PD::print(digits[i - 1], 10);
    }

    if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)) {
        this->state = GameState::HighScore_Init;
        cookie->setLastScore(this->player.getScore());
    }
  
}
