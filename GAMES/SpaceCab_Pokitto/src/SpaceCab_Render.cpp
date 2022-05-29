#include "SpaceCab.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

void Game::drawLevel_Intro(Level &level, uint8_t gateToRender) {

    bool alt = PC::frameCount % 64 < 32;

    for (uint8_t y = 0; y < level.getHeightInTiles(); y++) {

        for (uint8_t x = 0; x < level.getWidthInTiles(); x++) {
            
            const int16_t tileX = (x * TILE_SIZE);
            const int16_t tileY = (y * TILE_SIZE);
            const int16_t bitmapX = tileX + level.getXOffsetDisplay();
            const int16_t bitmapY = tileY + level.getYOffsetDisplay();

            uint8_t tile = level.getLevelData(x, y);

            switch (tile) {

                case EMPTY: 
                    {
                        uint16_t tileFrame = ((y * level.getHeightInTiles()) + x + 3) % 27;

                        if (tileFrame % 8 == 0 && PC::frameCount % 4 != (y * level.getHeightInTiles() + x) % 4) {
                            PD::drawBitmap(bitmapX, bitmapY, Images::Empty_With_Stars[tileFrame >> 3]);
                        }

                    }
                    break;

                case SIGN1:
                    {
                        bool found = false;
                        const uint8_t numberOfPositions = level.getNumberOfCustomerPositions();
                        
                        for (uint8_t i = 0; i < numberOfPositions; ++i) {

                            const uint8_t startPosX = level.getEndingPosition(i * 2);
                            const uint8_t startPosY = level.getEndingPosition((i * 2) + 1);

                            if (x == startPosX && y == startPosY && gateToRender == i) {

                                PD::setColor(7, 0);
                                PD::drawBitmap(bitmapX, bitmapY, Images::Tiles_Large[tile]);
                                PD::fillRect(bitmapX + 2, bitmapY - 2, 5, 6);
                                PD::setColor(0, 14);
                                PD::setCursor(bitmapX + 3, bitmapY - 1);
                                PD::print(i + 1, 10);
                                found = true;

                            }

                        }

                        if (!found) PD::drawBitmap(bitmapX, bitmapY, Images::Tiles_Large[EDGE1]);
                        
                    }

                    break;

                case WATER:
                    PD::drawBitmap(bitmapX, bitmapY, alt ? Images::Tiles_Large[tile] : Images::WaterAlt);
                    break;

                default:
                    PD::drawBitmap(bitmapX, bitmapY, Images::Tiles_Large[tile]);
                    break;
                    
            }

        }

    }

    PD::setColor(0, 0);

}


void Game::drawLevel(Level &level) {

    bool alt = PC::frameCount % 64 < 32;

    for (uint8_t y = 0; y < level.getHeightInTiles(); y++) {

        for (uint8_t x = 0; x < level.getWidthInTiles(); x++) {

            const int16_t tileX = (x * TILE_SIZE);
            const int16_t tileY = (y * TILE_SIZE);
            const int16_t bitmapX = tileX + level.getXOffsetDisplay();
            const int16_t bitmapY = tileY + level.getYOffsetDisplay();
            

            // Do we really need to render the tile?

            if (bitmapX < -8 || bitmapX >= SCREEN_WIDTH || bitmapY < -8 || bitmapY >= SCREEN_HEIGHT)
                continue;

            uint8_t tile = level.getLevelData(x, y);

            switch (tile) {

                case EMPTY: 
                    {
                        uint16_t tileFrame = ((y * level.getHeightInTiles()) + x + 3) % 27;

                        if (tileFrame % 8 == 0 && PC::frameCount % 4 != (y * level.getHeightInTiles() + x) % 4) {
                            PD::drawBitmap(bitmapX, bitmapY, Images::Empty_With_Stars[tileFrame >> 3]);
                        }
                        
                    }
                    break;

                case SIGN1:

                    PD::setColor(7, 0);
                    PD::drawBitmap(bitmapX, bitmapY, Images::Tiles_Large[tile]);
                    PD::fillRect(bitmapX + 2, bitmapY - 2, 5, 6);
                    PD::setColor(0, 14);

                    if (this->gamePlayVariables.flashingCounter < (FLASH_MAX / 2)) {

                        const uint8_t numberOfPositions = level.getNumberOfCustomerPositions();
                        // const uint8_t *levelEndingPosition = levelEndingPositions[level.getLevelNumber()];

                        for (uint8_t i = 0; i < numberOfPositions; ++i) {

                            const uint8_t startPosX = level.getEndingPosition(i * 2);
                            const uint8_t startPosY = level.getEndingPosition((i * 2) + 1);

                            if (x == startPosX && y == startPosY) {

                                PD::setCursor(bitmapX + 3, bitmapY - 1);
                                PD::print(i + 1, 10);

                            }

                        }

                    }

                    break;

                case FUEL1:
                    {
                        Fuel &fuel = level.getFuel(x, y);
                        PD::drawBitmap(bitmapX, bitmapY, Images::Fuels[fuel.getFuelLeftPerCent()]);
                    }
                    break;

                case WATER:
                    PD::drawBitmap(bitmapX, bitmapY, alt ? Images::Tiles_Large[tile] : Images::WaterAlt);
                    break;

                default: 
                    PD::drawBitmap(bitmapX, bitmapY, Images::Tiles_Large[tile]);
                    break;
                    
            }

        }

    }
                         
}

