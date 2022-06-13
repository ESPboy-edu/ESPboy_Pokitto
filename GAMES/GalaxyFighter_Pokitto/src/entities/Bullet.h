#pragma once

#include "Pokitto.h"
#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "../utils/Structs.h"

class Bullet {

    public:

        Bullet();

        
        // Properties ..
        
        uint8_t getX();
        uint8_t getY();
        bool isEnabled();

        void setX(uint8_t x);
        void setY(uint8_t y);
        void setEnabled(bool enabled);

    private:

        uint8_t x = 0;
        uint8_t y= 0;
        bool enabled = false;
        
};