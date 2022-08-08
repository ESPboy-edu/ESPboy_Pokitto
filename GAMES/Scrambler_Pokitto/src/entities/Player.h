#pragma once

#include "../utils/Enums.h"
#include "../utils/Utils.h"

class Player : public Point {

    private:

        uint8_t lives = 0;
        uint8_t fuel = 0;
        uint8_t countdown = 0;


        // Inertia ..

        uint8_t xDelay = 16;
        uint16_t xFrameCount = 0;
        Direction xDirection = Direction::None;

        uint8_t yDelay = 16;
        uint16_t yFrameCount = 0;
        Direction yDirection = Direction::None;


    public:

        uint8_t getFuel()                       { return this->fuel; }
        uint8_t getLives()                      { return this->lives; }
        uint8_t getCountdown()                  { return this->countdown; }
        uint8_t getXDelay()                     { return this->xDelay; }
        uint16_t getXFrameCount()               { return this->xFrameCount; }
        Direction getXDirection()               { return this->xDirection; }
        uint8_t getYDelay()                     { return this->yDelay; }
        uint16_t getYFrameCount()               { return this->yFrameCount; }
        Direction getYDirection()               { return this->yDirection; }

        void setFuel(uint8_t val)               { this->fuel = val; }
        void setLives(uint8_t val)              { this->lives = val; }
        void setCountdown(uint8_t val)          { this->countdown = val; }
        void setXDelay(uint8_t val)             { this->xDelay = val; }
        void setXFrameCount(uint16_t val)       { this->xFrameCount = val; }
        void setXDirection(Direction val)       { this->xDirection = val; }
        void setYDelay(uint8_t val)             { this->yDelay = val; }
        void setYFrameCount(uint16_t val)       { this->yFrameCount = val; }
        void setYDirection(Direction val)       { this->yDirection = val; }

    public:

        void decLives() {

            this->lives--;

        }
        
        void decFuel() {

            this->fuel--;

        }
        
        void incFuel(uint8_t inc) {

            this->fuel = this->fuel + inc;

            if (this->fuel > 150) this->fuel = 150;

        }

        void incY(uint8_t inc) {

            this->setY(this->getY() + inc);

        }

        void decY(uint8_t inc) {

            this->setY(this->getY() - inc);

        }

        void incX(uint8_t inc) {

            this->setX(this->getX() + inc);

        }

        void incX(uint8_t inc, uint16_t frameCount) {

            this->setX(this->getX() + inc);
            this->xFrameCount = frameCount;
            this->xDirection = Direction::Right;

            if (this->xDelay > 1) this->xDelay = this->xDelay / 2;

        }

        void incX(uint8_t inc, uint16_t frameCount, uint8_t delay, bool movingToStop = false) {

            this->setX(this->getX() + inc);
            this->xDelay = delay;
            this->xFrameCount = frameCount;
            this->xDirection = Direction::Right;

            if (movingToStop && this->yDelay == Constants::Player_Inertia) this->xDirection = Direction::None;

        }

        void decX(uint8_t inc, uint16_t frameCount) {

            this->setX(this->getX() - inc);
            this->xFrameCount = frameCount;
            this->xDirection = Direction::Left;

            if (this->xDelay > 1) this->xDelay = this->xDelay / 2;

        }

        void decX(uint8_t inc, uint16_t frameCount, uint8_t delay, bool movingToStop = false) {

            this->setX(this->getX() - inc);
            this->xDelay = delay;
            this->xFrameCount = frameCount;
            this->xDirection = Direction::Left;

            if (movingToStop && this->xDelay == Constants::Player_Inertia) this->xDirection = Direction::None;

        }

        void incY(uint8_t inc, uint16_t frameCount) {

            this->setY(this->getY() + inc);
            this->yFrameCount = frameCount;
            this->yDirection = Direction::Down;

            if (this->yDelay > 1) this->yDelay = this->yDelay / 2;

        }

        void incY(uint8_t inc, uint16_t frameCount, uint8_t delay, bool movingToStop = false) {

            this->setY(this->getY() + inc);
            this->yDelay = delay;
            this->yFrameCount = frameCount;
            this->yDirection = Direction::Down;

            if (movingToStop && this->yDelay == Constants::Player_Inertia) this->yDirection = Direction::None;

        }

        void decY(uint8_t inc, uint16_t frameCount) {

            this->setY(this->getY() - inc);
            this->yFrameCount = frameCount;
            this->yDirection = Direction::Up;

            if (this->yDelay > 1) this->yDelay = this->yDelay / 2;

        }

        void decY(uint8_t inc, uint16_t frameCount, uint8_t delay, bool movingToStop = false) {

            this->setY(this->getY() - inc);
            this->yDelay = delay;
            this->yFrameCount = frameCount;
            this->yDirection = Direction::Up;

            if (movingToStop && this->yDelay == Constants::Player_Inertia) this->yDirection = Direction::None;

        }

        bool movePlayerX(uint16_t frameCount) {

            return ((frameCount - this->xFrameCount) % (this->xDelay / 2) == 0); 

        }

        bool movePlayerY(uint16_t frameCount) {

            return ((frameCount - this->yFrameCount) % (this->yDelay / 2) == 0); 

        }

        bool getMoveScenery() {

            switch (this->countdown) {

                case 0:
                case 1:
                case 2:
                case 4:
                case 6:
                case 8:
                case 11:
                case 14:
                case 17:
                case 21:
                case 25:
                case 29:
                case 34:
                case 39:
                case 44:
                case 50:
                case 56:
                case 62:
                case 70:
                case 79:
                case 88:
                case 98:
                case 112:
                    return true;
                
            }

            return false;

        }

        void updateCounter() {

            if (this->countdown >= 1 && this->countdown < Constants::GrindToHalt) {

                this->countdown++;

            }

        }

        void reset(bool resetLives) {

            this->setActive(true);
            this->countdown = 0;
            this->setX(25);
            this->setY(16015);
            this->fuel = 150;
            if (resetLives) this->lives = 3;
            
        }

};
