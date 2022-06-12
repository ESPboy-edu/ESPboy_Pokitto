/* Code lifted from NewBlocksOnTheKid by Kevin Bates.
 * Code concept from filmote thanks filmote
 * Pharap and MLXXXP helped too thanks!
 * 
 *  ARDUBOY FOREVER!
 * 
 * 
 */
#include "../utils/Constants.h"

struct Particle {

    private:

        int16_t x = 0;
        int16_t y = 0;
        float velx = 0;
        float vely = 0;
        uint8_t counter = 0;
        uint8_t color = 1;

    public:

        static constexpr float rThresh          = 0.000001 * 16;
        static constexpr float cF               = 0.96;
        static constexpr float gravity          = 0.12;

        int16_t getX()                          { return this->x; }
        int16_t getY()                          { return this->y; }
        int8_t getCounter()                     { return this->counter; }
        uint8_t getColor()                      { return this->color; }

        void setX(int16_t val)                  { this->x = val; }
        void setY(int16_t val)                  { this->y = val; }
        void setCounter(int16_t val)            { this->counter = val; }
        void setVelX(float val)                 { this->velx = val; }
        void setVelY(float val)                 { this->vely = val; }
        void setColor(uint8_t val)              { this->color = val; }

    public:

        void update() {

            if (counter == 0) return;


            // move your particle based on direction, whatever ..

            const uint8_t boundL = 0;
            const uint8_t boundR = 110;
            const uint8_t maxR = 88;
            this->vely -= gravity; 
            this->velx *= cF;

            if (this->x > boundR - 2 ){
                this->x = boundR - 2 ;
                this->velx = -this->velx;
            }

            if (this->x < boundL) {
                this->x = boundL;
                this->velx = -this->velx;
            }

            if (this->y > maxR) { // above (below) board height - bottom of screen

                this->y = maxR;

                if (this->vely > rThresh)
                    this->vely = -this->vely * rThresh;
                else
                    this->vely = 0;

            }

            if (this->y < 0) { // below (above) board - top of screen

                if (this->vely > rThresh)
                    this->vely = -this->vely * rThresh;
                else
                    this->vely = 0;         

            }           

            this->x += static_cast<int16_t>(this->velx);
            this->y -= static_cast<int16_t>(this->vely);

            if (this->counter > 0) this->counter--;

        }

        bool render() {
            return (this->counter > 0);
        }

};