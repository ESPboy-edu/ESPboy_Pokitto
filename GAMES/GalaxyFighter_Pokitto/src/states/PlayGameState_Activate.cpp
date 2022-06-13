#include "PlayGameState.h"

#include "Pokitto.h"

#include "../entities/Entities.h"
#include "../data/Formations.h"
#include "../images/Images.h"
#include "../utils/Constants.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void PlayGameState::activate() {

    this->levelStartType = LevelStartType::StartOfGame_Init;
    this->counter = LEVEL_DELAY;
    this->level = 0;
    this->score = 0;
    
    this->enemies.reset();
    this->player.reset(true);
    this->bullets.reset();
    this->enemyBullets.reset();

    this->initStarField();

    this->challenge.clear(false);
    this->gamePaused = false;
    this->captureController.reset();

    this->extraLife1 = false;
    this->extraLife2 = false;
    this->extraLifeCounter = 0;
    this->starFieldSpeed = 1;
    this->bulletsInPlay = this->getBulletsInPlay();
    
}
