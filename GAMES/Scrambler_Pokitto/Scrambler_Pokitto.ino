#include "Pokitto.h"
#include "src/utils/GameCookie.h"
#include "src/utils/Enums.h"
#include "src/utils/PicoPalExt.cpp"
#include "src/Scramble.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


Game game;
GameCookie cookie;


void setup() {
    //Serial.begin(115200);
    cookie.begin("Scramble", sizeof(cookie), (char*)&cookie);
    PC::begin();
    PD::loadRGBPalette(palettePicoExt);  
    PD::persistence = true;
    PD::setColor(5);
    PD::setInvisibleColor(14);
    PC::setFrameRate(55);
    PD::setFont(font5x7);
    PD::adjustCharStep = 1;
    PD::textWrap = false;
    // Has the cookie been initialised?
    if (cookie.initialised != COOKIE_INITIALISED) {
        cookie.initialise();
    }
    
    game.setup(&cookie);
};


void loop(){
    if (PC::update()) {PD::clear(); game.loop(); PD::update(); }
    delay(0);
};
