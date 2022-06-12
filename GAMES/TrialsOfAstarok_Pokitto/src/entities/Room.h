#pragma once

#include "Pokitto.h"
#include "../utils/Constants.h"

class Room {

    public:
        void clearRoom();
        void setTile(uint8_t x, uint8_t y);
        void clearTile(uint8_t x, uint8_t y);
        bool readTile(uint8_t x, uint8_t y);

        uint16_t data[Constants::RoomBytes];

};