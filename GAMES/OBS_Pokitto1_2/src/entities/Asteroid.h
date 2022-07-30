#pragma once

#include "Point.h"

class Asteroid : public Point {

    private:

        uint8_t type = 0;
    
    public:

        uint8_t getType()                       { return this->type; }

        void setType(uint8_t val)               { this->type = val; }

        Rect getLargeAsteroidRect() {

            Rect rect = { this->getX() + 1, this->getY() + 1, 17, 17 };
            return rect;

        }

        Rect getSmallAsteroidRect() {

            Rect rect = { this->getX() + 1, this->getY() + 1, 17, 17 };
            return rect;

        }

};