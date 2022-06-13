#pragma once

#include "Pokitto.h"
#include "BaseState.h"
#include "../utils/Enums.h"
#include "../images/Images.h"
#include "../utils/GameCookie.h"

class TitleScreenState : public BaseState {

    enum class ViewState : uint8_t {
    	Normal,
    	StartGame,
        Marquee
    };
    
    
    private:

        ViewState viewState;
        uint8_t counter = 0;
        uint8_t titleSeq = 0;
        uint16_t marquee = 0;
        uint16_t stateToggle = 0;

        void printSingleChar(char theChar);
        void printChar(uint8_t charIndex);
        void printNumber(uint8_t number);
        

    public:	
        
        void activate();
        GameStateType update(GameStateType currentState, GameCookie *cookie);
        void render(GameCookie *cookie);

};

