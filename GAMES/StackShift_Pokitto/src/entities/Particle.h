#include "Pokitto.h"
#include "../utils/Consts.h"
#include "../utils/Utils.h"

struct Particle {

    private:

        ParticleType type = ParticleType::One;
        Color colour;

        int16_t x = 0;
        int16_t y = 0;
        float velx = 0;
        float vely = 0;
        uint8_t counterInit = 0;
        uint8_t counter = 0;
        uint8_t pSize = 1;
        uint16_t score = 0;
        int16_t boundL, boundR;
        uint8_t delay = 0;

    public:

        static constexpr float rThresh = 0.000001 * 16;
        static constexpr float cF = 0.96;
        static constexpr float gravity = 0.12;

        int16_t getX()                          { return this->x; }
        int16_t getY()                          { return this->y; }
        uint8_t getCounter()                    { return this->counter; }
        uint8_t getSize()                       { return this->pSize; }
        Color getColour()                       { return this->colour; }
        uint16_t getScore()                     { return this->score; }
        ParticleType getType()                  { return this->type; }
        float getVelX()                         { return this->velx; }
        float getVelY()                         { return this->vely; }
        uint8_t getDelay()                      { return this->delay; }

        void setX(int16_t val)                  { this->x = val; }
        void setY(int16_t val)                  { this->y = val; }
        void setCounter(int16_t val)            { this->counter = val; this->counterInit = val; }
        void setVelX(float val)                 { this->velx = val; }
        void setVelY(float val)                 { this->vely = val; }
        void setSize(uint8_t val)               { this->pSize = val; }
        void setType(ParticleType val)          { this->type = val; }
        void setColour(Color val)               { this->colour = val; } 
        void setScore(uint16_t val)             { this->score = val; }
        void setDelay(uint8_t val)              { this->delay = val; }

    public:

        void update() {


            // burn delay ..

            if (this->delay > 0) {
                this->delay--;
                return;
            }


            // move your particle based on direction, whatever ..

            this->vely -= gravity * this->pSize;
            this->velx *= cF;

            switch (this->type) {

                case ParticleType::Zero:
                    this->boundL = 0;
                    this->boundR = 220;
                    break;

                case ParticleType::One:
                    this->boundL = BOARD_X_OFFSET + 2;
                    this->boundR = (BOARD_WIDTH*PART_SIZE) + 2 + BOARD_X_OFFSET;
                    break;

                case ParticleType::Two:
                    this->boundL = 0;
                    this->boundR = 220;
                    break;

                case ParticleType::Score:
                    this->boundL = (BOARD_WIDTH*PART_SIZE) + BOARD_X_OFFSET + 4;  
                    this->boundR = 180;
                    break;

            }


            if (this->x > this->boundR - this->pSize) {
                this->x = this->boundR - this->pSize;
                this->velx = -this->velx;

            }

            if (this->x < this->boundL) {
                this->x = this->boundL;
                this->velx = -this->velx;
            }

            if (this->y > (BOARD_HEIGHT*PART_SIZE) + 4) { // above (below) board height - bottom of screen

                this->y = (BOARD_HEIGHT*PART_SIZE) + 4;

                if(this->vely > rThresh) {

                    this->vely = -this->vely * rThresh;

                }
                else {

                    this->vely = 0;

                }

            }

            if (this->type != ParticleType::Score) {
                if (this->y < 0) { // below (above) board - top of screen
                    if (this->vely > rThresh) {
                        this->vely = -this->vely * rThresh;
                    }
                    else {
                        this->vely = 0;            
                    }
                }           
            }

            this->x += this->velx;
            this->y -= this->vely;


            // shift size

            if (this->counter < counterInit * 0.5) {
                if( this->pSize > 2) this->pSize = 2;
            }

            if (this->counter <  counterInit * 0.2) {
                if( this->pSize > 1) this->pSize = 1;
            }

            if (this->counter > 0) this->counter--;

        }

        bool render() {

            return (this->counter > 0 && this->delay == 0);

        }

        bool isActive() {

            return (this->counter > 0);

        }

};
