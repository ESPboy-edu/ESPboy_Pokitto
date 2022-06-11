#include "SpaceCab.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


//------------------------------------------------------------------------------

void Game::initGame(Player &player) {

//SJH
    player.setNumberOfLives(PLAYER_NUMBER_OF_LIVES_MAX);
    player.setScore(0);
    // player.setNumberOfLives(1);
    // player.setScore(random(11, 20));

}

void Game::initLevel(Level &level, Player &player, Customer &customer, uint8_t levelNumber) {

    level.reset(levelNumber, false);
    player.reset(level);
    customer.setStartingPosition(CUSTOMER_NO_STARTING_POS);

}

// ----------------------------------------------------------------------------------------------------------
//    Is the nominated tile solid?
// 
bool Game::isTileSolid(uint8_t tileType) {

    switch (tileType) {
        
        case BRICK:
        case PLAT1:
        case ROCKS:
        case METAL:
        case SAND1:
        case GATE1:
        case GATE2:
        case SHADE:
            return true;

        default:
            return false;

    }
    
}



bool Game::collide(Rect rect1, Rect rect2) {
    return !(rect2.x                >= rect1.x + rect1.width  ||
             rect2.x + rect2.width  <= rect1.x                ||
             rect2.y                >= rect1.y + rect1.height ||
             rect2.y + rect2.height <= rect1.y);
 }



void Game::handleInput(Player &player) {


    // You cannot move while loading a customer ..

    if (player.getPickingUpCustomer()) return;

//    if (state != GameState::PlayGame_FlashingCar && (PC::buttons.pressed(BTN_B) || PC::buttons.repeat(BTN_B, 1)) && player.getFuel() != 0) {
    if (state != GameState::PlayGame_FlashingCar && PC::buttons.pressed(BTN_B) && player.getFuel() != 0) {

        player.setLandingGearDown(!player.isLandingGearDown());

    }
    else {
            
        if (PC::frameCount % 4 == 0) {

            if (!player.hasJustLanded()) {

                if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1)) {
                    player.decXDelta();
                    player.setFrame(1);
                }

                else if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1)) {
                    player.incXDelta();
                    player.setFrame(0);
                }

            }

            if ((PC::buttons.pressed(BTN_A) || PC::buttons.repeat(BTN_A, 1)) && player.getFuel() > 0) {

                switch (player.getFrame()) {

                    case 0: 
                        PD::drawBitmap(player.getXDisplay(), player.getYDisplay() + 8, Images::ThrusterRight[this->gamePlayVariables.thrusterFrame]);
                        break;

                    case 1:
                        PD::drawBitmap(player.getXDisplay(), player.getYDisplay() + 8, Images::ThrusterLeft[this->gamePlayVariables.thrusterFrame]);
                        break;

                }


                // Alternate thruster frame every 5 frames ..

                if (PC::frameCount % 5 == 0) {
                    ++this->gamePlayVariables.thrusterFrame;
                    this->gamePlayVariables.thrusterFrame %=2;
                }

                player.decYDelta();
                // sound.tone(NOTE_C1, 50, NOTE_C2, 50, NOTE_C1, 50);
                //tone(D3, 10, 10);
            }

            if (PC::frameCount % 8 == 0) {


                // If the A Button is not being pressed, then we should start falling ..

                if (!PC::buttons.aBtn() || player.getFuel() == 0) {

                    uint16_t playerXPosition = player.getXDisplay() - level.getXOffsetDisplay();
                    uint16_t playerYPosition = player.getYDisplay() - level.getYOffsetDisplay();

                    if (canMoveDown(this->level, playerXPosition, playerYPosition, this->player.getHeight())) {
                        // printf("incYDelta\n");
                        player.incYDelta(); 
                    }

                }

            }


            // If the player is not pressing the left or right button then start slowing down ..

            if (PC::frameCount % 16 == 0) {

                if (!PC::buttons.leftBtn() && !PC::buttons.rightBtn()) {

                    if (player.getXDelta() > 0)    player.decXDelta();
                    if (player.getXDelta() < 0)    player.incXDelta();

                }

            }

        }

    }

}


//------------------------------------------------------------------------------
//    Launch a new customer.
//
//    Valid launching positions are derived from the level design.
//------------------------------------------------------------------------------

