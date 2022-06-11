#pragma once

#include "../Utils/Constants.h"
//#include <LibAudio>
#include "Levels.h"
#include "Fuel.h"
#include "Gate.h"
#include "scLevels.h"
//#include <LittleFS.h>


struct Level {

    public:
 
        float xOffset = 0;
        float yOffset = 0;

    private:
 
        char _levelName[33];
        uint8_t _number;
        uint16_t _playerOffsetX;
        uint16_t _playerOffsetY;
        uint16_t _height = 0;
        uint16_t _width = 0;
        uint16_t _heightInTiles = 0;
        uint16_t _widthInTiles = 0;
        uint8_t _levelData[4096];
        uint8_t _startingPositionsCount;
        uint8_t _startingPositions[STARTING_POSITIONS_MAX];
        uint8_t _endingPositionsCount;
        uint8_t _endingPositions[ENDING_POSITIONS_MAX];
        uint8_t _faresRequired;
        uint8_t _levelNameOffset;
        uint8_t _numberOfPositions;
        uint8_t _levelGateLeft;
        uint8_t _levelGateRight;
        uint16_t _fuelMax = 0;
        uint16_t _internalGateInterval = 150;                         // Period of time internal gate is open.
        uint16_t _internalGateCounter = 0;                            // Gate open countdown.
        GateMode _internalGateMode = GateMode::Closed;
        uint32_t filePosition=0;
        uint32_t levelNumber=0;

        Fuel _fuels[FUEL_TILES_MAX];
        Gate _gates[GATE_TILES_MAX];

    public:

        void file_openRO(uint32_t lvl){
           filePosition=0;
           levelNumber=lvl;
        }       

        void file_readBytes(char *pointer, uint16_t counter){
           for(uint16_t i=0; i<counter;i++)
             pointer[i] = scLevels[levelNumber][i+filePosition];
           filePosition+=counter;
        }
        
        void file_seek(uint32_t pos){
          filePosition=pos;
        };


        Level() {
            this->_levelName[32] = 0;
            for (uint8_t x = 0 ; x < GATE_TILES_MAX; x++) {
                _gates[x].setActive(false);
            }
        };


        int16_t getXOffsetDisplay()                   const { return static_cast<int16_t>(xOffset); }
        int16_t getYOffsetDisplay()                   const { return static_cast<int16_t>(yOffset); }
        uint16_t getPlayerOffsetX()                   const { return this->_playerOffsetX; }
        uint16_t getPlayerOffsetY()                   const { return this->_playerOffsetY; }

        uint8_t getLevelNumber()                      const { return _number; }
        uint16_t getHeight()                          const { return _height; }
        uint16_t getWidth()                           const { return _width; }
        uint16_t getHeightInTiles()                   const { return _heightInTiles; }
        uint16_t getWidthInTiles()                    const { return _widthInTiles; }
        uint16_t getFaresRequired()                   const { return _faresRequired; }
        uint8_t getLevelNameOffset()                  const { return _levelNameOffset; }
        uint8_t getNumberOfCustomerPositions()        const { return _numberOfPositions; }
        uint16_t getFuelMax()                         const { return _fuelMax; }
        uint16_t getGateInterval()                    const { return _internalGateInterval; }
        uint8_t *getLevelData()                       { return this->_levelData; }

        Fuel &getFuel(uint8_t idx)                    { return _fuels[idx]; }


        void setPlayerOffsetX(uint16_t val)           { this->_playerOffsetX = val; }
        void setPlayerOffsetY(uint16_t val)           { this->_playerOffsetY = val; }

        void setLevelNumber(uint8_t val)              { _number = val; }
        void setHeight(uint16_t val)                  { _height = val; }
        void setWidth(uint16_t val)                   { _width = val; }
        void setHeightInTiles(uint16_t val)           { _heightInTiles = val; _height = val * TILE_SIZE; }
        void setWidthInTiles(uint16_t val)            { _widthInTiles = val; _width = val * TILE_SIZE; }

        void setFuel(uint8_t idx, Fuel &fuel)         { _fuels[idx] = fuel; }
        void setFuelMax(uint16_t val)                 { _fuelMax = val; }
        void setFaresRequired(uint8_t val)            { _faresRequired = val; }
        void setGateInterval(uint16_t val)            { _internalGateInterval = val; }