#define HUD_OFFSET 10
#define HUD_WIDTH 66

void Game::drawHUD(Player &player, Customer &customer) {

    PD::drawBitmap(0, 80, Images::FULL_HUD);


    // Draw G Forces ..

    switch (this->player.getFalling()) {

        case 0:
            break;

        case 1 ... 2:
            PD::drawBitmap(103, 82, Images::Falling_1G);
            break;

        case 3 ... 5:
            PD::drawBitmap(103, 82, Images::Falling_2G);
            break;

        case 6 ... 12:
            PD::drawBitmap(103, 82, Images::Falling_3G);
            break;

        default:
            if (PC::frameCount % 24 < 12) {
                PD::drawBitmap(103, 82, Images::Falling_4G);
            }
            break;
            
    }


    {
        PD::setCursor(10, 82);
        PD::setColor(10, 0);
        uint8_t digits[5];
        extractDigits(digits, player.getScore());

        for (uint8_t i = 5; i > 0; --i) {
            PD::print(digits[i - 1], 10);
        }
    }

    if (player.getFuel() > 0 && player.getFuel() < PLAYER_FUEL_MIN_BLINK && this->gamePlayVariables.flashingCounter < (FLASH_MAX / 2)) {
    
        PD::setColor(8, 0);
    
    }
    else {

        PD::setColor(10, 0);

        uint8_t digitsFuel[3];
        PD::setCursor(43, 82);
        extractDigits(digitsFuel, player.getFuel());

        for(uint8_t i = 3; i > 0; --i) {
            PD::print(digitsFuel[i - 1], 10);
        }

    }


    {
        uint8_t digitsLives[1];
        PD::setCursor(75, 82);
        PD::setColor(10, 0);
        extractDigits(digitsLives, player.getNumberOfLives());

        for(uint8_t i = 1; i > 0; --i) {
            PD::print(digitsLives[i - 1], 10);
        }
    }

    {
        uint8_t digitsFare[2];
        PD::setCursor(91, 82);
        PD::setColor(10, 0);
        extractDigits(digitsFare, customer.getFare());
        
        for(uint8_t i = 2; i > 0; --i) {
            PD::print(digitsFare[i - 1], 10);
        }
    }

    PD::setColor(7, 0);

}

void Game::scrollingBackground(bool scrollLeft, uint8_t y, uint8_t idx) {

    for (int16_t x = this->gamePlayVariables.backdropx[idx]; x < SCREEN_WIDTH; x = x + 10) {

        PD::drawBitmap(x, y, Images::Checkers_Large);

    }

    if (PC::frameCount % 4 == 0) { // when running at 60fps

        if (scrollLeft) {
            --this->gamePlayVariables.backdropx[idx];
            if (this->gamePlayVariables.backdropx[idx] <= -SCREEN_WIDTH) {
                this->gamePlayVariables.backdropx[idx] = 0;
            }
        }
        else {
            ++this->gamePlayVariables.backdropx[idx];
            if (this->gamePlayVariables.backdropx[idx] >= 0) {
                this->gamePlayVariables.backdropx[idx] = -SCREEN_WIDTH;
            }
        }
    
    }

}

