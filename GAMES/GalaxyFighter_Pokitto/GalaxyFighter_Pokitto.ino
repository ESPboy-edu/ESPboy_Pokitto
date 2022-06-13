#include "Pokitto.h"
#include "src/utils/Constants.h"

#include "libs/LibAudio/LibAudio.h"
Audio::Sink<MAXCHANNELS, 8000> audio;

#include "PokittoCookie.h"
#include "src/Game.h"

#include "src/entities/Entities.h"
#include "src/data/Formations.h"
#include "src/images/Images.h"

#include "src/utils/Utils.h"
#include "src/utils/Enums.h"


using PC = Pokitto::Core;
using PD = Pokitto::Display;
//using PS = Pokitto::Sound;


Game game;
GameCookie cookie;

void setup() {
    //Serial.begin(115200);
    //Serial.println();
    cookie.begin("GALAXY", sizeof(cookie), (char*)&cookie);
    PC::begin();
    PD::loadRGBPalette(palettePico);   
    PD::persistence = true;
    PD::setColor(5);
    PC::setFrameRate(100);
    PD::setFont(fontC64);

/*
    #if POK_HIGH_RAM == HIGH_RAM_MUSIC
    memset(buffers[0], 128, BUFFER_SIZE);
    memset(buffers[1], 128, BUFFER_SIZE);
    memset(buffers[2], 128, BUFFER_SIZE);
    memset(buffers[3], 128, BUFFER_SIZE);
    #else
    memset(&(buffers[0]), 128, BUFFER_SIZE);
    memset(&(buffers[1]), 128, BUFFER_SIZE);
    memset(&(buffers[2]), 128, BUFFER_SIZE);
    memset(&(buffers[3]), 128, BUFFER_SIZE);
    #endif

    // Kick off the random number generator ..
    srand(time(0));
*/

    // Has the cookie been initialised?
    if (cookie.initialised != COOKIE_INITIALISED) {
        cookie.initialise();}
    game.setup(&cookie);
};



void loop(){
    if (PC::update()) {PD::clear(); game.loop(); PD::update();};
    delay(0);
};

    