        void setLevelData(uint16_t xPos, uint16_t yPos, uint8_t val) { 

            uint16_t x = (yPos * _widthInTiles) + xPos;

            if (x % 2 == 0) {
                _levelData[x / 2] = (_levelData[x / 2] & 0x0F) | (val << 4);
            }
            else {
                _levelData[x / 2] = (_levelData[x / 2] & 0xF0) | val;
            }

        }

        uint8_t getStartingPosition(uint8_t idx) { 
            return _startingPositions[idx]; 
        }

        uint8_t getEndingPosition(uint8_t idx) { 
            return _endingPositions[idx]; 
        }

        char * getLevelName() {

            return _levelName;
            
        }

        Fuel & getFuel(uint8_t xTile, uint8_t yTile) {

            for (uint8_t i = 0; i < FUEL_TILES_MAX; i++) {

                Fuel &fuel = _fuels[i];

                if (fuel.getXTile() == xTile && fuel.getYTile() == yTile) {
                    return fuel;
                }

            }

            return _fuels[0];

        }

        uint8_t getLevelData(uint8_t x, uint8_t y) {

            uint8_t tile = getTile(x, y);


            // If we have gate tiles and they are not the level (y != 0) check to    
            // see if the tiles need to be rendered vertically ot horizontally ..

            if (tile == GATE1 && y > 0 && (getTile(x, y - 1) == GATE1 || getTile(x, y + 1) == GATE1)) {
                return GATE2;
            }

            if (tile == LEVE1) {
                return (_internalGateMode == GateMode::Closed ? LEVE1 : LEVE2);
            }

            return tile;

        }

        void openLevelGates() {

            for (uint8_t x = _levelGateLeft; x <= _levelGateRight; x++) {

                if (x % 2 == 0) {
                    _levelData[x / 2] = (_levelData[x / 2] & 0x0F);
                }
                else {
                    _levelData[x / 2] = (_levelData[x / 2] & 0xF0);
                }

            }

        }

        void decInternalGateCounter() {

            if (_internalGateCounter > 0) {

                _internalGateCounter--;

                if (_internalGateCounter == 0) {

                    changeInternalGate(GateMode::Closed);

                }

            }

        }

        void changeInternalGate(GateMode mode) {

            for (uint8_t i = 0; i < GATE_TILES_MAX; i++) {

                Gate &gate = _gates[i];

                if (gate.isActive()) {

                    if (gate.getXTile() % 2 == 0) {
                        _levelData[((gate.getYTile() * _widthInTiles) + gate.getXTile()) / 2] = (_levelData[((gate.getYTile() * _widthInTiles) + gate.getXTile()) / 2] & 0x0F) | (mode == GateMode::Closed ? GATE1 << 4 : EMPTY);
                    }
                    else {
                        _levelData[((gate.getYTile() * _widthInTiles) + gate.getXTile()) / 2] = (_levelData[((gate.getYTile() * _widthInTiles) + gate.getXTile()) / 2] & 0xF0) | (mode == GateMode::Closed ? GATE1 : EMPTY);
                    }

                }

            }

            _internalGateMode = mode;
            _internalGateCounter = (mode == GateMode::Open ? _internalGateInterval : 0);

        }

