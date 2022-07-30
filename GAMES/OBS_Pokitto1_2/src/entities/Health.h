#pragma once

#include "Point.h"

class Health : public Point {

    private:

        uint8_t type = 0;
    
    public:

        uint8_t getType()                       { return this->type; }

        void setType(uint8_t val)               { this->type = val; }

        Rect getRect() {

            Rect rect = { this->getX() + 1, this->getY() + 1, 10, 10 };
            return rect;

        }

};