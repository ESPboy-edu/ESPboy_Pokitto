#include "Pokitto.h"
#include "Game.h"
#include "utils/Enums.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;



void Game::showInventory() {


    // If the cursor > active inventory slots then decrease it (Allow 1 for Rune Bag)..

    if (this->inventoryMenu.mainCursor > player.getActiveSlotCount() + 1) {

        this->inventoryMenu.mainCursor = player.getActiveSlotCount() + 1;

    }


    // Handle player actions ..

    switch (this->inventoryMenu.mode) {

        case InventoryMenuMode::Inventory:
                
            if (!inventoryMenu.showActionMenu) {

                if (PC::buttons.pressed(BTN_B)) {

                    gameState = GameState::Game;

                }

                if (PC::buttons.pressed(BTN_C)) {
            
                    gameState = GameState::Game;

                }

                if (PC::buttons.pressed(BTN_UP) && this->inventoryMenu.mainCursor > 0) {

                    this->inventoryMenu.mainCursor--;

                }

                if (PC::buttons.pressed(BTN_DOWN) && this->inventoryMenu.mainCursor < player.getActiveSlotCount() + 1) {

                    this->inventoryMenu.mainCursor++;

                }

                if (PC::buttons.pressed(BTN_A)) {

                    if (this->inventoryMenu.mainCursor == 0) {
                        this->inventoryMenu.mode = InventoryMenuMode::AltarPieces;
                    }
                    else if (this->inventoryMenu.mainCursor < player.getActiveSlotCount() + 1) {
                        this->inventoryMenu.showActionMenu = true;
                        this->inventoryMenu.actionCursor = 0;
                    }
                    else {

                        gameState = GameState::Game;

                    }

                }

            }
            else {

                if (PC::buttons.pressed(BTN_B) || PC::buttons.pressed(BTN_C)) {

                    this->inventoryMenu.showActionMenu = false;

                }

                if (PC::buttons.pressed(BTN_UP) && this->inventoryMenu.actionCursor > 0) {

                    this->inventoryMenu.actionCursor--;

                }

                if (PC::buttons.pressed(BTN_DOWN) && this->inventoryMenu.actionCursor < 3) {

                    this->inventoryMenu.actionCursor++;

                }

                if (PC::buttons.pressed(BTN_A)) {

                    switch (this->inventoryMenu.actionCursor) {
                    
                        case 0:
                            {
                                bool itemUsed = false;
                                InventoryItem & inventoryItem = this->player.getActiveInventoryItem(this->inventoryMenu.mainCursor - 1);


                                // If the user selected 'put away' ..

                                if (inventoryItem.type == this->player.getWeapon()) {

                                    this->player.setWeapon(Object::FireBall);
                                    this->inventoryMenu.showActionMenu = false;

                                }
                                else {
                        
                                    if (inventoryItem.quantity > 0) {
                        
                                        switch (inventoryItem.type) {
                        
                                            case Object::IceSpell:

                                                this->player.setWeapon(Object::IceSpell);
                                                itemUsed = true;
                                                inventoryItem.quantity--;  
                                                break;
                        
                                            case Object::GreenSpell:
                                            case Object::RedSpell:
                                            case Object::MauveSpell:

                                                this->player.setWeapon(inventoryItem.type);
                                                itemUsed = true;
                                                break;
                        
                                            case Object::Key:
                                            case Object::Tools:
                                                {
                                                    // Try the surrounding blocks to see if it can be used ..

                                                    uint8_t x = this->map.getTileX(this->player.getX());
                                                    uint8_t y = this->map.getTileY(this->player.getY());
                                                    MapTiles block = this->map.getBlock(x, y);

                                                    itemUsed = this->interactWithBlock(x, y, block);

                                                    static PROGMEM const int8_t xOffset[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
                                                    static PROGMEM const int8_t yOffset[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

                                                    if (!itemUsed) {

                                                        for (uint8_t i = 0; i < 8; i++) {

                                                            block = this->map.getBlock(x + xOffset[i], y + yOffset[i]);
                                                            itemUsed = this->interactWithBlock(x + xOffset[i], y + yOffset[i], block);

                                                            if (itemUsed) break;

                                                        }

                                                    }

                                                }
                                                break;
                        
                                            case Object::Tonic:
                                                if (player.getHealth() < 100) {
                                                    player.incHealth(HEALTH_INC_TONIC); 
                                                    inventoryItem.quantity--;  
                                                    itemUsed = true;
                                                    //sound health going up
                                                }
                                                else {
                                                    playSoundEffect(SoundEffect::CannotPickUp);
                                                }
                                                break;
                        
                                            case Object::Bread:
                                                if (player.getHealth() < 100) {
                                                    player.incHealth(HEALTH_INC_BREAD); 
                                                    inventoryItem.quantity--;  
                                                    itemUsed = true;
                                                    //sound health going up
                                                }
                                                else {
                                                    playSoundEffect(SoundEffect::CannotPickUp);
                                                }
                                                break;
                        
                                            case Object::Chicken:
                                                if (player.getHealth() < 100) {
                                                    player.incHealth(HEALTH_INC_CHICKEN); 
                                                    inventoryItem.quantity--;  
                                                    itemUsed = true;
                                                    //sound health going up
                                                }
                                                else {
                                                    playSoundEffect(SoundEffect::CannotPickUp);
                                                }
                                                break;
                        
                                        }
                        
                                        // Did we just use the last item ?  If so move cursor up.

                                        if (itemUsed) {           
                                            
                                            if (inventoryItem.quantity == 0 && this->inventoryMenu.mainCursor > 0) this->inventoryMenu.mainCursor--;
                                            this->inventoryMenu.showActionMenu = false;
                                            gameState = GameState::Game;
                                            
                                        }
                        
                                    }

                                }
                                
                            }
                            
                            break;
                        
                        case 1: // Drop
                            {
                                // Find a matching Object in the sprites collecion that is disabled, otherwise add one ..

                                InventoryItem & inventoryItem = this->player.getActiveInventoryItem(this->inventoryMenu.mainCursor - 1);
                                uint8_t spriteIdx = this->objects.getFirstInactiveSpriteIndex(inventoryItem.type);

                                if (spriteIdx == NO_SPRITE_FOUND) {

                                    this->objects.setObjectNum(this->objects.getObjectNum() + 1);
                                    spriteIdx = this->objects.getObjectNum() - 1;

                                }   




                                Sprite &sprite = this->objects.getSprite(spriteIdx);


                                // See if we can drop the item in a clear spot behind the player ..

                                static PROGMEM const int8_t launchXOffset[] = { 0, -16, -16, -16, 0, 16, 16, 16 };
                                static PROGMEM const int8_t launchYOffset[] = { 16, 16, 0, -16, -16, -16, 0, 16 };
                                static PROGMEM const int8_t directions[] = { 8, 9, 7, 10, 6, 11, 5, 4 };

                                int launchX = 0;
                                int launchY = 0;
                                bool found = false;

                                for (uint8_t d = 0; d < 7; d++) {

                                    launchX = this->player.getX() + launchXOffset[(static_cast<uint8_t>(this->player.getDirection()) + directions[d]) % 8];
                                    launchY = this->player.getY() + launchYOffset[(static_cast<uint8_t>(this->player.getDirection()) + directions[d]) % 8];

                                    uint8_t tileLaunchX = this->map.getTileX(launchX);
                                    uint8_t tileLaunchY = this->map.getTileX(launchY);

                                    // uint8_t width = spriteWidths[sprite.getType()];
                                    // uint8_t height = spriteHeights[sprite.getType()];
                                    
                                    launchX = (tileLaunchX * TILE_WIDTH) + spriteWidths[sprite.getType()];
                                    launchY = (tileLaunchY * TILE_HEIGHT) + spriteHeights[sprite.getType()];
                                        
                                    sprite.setX(launchX);
                                    sprite.setY(launchY);
                                    sprite.setWidth(spriteWidths[sprite.getType()]);
                                    sprite.setHeight(spriteHeights[sprite.getType()]);
                                    sprite.setType(inventoryItem.type);

                                    if (map.getBlock(tileLaunchX, tileLaunchY) == MapTiles::Empty && !collision(this->player, sprite)) {

                                        found = true;
                                        break;

                                    }

                                }


                                // If we could not find a proper location to drop it, then drop it on the player itself!

                                if (!found) {

                                    launchX = this->player.getX();
                                    launchY = this->player.getY();

                                }

                                sprite.setSprite(launchX, launchY, 0, inventoryItem.type, SpriteStatus::Active, false);
                                sprite.setPreventImmediatePickup(true);
                                sprite.setQuantity(inventoryItem.quantity);

                                switch (inventoryItem.type) {

                                    case Object::GreenSpell:
                                    case Object::RedSpell:
                                        inventoryItem.quantity = 0;
                                        this->player.setWeapon(Object::FireBall);
                                        break;

                                    default:
                                        inventoryItem.quantity--;
                                        break;

                                }


                                // Did we just use the last item ?  If so move cursor up.
                             
                                if (inventoryItem.quantity == 0 && this->inventoryMenu.mainCursor > 0) this->inventoryMenu.mainCursor--;
                                this->inventoryMenu.showActionMenu = false;

                            }
        
                            break;
                        
                        case 2:
                            this->inventoryMenu.showActionMenu = false;
                            break;
                        
                    }
                    

                }

            }

            break;

        case InventoryMenuMode::AltarPieces:

            if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B) || PC::buttons.pressed(BTN_C)) {
        
                this->gameState = GameState::Game;
                
            }

            break;

    }
    

    // Render screen ..

    switch (this->inventoryMenu.mode) {

        case InventoryMenuMode::Inventory:
            {    
                this->renderEnvironment(!this->map.isBossLevel() && !this->map.isAltarLevel(), 0, 0);
                this->renderHud();
                PD::setColor(0);
                PD::fillRectangle(0, 0, 91, 81);
                PD::setColor(9);
                PD::drawRectangle(0, 0, 88, 79);
                PD::setColor(4);
                PD::drawLine(1, 80, 89, 80);
                PD::drawLine(89, 1, 89, 80);
                PD::setColor(6);
                PD::setCursor(4, 3);
                PD::print("Inventory\n\n");

                PD::setColor(5);
                PD::setFont(font3x5);
                PD::setCursor(68, 4);
                PD::print(player.getInventoryCount(), 10);
                PD::setCursor(73, 4);
                PD::print("of");
                PD::setCursor(82, 4);
                PD::print(static_cast<uint8_t>(MAX_INVENTORY_ITEMS), 10);
                PD::setFont(fontKoubit);
                PD::setColor(6);


                uint8_t items = 0;

                PD::setCursor(10, 14);
                PD::print("Rune Bag");       

                if (player.getInventoryCount() > 0) {

                    for (uint8_t i = 0; i < MAX_INVENTORY_ITEMS; i++) {

                        InventoryItem inventoryItem = this->player.getInventoryItem(i);

                        if (inventoryItem.quantity > 0) {

                            renderInventoryItem(23 + (items * 9), inventoryItem);
                            items++;
                
                        }

                    }

                }

                PD::setCursor(10, 71);
                PD::setColor(6);
                PD::print("Go Back");

                if (!this->inventoryMenu.showActionMenu) {

                    if (this->inventoryMenu.mainCursor < player.getActiveSlotCount() + 1) {
                        PD::drawBitmap(3, 15 + (this->inventoryMenu.mainCursor * 9), Images::Arrow);
                    }
                    else {
                        PD::drawBitmap(3, 72, Images::Arrow);
                    }

                }
                else {

                    static PROGMEM const uint8_t itemOffset[] = { 0, 0, 0, 0, 2, 10, 0 };
                    uint8_t yOffset = this->inventoryMenu.mainCursor[itemOffset];

                    PD::drawBitmap(3, 15 + (this->inventoryMenu.mainCursor * 9), Images::Arrow_Dark);

                    PD::setColor(0);
                    PD::fillRect(39, 5 + (this->inventoryMenu.mainCursor * 9) - yOffset, 72, 48);
                    PD::setColor(9);
                    PD::drawRectangle(40, 6 + (this->inventoryMenu.mainCursor * 9) - yOffset, 67, 45);
                    PD::setColor(4);
                    PD::drawLine(41, 52 + (this->inventoryMenu.mainCursor * 9) - yOffset, 108, 52 + (this->inventoryMenu.mainCursor * 9) - yOffset);
                    PD::drawLine(108, 7 + (this->inventoryMenu.mainCursor * 9) - yOffset, 108, 52 + (this->inventoryMenu.mainCursor * 9) - yOffset);

                    PD::setColor(6);
                    PD::setCursor(44, 9 + (this->inventoryMenu.mainCursor * 9) - yOffset);
                    PD::print("Actions");
                    PD::setCursor(50, 20 + (this->inventoryMenu.mainCursor * 9) - yOffset);

                    InventoryItem & inventoryItem = this->player.getActiveInventoryItem(this->inventoryMenu.mainCursor - 1);

                    if (inventoryItem.type == this->player.getWeapon()) {
                        PD::print("Put Away");
                    }
                    else {
                        PD::print("Use");
                    }

                    PD::setCursor(50, 29 + (this->inventoryMenu.mainCursor * 9) - yOffset);
                    PD::print("Drop");
                    PD::setCursor(50, 41 + (this->inventoryMenu.mainCursor * 9) - yOffset);
                    PD::print("Go Back");

                    switch (this->inventoryMenu.actionCursor) {

                        case 0:
                            PD::drawBitmap(43, 21 + (this->inventoryMenu.mainCursor * 9) - yOffset, Images::Arrow);
                            break;

                        case 1:
                            PD::drawBitmap(43, 30 + (this->inventoryMenu.mainCursor * 9) - yOffset, Images::Arrow);
                            break;

                        case 2:
                            PD::drawBitmap(43, 42 + (this->inventoryMenu.mainCursor * 9) - yOffset, Images::Arrow);
                            break;
                            
                    }
                
                }

            }

            break;

        case InventoryMenuMode::AltarPieces:

            this->renderEnvironment(!this->map.isBossLevel() && !this->map.isAltarLevel(), 0, 0);
            this->renderHud();

            PD::setColor(15);
            PD::fillRect(22, 8, 70, 60);

            PD::drawBitmap(15, 1, Images::AltarTOP);
            PD::drawBitmap(14, 8, Images::AltarLHS);
            PD::drawBitmap(88, 8, Images::AltarRHS);
            PD::drawBitmap(16, 64, Images::AltarBOT);

            PD::drawBitmap(33, 15, this->player.getAltarPieces() >= 1 ? Images::Rune_Red_00 : Images::Rune_Grey_00);
            PD::drawBitmap(50, 15, this->player.getAltarPieces() >= 2 ? Images::Rune_Red_01 : Images::Rune_Grey_01);
            PD::drawBitmap(67, 15, this->player.getAltarPieces() >= 3 ? Images::Rune_Red_02 : Images::Rune_Grey_02);
            PD::drawBitmap(33, 43, this->player.getAltarPieces() >= 4 ? Images::Rune_Red_03 : Images::Rune_Grey_03);
            PD::drawBitmap(50, 43, this->player.getAltarPieces() >= 5 ? Images::Rune_Red_04 : Images::Rune_Grey_04);
            PD::drawBitmap(67, 43, this->player.getAltarPieces() >= 6 ? Images::Rune_Red_05 : Images::Rune_Grey_05);

            break;



    }

}

void Game::renderInventoryItem(uint8_t y, InventoryItem inventoryItem) {

    PD::setCursor(10, y);

    PD::setFont(fontKoubit);
    PD::setColor(6);
    PD::print(object_Descs[static_cast<uint8_t>(inventoryItem.type)]);
    PD::setColor(5);
    PD::setFont(font3x5);
    PD::setCursor(64, y + 1);
    PD::print(" x");
    PD::setFont(fontKoubit);
    PD::setCursor(72, y);
    PD::print(inventoryItem.quantity, 10);
    PD::print("\n");

}

