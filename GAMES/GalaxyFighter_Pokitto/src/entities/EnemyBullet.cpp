#include "EnemyBullet.h"

#include "../utils/Constants.h"
#include "../utils/Structs.h"
#include "../utils/Enums.h"

EnemyBullet::EnemyBullet() {} 
    
float EnemyBullet::getX() {

    return this->x;

}

float EnemyBullet::getXDelta() {

    return this->xDelta;

}

uint8_t EnemyBullet::getY() {

    return this->y;

}

BulletType EnemyBullet::getBulletType() {

    return this->bulletType;

}

bool EnemyBullet::isEnabled() {

    return this->enabled;

}

void EnemyBullet::setX(float x) {

    this->x = x;

}

void EnemyBullet::setXDelta(float xDelta) {

    this->xDelta = xDelta;

}

void EnemyBullet::setY(uint8_t y) {

    this->y = y;

}

void EnemyBullet::setEnabled(bool enabled) {

    this->enabled = enabled;

}

void EnemyBullet::setBulletType(BulletType bulletType) {

    this->bulletType = bulletType;

}
