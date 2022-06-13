#pragma once

#include "Pokitto.h"
#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "../utils/Structs.h"

class EnemyBullet {

    public:

        EnemyBullet();

        
        // Properties ..
        
        float getX();
        float getXDelta();
        uint8_t getY();
        bool isEnabled();
        BulletType getBulletType();

        void setX(float x);
        void setXDelta(float xDelta);
        void setY(uint8_t y);
        void setEnabled(bool enabled);
        void setBulletType(BulletType bulletType);

    private:

        float x = 0;
        float xDelta = 0;
        uint8_t y = 0;

        bool enabled = false;
        BulletType bulletType;
        
};