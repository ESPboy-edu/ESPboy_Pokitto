#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../utils/Structs.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;



class Player {

    public:

        Player();

        uint16_t getX();
        uint16_t getY();
        PROGMEM const uint8_t getWidth();
        PROGMEM const uint8_t getHeight();
        Direction getDirection();
        int8_t getHealth();
        uint8_t getCoins();
        uint8_t getCoinsOverall();
        uint8_t getKills();
        uint8_t getCultists();
        uint8_t getFrame();
        bool getMoving();
        Object getWeapon();
        int8_t getPuffIndex();
        uint8_t getAltarPieces();
        PlayerStatus getPlayerStatus();

        void setX(uint16_t x);
        void setY(uint16_t y);
        void setDirection(Direction direction);
        void setHealth(int8_t health);
        void setCoins(uint8_t coins);
        void setCoinsOverall(uint8_t coins);
        void setKills(uint8_t kills);
        void setCultists(uint8_t cultists);
        void setFrame(uint8_t frame);
        void setMoving(bool moving);
        void setWeapon(Object weapon);
        void setPlayerStatus(PlayerStatus playerStatus);

        void incFrame();
        void incCoins(uint8_t coins);
        void initLevel(uint16_t x, uint16_t y);
        void decWeaponCount();
        void decPuffIndex();

        void incHealth(uint8_t amount);
        void decHealth(uint8_t amount);
        
        uint8_t getWeaponFrame();
        uint32_t getWeaponCount();
        Rect getRect();
        void reset();
        void incAltarPieces();


        // Inventory methods

        InventoryItem & getInventoryItem(uint8_t index);
        InventoryItem & getActiveInventoryItem(uint8_t index);                  // index skips qty = 0 values
        uint8_t addInventoryItem(Object type, uint8_t qty);                     // returns slot used if success, NO_SLOT_FOUND if failed
        uint8_t decInventoryItem(Object type);                                  // returns slot used if success, NO_SLOT_FOUND if failed
        uint8_t getInventorySlot(Object type);                                  // returns slot used if success, NO_SLOT_FOUND if failed
        uint8_t getEmptySlot();                                                 // returns slot used if success, NO_SLOT_FOUND if failed
        uint8_t getInventoryCount();
        uint8_t getInventoryCount(Object type);
        uint8_t getActiveSlotCount();

    private:
        uint16_t x;
        uint16_t y;
        PlayerStatus playerStatus;

};
