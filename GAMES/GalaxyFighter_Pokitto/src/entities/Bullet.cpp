#include "Bullet.h"

#include "../utils/Constants.h"
#include "../utils/Structs.h"
#include "../utils/Enums.h"

Bullet::Bullet() {} 
    
uint8_t Bullet::getX() {

    return this->x;

}

uint8_t Bullet::getY() {

    return this->y;

}

bool Bullet::isEnabled() {

    return this->enabled;

}

void Bullet::setX(uint8_t x) {

    this->x = x;

}

void Bullet::setY(uint8_t y) {

    this->y = y;

}

void Bullet::setEnabled(bool enabled) {

    this->enabled = enabled;

}