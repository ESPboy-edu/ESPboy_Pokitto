#pragma once

#include "Pokitto.h"
#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "../utils/Structs.h"
#include "../entities/Entities.h"

class CaptureController {

    public:

        CaptureController();

        int32_t getX();
        int32_t getY();
        Enemy * getEnemy();
        Player * getPlayer();
        
        void setEnemy(Enemy * enemy);
        void setPlayer(Player * player);

        CapturedPlayer getCapturedPlayer();
        void setCapturedPlayer(CapturedPlayer capturedPlayer);
        void move(bool &atTopOfScreen, bool &waitUntilComplete);
        void reset();
        uint8_t getImage();
        bool getImageFlip();

    private:

        Enemy * enemy;
        Player * player;

        int32_t x;
        int32_t y;

        uint8_t capturedRotation;
        CapturedPlayer capturedPlayer = CapturedPlayer::None;
        
};