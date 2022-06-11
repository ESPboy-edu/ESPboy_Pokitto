#include "Pokitto.h"
//#include <LibAudio>
#include "src/Game.h"
#include "src/utils/GameCookieHighScores.h"
#include "src/utils/GameCookieSaveGame.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


Game game;
GameCookieHighScores cookieHighScore;
GameCookieSaveGame cookieSaveGame;


//Audio::Sink<4, PROJ_AUD_FREQ> audio;

void setup() {
    //Serial.begin(115200);
    PC::begin();
    
    // Initialise pokitto ..
    cookieHighScore.begin("DarkRit1", sizeof(cookieHighScore), (char*)&cookieHighScore);
    cookieSaveGame.begin("DarkRit2", sizeof(cookieSaveGame), (char*)&cookieSaveGame);

    PD::loadRGBPalette(palettePico);   
    PD::persistence = true;
    PD::setColor(5);
    PD::setInvisibleColor(14);
    PC::setFrameRate(35);
    PD::setFont(fontKoubit);

    if (cookieHighScore.initialised != COOKIE_INITIALISED) {
        cookieHighScore.initialise();}
        
    if (cookieSaveGame.initialised != COOKIE_INITIALISED) {
        cookieSaveGame.initialise();}
    
    // Kick off the random number generator ..
    game.setup(&cookieHighScore, &cookieSaveGame);
}


void loop() {
 if(PC::update()){PD::clear(); game.loop(); PD::update();};
 delay(0);
}
