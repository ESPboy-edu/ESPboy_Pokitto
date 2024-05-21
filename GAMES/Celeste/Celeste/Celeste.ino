#include "game.h"
#include "pico8_pal.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PB = Pokitto::Buttons;


Game game;
Pokitto::Core pb;

void setup() {
    //Serial.begin(74880);
    pb.begin();
    //Pokitto::Sound::ampEnable(true);
    pb.setFrameRate(30);

    pb.display.loadRGBPalette(palettePico);
    pb.display.setInvisibleColor(BLACK);
    pb.display.setFont(pico8);
    game.init();
}
    
 void loop() {
        if (pb.update())
        {
            game.update();
            game.draw();
            PD::update();
        }
}
