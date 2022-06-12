#include "Pokitto.h"

#include "libs/LibAudio/LibAudio.h"
Audio::Sink<3, 8000> audio;

//#include <LibAudio>
#include "src/sounds/Sounds.h"
#include "src/utils/Constants.h"
#include "src/utils/GameCookie.h"
#include "src/utils/Enums.h"
#include "src/Astarok.h"
#include "src/utils/DuelPalette.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


Game game;
GameCookie cookie;


void setup() {
    //Serial.begin(115200); Serial.println();
    cookie.begin("Astarok", sizeof(cookie), (char*)&cookie);
    PC::begin();
    PD::loadRGBPalette(duel);  
    PD::persistence = true;
    PD::setColor(5);
    PD::setInvisibleColor(149);
    PC::setFrameRate(50);
    PD::textWrap = false;
    PD::setFont(font3x5);
    // Has the cookie been initialised?
    if (cookie.initialised != COOKIE_INITIALISED) {
        cookie.initialise();}
    game.setup(&cookie);
};


void loop(){    
   if(PC::update()) {PD::clear(); game.loop(); PD::update();}
   delay(0);
};
