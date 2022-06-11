#pragma once

#include "Pokitto.h"
#include "Enums.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

struct IntroTextVariables {

    int16_t y = 90;

};

struct InstructionVariables {

    uint8_t instruction;
    bool performedFightReady;
    bool performedUpright;
    bool kickHigh;
    bool kickMed;
    bool kickLow;
    bool punchHigh;
    bool punchMed;
    bool punchLow;
    
    void reset() {

        this->instruction = 0;
        this->performedFightReady = false;
        this->performedUpright = false;
        this->kickHigh = false;
        this->kickMed = false;
        this->kickLow = false;
        this->punchHigh = false;
        this->punchMed = false;
        this->punchLow = false;
        
    }

};

struct SplashScreenVariables {

    uint8_t counter = 0;
    uint8_t buttonCounter = 0;

};

struct TitleScreenVars {

    int8_t arrowCounter = 0;
    uint8_t orbCounter = 0;
    uint8_t fadeCounter = 0;
    int32_t yPos = 0;

};

#define IDLE_INC 24
#define IDLE_MIN (IDLE_INC * 3)

struct Entity {
    
    private:
        uint8_t health;
        uint8_t stance;
        int16_t xPos;
        int16_t xPosDelta;
        int16_t xPosOverall;
        int16_t yPos;
        int16_t yPosDelta;
        EntityType entityType;   
        Movement movement;                        
        bool rightPunch;
        bool rightFoot;
        bool dead;
        uint8_t regain;
        uint8_t regainLimit;
        uint8_t activity;        // For enemies, defines how active they are (used in random actions). 
                                // For player, defines the number of kicks or punches they have taken from the kick / punch ready position.
        uint8_t mode = EAGLE_MODE_NONE;
        uint8_t frame = 0;
        uint8_t idleFrame = 0;
        uint8_t immediateAction = 0;
        uint8_t retreatAction = 0;
        uint8_t actionPreference = 0;
        uint8_t movementFrequency = 0;
        uint8_t eagleAttack = 0;
        uint8_t eagleAttackLength = 0;
        uint8_t actionsBeforeReturn = 0;
        
        Stack <uint8_t, 30> *stack;

    public:

        uint8_t getStance()                         { return this->stance; }
        uint8_t getHealth()                         { return this->health; }
        uint8_t getRegain()                         { return this->regain; }
        uint8_t getRegainLimit()                    { return this->regainLimit; }
        uint8_t getActivity()                       { return this->activity; }
        int16_t getXPos()                           { return this->xPos; }
        int16_t getXPosDelta()                      { return this->xPosDelta; }
        int16_t getXPosOverall()                    { return this->xPosOverall; }
        int16_t getYPos()                           { return this->yPos; }
        int16_t getYPosDelta()                      { return this->yPosDelta; }
        int16_t getXPosDisplay()                    { return (this->xPos / 2); }
        uint8_t getMode()                           { return this->mode; }
        uint8_t getFrame()                          { return this->frame; }
        uint8_t getIdleFrame()                      { return this->idleFrame >= IDLE_MIN ? (this->idleFrame - IDLE_MIN) / IDLE_INC : 0; }
        uint8_t getImmediateAction()                { return this->immediateAction; }
        uint8_t getRetreatAction()                  { return this->retreatAction; }
        uint8_t getActionPreference()               { return this->actionPreference; }
        uint8_t getMovementFrequency()              { return this->movementFrequency; }
        uint8_t getActionsBeforeReturn()            { return this->actionsBeforeReturn; }

        EntityType getEntityType()                  { return this->entityType; }
        Movement getMovement()                      { return this->movement; }
        Stack <uint8_t, 30> * getStack()            { return this->stack; }

        bool getRightPunch()                        { return this->rightPunch; }
        bool getRightFoot()                         { return this->rightFoot; }
        bool isDead()                               { return this->dead; }

        void setStance(uint8_t stance)              { this->stance = stance; }
        void setHealth(uint8_t health)              { this->health = health; }
        void setRegain(uint8_t regain)              { this->regain = regain; }
        void setRegainLimit(uint8_t regainLimit)    { this->regainLimit = regainLimit; }
        void setActivity(uint8_t val)               { this->activity = val; }
        void setXPos(int16_t val)                   { this->xPos = val; }
        void setXPosDelta(int16_t val)              { this->xPosDelta = val; }
        void setXPosOverall(int16_t val)            { this->xPosOverall = val; }
        void setYPos(int16_t val)                   { this->yPos = val; }
        void setYPosDelta(int16_t val)              { this->yPosDelta = val; }
        void setEntityType(EntityType val)          { this->entityType = val; this->setYPos(79); }
        void setMovement(Movement val)              { this->movement = val; }
        void setMode(uint8_t val)                   { this->mode = val; }
        void setFrame(uint8_t val)                  { this->frame = val; }
        void setIdleFrame(uint8_t val)              { this->idleFrame = val; }
        void setImmediateAction(uint8_t val)        { this->immediateAction = val; }
        void setRetreatAction(uint8_t val)          { this->retreatAction = val; }
        void setActionPreference(uint8_t val)       { this->actionPreference = val; }
        void setMovementFrequency(uint8_t val)      { this->movementFrequency = val; }
        void setActionsBeforeReturn(uint8_t val)    { this->actionsBeforeReturn = val; }

        void setRightPunch(bool val)                { this->rightPunch = val; }
        void setRightFoot(bool val)                 { this->rightFoot = val; }
        void setDead(bool val)                      { this->dead = val; }
        void setStack(Stack <uint8_t, 30> *val)     { this->stack = val; }

