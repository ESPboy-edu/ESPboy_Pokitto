#pragma once

#include "Rect.h"

class Player {

    private:

        uint8_t y = 26;
        uint16_t health = (17 * Constants::Health_Factor) - 1;
        uint8_t explodeCounter = 0;
        Direction direction = Direction::None;


    public:

        uint8_t getY()                          { return this->y; }
        uint16_t getHealth()                    { return this->health; }
        uint8_t getExplodeCounter()             { return this->explodeCounter; }
        Direction getDirection()                { return this->direction; }

        void setY(uint8_t val)                  { this->y = val; }
        void setHealth(uint16_t val)            { this->health = val; }
        void setExplodeCounter(uint8_t val)     { this->explodeCounter = val; }
        void setDirection(Direction val)        { this->direction = val; }


        bool updateExplosion() {

            if (this->explodeCounter > 0) {

                this->explodeCounter--;

                if (this->explodeCounter == 0) {

                    this->explodeCounter = 0;
                    return true;

                }

            }

            return false;

        }


        void decHealth(uint8_t i) {

            if (this->health >= i) {
                this->health = this->health - i;
            }
            else {
                this->health = 0;
            }

        }


        void incHealth(uint8_t i) {

            if (this->health + i >= (17 * Constants::Health_Factor) - 1) {
                this->health = (17 * Constants::Health_Factor) - 1;
            }
            else {
                this->health = (17 * Constants::Health_Factor) - 1;
            }

        }


        void reset() {

            this->y = 26;
            this->direction = Direction::None;
            this->health = (17 * Constants::Health_Factor) - 1;
            this->explodeCounter = 0;

        }


        Rect getRect() {

            Rect rect = { 10, this->getY() + 1, 12, 8 };

            return rect;

        }

};