void Game::launchCustomer(Level &level, Customer &customer, uint8_t defaultStartPosition, uint8_t defaultEndingPosition) {

    const uint8_t numberOfPositions = level.getNumberOfCustomerPositions();

    uint8_t customerStartingPos = 0;
    uint8_t customerDestination = 0;


    switch (numberOfPositions) {

        case 2:
            customerStartingPos = customer.getStartingPosition() == 0 ? 1 : 0;
            customerDestination = customer.getDestinationPosition() == 0 ? 1 : 0;
            break;

        case 3 ... 9:

            customerStartingPos = (defaultStartPosition == RANDOM_START_POSITION ? random(numberOfPositions) : defaultStartPosition);
            customerDestination = (defaultEndingPosition == RANDOM_END_POSITION ? random(numberOfPositions) : defaultEndingPosition);


            // Ensure new customer is not placed in the location the last customer was dropped at ..

            while (defaultStartPosition == RANDOM_START_POSITION && (customerStartingPos == customer.getStartingPosition() || customerStartingPos == customer.getDestinationPosition())) {
                    customerStartingPos = random(numberOfPositions);
            }


            // Make sure the starting point and destination are different!

            while (defaultStartPosition == RANDOM_START_POSITION && customerStartingPos == customerDestination) {
                customerDestination = random(numberOfPositions);
            }

            break;

        default:

            customerStartingPos = 0;
            customerDestination = GO_TO_GATE;
            break;

    }

    customer.setXTile(level.getStartingPosition(customerStartingPos * 2));
    customer.setYTile(level.getStartingPosition((customerStartingPos * 2) + 1));
    customer.setStartingPosition(customerStartingPos);
    customer.setDestinationPosition(customerDestination);

    if (customerDestination != GO_TO_GATE) {

        customer.setXDestinationTile(level.getEndingPosition(customerDestination * 2));
        customer.setYDestinationTile(level.getEndingPosition((customerDestination * 2) + 1));

    }

    customer.setFrame(0);
    customer.setStatus(CustomerStatus::Alive);
    customer.setFare(random(FARE_MIN, FARE_MAX));
    customer.setHailCounter(40);

}


//------------------------------------------------------------------------------
//    Has the player collided with the customer ?
//------------------------------------------------------------------------------

void Game::checkCollisionWithCustomer(Level &level, Player &player, Customer &customer) {

    if (player.isCarryingCustomer() || customer.getStatus() == CustomerStatus::Dead) return;

    Rect playerRect = { static_cast<int16_t>(player.getXDisplay()), static_cast<int16_t>(player.getYDisplay()), PLAYER_WIDTH, player.getHeight() };


    // Check customer collision only if they are on-screen ..

    int16_t customerXVal = static_cast<uint16_t>(customer.getX() + level.xOffset);
    int16_t customerYVal = static_cast<uint16_t>(customer.getY() + level.yOffset);

    if (customerXVal >= -CUSTOMER_WIDTH && customerXVal < SCREEN_WIDTH && customerYVal >= -CUSTOMER_HEIGHT && customerYVal < SCREEN_HEIGHT) {
    
        Rect customerRect = { customerXVal, customerYVal, CUSTOMER_WIDTH, CUSTOMER_HEIGHT };

        if (collide(playerRect, customerRect)) {

            this->gamePlayVariables.ouchCounter = OUCH_COUNTER_MAX;
            customer.setStatus(CustomerStatus::Dead);
            player.setPickingUpCustomer(false);
            this->playSoundEffect(this->maleOrFemale);

        }

    }

}



//------------------------------------------------------------------------------
//    Handle collisions with level elements ..
//------------------------------------------------------------------------------

