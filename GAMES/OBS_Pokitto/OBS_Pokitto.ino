#include "Pokitto.h"

#include "src/utils/GameCookie.h"
#include "src/utils/Enums.h"
#include "src/OBS.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

Game game;
GameCookie cookie;


void setup() {
    //Serial.begin(115200); Serial.println();
    cookie.begin("OBS", sizeof(cookie), (char*)&cookie);
    PC::begin();
    PD::loadRGBPalette(palettePico);  
    PD::persistence = true;
    PD::setColor(5);
    PD::setInvisibleColor(14);
    PC::setFrameRate(60);
    PD::setFont(fontTiny);
    PD::textWrap = false;
    if (cookie.initialised != COOKIE_INITIALISED) {
        cookie.initialise();}
    game.setup(&cookie);
};



void loop(){    
   if(PC::update()) {PD::clear(); game.loop(); PD::update();}
   delay(0);
};