void Game::playerDisplay(Player &player) {

    uint8_t const *imageName = nullptr;
    int16_t xOffset = 0;
    int16_t yOffset = 0;
    uint8_t frameNumber = player.getFrame();

    switch (player.getStatus()) {

        case PlayerStatus::OutOfFuel_Img1_Start ... PlayerStatus::OutOfFuel_Img1_End:
            imageName = Images::SpaceTaxi_OutOfFuel_1[0];
            xOffset = -5;
            yOffset = -5;
            break;

        case PlayerStatus::OutOfFuel_Img2_Start ... PlayerStatus::OutOfFuel_Img2_End:
            imageName = Images::SpaceTaxi_OutOfFuel_2[0];
            xOffset = -5;
            yOffset = -5;
            frameNumber = 0;
            break;

        case PlayerStatus::OutOfFuel_Img3_Start ... PlayerStatus::OutOfFuel_Img3_End:
            imageName = Images::SpaceTaxi_OutOfFuel_3[frameNumber];
            xOffset = -5;
            yOffset = -5;
            break;

        case PlayerStatus::OutOfFuel_Img4_Start ... PlayerStatus::OutOfFuel_Img4_End:
            imageName = Images::SpaceTaxi_OutOfFuel_4[frameNumber];
            xOffset = -5;
            yOffset = -5;
            break;

        case PlayerStatus::Active:

            if (player.isLandingGearDown()) {
                imageName = Images::SpaceTaxi_LandingGear[frameNumber];
            }
            else {
                imageName = Images::SpaceTaxi[frameNumber];
            }
            break;

        default: break;

    }

    if (imageName != nullptr) {
        PD::drawBitmap(player.getXDisplay() + xOffset, player.getYDisplay() + yOffset, imageName);
    }

}


void Game::customerDisplay(Level &level, Player &player, Customer &customer, int16_t customerXVal, int16_t customerYVal) {

    uint8_t frame = customer.getFrame();

    if (!player.isCarryingCustomer() && customerXVal >= -CUSTOMER_WIDTH && customerXVal < SCREEN_WIDTH && customerYVal >= -CUSTOMER_HEIGHT && customerYVal < SCREEN_HEIGHT) {

        switch (customer.getStatus()) {

            case CustomerStatus::Dead:

                PD::drawBitmap(customerXVal, customerYVal, Images::Customer_Flat);
                break;

            case CustomerStatus::Alive:

                PD::drawBitmap(customerXVal, customerYVal, Images::Customer_Img[frame]);
                if (PC::frameCount % 15 == 0) {
                    customer.incFrame();
                }

                break;

            case CustomerStatus::BoardingCab:
                {
                    int8_t walkingOffset = customer.getXWalkingOffset();

                    if (customer.getWalkingDirection() == Direction::Left) {

                        PD::drawBitmap(customerXVal + walkingOffset, customerYVal, Images::Customer_WalkingLeft[frame]);

                    }
                    else {

                        PD::drawBitmap(customerXVal + walkingOffset, customerYVal, Images::Customer_WalkingRight[frame]);

                    }

                    if (PC::frameCount % 8 == 0) {

                        uint16_t customerXPosition = customer.getX();

                        if (customerXPosition + CUSTOMER_WIDTH_HALF + walkingOffset != player.getXDisplay() - level.getXOffsetDisplay() + PLAYER_WIDTH_HALF) {

                            customer.incFrame();

                            if (customer.getWalkingDirection() == Direction::Left) {
                                customer.decXWalkingOffset();
                            }
                            else {
                                customer.incXWalkingOffset();
                            }

                        }
                        else {

                            player.setCarryingCustomer(true);
                            player.setPickingUpCustomer(false);
                            if (player.getFaresCompleted() >= level.getFaresRequired())    level.openLevelGates(); 

                            // sound.tone(NOTE_E6, 50, NOTE_E3, 50, NOTE_E2, 50);

                        }

                    }

                }

                break;

        }

    }
    else if (state == GameState::PlayGame)    { 

        if (player.isCarryingCustomer() && customer.getDestinationPosition() == GO_TO_GATE) { return; }

        uint16_t customerX = 0;
        uint16_t customerY = 0;
        uint8_t arrowX = 0;
        uint8_t arrowY = 0;
        int8_t arrowX_TextOffset = 0;
        int8_t arrowY_TextOffset = 0;
        uint8_t playerX = player.getXDisplay();
        uint8_t playerY = player.getYDisplay();

        Direction direction = Direction::Up;


        // Render arrows.

        if (this->gamePlayVariables.flashingCounter < (FLASH_MAX / 2)) { 

            if (!player.isCarryingCustomer()) {

                customerX = customer.getX();
                customerY = customer.getY();

            }
            else {

                customerX = customer.getXDestinationTile() * TILE_SIZE;
                customerY = customer.getYDestinationTile() * TILE_SIZE;

            }


            // If the customer location is on screen then do not render ..
            {
                int16_t customerXDisplay = customerX + level.getXOffsetDisplay();
                int16_t customerYDisplay = customerY + level.getYOffsetDisplay();

                if (customerXDisplay >= -CUSTOMER_WIDTH && customerXDisplay < SCREEN_WIDTH && customerYDisplay >= -CUSTOMER_HEIGHT && customerYDisplay < SCREEN_HEIGHT) {
                    return;
                } 

            }

            int16_t dX = customerX - static_cast<int16_t>(player.getX() - level.xOffset);
            int16_t dY = customerY - static_cast<int16_t>(player.getY() - level.yOffset);

            if (dX < -playerX) {

                if (dY < -playerY)                                  { direction = Direction::UpLeft; arrowX = 0; arrowY = 0; arrowX_TextOffset = 6, arrowY_TextOffset = 5; }
                if (dY >= -playerY && dY < -playerY + 47)           { direction = Direction::Left; arrowX = 0; arrowY = playerY + dY - 4; arrowX_TextOffset = 8, arrowY_TextOffset = 2; }
                if (dY >= -playerY + 47)                            { direction = Direction::DownLeft; arrowX = 0; arrowY = SCREEN_HEIGHT - 20; arrowX_TextOffset = 6, arrowY_TextOffset = 2; }

            }

            if (dX >= -playerX && dX < -playerX + SCREEN_WIDTH) {

                if (dY < 0)                                         { direction = Direction::Up; arrowX = playerX + dX; arrowY = 0; arrowX_TextOffset = 3, arrowY_TextOffset = 7; }
                if (dY > 0)                                         { direction = Direction::Down; arrowX = playerX + dX; arrowY = SCREEN_HEIGHT - 22; arrowX_TextOffset = 3, arrowY_TextOffset = 2; }

            }

            if (dX >= -playerX + SCREEN_WIDTH) {

                if (dY < -playerY)                                  { direction = Direction::UpRight; arrowX = SCREEN_WIDTH - 12; arrowY = 0; arrowX_TextOffset = 3, arrowY_TextOffset = 5; }
                if (dY >= -playerY && dY < -playerY + 47)           { direction = Direction::Right; arrowX = SCREEN_WIDTH - 14; arrowY = playerY + dY - 4; arrowX_TextOffset = 3, arrowY_TextOffset = 2; }
                if (dY >= -playerY + 47)                            { direction = Direction::DownRight; arrowX = SCREEN_WIDTH - 12; arrowY = SCREEN_HEIGHT - 20; arrowX_TextOffset = 3, arrowY_TextOffset = 2; }

            }

            PD::drawBitmap(arrowX, arrowY, Images::ArrowImgs[static_cast<uint8_t>(direction)]);
            PD::setCursor(arrowX + arrowX_TextOffset, arrowY + arrowY_TextOffset);
            PD::setColor(9, 5);

            if (player.isCarryingCustomer()) {
                PD::print(customer.getDestinationPosition() + 1, 10);
            }
            else {
                PD::print(customer.getStartingPosition() + 1, 10);
            }

        }

    }

}


