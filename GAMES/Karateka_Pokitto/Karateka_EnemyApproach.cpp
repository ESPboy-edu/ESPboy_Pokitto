#include "Pokitto.h"
#include "Game.h"

#include "utils/Stack.h"
#include "utils/PlayerStances.h"
#include "utils/EnemyStances.h"
#include "images/images.h"
#include "utils/Enums.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

void Game::enemy_approach_init() {

    for (int i = 0; i < 2; i++) {

        this->enemy.push(STANCE_RUNNING_RF_END, STANCE_RUNNING_8, STANCE_RUNNING_5, true);
        this->enemy.push(STANCE_RUNNING_4, STANCE_RUNNING_LF_END, STANCE_RUNNING_2, true);
        this->enemy.push(STANCE_RUNNING_7, STANCE_RUNNING_4, true);

    }

    this->player.setXPosDelta(MAIN_SCENE_X_SIDLING_4_DELTA);
    this->gameStateDetails.setCurrState(GAME_STATE_ENEMY_APPROACH);

    this->enemy.setXPos(96);
    this->enemy.setYPos(76);

}
