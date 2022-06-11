#include "Player.h"

Player::Player() {

   for (uint8_t index = 0; index < MAX_INVENTORY_ITEMS; index++) {

        auto & inventoryHolding = this->playerStatus.inventoryItems[index];
        inventoryHolding.index = index;

   }

}

void Player::reset() { 

    this->x = 0;
    this->y = 0;
    this->playerStatus.direction = Direction::Up;;
    this->playerStatus.health = 0;
    this->playerStatus.coins = 0;
    this->playerStatus.coinsOverall = 0;
    this->playerStatus.kills = 0;
    this->playerStatus.cultists = 0;
    this->playerStatus.moving = false;
    this->playerStatus.frame = 0;
    this->playerStatus.weapon = Object::FireBall;
    this->playerStatus.weaponCount = 0;
    this->playerStatus.puffIndex = 0;
    this->playerStatus.altarPieces = 0;

    for (uint8_t x = 0; x < MAX_INVENTORY_ITEMS; x++) {
        this->playerStatus.inventoryItems[x].type = Object::None;
        this->playerStatus.inventoryItems[x].quantity = 0;
    }

}

void Player::initLevel(uint16_t x, uint16_t y) {

    this->x = x;
    this->y = y;
    this->playerStatus.direction = Direction::Down;
    this->playerStatus.coins = 0;
    this->playerStatus.kills = 0;
    this->playerStatus.cultists = 0;
    this->playerStatus.health = (this->playerStatus.health <= 0 ? 100 : this->playerStatus.health);
    this->playerStatus.moving = false;
    
}

void Player::incAltarPieces() {
    if (this->playerStatus.altarPieces < 7) this->playerStatus.altarPieces++;
}

uint16_t Player::getX() { 
    return this->x; 
}

uint16_t Player::getY() { 
    return this->y; 
}

PROGMEM const uint8_t Player::getWidth() { 
    return 10; 
}

PROGMEM const uint8_t Player::getHeight() { 
    return 12; 
}

Direction Player::getDirection() { 
    return this->playerStatus.direction; 
}

int8_t Player::getHealth() { 
    return this->playerStatus.health; 
}

uint8_t Player::getCoins() { 
    return this->playerStatus.coins; 
}

uint8_t Player::getCoinsOverall() { 
    return this->playerStatus.coinsOverall; 
}

uint8_t Player::getKills() { 
    return this->playerStatus.kills; 
}

uint8_t Player::getCultists() { 
    return this->playerStatus.cultists; 
}

uint8_t Player::getAltarPieces() { 
    return this->playerStatus.altarPieces; 
}

uint8_t Player::getFrame() { 
    return this->playerStatus.frame; 
}

bool Player::getMoving() { 
    return this->playerStatus.moving; 
}

Object Player::getWeapon() { 
    return this->playerStatus.weapon; 
}

Rect Player::getRect() {
    return Rect { this->getX() - (this->getWidth() / 2), this->getY() - (this->getHeight() / 2), this->getWidth(), this->getHeight() };
}

int8_t Player::getPuffIndex() { 
    return this->playerStatus.puffIndex; 
}

PlayerStatus Player::getPlayerStatus() { 
    return this->playerStatus; 
}

void Player::setX(uint16_t x) { 
    this->x = x; 
}

void Player::setY(uint16_t y) { 
    this->y = y; 
}

void Player::setDirection(Direction direction) { 
    this->playerStatus.direction = direction; 
}

void Player::setHealth(int8_t health) { 
    this->playerStatus.health = health; 
    if (this->playerStatus.health > 100) this->playerStatus.health = 100; 
}

void Player::incHealth(uint8_t amount) { 
    this->playerStatus.health = this->playerStatus.health + amount; 
    if (this->playerStatus.health > 100) this->playerStatus.health = 100; 
}

void Player::decHealth(uint8_t amount) { 
    this->playerStatus.health = this->playerStatus.health - amount; 
    if (this->playerStatus.health <= 0) this->playerStatus.puffIndex = 10;
}

void Player::setCoins(uint8_t coins) { 
    this->playerStatus.coins = coins; 
}

void Player::setCoinsOverall(uint8_t coins) { 
    this->playerStatus.coinsOverall = coins; 
}

void Player::setKills(uint8_t kills) { 
    this->playerStatus.kills = kills; 
}

void Player::setCultists(uint8_t cultists) { 
    this->playerStatus.cultists = cultists; 
}

void Player::setFrame(uint8_t frame) { 
    this->playerStatus.frame = frame;
}

void Player::incCoins(uint8_t coins) { 
    this->playerStatus.coins = this->playerStatus.coins + coins; 
    this->playerStatus.coinsOverall = this->playerStatus.coinsOverall + coins; 
    if (this->playerStatus.coinsOverall > 99) this->playerStatus.coins = 99;
}

void Player::setMoving(bool moving) { 
    this->playerStatus.moving = moving; 
}

void Player::setPlayerStatus(PlayerStatus playerStatus) { 
    this->playerStatus = playerStatus; 
}

void Player::setWeapon(Object weapon) { 
    
    this->playerStatus.weapon = weapon; 

    switch (weapon) {

        case Object::IceSpell:
            this->playerStatus.weaponCount = ICE_SPELL_DELAY - 1;
            break;

        default: 
            break;

    }

}

