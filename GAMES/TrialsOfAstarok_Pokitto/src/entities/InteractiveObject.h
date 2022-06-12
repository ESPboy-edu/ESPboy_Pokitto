#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"

class AstarokGame;

class InteractiveObject {

    public:
        int16_t             x, y;
        ObjectTypes         type;
        AstarokGame         * game;
        uint8_t             explodeCounter;

        uint8_t collide(int16_t tX, int16_t tY);
        void deactivate(bool explode);
        ObjectTypes getType();
        void updateExplosion();
        bool getActive();

};