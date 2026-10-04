#include "Pokitto.h"

#include "Pokitto.h"
//#include <LibAudio>
#include "src/Game.h"
#include "src/utils/GameCookie.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

Game game;
GameCookie cookie;

//Audio::Sink<4, PROJ_AUD_FREQ> audio;

void setup(){
    //Serial.begin(115200);
  
    cookie.begin("STACK", sizeof(cookie), (char*)&cookie);

    PC::begin();
    PD::loadRGBPalette(palettePico);   
    PD::persistence = true;
    PD::setColor(5, 0);
    PD::setInvisibleColor(15);
    PC::setFrameRate(40);
    PD::setFont(fontC64);

    if (cookie.initialised != COOKIE_INITIALISED) {
        cookie.initialise();
    }

    game.setup(&cookie);
};


void loop(){
   if(PC::update()) {PD::clear(); game.loop(); PD::update();}
   delay(0);
}
    
