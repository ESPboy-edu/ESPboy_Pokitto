#pragma once

#include "Pokitto.h"
#include "BaseState.h"
#include "../utils/Enums.h"
#include "../utils/GameCookie.h"
#include "../images/Images.h"

class HighScoreState : public BaseState {

  private:

    uint8_t counter = 0;
    uint8_t cursor = 0;

  public:	
  
    void activate();
    GameStateType update(GameStateType currentState, GameCookie *cookie);
    void render(GameCookie *cookie);

};

