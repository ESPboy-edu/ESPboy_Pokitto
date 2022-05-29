#include "Pokitto.h"
#include "Game.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


Game game;

void setup(){
    Serial.begin(115200);
    PC::begin();
    PD::loadRGBPalette(palettePico);   
    PD::persistence = true;
    PD::setColor(5);
    PD::setInvisibleColor(14);
    PC::setFrameRate(40);
    PD::setFont(fontTight);
    game.setup();
}

void loop(){
  if (PC::update()) { PD::clear(); game.loop(); PD::update();};
  delay(0);
};