        void reset(uint8_t levelNumber, bool designer) { 

            int16_t levelOffsetX;
            int16_t levelOffsetY;         
            //File file;

            //char level[31] = "SPCAB000.raw";

            //level[7] = (levelNumber % 10) + 48;
            //level[6] = (levelNumber / 10) + 48;

            //file = LittleFS.open(level, "r");
            //file_openRO(level);
            
            file_openRO(levelNumber);

            _number = levelNumber; 
            _internalGateMode = GateMode::Closed;

            file_readBytes((char *)&_levelName, 32);
            file_seek(32);
            file_readBytes((char *)&_widthInTiles, 1);

            _width = _widthInTiles * TILE_SIZE;


            file_readBytes((char *)&_heightInTiles, 1);
            _height = _heightInTiles * TILE_SIZE;


            // Clear fuel locations ..

            for (uint8_t i = 0; i < FUEL_TILES_MAX; i++) {

                Fuel &fuel = _fuels[i];
                fuel.setXTile(0);
                fuel.setYTile(0);
                fuel.setFuelLeft(0);

            }


            // Clear gate locations ..

            for (uint8_t i = 0; i < GATE_TILES_MAX; i++) {

                Gate &gate = _gates[i];
                gate.setActive(false);

            }


            // Read map data ..
            {

                uint16_t levelDataLen = _widthInTiles * _heightInTiles / 2;

                uint8_t fuelIdx = 0;
                uint8_t gateIdx = 0;
                uint16_t dataOffset = 0;
//                uint16_t cursor = 0;

                for (uint16_t i = 0; i < levelDataLen; i++) {

                    uint8_t data = 0;
                    file_readBytes((char *)&data, 1);
                    _levelData[i] = data;
                    uint8_t tile1 = (data & 0xF0) >> 4;
                    uint8_t tile2 = data & 0x0F;

                    switch (tile1) {

                        case FUEL1:
                            updateFuelDetails((i * 2) % _widthInTiles, (i * 2) / _widthInTiles, fuelIdx);
                            fuelIdx++;
                            break;

                        case GATE1:
                        case GATE2:
                      
                            if (i > _widthInTiles / 2) {
                                updateGateDetails((i * 2) % _widthInTiles, (i * 2) / _widthInTiles, gateIdx);
                                gateIdx++;
                            }
                            break;

                    }

                    switch (tile2) {

                        case FUEL1:
                            updateFuelDetails((i * 2) % _widthInTiles + 1, (i * 2) / _widthInTiles, fuelIdx);
                            fuelIdx++;
                            break;

                        case GATE1:
                        case GATE2:
                       
                            if (i  > _widthInTiles / 2) {
                                updateGateDetails((i * 2) % _widthInTiles+ 1, (i * 2) / _widthInTiles, gateIdx);
                                gateIdx++;
                            }
                            break;

                    }

                }


                // Read in starting positions / ending positions ..
   
                file_readBytes((char *)&_startingPositionsCount, 1);
                for (uint8_t i = 0; i < _startingPositionsCount; i++) {

                    file_readBytes((char *)&this->_startingPositions[i], 1);
                }
                
                file_readBytes((char *)&_endingPositionsCount, 1);
                for (uint8_t i = 0; i < _endingPositionsCount; i++) {

                    file_readBytes((char *)&this->_endingPositions[i], 1);
                }

                // Lever offsets x / y ..

                file_readBytes((char *)&levelOffsetX, 2);
                file_readBytes((char *)&levelOffsetY, 2);
                file_readBytes((char *)&this->_playerOffsetX, 2);
                file_readBytes((char *)&this->_playerOffsetY, 2);

                if (designer) {
                    this->_playerOffsetX = this->_playerOffsetX - levelOffsetX;
                    this->_playerOffsetY = this->_playerOffsetY - levelOffsetY - 5;
                }

                // Fuel, fares, nameOffset

                uint8_t fuel = 0;
                file_readBytes((char *)&fuel, 1);
                this->_fuelMax = fuel * 10;

                file_readBytes((char *)&_faresRequired, 1);
                file_readBytes((char *)&_levelNameOffset, 1);
                file_readBytes((char *)&_numberOfPositions, 1);
                file_readBytes((char *)&_levelGateLeft, 1);
                file_readBytes((char *)&_levelGateRight, 1);
                uint8_t gateInterval = 0;
                file_readBytes((char *)&gateInterval, 1);
                this->_internalGateInterval = gateInterval * 10;

                if (!designer) {
                    xOffset = static_cast<float>(levelOffsetX);
                    yOffset = static_cast<float>(levelOffsetY);
                }
                else {
                    xOffset = 0;
                    yOffset = 0;
                }

            }

            this->_levelNameOffset = calculateNameLength(255);

        }


        uint16_t calculateNameLength(uint8_t noOfChars) {

            uint8_t spaces = 0;
            uint8_t chars = 0;
            uint8_t lastChar = 0;

            // Last character ..

            if (noOfChars == 255) {

                for (uint8_t i = 0; i < LEVEL_NAME_LENGTH; i++) {

                    if (this->_levelName[i] != 32 && this->_levelName[i] != 0) {

                        lastChar = i;
                        
                    } 

                }

            }
            else {

                lastChar = noOfChars;

            }

            for (uint8_t i = 0; i < lastChar + 1; i++) {

                if (this->_levelName[i] == 32)  spaces++;
                if (this->_levelName[i] != 32 && this->_levelName[i] != 0)     chars++;


            }

            return (chars * 4) + (spaces * 3);

        }


