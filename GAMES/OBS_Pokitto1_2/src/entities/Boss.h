#pragma once


enum class ExplodeType : uint8_t {
    Body,
	TopHand,
    BottomHand
};

class Boss : public Point {

    private:

        uint8_t pathCounter = 0;         
        uint8_t explodeCounter[3] = { 0, 0, 0};
        uint8_t topHealth = 3;
        uint8_t bottomHealth = 3;

        Point explodePoint;
        

    public:

        uint8_t getPathCounter()                                { return this->pathCounter; }
        uint8_t getExplodeCounter(ExplodeType ex)               { return this->explodeCounter[static_cast<uint8_t>(ex)]; }
        uint8_t getTopHealth()                                  { return this->topHealth; }
        uint8_t getBottomHealth()                               { return this->bottomHealth; }
        Point &getExplodePoint()                                { return this->explodePoint; }

        void setPathCounter(uint8_t val)                        { this->pathCounter = val; }
        void setExplodeCounter(ExplodeType ex, uint8_t val)     { this->explodeCounter[static_cast<uint8_t>(ex)] = val; }
        void setTopHealth(uint8_t val)                          { this->topHealth = val; }
        void setBottomHealth(uint8_t val)                       { this->bottomHealth = val; }
        void setExplodePoint(Point &val)                        { this->explodePoint = val; }

        void reset() {

            this->setActive(false);
            this->setY(0);         
            this->setX(0);         
            this->pathCounter = 0;         
            this->explodeCounter[0] = 0;
            this->explodeCounter[1] = 0;
            this->explodeCounter[2] = 0;

            this->topHealth = 3;
            this->bottomHealth = 3;

        }

        void incPathCounter() {

            this->pathCounter++;
            if (this->pathCounter == 70) this->pathCounter = 0;

        }

        void decExplodeCounter(ExplodeType explodeType) {

            this->explodeCounter[static_cast<uint8_t>(explodeType)] = this->explodeCounter[static_cast<uint8_t>(explodeType)] - 1;

        }


};
