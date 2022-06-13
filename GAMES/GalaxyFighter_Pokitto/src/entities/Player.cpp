#include "Player.h"

#include "../utils/Constants.h"

#define PLAYER_MAX_INERTIA 2
#define PLAYER_MAX_INERTIA_HALF (PLAYER_MAX_INERTIA / 2)

using PD = Pokitto::Display;

Player::Player() { 
}

void Player::reset(bool startOfGame) {
    
    this->x = PLAYER_X_POS;
    this->y = PLAYER_Y_POS;
    this->xInertia = 0;
    this->health = PLAYER_MAX_HEALTH;
    this->enabled = true;
    this->justHit = 0;
    this->explosionCounter = 0;   
    this->twinPlayers = false;

    if (startOfGame) {
        this->lives = PLAYER_MAX_LIVES;
    }

}

uint8_t Player::getImage() {
        
    return 0;
    
}

bool Player::getImageFlip() {
    
    return false;

}

uint8_t Player::getX() {

    return this->x;

}

uint8_t Player::getY() {

    return this->y;

}

uint8_t Player::getHeight() {

    return this->height;

}

uint8_t Player::getWidth() {

    return this->width;

}

uint8_t Player::getHealth() {

    return this->health;

}

uint8_t Player::getLives() {

    return this->lives;

}

bool Player::isEnabled() {

    return this->enabled;

}

bool Player::isJustHit() {

    return this->justHit > 0;

}

Side Player::getJustHitSide() {

    return this->justHitSide;

}

void Player::setX(uint8_t x) {

    this->x = x;

}

void Player::setY(uint8_t y) {

    this->y = y;

}

void Player::setHealth(uint8_t health) {

    this->health = health;

}

void Player::setLives(uint8_t lives) {

    this->lives = lives;

}

void Player::setEnabled(bool enabled) {

    this->enabled = enabled;

}

void Player::setJustHitSide(Side justHitSide) {

    this->justHitSide = justHitSide;

}

void Player::decHealth(bool twinPlayers, uint8_t amount) {

    #ifdef DEBUG_NEVER_DIE
        return;
    #endif

    this->twinPlayers = twinPlayers;

    if (this->health > amount) {
        
        this->health = this->health - amount;
        this->justHit = 3;
        
    }
    else {

        this->health = 0;
                
    }
    
    if (this->health <= 0 && this->explosionCounter == 0) {
        
        this->explosionCounter = 1;
        
    }

}

void Player::decLives() {

    if (this->lives > 0) {
        
        this->lives--;
        
    }

}

void Player::incLives() {
        
    this->lives++;

}

void Player::decX() {

    switch (this->xInertia) {
        
        case -PLAYER_MAX_INERTIA_HALF ... -1:
            this->xInertia = this->xInertia * 2;
            break;
            
        case 0:
            this->xInertia = -1;
            break;

        case 1:
            this->xInertia = 0;
            break;

        case 2 ... PLAYER_MAX_INERTIA:
            this->xInertia = this->xInertia / 2;
            break;
        
    }

}

void Player::incX() {

    switch (this->xInertia) {
        
        case -PLAYER_MAX_INERTIA ... -2:
            this->xInertia = this->xInertia / 2;
            break;
            
        case -1:
            this->xInertia = 0;
            break;

        case 0:
            this->xInertia = 1;
            break;

        case 1 ... PLAYER_MAX_INERTIA_HALF:
            this->xInertia = this->xInertia * 2;
            break;
        
    }

}

void Player::decelerate() {

    switch (this->xInertia) {
        
        case -PLAYER_MAX_INERTIA ... -2:
            this->xInertia = this->xInertia / 2;
            break;
            
        case -1:
            this->xInertia = 0;
            break;
            
        case 1:
            this->xInertia = 0;
            break;
            
        case 2 ... PLAYER_MAX_INERTIA:
            this->xInertia = this->xInertia / 2;
            break;
            
    }

}


// Returns true if the player has died ..

bool Player::move() {
            
    if (this->justHit > 0) this->justHit--;
    
    if (this->explosionCounter > 0) {

        this->explosionCounter++;

        if (this->explosionCounter == 13) {
            
            if (!this->twinPlayers) {

                this->enabled = false;
            }
            
            this->explosionCounter = 0;

        }
        
        return true;        
        
    }

    if (this->xInertia < 0) {

        if (this->x > -this->xInertia) {

            this->x = this->x + this->xInertia;

        }
        else {
            
            this->x = 0;

        }

    }
    else {

        this->x = this->x + this->xInertia;

        if (this->x > SCREEN_WIDTH - this->width - (twinPlayers ? this->width : 0)) {
            
            this->x = SCREEN_WIDTH - this->width - (twinPlayers ? this->width : 0);

        }

    }

    return false;

}

bool Player::isExploding() {

    return (this->explosionCounter > 0);

}

uint8_t Player::getExplosionImageIndex() {

    return (this->explosionCounter - 1) / 3;

}

uint8_t Player::getExplosionImageOffset() {
    
    return 8;

}