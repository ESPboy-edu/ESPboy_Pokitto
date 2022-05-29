#include <Pokitto.h>
//#include <LibAudio>
#include "src/SpaceCab.h"
#include "src/utils/GameCookie.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

Game game;
GameCookie cookie;

//Audio::Sink<4, PROJ_AUD_FREQ> audio;

void setup(){
  //Serial.begin(115200);
  //Serial.println();
  cookie.begin("SPACECAB", sizeof(cookie), (char*)&cookie);
  PC::begin();
  PD::loadRGBPalette(palettePico);   
  PD::persistence = true;
  PD::setColor(5);
  PD::setInvisibleColor(14);
  PC::setFrameRate(60);
  PD::setFont(font3x5);
  PD::textWrap = false;
  if (cookie.initialised != COOKIE_INITIALISED) {cookie.initialise();}
  game.setup(&cookie);
};

void loop(){
  if(PC::update()) {
    game.loop();
    PD::update();}
}