void Game::checkCollisionWithLevelElements(Level &level, Player &player) {

    player.setFuelling(false);

    uint8_t tileAlreadyTested[TILE_COUNT];

    for (uint8_t i = 0; i < TILE_COUNT; i++)    tileAlreadyTested[i] = 0;

    uint16_t playerXPosition = player.getXDisplay() - level.getXOffsetDisplay();
    uint16_t playerYPosition = player.getYDisplay() - level.getYOffsetDisplay();

    uint8_t tileX1 = (playerXPosition / 8);
    uint8_t tileX2 = (playerXPosition / 8) + 1;
    uint8_t tileX3 = (playerXPosition / 8) + 2;
    uint8_t tileY1 = (playerYPosition / 8);
    uint8_t tileY2 = (playerYPosition / 8) + 1;

    uint8_t tile = level.getLevelData(tileX1, tileY1);
    if (tileAlreadyTested[tile] == 0) {
        checkCollisionWithLevelElements_TestElement(level, player, tileX1, tileY1, tile);
        tileAlreadyTested[tile] = 1;
    }

    tile = level.getLevelData(tileX2, tileY1);
    if (tileAlreadyTested[tile] == 0) {
        checkCollisionWithLevelElements_TestElement(level, player, tileX2, tileY1, tile);
        tileAlreadyTested[tile] = 1;
    }

    tile = level.getLevelData(tileX3, tileY1);
    if (tileAlreadyTested[tile] == 0) {
        checkCollisionWithLevelElements_TestElement(level, player, tileX3, tileY1, tile); 
        tileAlreadyTested[tile] = 1;
    }

    if (playerYPosition / 8 != 0) {

        tile = level.getLevelData(tileX1, tileY2);
        if (tileAlreadyTested[tile] == 0) {
            checkCollisionWithLevelElements_TestElement(level, player, tileX1, tileY2, tile);
            tileAlreadyTested[tile] = 1;
        }

        tile = level.getLevelData(tileX2, tileY2);
        if (tileAlreadyTested[tile] == 0) {
            checkCollisionWithLevelElements_TestElement(level, player, tileX2, tileY2, tile);
            tileAlreadyTested[tile] = 1;
        }

        tile = level.getLevelData(tileX3, tileY2);
        if (tileAlreadyTested[tile] == 0) {
            checkCollisionWithLevelElements_TestElement(level, player, tileX3, tileY2, tile);
            tileAlreadyTested[tile] = 1;
        }

    } 

}

void Game::checkCollisionWithLevelElements_TestElement(Level &level, Player &player, uint8_t x, uint8_t y, uint8_t tile) {

    switch (tile) {

        case FUEL1:
            if (!player.isFuelling()) {
                player.setFuelling(true);
                // this->playSoundEffect(5);
            }
            //sound if (fuelSound[0] == 0) { fuelSound[0] = 200; }

            if (PC::frameCount % 4 == 0) {
                Fuel &fuel = level.getFuel(x, y);
                if (fuel.getFuelLeft() > 0 && player.getFuel() < level.getFuelMax()) {

                   // #ifdef SOUNDS
                     Game::playFXS(3, player.getFuel());
                      /*  auto note = Audio::Note(player.getFuel())
                            .wave(WSQUARE)
                            .duration(50)
                            .volume(75);
                        note.play(2);  
*/
               
                  //  #endif

                    player.incFuel();
                    fuel.decFuel();
                }
                else {
                    //sound fuelSound[0] = 0;
                }
            }
            break;
        
        case LEVE1:
            level.changeInternalGate(GateMode::Open);
            // sound.tone(NOTE_C1, 80, NOTE_D3, 50, NOTE_F6, 80);
            break;

        case SPIKU:
        case SPIKD:
            player.setStatus(PlayerStatus::OutOfFuel_Max);
            break;
     
    }

    // Going down?

// printf("YDelta %i, tile: %i =  %i\n", player.getYDelta(), tile, isTileSolid(tile));
    if (player.getYDelta() > 0 && isTileSolid(tile)) {
        if (player.getYDelta() > 4) {
// printf("1\n");
            player.setStatus(PlayerStatus::OutOfFuel_Max);

        }
        else  if (!player.isLandingGearDown()) {
// printf("2\n");

            player.setStatus(PlayerStatus::OutOfFuel_Max);

        }

    }

}


