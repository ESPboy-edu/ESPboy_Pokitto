#include "Pokitto.h"
#include "Game.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


#define SHOP_ITEMS_TOP          2
#define SHOP_ITEMS_SPACING      13
#define SHOP_ITEMS_ICON_LEFT    8
#define SHOP_ITEMS_DESC_LEFT    SHOP_ITEMS_ICON_LEFT + 14
#define SHOP_ITEMS_COST_LEFT    SHOP_ITEMS_ICON_LEFT + 71


void Game::showShop() {


    // Update timer, counters, etc ..

    if (Pokitto::Core::frameCount % TIMER_STEP == 0) { this->map.decTimer();  }

    if (this->shopVariables.counter > 0) this->shopVariables.counter--;

    if (PC::buttons.pressed(BTN_A)) {

        if (this->shopVariables.message == ShopMessage::None) {

            ShopObject &shopObject = this->shopObjects[this->shopVariables.upperIndex + this->shopVariables.itemIndex];

            if (shopObject.quantityLeft == 0) {

                this->shopVariables.message = ShopMessage::OutOfStock;

            }
            else if (shopObject.price > this->player.getCoinsOverall()) {

                this->shopVariables.message = ShopMessage::NotEnoughGold;

            }
            else {
            
                uint8_t slot = this->player.addInventoryItem(shopObject.object, 1);

                if (slot == NO_SLOT_FOUND) {

                    this->shopVariables.message = ShopMessage::InventoryFull;

                }
                else {

                    this->player.setCoinsOverall(this->player.getCoinsOverall() - shopObject.price);
                    shopObject.quantityLeft = shopObject.quantityLeft - 1;
                    this->shopVariables.counter = SHOP_PURCHASE_DELAY;
                    
                }

            }

        }
        else {

           this->shopVariables.message = ShopMessage::None;

        }

    }


    if (PC::buttons.pressed(BTN_B) || PC::buttons.pressed(BTN_C)) {
        gameState = GameState::Game_Init_Music;
    }

    if (PC::buttons.pressed(BTN_UP)) {

        switch (this->shopVariables.upperIndex) {

            case 0:
                if (this->shopVariables.itemIndex > 0) {
                    this->shopVariables.itemIndex--;
                }
                break;

            default:
                if (this->shopVariables.itemIndex > 4) {
                    this->shopVariables.itemIndex--;
                } 
                else {
                    this->shopVariables.upperIndex--;
                }
                break;

        }
      
    }

    if (PC::buttons.pressed(BTN_DOWN)) {

        switch (this->shopVariables.upperIndex) {

            case 0 ... 3:
                if (this->shopVariables.itemIndex < 2) {
                    this->shopVariables.itemIndex++;
                }
                else {
                    this->shopVariables.upperIndex++;
                }
                break;

            default:
                if (this->shopVariables.itemIndex < 4) {
                    this->shopVariables.itemIndex++;
                }
                break;
                
        }

    }





    //this->renderEnvironment(!this->map.isBossLevel() && !this->map.isAltarLevel(), 0, 0);
    PD::setColor(15, 0);
    this->renderHud();
    PD::setColor(6);


    for (uint8_t i = this->shopVariables.upperIndex, j = 0; i < this->shopVariables.upperIndex + 5; i++, j++) {

        ShopObject shopObject = this->shopObjects[i];

        this->objects.renderSprite(shopObject.object, SHOP_ITEMS_ICON_LEFT + 4, SHOP_ITEMS_TOP + (j * SHOP_ITEMS_SPACING) + 4);
        PD::setCursor(SHOP_ITEMS_DESC_LEFT, SHOP_ITEMS_TOP + 1 + (j * SHOP_ITEMS_SPACING));
        PD::print(object_Descs[static_cast<uint8_t>(shopObject.object)]);

        if (shopObject.quantityLeft != 0) {
            PD::setCursor(SHOP_ITEMS_COST_LEFT + (shopObject.price < 10 ? 6 : 0), SHOP_ITEMS_TOP + 1 + (j * SHOP_ITEMS_SPACING));
            PD::print("$ ");
            PD::print(shopObject.price);
        }
        else {

            PD::drawBitmap(SHOP_ITEMS_COST_LEFT - 4, SHOP_ITEMS_TOP + 2 + (j * SHOP_ITEMS_SPACING), Images::SoldOut);

        }

    }

    PD::setColor(this->shopVariables.counter > 0 && (this->shopVariables.counter % 24 < 12) ? 9: 5);    
    PD::drawRect(SHOP_ITEMS_ICON_LEFT - 4, SHOP_ITEMS_TOP - 2 + (this->shopVariables.itemIndex * SHOP_ITEMS_SPACING), 101, 12 );
    PD::setColor(5);
    PD::drawLine(0, 71, 92, 71);
    PD::drawBitmap(92, 53, Images::Seller);

    if (this->shopVariables.message != ShopMessage::None) { 
        
        // PD::setColor(15);
        // PD::fillRect(21, 27, 70, 24);
        // PD::drawBitmap(15, 22, Images::MessagePanelTOP); 
        // PD::drawBitmap(15, 29, Images::MessagePanelLHS); 
        // PD::drawBitmap(88, 29, Images::MessagePanelRHS); 
        // PD::drawBitmap(15, 50, Images::MessagePanelBOT); 
        // PD::setColor(4, 15);
        // PD::setFont(font3x5);
        this->renderMessageBox();

        switch (this->shopVariables.message) {

            case ShopMessage::NotEnoughGold:
                PD::setCursor(27, 30);
                PD::print("You do not have");
                PD::setCursor(29, 37);
                PD::print("enough gold to");
                PD::setCursor(42, 44);
                PD::print("buy that!");
                break;

            case ShopMessage::OutOfStock:
                PD::setCursor(24, 30);
                PD::print("We are currently");
                PD::setCursor(26, 37);
                PD::print("out of stock of");
                PD::setCursor(37, 44);
                PD::print("that item!");
                break;

            case ShopMessage::InventoryFull:
                PD::setCursor(25, 30);
                PD::print("You are carrying");
                PD::setCursor(23, 37);
                PD::print("more than you can");
                PD::setCursor(42, 44);
                PD::print("handle!");
                break;                
                
        }

        PD::setFont(fontKoubit);

    }


    PD::setColor(15, 0);

}
