#pragma once

#include "Constants.h"
#include "Vector2.h"

struct SplashScreenVariables {

    uint8_t counter = 0;

    void reset() {

        this->counter = 0;

    }

};

struct GamePlayVariables {

    Vector2 stars[MAX_STARS];
    uint8_t levelNumber = 0;
    uint8_t thrusterFrame = 0;
    int16_t backdropx[2] = { 0, 0 };
    uint8_t fareCount = 0;
    uint8_t dollarsCount = 0;
    uint8_t flashingCounter = 0;
    uint8_t bootCounter = 50;
    uint8_t gotoCounter = 0;
    uint8_t ouchCounter = 0;
    uint8_t gateToRender = 1; // For introduction.
    bool starsInitialised = false;
    bool paused = false;

    uint8_t maxNumberOfLevels = 0;

    void reset() {

        this->levelNumber = 0;
        this->thrusterFrame = 0;
        this->backdropx[0] = 0;
        this->backdropx[1] = 0;
        this->fareCount = 0;
        this->dollarsCount = 0;
        this->flashingCounter = 0;
        this->bootCounter = 50;
        this->gotoCounter = 0;
        this->ouchCounter = 0;
        this->gateToRender = 1; // For introduction.
        this->starsInitialised = false;
        this->paused = false;

        // this->maxNumberOfLevels = 0; // Do not reset as this is calculated once and thats it!

    }

};

struct HighScoreScreenVariables {

    uint8_t alternate = 0;
    uint8_t clearScores = 0;

    void reset() {

        this->alternate = 0;
        this->clearScores = 0;

    }

};

struct DesignerScreenVariables {

    char names[DESIGNER_ENTRY_COUNT][33];
    uint8_t entryTop = 0;
    uint8_t entryCursor = 0;
    uint8_t entryCount = 0;
    uint8_t subMenuCursor = 0;
    uint8_t levelName_cursor = 0;
    uint8_t cursorX = 0;
    uint8_t cursorY = 0;
    int16_t cursorXOffset = 0;
    int16_t cursorYOffset = 0;
    uint8_t cursorTile = 0;
    uint8_t cursorTileOld = 0;
    uint8_t toolTop = 0;
    uint8_t origWidthInTiles = 0;
    uint8_t origHeightInTiles = 0;

    DesignerScreenMode mode = DesignerScreenMode::MainMenu;
    DesignerScreenMode prevMode = DesignerScreenMode::MainMenu;
    DesignerError error = DesignerError::Signs;

    void reset() {

        this->entryTop = 0;
        this->entryCount = 0;
        this->entryCursor = 0;
        this->subMenuCursor = 0;
        this->levelName_cursor = 0;
        this->cursorX = 0;
        this->cursorY = 0;
        this->cursorXOffset = 0;
        this->cursorYOffset = 0;
        this->cursorTile = 0;
        this->toolTop = 0;
        this->mode = DesignerScreenMode::MainMenu;

    }

};

struct LevelDefinition {
  uint8_t levelWidth;
  uint8_t levelHeight;
  int16_t levelXOffset;
  int16_t levelYOffset;
  uint8_t playerXOffset;
  uint8_t playerYOffset;
  uint16_t playerInitialFuel;
  uint8_t faresRequired;
  uint8_t levelNameOffset;
  uint8_t numberOfPositions;
  uint8_t levelGateLeft;
  uint8_t levelGateRight;
  uint16_t internalGateInterval;
};