        bool decActionsBeforeReturn(uint8_t val) {

            if (this->actionsBeforeReturn == 0) return false;

            if (this->actionsBeforeReturn <= val) {

                this->actionsBeforeReturn = 0;
                return true;

            }
            else {

                this->actionsBeforeReturn = this->actionsBeforeReturn - val;
                return false;
                
            }

        }
        
        uint8_t getEagleAttack() {

            if (this->eagleAttackLength > 0) {

                this->eagleAttackLength--;
                return this->eagleAttack;

            }

            return EAGLE_LEVEL_NONE;

        }
        
        void setEagleAttack(uint8_t val) { 
            this->eagleAttack = val; 
            this->eagleAttackLength = 12; 
        }

        uint8_t getActivityForRepeatAction() {

            return (this->activity > 70 ? (this->activity - 70) / 4 : 0);

        }

        void reset(uint16_t xPos) {

            this->setStance(STANCE_DEFAULT);
            this->setXPos(xPos);
            this->setXPosDelta(0);
            this->setXPosOverall(0);
            this->setYPos(76);
            this->setYPosDelta(0);
            this->setHealth(HEALTH_STARTING_POINTS);
            this->setRegain(0);
            this->setRegainLimit(HEALTH_STARTING_POINTS);
            // this->setActivity(0);
            this->setFrame(0);
            this->setMovement(Movement::None);
            this->setMode(EAGLE_MODE_FLY_INIT);
            this->setRightPunch(true);
            this->setRightFoot(true);
            this->setDead(false);
            this->stack->clear();

        }

        void incRegain() {

            this->regain++;

            if (this->regain >= HEALTH_REGAIN_LIMIT) {

                this->setHealth(this->getHealth() + HEALTH_REGAIN_POINTS < this->getRegainLimit() ? this->getHealth() + HEALTH_REGAIN_POINTS : this->getRegainLimit());
                this->setRegain(0);

            }

        }

        void incMode() {

            this->mode++;

        }

        void incFrame(uint8_t frameMax) {

            this->frame++;

            if (this->frame >= frameMax) this->frame = 0;

        }

        void incIdleFrame() {

            this->idleFrame++;

            if (this->idleFrame >= IDLE_MIN + (3 * IDLE_INC)) this->idleFrame = IDLE_MIN;

        }

        int8_t getDistToMove() {

            switch (this->movement) {

                case Movement::None:                    return 0;
                case Movement::Sidle_Backward:          return -50;
                case Movement::Sidle_Forward_Tiny:      return this->stack->getCount();
                case Movement::Sidle_Forward_SML:       return this->stack->getCount() * 2;
                case Movement::Sidle_Forward_MED:       return this->stack->getCount() * 5;
                case Movement::Sidle_Forward_LRG:       return this->stack->getCount() * 8;
                default:                                return 0;

            }

        }

        bool isNormalEnemy() {

            return this->getEntityType() == EntityType::EnemyOne || this->getEntityType() == EntityType::EnemyTwo || this->getEntityType() == EntityType::EnemyThree || this->getEntityType() == EntityType::Emperor;
            
        }

        bool isNormalEnemyOrDoor() {

            return this->getEntityType() == EntityType::EnemyOne || this->getEntityType() == EntityType::EnemyTwo || this->getEntityType() == EntityType::EnemyThree || this->getEntityType() == EntityType::Emperor || this->getEntityType() == EntityType::Door;
            
        }


      	uint8_t getCount(void) {
            return this->stack->getCount();
        }


        uint8_t & peek(void) {
            return this->stack->peek();
        }

        const uint8_t & peek(void) const {
            return this->stack->peek();
        }

        bool insert(const uint8_t & item) {
            this->idleFrame = 0;
            return this->stack->insert(item);
        }

        bool push(uint8_t item, bool resetFrame) {
            this->idleFrame = 0;
            return this->stack->push(static_cast<uint8_t>(item), resetFrame);
        }

        bool push(uint8_t item1, uint8_t item2, bool resetFrame) {
            this->idleFrame = 0;
            return this->stack->push(static_cast<uint8_t>(item1), static_cast<uint8_t>(item2), resetFrame);
        }

        bool push(uint8_t item1, uint8_t item2, uint8_t item3, bool resetFrame) {
            this->idleFrame = 0;
            return this->stack->push(static_cast<uint8_t>(item1), static_cast<uint8_t>(item2), static_cast<uint8_t>(item3), resetFrame);
        }

        uint8_t & pop(void) {
            return this->stack->pop();
        }

        bool isEmpty(void) {
            return this->stack->isEmpty();
        }

    	bool isFull(void) {
            return this->stack->isFull();
        }

    	void clear(void) {
            this->stack->clear();
        }

    	bool contains(const uint8_t & item) {
            return this->stack->contains(item);
        }

    	void update() {
            this->stack->update();
        }

    	uint8_t getStackFrame() {
            return this->stack->getFrame();
        }

};

struct GameStateDetails {

    public:

        uint8_t getCurrState() {
            return currState;
        }

        void setCurrState(uint8_t value) {
            prevState = currState;
            currState = value;
        }

        void reset() {

            archGatePos = 22;
            archGateDirection = Direction::Down;

        }

        bool hasDelay;
        uint8_t delayInterval;
        uint8_t arch;
        uint8_t archGatePos = 22;
        Direction archGateDirection = Direction::Down;
        bool showCrevice;
        int16_t archXPos;
        uint8_t prevState;
        uint16_t sequence;    
        Background background;
        uint8_t minXTravel;

    private:
        uint8_t currState = GAME_STATE_SPLASH_SCREEN_INIT;

};

template< size_t size >
void extractDigits(uint8_t (&buffer)[size], uint16_t value) {

    for(uint8_t i = 0; i < size; ++i) {
        buffer[i] = value % 10;
        value /= 10;
    }

}