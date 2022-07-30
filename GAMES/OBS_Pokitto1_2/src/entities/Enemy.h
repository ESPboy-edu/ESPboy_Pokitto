#pragma once

#include "Point.h"
#include "Rect.h"
#include "../utils/Enums.h"

class Enemy : public Point {

    private:
        
        Path path = Path::Small;
        Motion motion = Motion::Slow;

        uint8_t pathCount = 0; 
        uint8_t yOffset = 0;         
        uint8_t explodeCounter = 0;


    public:
        
        Path getPath()                          { return this->path; }
        Motion getMotion()                      { return this->motion; }

        uint8_t getPathCount()                  { return this->pathCount; }
        uint8_t getYOffset()                    { return this->yOffset; }
        uint8_t getExplodeCounter()             { return this->explodeCounter; }

        void setPath(Path val)                  { this->path = val; }
        void setMotion(Motion val)              { this->motion = val; }

        void setPathCount(uint8_t val)          { this->pathCount = val; }
        void setYOffset(uint8_t val)            { this->yOffset = val; }
        void setExplodeCounter(uint8_t val)     { this->explodeCounter = val; }


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
    

        void incPathCount(uint8_t limit) {

            this->pathCount++;
            if (this->pathCount == limit) this->pathCount = 0;

        }


        Rect getRect() {

            Rect rect = { this->getX() + 1, this->getY() + 1, 9, 11 };

            return rect;

        }

};