void Player::decWeaponCount() {

    if (this->playerStatus.weaponCount > 0) {

        this->playerStatus.weaponCount--;

        if (this->playerStatus.weaponCount == 0) {

            this->playerStatus.weapon = Object::FireBall;

        }

    }

}

void Player::decPuffIndex() {

    if (this->playerStatus.puffIndex > PLAYER_DEAD_DELAY) this->playerStatus.puffIndex--;

}

uint8_t Player::getWeaponFrame() {

    return this->playerStatus.weaponCount / ICE_SPELL_DELAY_INC;
    
}

uint32_t Player::getWeaponCount() {

    return this->playerStatus.weaponCount;
    
}

void Player::incFrame() {
    
    this->playerStatus.frame++;
    this->playerStatus.frame %= 2;

}


InventoryItem & Player::getInventoryItem(uint8_t index) {

    auto & inventoryHolding = this->playerStatus.inventoryItems[index];
    return this->playerStatus.inventoryItems[index];

}

InventoryItem & Player::getActiveInventoryItem(uint8_t index) {

    uint8_t count = 0;

    for (uint8_t i = 0; i < MAX_INVENTORY_ITEMS; i++) {

        auto & inventoryHolding = this->playerStatus.inventoryItems[i];

        if (inventoryHolding.quantity > 0) {

            if (count == index) {

                return this->playerStatus.inventoryItems[i];

            } 

            count++;

        }

    }

    return this->playerStatus.inventoryItems[0]; // Default.

}


uint8_t Player::addInventoryItem(Object type, uint8_t qty) {

    uint8_t slot = NO_SLOT_FOUND;


    // Are we carrying the maximum items?

    if (getInventoryCount() == MAX_INVENTORY_COUNT) {

        return NO_SLOT_FOUND;

    }



    // Otherwise, do we have an existing slot with this item in it?

    slot = getInventorySlot(type);

    if (slot != NO_SLOT_FOUND) {

        InventoryItem & inventoryHolding = this->playerStatus.inventoryItems[slot];
        inventoryHolding.quantity = inventoryHolding.quantity + qty;
        return slot;

    }


    // Otherwise, is there and empty slot?

    slot = getEmptySlot();

    if (slot != NO_SLOT_FOUND) {

        InventoryItem & inventoryHolding = this->playerStatus.inventoryItems[slot];
        inventoryHolding.type = type;
        inventoryHolding.quantity = qty;
        return slot;

    }

    return NO_SLOT_FOUND;

}


uint8_t Player::decInventoryItem(Object type) {

    uint8_t slot = getInventorySlot(type);


    // Do we have an existing slot with this item in it?

    if (slot != NO_SLOT_FOUND) {

        InventoryItem & inventoryHolding = this->playerStatus.inventoryItems[slot];
        inventoryHolding.quantity--;
        return slot;

    }

    return NO_SLOT_FOUND;

}

// Get the slot number of the inventory item provided, return NO_SLOT_FOUND if not found ..

uint8_t Player::getInventorySlot(Object type) {

    bool found = false;
    uint8_t index = 0;

    for (index = 0; index < MAX_INVENTORY_ITEMS; index++) {

        auto & inventoryHolding = this->playerStatus.inventoryItems[index];

        if (inventoryHolding.type == type) {

            found = true;
            break;

        }

    }

    return (found ? index : NO_SLOT_FOUND);

}

// Get an empty inventory slot, return NO_SLOT_FOUND if none available ..

uint8_t Player::getEmptySlot() {

    bool found = false;
    uint8_t index = 0;

    for (index = 0; index < MAX_INVENTORY_ITEMS; index++) {

        auto & inventoryHolding = this->playerStatus.inventoryItems[index];

        if (inventoryHolding.quantity == 0) {

            found = true;
            break;

        }

    }

    return (found ? index : NO_SLOT_FOUND);

}


// Get a count of inventory items currently being held ..

uint8_t Player::getInventoryCount() {

    uint8_t count = 0;

    for (uint8_t index = 0; index < MAX_INVENTORY_ITEMS; index++) {

        auto & inventoryHolding = this->playerStatus.inventoryItems[index];

        if (inventoryHolding.quantity > 0) {

            switch (inventoryHolding.type) {

                case Object::IceSpell:
                case Object::GreenSpell:
                case Object::RedSpell:
                case Object::MauveSpell:
                    count = count + 1;
                    break;

                default:
                    count = count + inventoryHolding.quantity;
                    break;

            }

        }

    }

    return count;

}

uint8_t Player::getInventoryCount(Object type) {

    uint8_t count = 0;

    for (uint8_t index = 0; index < MAX_INVENTORY_ITEMS; index++) {

        auto & inventoryHolding = this->playerStatus.inventoryItems[index];

        if (inventoryHolding.type == type && inventoryHolding.quantity > 0) {

            count = count + inventoryHolding.quantity;

        }

    }

    return count;

}


// Get a count of active inventory slots ..

uint8_t Player::getActiveSlotCount() {

    uint8_t count = 0;

    for (uint8_t index = 0; index < MAX_INVENTORY_ITEMS; index++) {

        auto & inventoryHolding = this->playerStatus.inventoryItems[index];

        if (inventoryHolding.quantity > 0) {

            count++;

        }

    }

    return count;

}