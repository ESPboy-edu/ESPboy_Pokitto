#pragma once

#include "Pokitto.h"

#include "../utils/Constants.h"

#include "Room.h"
#include "InteractiveObject.h"

class AstarokGame;

class Map {

    public:
        void newMap();
        void loadMap();
        void generateRoom(uint8_t roomNum);
        void addObject(ObjectTypes type, int16_t x, int16_t y);
        uint8_t checkObject(int16_t x, int16_t y);
        InteractiveObject *getObject(int16_t x, int16_t y);
        bool isTile(int16_t x, int16_t y);
        void addSign(int16_t x, int16_t y);
        void addExit(ObjectTypes exitType, int16_t x, int16_t y);

        int16_t minXPixel();
        int16_t maxXPixel();
        int16_t maxYPixel();
        int16_t minXTile();
        int16_t maxXTile();
        int16_t maxYTile();

        AstarokGame           * game;
        Room                  rooms[Constants::MapRooms];
        InteractiveObject     objects[Constants::MapObjects];
        uint8_t               objectIndex;
        uint8_t               firstRoom, lastRoom, mapHeight, spawnBarrier;

};