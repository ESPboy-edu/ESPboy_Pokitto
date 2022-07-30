#pragma once

class Point {

    private:

        int16_t x = 0;
        int16_t y = 0;
        bool active = false;

    
    public:

        int16_t getX()                          { return this->x; }
        int16_t getY()                          { return this->y; }
        bool getActive()                        { return this->active; }

        void setX(int16_t val)                  { this->x = val; }
        void setY(int16_t val)                  { this->y = val; }
        void setActive(bool val)                { this->active = val; }

    
    public:

        void decX()                             { this->x--;}
        void incX()                             { this->x++;}
        void decY()                             { this->y--;}
        void incY()                             { this->y++;}

};