void Game::drawDollars(Player &player) {

    if (this->gamePlayVariables.dollarsCount > 0) {

        uint8_t idx = (DOLLARS_COUNT_MAX - this->gamePlayVariables.dollarsCount) / DOLLARS_COUNT_MULT;

        PD::drawBitmap(player.getXDisplay() - 5, player.getYDisplay() - 10, Images::Dollars[idx]);
        this->gamePlayVariables.dollarsCount--;
    
    }

}


void Game::drawGoto(Level &level, Player &player, Customer &customer, int16_t customerXVal, int16_t customerYVal) {

    if (this->gamePlayVariables.gotoCounter == GOTO_COUNTER_MAX - 1) {

        if (player.getFaresCompleted() >= level.getFaresRequired()) {
            this->playTakeMe(0);
        }
        else {
            this->playTakeMe(customer.getDestinationPosition() + 1);
        }

    }


    if (this->gamePlayVariables.gotoCounter > 0) {

        int8_t walkingOffset = customer.getXWalkingOffset() + 1;
        
        if (player.getFaresCompleted() >= level.getFaresRequired()) {
            PD::drawBitmap(customerXVal + walkingOffset, customerYVal - 11, Images::Hail_GoGate);
        }
        else {
            PD::drawBitmap(customerXVal + walkingOffset, customerYVal - 11, Images::Hail);
            // PD::setCursor(customerXVal + walkingOffset + 24, customerYVal - 6);
            // PD::print(customer.getDestinationPosition() + 1, 10);
            PD::drawBitmap(customerXVal + walkingOffset + 24, customerYVal - 6, Images::HailNumbers[customer.getDestinationPosition()]);
        }

    }

}

void Game::drawOuch(Customer &customer, int16_t customerXVal, int16_t customerYVal) {

    if (this->gamePlayVariables.ouchCounter > 0) {

        PD::drawBitmap(customerXVal + customer.getXWalkingOffset() + 1, customerYVal - 11, Images::Hail_Ouch);

    }

}
