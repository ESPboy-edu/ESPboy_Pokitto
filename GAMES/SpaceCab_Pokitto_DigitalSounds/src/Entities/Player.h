#pragma once

#include "../Utils/Constants.h"

#define PLAYER_X_CENTRE ((SCREEN_WIDTH-12)/2)
#define PLAYER_Y_CENTRE ((SCREEN_HEIGHT-8)/2)

struct Player {

    private:

        float x;
        float y;
        int8_t xDelta = 0;
        int8_t yDelta = 0;
        uint8_t frame = 0;
        uint8_t retractLandgingGear = 0; // Counter when moving up.
        uint16_t fuel = 0;
        uint16_t score = 0;
        uint8_t numberOfLives = 0;
        PlayerStatus status;
        PlayerStatus nextStatus;
        uint8_t faresCompleted;
        bool carryingCustomer = false;
        bool landingGearDown = false;
        bool justLanded = true;
        bool pickingUpCustomer = false;
        bool fuelling = false;
        uint8_t falling = 0;

    public:

        const float getX()                                      { return this->x; }
        const float getY()                                      { return this->y; }
        int8_t getXDelta()                                      { return this->xDelta; }
        int8_t getYDelta()                                      { return this->yDelta; }
        uint8_t getFrame()                                      { return this->frame; }
        uint8_t getNumberOfLives()                              { return this->numberOfLives; }
        uint16_t getFuel()                                      { return this->fuel; }
        uint16_t getScore()                                     { return this->score; }
        bool isCarryingCustomer()                               { return this->carryingCustomer; }
        bool isLandingGearDown()                                { return this->landingGearDown; }
        bool hasJustLanded()                                    { return this->justLanded; }
        bool getPickingUpCustomer()                             { return this->pickingUpCustomer; }
        bool isFuelling()                                       { return this->fuelling; }
        PlayerStatus getStatus()                                { return this->status; }
        PlayerStatus getNextStatus()                            { return this->nextStatus; }
        uint8_t getRetractLandingGear()                         { return this->retractLandgingGear; }
        uint8_t getFaresCompleted()                             { return this->faresCompleted; }
        uint8_t getFalling()                                    { return this->falling; }

        void setX(float val)                                    { this->x = val; }
        void setY(float val)                                    { this->y = val; }
        void setXDelta(int8_t val)                              { this->xDelta = val; }
        void setYDelta(int8_t val)                              { this->yDelta = val; if (val == 0) this->falling = 0; }
        void setFrame(uint8_t val)                              { this->frame = val; }
        void setNumberOfLives(uint8_t val)                      { this->numberOfLives = val; }
        void setFuel(uint16_t val)                              { this->fuel = val; }
        void setScore(uint16_t val)                             { this->score = val; }
        void setCarryingCustomer(bool val)                      { this->carryingCustomer = val; }
        void setLandingGearDown(bool val)                       { this->landingGearDown = val; }
        void setJustLanded(bool val)                            { this->justLanded = val; }
        void setPickingUpCustomer(bool val)                     { this->pickingUpCustomer = val; }
        void setFuelling(bool val)                              { this->fuelling = val; }
        void setStatus(PlayerStatus val)                        { this->status = val; }
        void setNextStatus(PlayerStatus val)                    { this->nextStatus = val; }
        void setRetractLandingGear(int8_t val)                  { this->retractLandgingGear = val; }
        void setFaresCompleted(int8_t val)                      { this->faresCompleted = val; }
        void setFalling(uint8_t val)                            { this->falling = val; }

        uint16_t getXDisplay()                                  { return static_cast<int16_t>(this->x); }
        uint16_t getYDisplay()                                  { return static_cast<int16_t>(this->y); }
        float getXDeltaVal()                                    { return (static_cast<float>(this->xDelta) / 8.00); }
        float getYDeltaVal()                                    { return (static_cast<float>(this->yDelta) / 8.00); }

        void incFaresCompleted()                                { this->faresCompleted++;}
        void incFuel()                                          { this->fuel++;}
        void decFuel()                                          { if (this->fuel > 0) this->fuel--; }
        void decNumberOfLives()                                 { this->numberOfLives--; }
        void decStatus()                                        { this->status--; }

        void decRetractLandingGear() { 

            if (this->retractLandgingGear > 0) {

                this->retractLandgingGear--;

                if (this->retractLandgingGear == 0) {

                    this->landingGearDown = false;

                }

            }

        }

        void incXDelta() {

            switch (this->xDelta) {

                case -8 ... -2:
                    this->xDelta = this->xDelta / 2;
                    break;
                    
                case -1:
                    this->xDelta = 0;
                    break;
                    
                case 0:
                    this->xDelta = 1;
                    break;

                case 1 ... 4:
                    this->xDelta = this->xDelta * 2;
                    break;

            }

        }

        void decXDelta() {

            switch (this->xDelta) {

                case -4 ... -1:
                    this->xDelta = this->xDelta * 2;
                    break;

                case 0:
                    this->xDelta = -1;
                    break;

                case 1:
                    this->xDelta = 0;
                    break;

                case 2 ... 8:
                    this->xDelta = this->xDelta / 2;
                    break;
                    
            }

        }

        void incYDelta() {
            
            switch (this->yDelta) {

                case -8 ... -2:
                    this->yDelta = this->yDelta / 2;
                    break;
                    
                case -1:
                    this->yDelta = 0;
                    break;
                    
                case 0:
                    this->yDelta = 1;
                    break;

                case 1 ... 4:
                    this->yDelta = this->yDelta * 2;
                    break;

            }

            if (this->falling < 255) this->falling++;

        }

        void decYDelta() {

            switch (this->yDelta) {

                case -4 ... -1:
                    this->yDelta = this->yDelta * 2;
                    break;

                case 0:
                    this->yDelta = -1;
                    break;

                case 1:
                    this->yDelta = 0;
                    break;

                case 2 ... 8:
                    this->yDelta = this->yDelta / 2;
                    break;
                    
            }

            this->falling = 0;

        }

        uint8_t getHeight() {

            return (this->landingGearDown ? PLAYER_HEIGHT + 3 : PLAYER_HEIGHT);

        }

        void reset(Level &level) {

            this->xDelta = 0;
            this->yDelta = 0;
            this->frame = 0;
            this->carryingCustomer = false;
            this->landingGearDown = true;
            this->justLanded = true;
            this->pickingUpCustomer = false;
            this->fuelling = false;
            this->status = PlayerStatus::Active;
            this->fuel = level.getFuelMax();
            this->x = static_cast<float>(level.getPlayerOffsetX()); 
            this->y = static_cast<float>(level.getPlayerOffsetY()); 
            this->status = PlayerStatus::Active;
            this->nextStatus = PlayerStatus::Active;

        }

};