        uint8_t getNameLength() {

            uint8_t lastChar = 0;

            for (uint8_t i = 0; i < LEVEL_NAME_LENGTH; i++) {

                if (this->_levelName[i] != 32 && this->_levelName[i] != 0) {

                    lastChar = i;
                    
                } 

            }

            return lastChar;

        }

        void clear(uint8_t levelNumber) { 

            int8_t levelOffsetX;
            int8_t levelOffsetY;         

            _number = levelNumber; 
            _widthInTiles = 24;
            _width = _widthInTiles * TILE_SIZE;

            _heightInTiles = 12;
            _height = _heightInTiles * TILE_SIZE;

            for (uint8_t i = 0; i < FUEL_TILES_MAX; i++) {

                Fuel &fuel = _fuels[i];
                fuel.setXTile(0);
                fuel.setYTile(0);
                fuel.setFuelLeft(0);

            }


            // Clear gate locations ..

            for (uint8_t i = 0; i < GATE_TILES_MAX; i++) {

                Gate &gate = _gates[i];
                gate.setActive(false);

            }

            memset(&_levelData, 0, 4096);
            memset(&_levelName, 32, 32);


            // Read in starting positions / ending positions ..
            
            for (uint8_t i = 0; i < STARTING_POSITIONS_MAX; i++) {
                this->_startingPositions[i] = 0;
            }
            
            for (uint8_t i = 0; i < ENDING_POSITIONS_MAX; i++) {
                this->_endingPositions[i] = 0;
            }

            this->_playerOffsetX = 0;
            this->_playerOffsetY = 0;
            this->_fuelMax = 200;
            this->_faresRequired = 4;
            this->_levelNameOffset = 0;
            this->_numberOfPositions = 0;
            this->_levelGateLeft = 0;
            this->_levelGateRight = 0;
            this->_internalGateInterval = 150;
            this->xOffset = 0;
            this->yOffset = 0;

        }

        void updateFuelDetails(uint8_t x, uint8_t y, uint8_t index) {

            Fuel &fuel = _fuels[index];
            fuel.setXTile(x);
            fuel.setYTile(y);
            fuel.setFuelLeft(random(FUEL_MIN, FUEL_MAX));
 
        }

        void updateGateDetails(uint8_t x, uint8_t y, uint8_t index) {

            Gate &gate = _gates[index];
            gate.setXTile(x);
            gate.setYTile(y);
            gate.setActive(true);
 
        }

        uint8_t getTile(uint8_t x, uint8_t y) {

            uint8_t tile = EMPTY;

            if (y > _heightInTiles) return BRICK;

            if ((x % 2) == 0) {
                tile = (_levelData[((y * _widthInTiles) + x) / 2] >> 4);
            }
            else {
                tile = (_levelData[((y * _widthInTiles) + x) / 2] & 0x0f);
            }

            return tile;

        }


        bool isGroundTile(uint8_t x, uint8_t y) {

            uint8_t tile = EMPTY;

            if (y > _heightInTiles) {
                tile = BRICK;
            }
            else {

                if ((x % 2) == 0) {
                    tile = (_levelData[((y * _widthInTiles) + x) / 2] >> 4);
                }
                else {
                    tile = (_levelData[((y * _widthInTiles) + x) / 2] & 0x0f);
                }

            }

// printf("isGroundTile(%i,%i) = %i\n",x,y,tile);

            switch (tile) {

                case BRICK:
                case GRASS:
                case PLAT1:
                case SHADE:
                case ROCKS:
                case METAL:
                case SAND1:
                    return true;

                default:
                    return false;

            }

        }


        bool isBlankTile(uint8_t x, uint8_t y) {

            uint8_t tile = EMPTY;

            if (y > _heightInTiles) {
                tile = BRICK;
            }
            else {

                if ((x % 2) == 0) {
                    tile = (_levelData[((y * _widthInTiles) + x) / 2] >> 4);
                }
                else {
                    tile = (_levelData[((y * _widthInTiles) + x) / 2] & 0x0f);
                }

            }

// printf("isBlankTile(%i,%i) = %i\n",x,y,tile);

            switch (tile) {

                case EMPTY:
                case EDGE1:
                case GRASS:
                case LEVE1:
                case LEVE2:
                    return true;

                default:
                    return false;

            }

        }
};