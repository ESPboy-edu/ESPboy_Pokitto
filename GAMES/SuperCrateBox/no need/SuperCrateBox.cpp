#include "SuperCrateBox/SuperCrateBox.h"
#include "Pokitto.h"

Pokitto::Core pb;

void setup() {
    pb.begin();
    pb.setFrameRate(30);

    pb.display.loadRGBPalette(palettePico);
    pb.display.setFont(font3x5);
    pb.display.setInvisibleColor(14);//pink
    _init();
}


void loop(){
        if (pb.update())
            _gameloop();
}
