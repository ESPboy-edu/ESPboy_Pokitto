#include "Pokitto.h"
//#include <LibAudio>
#include "src/utils/GameCookie.h"
#include "src/utils/Enums.h"
#include "src/Invader.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

Game game;
GameCookie cookie;

//Audio::Sink<2, PROJ_AUD_FREQ> audio;

void setup() {
    cookie.begin("1nvader", sizeof(cookie), (char*)&cookie);
    PC::begin();
    PD::loadRGBPalette(palettePico);  
    PD::persistence = true;
    PD::setColor(5);
    PD::setInvisibleColor(14);
    PC::setFrameRate(60);
    PD::setFont(font5x7);
    PD::textWrap = false;
    // Has the cookie been initialised?
    if (cookie.initialised != COOKIE_INITIALISED) {
        cookie.initialise();
    }
    game.setup(&cookie);
};


void loop(){    
   if(PC::update()) {PD::clear(); game.loop(); PD::update();}
   delay(0);
};
