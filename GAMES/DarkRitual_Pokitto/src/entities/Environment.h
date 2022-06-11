#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../../My_settings.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


class Environment{

    public:

        Environment() {}

        uint8_t getFinishX()    { return this->x1; }
        uint8_t getFinishY()    { return this->y1; }
        uint8_t getX()          { return this->x; }
        uint8_t getY()          { return this->y; }
        bool getActive()        { return this->active; }
        MapTiles getTile()      { return this->tile; }

        bool checkStart(uint8_t x, uint8_t y) { return (this->x == x && this->y == y); }

        void setEnv(uint8_t x, uint8_t y, uint8_t x1, uint8_t y1, bool active, MapTiles tile) {
            this->x = x; 
            this->y = y; 
            this->x1 = x1; 
            this->y1 = y1; 
            this->active = active;
            this->tile = tile;
        }

    private:

        uint8_t x;
        uint8_t y;
        uint8_t x1;
        uint8_t y1;
        MapTiles tile;
        bool active;
  
};