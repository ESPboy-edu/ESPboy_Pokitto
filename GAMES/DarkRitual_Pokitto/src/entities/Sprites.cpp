#include "Sprites.h"
#include "../images/Images.h"

Sprite & Sprites::getSprite(uint8_t index) {

    return this->objects[index];
    
}


uint8_t Sprites::getFirstInactiveSpriteIndex(Object type) {

    for (uint8_t i = 0; i < this->oNum; i++) {

        auto &object = this->objects[i];

        if (object.getType() == type && object.getActive() != SpriteStatus::Active) {

            return i;

        }

    }

    return NO_SPRITE_FOUND;
        
}

uint8_t Sprites::getObjectNum() {

    return this->oNum;

}

void Sprites::setObjectNum(uint8_t oNum) {
 
    this->oNum = oNum;

}

void Sprites::renderHealthBar(uint32_t x, uint32_t y, uint8_t health) {

    PD::drawBitmap(x, y, Images::HealthBar);
    PD::setColor(8);
    PD::drawLine(x + 2, y + 1, x + 2 + health, y + 1);

}

void Sprites::render(Player &player, bool showEnemies) {

    for (uint8_t i = 0; i < this->oNum; i++) {

        auto &object = this->objects[i];

        if (object.getActive() != SpriteStatus::Inactive) {

            int x = CENTERX - (player.getX() - object.getX());
            int y = CENTERY - (player.getY() - object.getY());

            uint8_t puffIndex = object.getPuffIndex();
            uint8_t frame = object.getFrame();
            int8_t xOffset = object.getXOffset();
            int8_t yOffset = object.getYOffset();
            bool showGuideText = object.getGuideText();
            Direction direction = object.getDirection();

            int health = object.getHealthOrig() <= 0 || object.getHealth() <= 0 ? 0 : 10 * object.getHealth() / object.getHealthOrig();

            // switch (object.getType()) {

            //     case Object::Guide01 ... Object::Guide15:

                    if (puffIndex == 0 || puffIndex > 5) {

                        this->renderSprite(object.getType(), x, y, xOffset, yOffset, direction, frame, object.getCountdown(), showEnemies, showGuideText, object.getRenderHealthBar(), health);

                    }

                //     break;


                // default:
                //     this->renderSprite(object.getType(), x, y, xOffset, yOffset, direction, frame, object.getCountdown(), showEnemies, showGuideText, object.getRenderHealthBar(), health);
                //     break;

            //}



            // Render puff ?

            if (puffIndex > 0 && puffIndex <= 10) {

                PD::drawBitmap(x - 8, y - 8, Images::Puff[(10 - puffIndex) / 2]);

            }

        }

    }

}

void Sprites::renderSprite(Object type, int x, int y) {

    int8_t xOffset = spriteOffsets[static_cast<uint8_t>(type) * 2];
    int8_t yOffset = spriteOffsets[(static_cast<uint8_t>(type) * 2) + 1];

    this->renderSprite(type, x, y, xOffset, yOffset, Direction::Up, 0, 0, false, false, 0, false);

}


