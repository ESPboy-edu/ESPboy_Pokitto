#pragma once

#include "Point.h"

struct Part : public Point {

    private:
        float x = 0;
        float y = 0;
        float deltaX = 0;
        float deltaY = 0;
        float size = 0;

        uint8_t age = 0;
        uint8_t maxAge = 0;

        bool active = false;
        ExplosionColor color = ExplosionColor::Blue;


    public:

        float getX()                            { return this->x; }
        float getY()                            { return this->y; }
        float getDeltaX()                       { return this->deltaX; }
        float getDeltaY()                       { return this->deltaY; }
        float getSize()                         { return this->size; }
        uint8_t getAge()                        { return this->age; }
        uint8_t getMaxAge()                     { return this->maxAge; }
        bool getActive()                        { return this->active; }
        ExplosionColor getColor()               { return this->color; }

        void setX(float val)                    { this->x = val; }
        void setY(float val)                    { this->y = val; }
        void setDeltaX(float val)               { this->deltaX = val; }
        void setDeltaY(float val)               { this->deltaY = val; }
        void setSize(float val)                 { this->size = val; }
        void setAge(uint8_t val)                { this->age = val; }
        void setMaxAge(uint8_t val)             { this->maxAge = val; }
        void setActive(bool val)                { this->active = val; }
        void setColor(ExplosionColor val)       { this->color = val; }


        void incAge() {

            this->age++;

        }

        void reset() {

        }
};