void Game::updateStatus(Player &player, Customer &customer) {


    // Burn fuel ..

    if (!player.isFuelling() && player.getStatus() == PlayerStatus::Active) {


        // If we are thrusting (yDelta < 0) then burn fuel proportionally to the speed.    Otherwise burn slowly ..

        if ((player.getYDelta() < 0 && PC::frameCount % (FUEL_BURN_RATE_DIV / -player.getYDelta()) == 0) || PC::frameCount % FUEL_BURN_RATE_MIN == 0) {

            player.decFuel();

            if (player.getFuel() == 0) {

                player.setLandingGearDown(false);

            }

        }

    }


    // Update player status ..

    switch (player.getStatus()) {

        case PlayerStatus::OutOfFuel_Max:
            this->playSoundEffect(3);
            player.decStatus();
            break;

        case PlayerStatus::OutOfFuel_Min ... PlayerStatus::OutOfFuel_MaxMinusOne:
            player.decStatus();
            break;

        case PlayerStatus::OutOfFuel_End:
            player.setStatus(PlayerStatus::Inactive);
            player.decNumberOfLives();

            if (player.getNumberOfLives() > 0) {
                level.reset(level.getLevelNumber(), false);
                player.setStatus(PlayerStatus::Active);
                player.setNextStatus(PlayerStatus::Active);
                player.setXDelta(0);
                player.setYDelta(0);
                this->state = GameState::PlayGame_InitLevel;
                this->nextState = GameState::PlayGame_FlashingCar;
            }
            else {
                this->state = GameState::GameOver_Init;
            }
            
            break;

        default:    break;

    }


    // Decrease fare ..

    if (PC::frameCount % FARE_X_FRAMES == 0) {

        this->gamePlayVariables.fareCount++;

        if (this->gamePlayVariables.fareCount > FARE_COUNT) {
            this->gamePlayVariables.fareCount = 0;
            customer.decFare();
        }

    }

}


//------------------------------------------------------------------------------
//    Play the game! 
//------------------------------------------------------------------------------

void Game::inGame(Level &level, Player &player, Customer &customer) {

    int16_t customerXVal = static_cast<uint16_t>(customer.getX() + level.xOffset);
    int16_t customerYVal = static_cast<uint16_t>(customer.getY() + level.yOffset);


    // Thruster noise ..

   // #ifdef SOUNDS

        if (player.getYDelta() < 0) {
            Game::playFXS(4, player.getYDelta());
            /*
            auto note = Audio::Note(10 - (player.getYDelta() * 5))
                            .wave(1 + rand()%3)
                            .duration(random(40, 80))
                            .volume(50 - (player.getYDelta() * 10));
            note.play();           
*/
        }

  //  #endif
 

    if (!this->gamePlayVariables.paused) {
            
        this->gamePlayVariables.flashingCounter++;
        this->gamePlayVariables.flashingCounter = this->gamePlayVariables.flashingCounter % FLASH_MAX;


        // Handle counters ..

        if (this->gamePlayVariables.gotoCounter != 0)         this->gamePlayVariables.gotoCounter--;
        
        if (this->gamePlayVariables.ouchCounter != 0) { 
            this->gamePlayVariables.ouchCounter--;
            if (this->gamePlayVariables.ouchCounter == 0)     launchCustomer(level, customer, RANDOM_START_POSITION, RANDOM_END_POSITION);
        }
        
        this->level.decInternalGateCounter();
        this->customer.decHailCounter();

        if (this->customer.getHailCounter() == 1) {

            this->playHailTaxi();

        }

    }
    


    // Render level,player and customers ..

    this->drawLevel(level);

    if (!this->gamePlayVariables.paused && this->player.getStatus() == PlayerStatus::Active) {

        if (this->player.getNextStatus() != PlayerStatus::OutOfFuel_Max) {
                
            this->handleInput(player);
            this->checkCollisionWithCustomer(level, player, customer);

            if (state == GameState::PlayGame) {
                this->checkCollisionWithLevelElements(level, player);
            }

        }
        else {

            this->player.setStatus(this->player.getNextStatus());
            this->player.setNextStatus(PlayerStatus::Active);

        }

    }

    if (state != GameState::PlayGame_FlashingCar || this->gamePlayVariables.flashingCounter < (FLASH_MAX / 2)) {
        this->playerDisplay(player);
    }

    this->drawDollars(player);
    this->customerDisplay(level, player, customer, customerXVal, customerYVal);
    this->drawHUD(player, customer);
    this->drawGoto(level, player, customer, customerXVal, customerYVal);
    this->drawOuch(customer, customerXVal, customerYVal);

    if (!this->gamePlayVariables.paused) {

        if (state == GameState::PlayGame_FlashingCar) {

            if (PC::buttons.pressed(BTN_A)) {
                state = GameState::PlayGame;
            }

        }
        else {
    
            this->updateStatus(player, customer);

        }

    }
    else {

        PD::drawBitmap(11, 36, Images::Pause);

    }


    if (PC::buttons.pressed(BTN_C)) {

        if (this->prevState == GameState::Designer) {

            PD::setColor(0, 0);
            this->state = this->prevState;

        }
        else {

            this->gamePlayVariables.paused = !this->gamePlayVariables.paused;

        }

    }
    
}