void Sprites::renderSprite(Object type, int x, int y, int8_t xOffset, int8_t yOffset, Direction direction, int8_t frame, uint8_t countdown, bool showEnemies, bool showGuideText, bool renderHealth, int healthValue) {

    switch (type) {

        case Object::Coin:
            PD::drawBitmap(x + xOffset, y + yOffset, Images::Coins[frame]);
            break;

        case Object::Bat:
            if (showEnemies) {
                PD::drawBitmap(x + xOffset, y + yOffset, Images::Bats[frame]);
                if (renderHealth) { this->renderHealthBar(x + 6, y - 6, healthValue); }
            }
            break;

        case Object::Spider:
            if (showEnemies) {
                if (frame < 0) {
                    uint8_t puffFrame = 4 - (frame / -4);
                    if (puffFrame >= 2) {
                        PD::drawBitmap(x + xOffset, y + yOffset, Images::Spiders[(static_cast<uint8_t>(direction) * 2)]);
                    }
                    PD::drawBitmap(x - 8, y - 8, Images::Puff[puffFrame]);
                }
                else {
                    PD::drawBitmap(x + xOffset, y + yOffset, Images::Spiders[(static_cast<uint8_t>(direction) * 2) + frame]);
                }
                if (renderHealth) { this->renderHealthBar(x + 6, y - 6, healthValue); }
            }
            break;

        case Object::BigSpider:
            if (showEnemies) {
                PD::drawBitmap(x + xOffset, y + yOffset, Images::BigSpiders[(static_cast<uint8_t>(direction) * 2) + frame]);
                if (renderHealth) { this->renderHealthBar(x + 6, y - 6, healthValue); }
            }
            break;

        case Object::Eye:
            if (showEnemies) {
                PD::drawBitmap(x + xOffset, y + yOffset, Images::Eyes[(static_cast<uint8_t>(direction) * 2) + frame]);
                if (renderHealth) { this->renderHealthBar(x + 6, y - 6, healthValue); }
            }
            break;

        case Object::Skeleton:
            if (frame < 0) {
                if (showEnemies) {
                    
                    PD::drawBitmap(x + xOffset, y + yOffset, Images::Skeletons[(frame / 8) + 5]);                              // Offset due to rising frames.
                    if (renderHealth) { this->renderHealthBar(x + 6, y - 6, healthValue); }
                }
            }
            else {
                if (showEnemies) {
                    PD::drawBitmap(x + xOffset, y + yOffset, Images::Skeletons[(static_cast<uint8_t>(direction) * 2) + frame + 5]);
                    if (renderHealth) { this->renderHealthBar(x + 6, y - 6, healthValue); }
                }
            }
            break;

        case Object::Snake:
            if (showEnemies) {
                PD::drawBitmap(x + xOffset, y + yOffset, Images::Snakes[(static_cast<uint8_t>(direction) * 2) + frame]);
                if (renderHealth) { this->renderHealthBar(x + 6, y - 6, healthValue); }
            }
            break;

        case Object::Chest:
            if (showEnemies) {
                PD::drawBitmap(x + xOffset, y + yOffset, Images::Chests[(static_cast<uint8_t>(direction) * 2) + frame]);
                if (renderHealth) { this->renderHealthBar(x + 6, y - 6, healthValue); }
            }
            break;

        case Object::Necromancer:
            if (frame < 0) { // Summoning skeleton
                if (showEnemies) {
                    PD::drawBitmap(x + xOffset, y + yOffset, Images::Necromancer[((frame / 5)  % 3) + 2]); // 3 offset due to summons frames.
                    if (frame >= -2) {
                        PD::drawBitmap(x - 8, y - 8, Images::Necromancer_Spell[frame + 2]); // 3 offset due to rising frames.
                    }
                    
                    if (renderHealth) { this->renderHealthBar(x + 6, y - 6, healthValue); }
                }

            }
            else {
                if (showEnemies) {
                    PD::drawBitmap(x + xOffset, y + yOffset, Images::Necromancer[(static_cast<uint8_t>(direction) * 2) + frame + 3]); // 3 offset due to summons frames.
                    if (renderHealth) { this->renderHealthBar(x + 6, y - 6, healthValue); }
                }
            }
            break;

        case Object::Hobgoblin:
            if (showEnemies) {
                PD::drawBitmap(x + xOffset, y + yOffset, Images::Hobgoblin[(static_cast<uint8_t>(direction) * 2) + frame]); 
                if (renderHealth) { this->renderHealthBar(x + 6, y - 6, healthValue); }
            }
            break;

        case Object::Beholder:
            if (showEnemies) {
                PD::drawBitmap(x + xOffset, y + yOffset, Images::Beholder[(static_cast<uint8_t>(direction) * 2) + frame]);  
                if (renderHealth) { this->renderHealthBar(x + 6, y - 6, healthValue); }
            }
            break;

        case Object::Cyclop:

            if (frame < 0) {

                if (showEnemies) {

                    uint8_t frameToRender = (CYCLOPS_FRAME_MAX + frame) / (CYCLOPS_FRAME_MAX / 10);
                    PD::drawBitmap(x + xOffset, y + yOffset, Images::Cyclop[16 + (static_cast<uint8_t>(direction) * 10) + frameToRender]);

                    if (renderHealth) { this->renderHealthBar(x + 6, y - 6, healthValue); }

                }
    
            }
            else {

                if (showEnemies) {
                    PD::drawBitmap(x + xOffset, y + yOffset, Images::Cyclop[(static_cast<uint8_t>(direction) * 2) + frame]); 
                    if (renderHealth) { this->renderHealthBar(x + 6, y - 6, healthValue); }
                }

            }
            break;

        case Object::SackOCash:
            PD::drawBitmap(x + xOffset, y + yOffset, Images::SackOCash);
            break;

        case Object::Bread:
            PD::drawBitmap(x + xOffset, y + yOffset, Images::Bread);
            break;

        case Object::Key:
            PD::drawBitmap(x + xOffset, y + yOffset, Images::Keys[frame]);
            break;

        case Object::Chicken:
            PD::drawBitmap(x + xOffset, y + yOffset, Images::Chicken);
            break;

        case Object::Tools:
            PD::drawBitmap(x + xOffset, y + yOffset, Images::Tools);
            break;

        case Object::Tonic:
            PD::drawBitmap(x + xOffset, y + yOffset, Images::Tonic);
            break;

        case Object::IceSpell:
            PD::drawBitmap(x + xOffset, y + yOffset, Images::IceSpell);
            break;

        case Object::GreenSpell:
            PD::drawBitmap(x + xOffset, y + yOffset, Images::GreenSpell);
            break;

        case Object::RedSpell:
            PD::drawBitmap(x + xOffset, y + yOffset, Images::RedSpell);
            break;

        case Object::MauveSpell:
            PD::drawBitmap(x + xOffset, y + yOffset, Images::MauveSpell);
            break;

        case Object::SpikeLHS:
            PD::drawBitmap(x + xOffset, y + yOffset, Images::SpikeLHS[spike_frameIdx[frame]]);
            break;

        case Object::SpikeRHS:
            PD::drawBitmapXFlipped(x + xOffset, y + yOffset, Images::SpikeLHS[spike_frameIdx[frame]]);
            break;

        case Object::FireTOP:
            PD::drawBitmap(x + xOffset, y + yOffset, Images::Fires[fire_frameIdx[frame]]);
            break;

        case Object::FireBOT:
            PD::drawBitmapYFlipped(x + xOffset, y + yOffset, Images::Fires[fire_frameIdx[frame]]);
            break;

        case Object::Guide01 ... Object::Guide07:
            
            PD::drawBitmap(x + xOffset, y + yOffset, Images::Guide);
            break;

        case Object::Guide08 ... Object::Guide15:
            
            PD::drawBitmap(x + xOffset, y + yOffset, Images::Guide);

            if (showGuideText) {

                switch (frame) {
    
                    case 0 ... 16:
                        PD::drawBitmap(x - 18, y + yOffset - 11, Images::GuideCaption[(frame / 2) % 4]);
                        break;
    
                    case 48 ... 64:
                        PD::drawBitmap(x - 18, y + yOffset - 11, Images::GuideCaption[(((frame - 48) / 2) % 4) + 4]);
                        break;
    
                }
                
            }
            break;

    }

}


void Sprites::clearPreventImmediatePickup(Player &player) {

    uint8_t playerX = player.getX() / TILE_WIDTH;
    uint8_t playerY = player.getY() / TILE_HEIGHT;

    for (uint8_t i = 0; i < this->oNum; i++) {

        auto &object = this->objects[i];

        uint8_t objectX = object.getX() / TILE_WIDTH;
        uint8_t objectY = object.getY() / TILE_HEIGHT;    

        if (object.getPreventImmediatePickup() && (playerX != objectX || playerY != objectY)) {

            object.setPreventImmediatePickup(false);

        }

    }

}