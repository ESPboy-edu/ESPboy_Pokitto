#pragma once

#include "Point.h"

class Shockwave : public Point {

    private:

        uint8_t radius = 0;
        uint8_t maxRadius = 0;
        uint8_t speed = 0;

    public:

        uint8_t getRadius()                         { return this->radius; }
        uint8_t getMaxRadius()                      { return this->maxRadius; }
        uint8_t getSpeed()                          { return this->speed; }

        void setRadius(uint8_t val)                 { this->radius = val; }
        void setMaxRadius(uint8_t val)              { this->maxRadius = val; }
        void setSpeed(uint8_t val)                  { this->speed = val; }

        void reset() {

            this->radius = 0;
            this->maxRadius = 0;
            this->speed = 0;

        }

};

