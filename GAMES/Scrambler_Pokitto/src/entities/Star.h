#pragma once

class Star {

    private:

        uint8_t x = 0;
        uint16_t y = 0;
    
    public:

        uint8_t getX()                          { return this->x; }
        uint16_t getY()                         { return this->y; }

        void setX(uint8_t val)                  { this->x = val; }
        void setY(uint16_t val)                 { this->y = val; }

};
