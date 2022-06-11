#pragma once
#include "Enums.h"
#include "../../My_settings.h"

#include "Pokitto.h"
#include "Enums.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

struct RuneEOG {

    Direction direction;
    uint8_t delay;
    uint32_t index;
    uint32_t x;
};

struct ShopObject {

    Object object;
    uint16_t price;
    uint8_t quantityLeft;

};

struct ShopVariables {

    uint8_t upperIndex = 0;
    uint8_t itemIndex = 0;
    uint8_t counter = 0;
    ShopMessage message = ShopMessage::None;

};

struct Cell {

    uint8_t segment;
    uint8_t variation;
    bool isBlank;
    
};

struct Point {

    int16_t x;
    int16_t y;

};

struct Rect {

    int16_t x;
    int16_t y;
    uint8_t width;
    uint8_t height;

};

struct InventoryMenuVariables {

    InventoryMenuMode mode;
    uint8_t mainCursor = 0;
    uint8_t actionCursor = 0;
    bool showActionMenu = false;

};

struct HighScoreVariables {

    uint8_t charIdx = 2;
    uint8_t entryIdx = 1;

};

struct SplashScreenVariables {

    uint8_t counter = 0;
    uint8_t buttonCounter = 0;
    SplashScreenMode mode = SplashScreenMode::PPOT;

};

struct TitleScreenVars {

    int8_t arrowCounter = 0;
    uint8_t orbCounter = 0;
    uint8_t fadeCounter = 0;
    int32_t yPos = 0;
    TitleScreenOption option = TitleScreenOption::Start;
    TitleScreenMode mode = TitleScreenMode::SelectOption;

};

struct WinScreenVars {

    RuneEOG runeEOG[6];
    uint32_t counter = 0;
    int32_t yPos = 0;
    WinScreenMode mode = WinScreenMode::ShowAnim;

};

struct InventoryItem {

    uint8_t index;      // Ordinal index in collection.
    Object type;
    uint8_t quantity;

    bool getCanEat() {

        switch (type) {

            case Object::Bread:
            case Object::Chicken:
                return true;

            default:
                return false;

        }

    }

};


static inline bool collide(Rect rect1, Rect rect2) {
    return !(rect2.x                >= rect1.x + rect1.width  ||
                rect2.x + rect2.width  <= rect1.x                ||
                rect2.y                >= rect1.y + rect1.height ||
                rect2.y + rect2.height <= rect1.y);
}


struct PlayerStatus {

    Direction direction;
    int8_t health;
    uint8_t coins;
    uint8_t coinsOverall;
    uint8_t kills;
    uint8_t cultists;
    bool moving;
    uint8_t frame;
    Object weapon = Object::FireBall;
    uint32_t weaponCount;
    int8_t puffIndex = 0;
    uint8_t altarPieces = 0;

    InventoryItem inventoryItems[MAX_INVENTORY_ITEMS];

};


struct Node {
    uint8_t x;
    uint8_t y;
    uint8_t value;
};


/* ----------------------------------------------------------------------------
 *  Puzzle structure.
 */
struct Puzzle {
    uint8_t level;                          // Level being played, eg. PUZZLE_5X5, PUZZLE_6X6 ..
    uint8_t index;                          // Puzzle within the current level being played.
    uint8_t board[9][9];                    // Actual board details - supports maximum of 9 x 9.
    Node highlightedNode;
    Node selectedNode;    
};