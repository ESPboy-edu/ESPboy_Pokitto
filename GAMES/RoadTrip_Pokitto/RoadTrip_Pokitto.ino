#include "Pokitto.h"
#include "src/utils/DuelPalette.h"
//#include "libs/Libaudio/LibAudio.h"
#include "src/RoadTrip.h"
#include "src/utils/GameCookie.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


Game game;
GameCookie cookie;

//Audio::Sink<3, 8000> audio;

void setup(){
    
    cookie.begin("ROADTRIP", sizeof(cookie), (char*)&cookie);

    PC::begin();
    PD::loadRGBPalette(duel);   
    PD::persistence = true;
    PD::setColor(5);
    PD::setInvisibleColor(255);
    PC::setFrameRate(40);
    PD::setFont(fontTight);
    PD::textWrap = false;
    // Has the cookie been initialised?
    if (cookie.initialised != COOKIE_INITIALISED) {
        cookie.initialise();}
    game.setup(&cookie);
}

void loop(){
 if (PC::update()){
   PD::update();
   game.loop();}
 else delay(0);
}
    
