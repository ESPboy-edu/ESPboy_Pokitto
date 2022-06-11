#include "Pokitto.h"
#include "Game.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

void Game::updateObjects(bool ignorePlayerDamage) {


    // Handle various counters ..

    this->player.decWeaponCount();
    if (this->shake > 0)                    this->shake--;
    if (this->shockwave > 0)                this->shockwave--;
    if (this->levelStartDelay > 0)          this->levelStartDelay--;
    if (this->launchSkeletonDelay > 0)      this->launchSkeletonDelay--;
    if (this->launchSpiderDelay > 0)        this->launchSpiderDelay--;
    if (this->launchCyclopsDelay > 0)       this->launchCyclopsDelay--;
    if (this->enemyBulletDelay > 0)         this->enemyBulletDelay--;

    if (this->changeStateDelay > 0) {

        this->changeStateDelay--;

        if (changeStateDelay == 0) {

            this->gameState = this->nextState;
        }

    }


    // Update other objects ..

    for (uint8_t i = 0; i < this->objects.getObjectNum(); i++) {

        auto &objectI = this->objects.getSprite(i);
        bool objectI_IsEnemy = objectI.isEnemy();


        // Reduce the health bar visual indicator counter ..

        objectI.update();

        if (objectI.getActive() == SpriteStatus::Active) { 


            // Dow we need to update the object?

            bool update = true;

            for (uint8_t j = 0; j < this->objects.getObjectNum(); j++) {

                auto &objectJ = this->objects.getSprite(j);

                if (objectJ.getActive() == SpriteStatus::Active) {


                    // If the enemy has collided with a flame or spear then decrease health ..

                    if (objectI.isEnemy() && (objectJ.getType() == Object::FireTOP || objectJ.getType() == Object::FireBOT) && collision(objectI, objectJ)) {

                        if (objectI.decHealth(Object::FireTOP)) {
                            playSoundEffect(SoundEffect::Death3);
                        }

                    }

                    if (objectI.isEnemy() && (objectJ.getType() == Object::SpikeLHS || objectJ.getType() == Object::SpikeRHS) && collision(objectI, objectJ)) {

                        if (objectI.decHealth(Object::SpikeLHS)) {
                            playSoundEffect(SoundEffect::Death3);
                        }

                    }

                    if (objectJ.isEnemy() && (objectI.getType() == Object::FireTOP || objectI.getType() == Object::FireBOT) && collision(objectI, objectJ)) {

                        if (objectI.decHealth(Object::FireTOP)) {
                            playSoundEffect(SoundEffect::Death3);
                        }

                    }

                    if (objectJ.isEnemy() && (objectI.getType() == Object::SpikeLHS || objectI.getType() == Object::SpikeRHS) && collision(objectI, objectJ)) {

                        if (objectJ.decHealth(Object::SpikeLHS)) {
                            playSoundEffect(SoundEffect::Death3);
                        }

                    }


                    // If the enemy has collided with another enemy then do not update the position ..

                    if (i < j && objectI_IsEnemy && objectJ.isEnemy() && this->collision(objectI, objectJ)) {

                        update = false;

                    }


                    // If an enemy has collided with an object then pick it up ..

                    if (i != j && objectI_IsEnemy && objectJ.isCarryable() && this->collision(objectI, objectJ)) {

                        if (objectI.getCarrying() == Object::None) {

                            objectJ.setActive(SpriteStatus::Inactive);
                            objectI.setCarrying(objectJ.getType());
                            
                        }

                    }

                }

            }


            if (!objectI_IsEnemy || (objectI_IsEnemy && update && this->levelStartDelay == 0)) { this->spriteAI(map, player, objectI); }


            // Has a collision between the object and player occured ?

            if (!objectI.getPreventImmediatePickup() && this->collision(player, objectI)) {

                uint16_t note = 0;
                uint16_t duration = 0;
                uint8_t type = objectI.getType();

                switch (type) {

                    case Object::Coin: 
                        player.incCoins(1); 
                        objectI.setActive(SpriteStatus::Inactive); 
                        playSoundEffect(SoundEffect::PickUpCoin);
                        break;

                    case Object::SackOCash: 
                        player.incCoins(5); 
                        objectI.setActive(SpriteStatus::Inactive); 
                        playSoundEffect(SoundEffect::PickUpCoin);
                        break;

                    case Object::Key:
                    case Object::Bread:
                    case Object::Chicken:
                    case Object::Tools:
                    case Object::Tonic:
                    case Object::IceSpell:
                    case Object::MauveSpell:
                        {
                            uint8_t slot = this->player.addInventoryItem(static_cast<Object>(type), 1);

                            if (slot != NO_SLOT_FOUND) {
                                objectI.setActive(SpriteStatus::Inactive);
                                playSoundEffect(SoundEffect::PickUpCoin);
                            }
                            else {
                                playSoundEffect(SoundEffect::CannotPickUp);
                            }

                        }
                        break;

                    case Object::GreenSpell:
                    case Object::RedSpell:
                        {
                            uint8_t slot = this->player.addInventoryItem(static_cast<Object>(type), objectI.getQuantity());

                            if (slot != NO_SLOT_FOUND) {
                                objectI.setActive(SpriteStatus::Inactive);
                                playSoundEffect(SoundEffect::PickUpCoin);
                            }
                            else {
                                playSoundEffect(SoundEffect::CannotPickUp);
                            }

                        }
                        break;

                    case Object::Eye:
                    case Object::Spider:
                    case Object::BigSpider:
                    case Object::Bat:
                    case Object::Skeleton:
                    case Object::SpikeLHS:
                    case Object::SpikeRHS:
                    case Object::FireTOP:
                    case Object::FireBOT:
                    case Object::Snake:
                    case Object::Necromancer:
                    case Object::Hobgoblin:
                    case Object::Cyclop:
                    case Object::Beholder:

                        if (!ignorePlayerDamage) {
                                
                            if (this->shake < 3) {
                                this->shake = this->shake + 2;
                            }

                            if (PC::frameCount % 4 == 0) { 

                                player.decHealth(object_DamageOnPlayer[static_cast<uint8_t>(type)] + (this->cookieSaveGame->gameC ? object_DamageOnPlayer[static_cast<uint8_t>(type)] / 2 : 0) );
                                playSoundEffect(SoundEffect::Death1);

                            }

                        }

                        break;
                        
                }

            }

        }

    }


    // Have the bullets hit anything ?

    for (uint8_t bulletIdx = 0; bulletIdx < PLAYER_BULLET_MAX + ENEMY_BULLET_MAX + BOSS_BULLET_MAX; bulletIdx++) {

        auto &bullet = bullets.getBullet(bulletIdx);
        
        if (bullet.getActive()) {

            uint8_t width = bullet.getWidth();
            uint8_t height = bullet.getHeight();

            Direction xDirection = this->getNearestCardinalDirection(bullet.getDirection(), Axis::XAxis);
            Direction yDirection = this->getNearestCardinalDirection(bullet.getDirection(), Axis::YAxis);

            uint16_t rx = bullet.getX();
            uint16_t ry = bullet.getY();

            bullet.update();


            // If the bullet has hit a wall or other fixed object ..

            if (xDirection != Direction::None && this->map.isWalkable(bullet.getX(), ry, xDirection, width, height) == WalkType::Stop) {

                if (bullet.getWeapon() == Object::SpiderWeb) {
                    bullet.setX(rx);
                    bullet.setDirection(Direction::None);
                }
                else {
                    bullet.setActive(false);
                }

            }

            if (yDirection != Direction::None && bullet.getActive() && this->map.isWalkable(rx, bullet.getY(), yDirection, width, height) == WalkType::Stop) {

                if (bullet.getWeapon() == Object::SpiderWeb) {
                    bullet.setY(ry);
                    bullet.setDirection(Direction::None);
                }
                else {
                    bullet.setActive(false);
                }

            }

            static PROGMEM const int8_t bullet_XMovement[8] = { 0, 5, 5, 5, 0, -5, -5, -5 };
            static PROGMEM const int8_t bullet_YMovement[8] = { -5, -5, 0, 5, 5, 5, 0, -5 };


            // Did we just break a barrel ?

            if (!bullet.getActive()) {

                uint8_t direction = static_cast<uint8_t>(bullet.getDirection());
                rx = rx + bullet_XMovement[direction];
                ry = ry + bullet_YMovement[direction];

                if (this->map.getBlock(this->map.getTileX(rx), this->map.getTileY(ry)) == MapTiles::Barrel) {

                    barrelBreak(map, this->map.getTileX(rx), this->map.getTileY(ry), this->objects);

                    static PROGMEM const uint8_t randomLimit[12] = { BARREL_RANDOM_NOTHING, BARREL_RANDOM_COIN, BARREL_RANDOM_SACK, BARREL_RANDOM_BREAD, BARREL_RANDOM_CHICKEN, }; 
                    static PROGMEM const uint8_t randomItems[11] = { Object::None,                Object::Coin,  Object::SackOCash,       Object::Bread,       Object::Chicken, };

                    uint8_t randObject = random(0, BARREL_RANDOM_CHICKEN);
                    uint8_t object = 0;

                    for (uint8_t x = 0; x < 12; x++) {

                        if  (randObject <= randomLimit[x]) {

                            object = randomItems[x];
                            break;

                        }

                    }

                    // Find a matching Object in the sprites collecion that is disabled, otherwise add one ..

                    if (object != Object::None) {

                        uint8_t spriteIdx = this->objects.getFirstInactiveSpriteIndex(static_cast<Object>(object));

                        if (spriteIdx == NO_SPRITE_FOUND) {

                            if (this->objects.getObjectNum() < MAXOBJECT - 1) {

                                this->objects.setObjectNum(this->objects.getObjectNum() + 1);
                                spriteIdx = this->objects.getObjectNum() - 1;

                            }

                        }   

                        if (spriteIdx != NO_SPRITE_FOUND) {

                            Sprite &sprite = this->objects.getSprite(spriteIdx);
                            sprite.setSprite((this->map.getTileX(rx) * TILE_SIZE) + 8, (this->map.getTileY(ry) * TILE_SIZE) + 8, 0, static_cast<Object>(object), SpriteStatus::Active, true);

                        }

                    }

                } 

            }
            else {

                switch (bulletIdx) {
                    

                    // Did the bullet hit an enemy?  Test only id it is a player bullet ..

                    case 0 ... PLAYER_BULLET_MAX - 1:

                        for (uint8_t i = 0; i < this->objects.getObjectNum(); i++) {

                            auto &object = this->objects.getSprite(i);


                            // Did we hit an enemy?
                            
                            if (object.getActive() == SpriteStatus::Active && object.isEnemy() && this->collision(object, bullet)) {

                                if (object.decHealth(bullet.getWeapon())) {
                                    playSoundEffect(SoundEffect::Death3);
                                }

                                bullet.setActive(false);

                                if (object.getActive() != SpriteStatus::Active) {

                                    player.setKills(this->player.getKills() + 1);

                                    if (object.getCarrying() != Object::None) {
                                        dropItem(object.getCarrying(), object.getX(), object.getY(), true, &object, this->objects);
                                    }


                                    // Did we kill a boss ?

                                    if (object.isBoss()) {

                                        this->player.incAltarPieces();
                                        this->nextState = GameState::AltarPieceAchieved;
                                        this->changeStateDelay = 24;
                                        break;
                                            
                                    }

                                }

                            }

                        }

                        break;


                    // Did the bullet hit the player?  Test only if it is an enemy bullet ..

                    case PLAYER_BULLET_MAX ... PLAYER_BULLET_MAX + ENEMY_BULLET_MAX + BOSS_BULLET_MAX:

                        if (this->collision(this->player, bullet)) {

                            //sound shot, ouch!

                            if (this->shake < 3) {
                                this->shake = this->shake + 2;
                            }

                            this->player.decHealth(DAMAGE_BULLET + (this->cookieSaveGame->gameC ? DAMAGE_BULLET / 2 : 0));
                            playSoundEffect(SoundEffect::Death1);
                            bullet.setActive(false);


                        }

                        break;

                }

            }

        }

    }

}


void Game::updateGame(GameMode gameMode) {
    
    const uint8_t offX[4] = { 1, 0,};
    const uint8_t offY[4] = { 0, 1 };

    if (player.getHealth() > 0) {

        if (Pokitto::Core::frameCount % TIMER_STEP == 0) { this->map.decTimer();  }
        this->playerMovement(gameMode);

    }

    this->updateObjects(player.getHealth() <= 0);

    if (this->shake > 0) {
        this->renderEnvironment(!this->map.isBossLevel() && !this->map.isAltarLevel(), offX[(this->shake - 1) % 2], offY[(this->shake - 1) % 2]);
        this->renderPlayer(offX[(this->shake - 1) % 2], offY[(this->shake - 1) % 2]);
    }
    else {
        this->renderEnvironment(!this->map.isBossLevel() && !this->map.isAltarLevel(), 0, 0);
        this->renderPlayer(0, 0);
    }

    this->renderObjects();
    this->renderHud();

    if (player.getHealth() <= 0) {

        this->player.decPuffIndex();

        if (this->player.getPuffIndex() == PLAYER_DEAD_DELAY || PC::buttons.pressed(BTN_A)) {

            ////aPS::playSFX(Sounds::sfx_Death5, Sounds::sfx_Death5_length); 
            gameState = GameState::Dead;

        }

    }

}

bool Game::isBlockedByEnemy(Player player, uint16_t playerX, uint16_t playerY) {

    Rect playerRect = { playerX - (player.getWidth() / 2), playerY - (player.getHeight() / 2), player.getWidth(), player.getHeight() };

    for (uint8_t i = 0; i < this->objects.getObjectNum(); i++) {

        auto &object = this->objects.getSprite(i);

        if (object.getActive() == SpriteStatus::Active && object.isEnemy()) {
            
            Rect objectRect = object.getRect();

            if (collide(playerRect, objectRect)) return true;

        }

    }

    return false;

}

bool Game::isBlockedBySolidSprite(Player player, uint16_t playerX, uint16_t playerY) {

    Rect playerRect = { playerX - (player.getWidth() / 2) + 2, playerY - (player.getHeight() / 2) + 2, player.getWidth() - 4, player.getHeight() - 4 };

    for (uint8_t i = 0; i < this->objects.getObjectNum(); i++) {

        auto &object = this->objects.getSprite(i);

        if (object.getActive() == SpriteStatus::Active && object.isSolidSprite()) {
            
            Rect objectRect = object.getRect();

            if (collide(playerRect, objectRect)) return true;

        }

    }

    return false;

}

bool Game::isBlockedByPlayer(Player player, Sprite enemy, uint16_t enemyX, uint16_t enemyY) {
   
    Rect enemyRect = { enemyX - (enemy.getWidth() / 2), enemyY - (enemy.getHeight() / 2), enemy.getWidth(), enemy.getHeight() };
    return collide(player.getRect(), enemyRect);

}

void Game::playerMovement_Up(Direction &direction, uint16_t &x, uint16_t &y, bool &moving, bool &nudgeUp, bool &nudgeDown, bool &nudgeLeft, bool &nudgeRight) {

    WalkType walk = this->map.isWalkable(x, y - 2, Direction::Up, this->player.getWidth(), this->player.getHeight(), nudgeUp, nudgeDown, nudgeLeft, nudgeRight);

    if ((walk == WalkType::Normal || (walk == WalkType::Slow && PC::frameCount % WALK_SLOW_FRAME_COUNT == 0)) && !isBlockedByEnemy(this->player, x, y - 2) && !isBlockedBySolidSprite(this->player, x, y - 2)) {
        
        y-=2;
        moving = true;

        if (walk == WalkType::Slow) {
            player.decHealth(HEALTH_DEC_SPIDERS_WEB + (this->cookieSaveGame->gameC ? HEALTH_DEC_SPIDERS_WEB / 2 : 0)); 
        }

    }

    switch (direction) {

        case Direction::Left:
            direction = Direction::UpLeft;
            break;

        case Direction::Right:
            direction = Direction::UpRight;
            break;

        default:
            direction = Direction::Up;
            break;
            
    }

}

void Game::playerMovement_Down(Direction &direction, uint16_t &x, uint16_t &y, bool &moving, bool &nudgeUp, bool &nudgeDown, bool &nudgeLeft, bool &nudgeRight) {

    WalkType walk = this->map.isWalkable(x, y + 2, Direction::Down, this->player.getWidth(), this->player.getHeight(), nudgeUp, nudgeDown, nudgeLeft, nudgeRight);

    if ((walk == WalkType::Normal || (walk == WalkType::Slow && PC::frameCount % WALK_SLOW_FRAME_COUNT == 0)) && !isBlockedByEnemy(this->player, x, y + 2) && !isBlockedBySolidSprite(this->player, x, y + 2)) {

        y+=2;
        moving = true;

        if (walk == WalkType::Slow) {
            player.decHealth(HEALTH_DEC_SPIDERS_WEB + (this->cookieSaveGame->gameC ? HEALTH_DEC_SPIDERS_WEB / 2 : 0)); 
        }

    }

    switch (direction) {

        case Direction::Left:
            direction = Direction::DownLeft;
            break;

        case Direction::Right:
            direction = Direction::DownRight;
            break;

        default:
            direction = Direction::Down;
            break;
            
    }

}

void Game::playerMovement_Right(Direction &direction, uint16_t &x, uint16_t &y, bool &moving, bool &nudgeUp, bool &nudgeDown, bool &nudgeLeft, bool &nudgeRight) {

    WalkType walk = this->map.isWalkable(x + 2, y, Direction::Right, this->player.getWidth(), this->player.getHeight(), nudgeUp, nudgeDown, nudgeLeft, nudgeRight);

    if ((walk == WalkType::Normal || (walk == WalkType::Slow && PC::frameCount % WALK_SLOW_FRAME_COUNT == 0)) && !isBlockedByEnemy(this->player, x + 2, y) && !isBlockedBySolidSprite(this->player, x + 2, y)) {

        x+=2;
        moving = true;

        if (walk == WalkType::Slow) {
            player.decHealth(HEALTH_DEC_SPIDERS_WEB + (this->cookieSaveGame->gameC ? HEALTH_DEC_SPIDERS_WEB / 2 : 0)); 
        }

    }
    else {

        if (nudgeUp)    playerMovement_Up(direction, x, y, moving, nudgeUp, nudgeDown, nudgeLeft, nudgeRight);
        if (nudgeDown)  playerMovement_Down(direction, x, y, moving, nudgeUp, nudgeDown, nudgeLeft, nudgeRight);

    }

    switch (direction) {

        case Direction::Up:
            direction = Direction::UpRight;
            break;

        case Direction::Down:
            direction = Direction::DownRight;
            break;

        default:
            direction = Direction::Right;
            break;
            
    }

}

void Game::playerMovement_Left(Direction &direction, uint16_t &x, uint16_t &y, bool &moving, bool &nudgeUp, bool &nudgeDown, bool &nudgeLeft, bool &nudgeRight) {

    WalkType walk = this->map.isWalkable(x - 2, y, Direction::Left, this->player.getWidth(), this->player.getHeight(), nudgeUp, nudgeDown, nudgeLeft, nudgeRight);

    if ((walk == WalkType::Normal || (walk == WalkType::Slow && PC::frameCount % WALK_SLOW_FRAME_COUNT == 0)) && !isBlockedByEnemy(this->player, x - 2, y) && !isBlockedBySolidSprite(this->player, x - 2, y)) {

        x-=2;
        moving = true;

        if (walk == WalkType::Slow) {
            player.decHealth(HEALTH_DEC_SPIDERS_WEB + (this->cookieSaveGame->gameC ? HEALTH_DEC_SPIDERS_WEB / 2 : 0)); 
        }

    }
    else {

        if (nudgeUp)    playerMovement_Up(direction, x, y, moving, nudgeUp, nudgeDown, nudgeLeft, nudgeRight);
        if (nudgeDown)  playerMovement_Down(direction, x, y, moving, nudgeUp, nudgeDown, nudgeLeft, nudgeRight);

    }

    switch (direction) {

        case Direction::Up:
            direction = Direction::UpLeft;
            break;

        case Direction::Down:
            direction = Direction::DownLeft;
            break;

        default:
            direction = Direction::Left;
            break;
            
    }

}

void Game::playerMovement(GameMode gameMode) {

    uint16_t x = player.getX();
    uint16_t y = player.getY();
    Direction direction = player.getDirection();

    bool moving = player.getMoving();
    bool nudgeUp = false;
    bool nudgeDown = false;
    bool nudgeLeft = false;
    bool nudgeRight = false;

    moving = false;

    if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 1)) {

        playerMovement_Up(direction, x, y, moving, nudgeUp, nudgeDown, nudgeLeft, nudgeRight);

    }

    else if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 1)) {

        playerMovement_Down(direction, x, y, moving, nudgeUp, nudgeDown, nudgeLeft, nudgeRight);

    }

    if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1) || (nudgeRight && !moving)) {

        playerMovement_Right(direction, x, y, moving, nudgeUp, nudgeDown, nudgeLeft, nudgeRight);

    }
    
    if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1) || (nudgeLeft && !moving) ) {

        playerMovement_Left(direction, x, y, moving, nudgeUp, nudgeDown, nudgeLeft, nudgeRight);

    }   

    player.setX(x);
    player.setY(y);
    player.setDirection(direction);
    player.setMoving(moving);

    if (moving) {    
        
        int relx = this->map.getTileX(x);
        int rely = this->map.getTileY(y);
        uint8_t ofx = this->map.getTileXOffset(x);
        uint8_t ofy = this->map.getTileYOffset(y);
        uint8_t block = this->map.getBlock(relx, rely);

        if (this->map.between(3, 3, 11, 11, ofx, ofy) && block == MapTiles::PressPlate_Up) {
            this->map.setBlock(relx,rely,MapTiles::PressPlate_Down);
            updateEnvironmentBlock(map, relx, rely, this->environments);
            playSoundEffect(SoundEffect::PressPlate);
        }


        // If the player has moved, then any object he may have previously dropped will be available for pickup once the player has moved off the tile ..

        this->objects.clearPreventImmediatePickup(player);

    }


    // Shoot a bullet ?

    if (PC::buttons.pressed(BTN_B)) {

        const int32_t xOffsets[8] = { 0, 2, 2, 2, 0, -2, -2, -2 };
        const int32_t yOffsets[8] = { -6, -6, 0, 6, 6, 6, 0, -2 };


        switch (this->player.getWeapon()) {

            case Object::FireBall:
                {
                    uint8_t inactiveBulletIdx = this->bullets.getInactivePlayerBullet();

                    if (inactiveBulletIdx != NO_INACTIVE_BULLET_FOUND) {

                        Bullet &bullet = this->bullets.getPlayerBullet(inactiveBulletIdx);
                        bullet.setBullet(x + xOffsets[static_cast<uint8_t>(direction)], y + yOffsets[static_cast<uint8_t>(direction)], direction, this->player.getWeapon(), BULLET_FIREBALL_FRAMES);

                    }
                }
                break;

            case Object::IceSpell:
                {
                    uint8_t inactiveBulletIdx = this->bullets.getInactivePlayerBullet();

                    if (inactiveBulletIdx != NO_INACTIVE_BULLET_FOUND) {

                        Bullet &bullet = this->bullets.getPlayerBullet(inactiveBulletIdx);
                        bullet.setBullet(x + xOffsets[static_cast<uint8_t>(direction)], y + yOffsets[static_cast<uint8_t>(direction)], direction, this->player.getWeapon(), BULLET_ICESPELL_FRAMES);

                        uint8_t slot = this->player.getInventorySlot(this->player.getWeapon());
                        InventoryItem &inventoryItem = this->player.getInventoryItem(slot);

                    }

                }
                break;

            case Object::GreenSpell:
            case Object::RedSpell:
                {
                    uint8_t inactiveBulletIdx = this->bullets.getInactivePlayerBullet();

                    if (inactiveBulletIdx != NO_INACTIVE_BULLET_FOUND) {

                        Bullet &bullet = this->bullets.getPlayerBullet(inactiveBulletIdx);
                        bullet.setBullet(x + xOffsets[static_cast<uint8_t>(direction)], y + yOffsets[static_cast<uint8_t>(direction)], direction, this->player.getWeapon(), BULLET_GREENRED_FRAMES);

                        uint8_t slot = this->player.getInventorySlot(this->player.getWeapon());
                        InventoryItem &inventoryItem = this->player.getInventoryItem(slot);

                        inventoryItem.quantity--;

                        if (inventoryItem.quantity == 0) {
                            this->player.setWeapon(Object::FireBall);
                        }

                    }

                }
                break;

            case Object::MauveSpell:
                {
                    int16_t xMin = this->player.getX() - 55;
                    int16_t xMax = this->player.getX() + 55;
                    int16_t yMin = this->player.getY() - 36;
                    int16_t yMax = this->player.getY() + 36;

                    for (uint8_t i = 0; i < this->objects.getObjectNum(); i++) {

                        auto &object = this->objects.getSprite(i);

                        if (object.getActive() == SpriteStatus::Active && object.isEnemy() && object.getX() >= xMin && object.getX() <= xMax && object.getY() >= yMin & object.getY() <= yMax) {

                            bool isDead = object.decHealth(Object::MauveSpell);


                            // Did we kill a boss ?

                            if (isDead && object.isBoss()) {
                                
                                this->player.incAltarPieces();
                                this->nextState = GameState::AltarPieceAchieved;
                                this->changeStateDelay = 24;
                                break;
                                    
                            }

                        }

                    }
                    
                    uint8_t slot = this->player.getInventorySlot(this->player.getWeapon());
                    InventoryItem &inventoryItem = this->player.getInventoryItem(slot);

                    inventoryItem.quantity--;
                    this->shockwave = 9;

                    if (inventoryItem.quantity == 0) {
                        this->player.setWeapon(Object::FireBall);
                    }

                }
                break;


        }

  
    }


    // Display Inventory?

    if (PC::buttons.pressed(BTN_C)) {

        this->gameState = GameState::Inventory;
        this->inventoryMenu.mode = InventoryMenuMode::Inventory;
        this->inventoryMenu.mainCursor = 0;
  
    }


    // Display Map Details ..

    #ifdef DEBUG

        if (PC::buttons.pressed(BTN_A) && PC::buttons.pressed(BTN_C)) {

            this->gameState = GameState::MapDetails;
    
        }

    #endif
    

    // Operate lever, open door, fix things ..

    if (PC::buttons.pressed(BTN_A)) {



        // Interaction with objects ..

        for (uint8_t i = 0; i < this->objects.getObjectNum(); i++) {
            auto &object = this->objects.getSprite(i);
            if (object.getActive() == SpriteStatus::Active && this->collision(this->player, object)) { 

                switch (object.getType()) {

                    case Object::Guide01 ... Object::Guide15:

                        object.setGuideText(false);
                        object.setPreventImmediatePickup(true);

                        if (PC::buttons.pressed(BTN_A) || PC::buttons.repeat(BTN_A, 1)) {

                            this->guideNumber = static_cast<uint8_t>(object.getType()) - static_cast<uint8_t>(Object::Guide01);
                            this->guide = &object;
                            this->guideTop = 0;
                            this->gameState = GameState::Guide;

                        }

                        break;

                }

            }

        }


        //


        int relx = this->map.getTileX(x);
        int rely = this->map.getTileY(y);
        MapTiles block = static_cast<MapTiles>(this->map.getBlock(relx, rely));

        switch (block) {

            case MapTiles::DownStairs:

                if (gameMode == GameMode::Normal) {


                    // Have we left a ruin behind?

                    if (this->map.getHasRune()) {
                        gameState = GameState::NeedRune;
                    }
                    else {

                        
                        // Is there a boss still alove?

                        bool boss = false;

                        for (uint8_t i = 0; i < this->objects.getObjectNum(); i++) {

                            auto &object = this->objects.getSprite(i);

                            if (object.getActive() == SpriteStatus::Active && object.isBoss()) {

                                boss = true;
                                break;

                            }

                        }

                        if (boss) {

                            gameState = GameState::NeedRune;

                        }
                        else {

                            //sound.tone(NOTE_C3,100,NOTE_E3,100,NOTE_G3,100);
                            gameState = GameState::EndOfLevel;

                        }

                    }

                }
                else {
                    this->gameState = GameState::MainMenu;
                    this->titleScreenVars.mode = TitleScreenMode::SelectOption;
                }
                break;

            case MapTiles::WormHole_F0:
                this->interactWithBlock(relx, rely, block);
                break;

            case MapTiles::Shop00 ... MapTiles::Shop05:
                this->gameState = GameState::Shop_Init_Music;
                break;

            case MapTiles::Altar00 ... MapTiles::Altar05:
                if (this->map.isAltarLevel()) { 
                    this->gameState = GameState::Puzzle_Init_Game;
                }
                break;


            default:

                switch(direction) {

                    case Direction::Up:         rely--;         break;
                    case Direction::UpRight:    relx++; rely--; break;
                    case Direction::Right:      relx++;         break;
                    case Direction::DownRight:  relx++; rely++; break;
                    case Direction::Down:       rely++;         break;
                    case Direction::DownLeft:   relx--; rely++; break;
                    case Direction::Left:       relx--;         break;
                    case Direction::UpLeft:     relx--; rely--; break;

                }

                block = static_cast<MapTiles>(this->map.getBlock(relx, rely));
                this->interactWithBlock(relx, rely, block);
                break;


        }

    }

}

// ----------------------------------------------------------------------
//   Handle player's interaction with a 'special' block.
//
//   Returns true if an element was changed.
//
bool Game::interactWithBlock(int x, int y, MapTiles block) {

    switch (block) {

        case MapTiles::SwitchOn: 

            this->map.setBlock(x, y, MapTiles::SwitchOff); 
            updateEnvironmentBlock(map, x, y, this->environments); 
            playSoundEffect(SoundEffect::LeverPull);
            
            return true;

        case MapTiles::SwitchOff: 

            this->map.setBlock(x, y, MapTiles::SwitchOn); 
            updateEnvironmentBlock(map, x, y, this->environments); 
            playSoundEffect(SoundEffect::LeverPull);

            return true;

        case MapTiles::ClosedChest_Key: 
            {
                this->map.setBlock(x, y, MapTiles::OpenChest); 
                playSoundEffect(SoundEffect::OpenChest);


                // Find a matching Object in the sprites collecion that is disabled, otherwise add one ..

                uint8_t spriteIdx = this->objects.getFirstInactiveSpriteIndex((block == MapTiles::ClosedChest_Key ? Object::Key : Object::Chest));

                if (spriteIdx == NO_SPRITE_FOUND) {

                    if (this->objects.getObjectNum() < MAXOBJECT - 1) {

                        this->objects.setObjectNum(this->objects.getObjectNum() + 1);
                        spriteIdx = this->objects.getObjectNum() - 1;

                    }

                }   

                if (spriteIdx != NO_SPRITE_FOUND) {

                    Sprite &sprite = this->objects.getSprite(spriteIdx);
                    sprite.setSprite((x * TILE_SIZE) + 8, (y * TILE_SIZE) + 8, 0, (block == MapTiles::ClosedChest_Key ? Object::Key : Object::Chest), SpriteStatus::Active, false);

                }

            }
            return true;

        case MapTiles::ClosedChest_Killer: 
            {
                this->map.setBlock(x, y, MapTiles::OpenChest); 
                playSoundEffect(SoundEffect::OpenChest);         



                // Find a matching Object in the sprites collecion that is disabled, otherwise add one ..

                uint8_t spriteIdx = this->objects.getFirstInactiveSpriteIndex((block == MapTiles::ClosedChest_Key ? Object::Key : Object::Chest));

                if (spriteIdx == NO_SPRITE_FOUND) {

                    if (this->objects.getObjectNum() < MAXOBJECT - 1) {

                        this->objects.setObjectNum(this->objects.getObjectNum() + 1);
                        spriteIdx = this->objects.getObjectNum() - 1;

                    }

                }   

                if (spriteIdx != NO_SPRITE_FOUND) {

                    Sprite &sprite = this->objects.getSprite(spriteIdx);
                    sprite.setSprite((x * TILE_SIZE) + 8, (y * TILE_SIZE) + 8, HEALTH_CHEST, (block == MapTiles::ClosedChest_Key ? Object::Key : Object::Chest), SpriteStatus::Active, false);
                    sprite.setCountdown(0);
                    sprite.setDirection(Direction::Down);
                    this->map.setBlock(x, y, MapTiles::Empty); 

                }

            }
            return true;

        case MapTiles::ClosedChest_Random: 
            {
                this->map.setBlock(x, y, MapTiles::OpenChest); 
                playSoundEffect(SoundEffect::OpenChest);  


                // random

                const uint8_t randomLimit[10] = { CHEST_RANDOM_COIN, CHEST_RANDOM_SACK, CHEST_RANDOM_BREAD, CHEST_RANDOM_CHICKEN, CHEST_RANDOM_TONIC, CHEST_RANDOM_ICE, CHEST_RANDOM_GREEN, CHEST_RANDOM_RED, CHEST_RANDOM_MAUVE, CHEST_RANDOM_END }; 
                const uint8_t randomItems[9] =  {      Object::Coin, Object::SackOCash,      Object::Bread,      Object::Chicken,      Object::Tonic,  Object::IceSpell, Object::GreenSpell, Object::RedSpell, Object::MauveSpell, };


                uint8_t randObject = random(0, CHEST_RANDOM_END);
                uint8_t object = 0;

                for (uint8_t x = 0; x < 12; x++) {

                    if  (randObject <= randomLimit[x]) {

                        object = randomItems[x];
                        break;

                    }

                }


                // Find a matching Object in the sprites collecion that is disabled, otherwise add one ..

                uint8_t spriteIdx = this->objects.getFirstInactiveSpriteIndex(static_cast<Object>(object));

                if (spriteIdx == NO_SPRITE_FOUND) {

                    if (this->objects.getObjectNum() < MAXOBJECT - 1) {

                        this->objects.setObjectNum(this->objects.getObjectNum() + 1);
                        spriteIdx = this->objects.getObjectNum() - 1;
                    
                    }

                }   

                if (spriteIdx != NO_SPRITE_FOUND) {

                    Sprite &sprite = this->objects.getSprite(spriteIdx);
                    sprite.setSprite((x * TILE_SIZE) + 8, (y * TILE_SIZE) + 8, 0, static_cast<Object>(object), SpriteStatus::Active, true);

                }

            }
            return true;

        case MapTiles::ClosedChest_Altar: 
            {
                this->map.setHasRune(false);
                this->map.setBlock(x, y, MapTiles::OpenChest); 
                playSoundEffect(SoundEffect::OpenChest);

                this->player.incAltarPieces();
                this->nextState = GameState::AltarPieceAchieved;
                this->changeStateDelay = 24;
            }
            return true;

        case MapTiles::LockedDoor: 

            if (this->player.getInventoryCount(Object::Key) > 0) {
                this->map.setBlock(x, y, MapTiles::OpenDoor); 
                this->player.decInventoryItem(Object::Key);
                playSoundEffect(SoundEffect::OpenChest);
                return true;
            } 
            else {
                playSoundEffect(SoundEffect::CannotPickUp);
                return false;
            }  

        case MapTiles::DoorLHS ... MapTiles::DoorBOT:

            if (this->player.getInventoryCount(Object::Key) > 0) {
                this->map.setBlock(x, y, static_cast<MapTiles>(block + MapTiles::DoorLHSOpen - MapTiles::DoorLHS)); 
                this->player.decInventoryItem(Object::Key);
                playSoundEffect(SoundEffect::OpenChest);
                return true;
            } 
            else {
                playSoundEffect(SoundEffect::CannotPickUp);
                return false;
            }  

        case MapTiles::LockedStairs: 

            if (this->player.getInventoryCount(Object::Key) > 0) {
                this->map.setBlock(x, y, MapTiles::DownStairs); 
                this->player.decInventoryItem(Object::Key);
                playSoundEffect(SoundEffect::OpenChest);
            } 
            else {
                playSoundEffect(SoundEffect::CannotPickUp);
            } 
            return true;

        case MapTiles::SwitchBroken: 

            if (this->player.getInventoryCount(Object::Tools) > 0) {
                this->map.setBlock(x, y, MapTiles::SwitchOff); 
                this->player.decInventoryItem(Object::Tools);
                // sound fix
                return true;
            } 
            else {
                playSoundEffect(SoundEffect::CannotPickUp);
                return false;
            } 

        case MapTiles::WormHole_F0:
            {
                for (uint8_t i = 0; i < this->environments.getEnvironmentNum(); i++) {

                    auto environment = this->environments.getEnvironment(i);

                    if (environment.getX() == x && environment.getY() == y) {

                        player.setX(environment.getFinishX() * TILE_SIZE + 8);
                        player.setY(environment.getFinishY() * TILE_SIZE + 8);
                        break;

                    }

                }

            }
            return false;

        case MapTiles::SavePost:
            this->cookieSaveGame->updateStatus(map.getLevel(), map.getDefinedMapLevel(), this->playerStatus);
            this->cookieSaveGame->saveCookie();
            this->gameState = GameState::GameSaved;
            this->titleScreenVars.option = TitleScreenOption::Resume;
            return false;

        case MapTiles::Altar00 ... MapTiles::Altar05:
            if (this->map.isAltarLevel()) { 
                this->gameState = GameState::Puzzle_Init_Game;
            }
            break;

    }

    return false;

}


void Game::updateEnvironmentBlock(MapInformation map, uint8_t x, uint8_t y, Environments &environments) {

    for (int i = 0; i < this->environments.getEnvironmentNum(); i++) {

        auto environment = this->environments.getEnvironment(i);

        if (environment.checkStart(x,y) && environment.getActive()) {

            uint8_t x1 = environment.getFinishX();
            uint8_t y1 = environment.getFinishY();

            MapTiles mapTile = this->map.getBlock(x1, y1);
            
            switch(mapTile) {

                case MapTiles::SpearDoor: 
                    this->map.setBlock(x1, y1, MapTiles::OpenDoor); 
                    break;

                case MapTiles::SpearDoorLHS ... MapTiles::SpearDoorBOT: 
                    this->map.setBlock(x1, y1, static_cast<MapTiles>(mapTile + (MapTiles::SpearDoorLHSOpen - MapTiles::SpearDoorLHS))); 
                    break;

                case MapTiles::SpearDoorLHSOpen ... SpearDoorBOTOpen: 
                    this->map.setBlock(x1, y1, static_cast<MapTiles>(mapTile - (MapTiles::SpearDoorLHSOpen - MapTiles::SpearDoorLHS))); 
                    break;
               
                case MapTiles::OpenDoor: 
//                    this->map.setBlock(x1, y1, MapTiles::SpearDoor); 
                    this->map.setBlock(x1, y1, environment.getTile()); 
                    break;

                case MapTiles::LockedStairs: 
                    this->map.setBlock(x1, y1, MapTiles::DownStairs); 
                    break;

                case MapTiles::DownStairs: 
                    this->map.setBlock(x1, y1, MapTiles::LockedStairs); 
                    break;

                case MapTiles::ExplosiveBarrel: 
                    this->map.setBlock(x1, y1, MapTiles::Rubble); 
                    break;

                case MapTiles::DoorLHSOpen: 
                    this->map.setBlock(x1, y1, MapTiles::DoorLHS); 
                    break;

            }

        }

    }

}

void Game::dropItem(Object droppedObject, uint16_t x, uint16_t y, bool enemyDrop, Sprite *enemy, Sprites &objects) {

    bool slotFound = false;
    uint8_t slotIndex = 0;
    

    // Find the first empty slot ..

    for (uint8_t i = 0; i < objects.getObjectNum(); i++) {

        auto &obj = this->objects.getSprite(i);
        
        if (obj.getActive() != SpriteStatus::Active) {
            slotFound = true;
            slotIndex = i;
            break;
        }

    }

    if (this->objects.getObjectNum() == MAXOBJECT && !slotFound) return;


    // If no disabled slot was found, then select the next available one in the collection ..

    if (this->objects.getObjectNum() < MAXOBJECT - 1) {

        uint8_t slotIndex = this->objects.getObjectNum();
        this->objects.setObjectNum(slotIndex + 1);
        
    }
    

    // Retrieve the sprite object and populate ..

    auto &object = this->objects.getSprite(slotIndex);

    if (enemyDrop) {

        object.setSprite(x, y, 1, static_cast<Object>(droppedObject), SpriteStatus::Active, true);
        
    }
    else{

        object.setSprite(x, y, 1, static_cast<Object>(droppedObject), SpriteStatus::Active, false);

    }
    
}


void Game::spriteAI(MapInformation &map, Player &player, Sprite &sprite) {

    Point location;
    location.x = sprite.getX();
    location.y = sprite.getY();
        
    switch(sprite.getType()) {

        case Object::Key: 

            spriteAI_UpdateFrame(sprite, 8, 10);
            break;

        case Object::Coin: 
            spriteAI_UpdateFrame(sprite, 4, 6);
            break;

        case Object::Eye:     

            spriteAI_UpdateFrame(sprite, 4, 2);
            spriteAI_CheckForMove(map, player, sprite, location, 10);
            break;

        case Object::Snake:
        case Object::Bat: 
        case Object::Chest: 
        case Object::Skeleton: 

            spriteAI_UpdateFrame(sprite, 4, 2);
            spriteAI_CheckForMove(map, player, sprite, location, 10);
            break;


        case Object::BigSpider: 
            {
    
                spriteAI_UpdateFrame(sprite, 4, 2);
                Direction direction = spriteAI_CheckForMove(map, player, sprite, location, 12);

                if (direction != Direction::None && this->launchSpiderDelay == 0) {


                    // Launch a new spider ..

                    // Find a matching Object in the sprites collecion that is disabled, otherwise add one ..

                    uint8_t spriteIdx = this->objects.getFirstInactiveSpriteIndex(Object::Spider);

                    if (spriteIdx == NO_SPRITE_FOUND) {

                        if (this->objects.getObjectNum() < MAXOBJECT - 1) {

                            this->objects.setObjectNum(this->objects.getObjectNum() + 1);
                            spriteIdx = this->objects.getObjectNum() - 1;

                        }

                    }   

                    if (spriteIdx != NO_SPRITE_FOUND) {
                            
                        Sprite &sprite = this->objects.getSprite(spriteIdx);


                        // Make sure we can launch the spider in a clear spot and not on top of the player ..

                        const int8_t launchSpider_X[] = { 0, 18, 18, 18, 18, -18, -18, -18 };
                        const int8_t launchSpider_Y[] = { -18, -18, 0, 18, 18, 18, 0, -18 };
                        const int8_t directions[] = { 8, 9, 7, 10, 6, 11, 5, 4 };

                        for (uint8_t d = 0; d < 7; d++) {

                            int launchX = location.x + launchSpider_X[(static_cast<uint8_t>(direction) + directions[d]) % 8];
                            int launchY = location.y + launchSpider_Y[(static_cast<uint8_t>(direction) + directions[d]) % 8];

                            uint8_t width = spriteWidths[static_cast<uint8_t>(Object::Spider)];
                            uint8_t height = spriteHeights[static_cast<uint8_t>(Object::Spider)];
                            sprite.setSprite(launchX, launchY, HEALTH_SPIDER, Object::Spider, SpriteStatus::Inactive, false);

                            if (map.isWalkable(launchX, launchY, direction, width, height) != WalkType::Stop && !collision(this->player, sprite)) {

                                sprite.setFrame(-PUFF_FRAME_MAX + 1);
                                sprite.setCountdown(0);
                                sprite.setDirection(direction);
                                sprite.setActive(SpriteStatus::Active);

                                break;

                            }

                        }



                        // Should the enemy create a new spider ?

                        this->launchSpiderDelay = random(LAUNCH_SPIDER_DELAY_MIN, LAUNCH_SPIDER_DELAY_MAX);

                    }

                }

            }
            break;

        case Object::Necromancer: 
            {
                switch (sprite.getFrame()) {

                    case -100 ... -2:
                        sprite.incFrame();
                        break;

                    case -1:    // launch a Skeleton
                        {
                            sprite.incFrame();


                            // Find a matching Object in the sprites collecion that is disabled, otherwise add one ..

                            uint8_t spriteIdx = this->objects.getFirstInactiveSpriteIndex(Object::Skeleton);

                            if (spriteIdx == NO_SPRITE_FOUND) {

                                if (this->objects.getObjectNum() < MAXOBJECT - 1) {

                                    this->objects.setObjectNum(this->objects.getObjectNum() + 1);
                                    spriteIdx = this->objects.getObjectNum() - 1;

                                }

                            }   

                            if (spriteIdx != NO_SPRITE_FOUND) {

                                Sprite &spriteNew = this->objects.getSprite(spriteIdx);


                                // Make sure we can launch the skeleton in a clear spot and not on top of the player ..

                                const int8_t launchSkeleton_X[] = { 0, 13, 13, 13, 13, -13, -13, -13 };
                                const int8_t launchSkeleton_Y[] = { -13, -13, 0, 13, 13, 13, 0, -13 };
                                const int8_t directions[] = { 8, 9, 7, 10, 6, 11, 5, 4 };

                                for (uint8_t d = 0; d < 7; d++) {

                                    int launchX = location.x + launchSkeleton_X[(static_cast<uint8_t>(this->launchSkeletonDirection) + directions[d]) % 8];
                                    int launchY = location.y + launchSkeleton_Y[(static_cast<uint8_t>(this->launchSkeletonDirection) + directions[d]) % 8];

                                    uint8_t tileLaunchX = this->map.getTileX(launchX);
                                    uint8_t tileLaunchY = this->map.getTileX(launchY);
                                    
                                    launchX = (tileLaunchX * TILE_WIDTH) + spriteWidths[sprite.getType()];
                                    launchY = (tileLaunchY * TILE_HEIGHT) + spriteHeights[sprite.getType()];

                                    spriteNew.setSprite(launchX, launchY, HEALTH_SKELETON, Object::Skeleton, SpriteStatus::Inactive, false);

                                    if (map.getBlock(tileLaunchX, tileLaunchY) == MapTiles::Empty && !collision(spriteNew, sprite)) {

                                        spriteNew.setFrame(-SKELETON_FRAME_MAX + 1);
                                        spriteNew.setCountdown(0);
                                        spriteNew.setDirection(Direction::Down);
                                        spriteNew.setActive(SpriteStatus::Active);
                                        break;

                                    }

                                }

                            }

                        }
                        break;

                    case 0 ... 100:
                        {
                            spriteAI_UpdateFrame(sprite, 4, 2);
                            Direction direction = spriteAI_CheckForMove(map, player, sprite, location, 12);

                            if (direction != Direction::None && this->launchSkeletonDelay == 0) {


                                // Should the enemy summons a skeleton ?

                                sprite.setFrame(-NECROMANCER_FRAME_MAX + 1);
                                this->launchSkeletonDirection = direction;
                                this->launchSkeletonDelay = random(LAUNCH_SKELETON_DELAY_MIN, LAUNCH_SKELETON_DELAY_MAX);

                            }

                        }
                        break;

                }

            }
            break;

        case Object::Spider:   
            {
                if (sprite.getFrame() < 0) {

                    sprite.incFrame();

                }
                else {

                    spriteAI_UpdateFrame(sprite, 4, 2);
                    Direction direction = spriteAI_CheckForMove(map, player, sprite, location, 10);

                    if (direction != Direction::None) {


                        // Should the enemy shoot a bullet?

                        if (this->enemyBulletDelay == 0 && random(0, 4) == 0) {

                            const int32_t xOffsets[8] = { 0, 4, 4, 4, 0, -4, -4, -4 };
                            const int32_t yOffsets[8] = { -4, -4, 0, 4, 4, 4, 0, -4 };

                            uint8_t inactiveBulletIdx = this->bullets.getInactiveEnemyBullet();

                            if (inactiveBulletIdx != NO_INACTIVE_BULLET_FOUND) {

                                Bullet &bullet = this->bullets.getEnemyBullet(inactiveBulletIdx);
                                bullet.setBullet(sprite.getX() + xOffsets[static_cast<uint8_t>(direction)], sprite.getY() + yOffsets[static_cast<uint8_t>(direction)], direction, Object::SpiderWeb, BULLET_WEB_FRAMES);
                                this->enemyBulletDelay = random(ENEMY_BULLET_DELAY_MIN, ENEMY_BULLET_DELAY_MAX);

                            }

                        }

                    }

                }

            }
            
            break;

        case Object::Hobgoblin:   
            {
                if (sprite.getFrame() < 0) {

                    sprite.incFrame();

                }
                else {

                    spriteAI_UpdateFrame(sprite ,4, 2);
                    Direction direction = spriteAI_CheckForMove(map, player, sprite, location, 10);

                    if (direction != Direction::None) {


                        // Should the enemy shoot a bullet?

                        if (this->enemyBulletDelay == 0 && random(0, 4) == 0 && direction != Direction::None) {

                            const int32_t xOffsets[8] = { 0, 6, 6, 6, 0, -6, -6, -6 };
                            const int32_t yOffsets[8] = { -6, -6, 0, 6, 6, 6, 0, -6 };

                            uint8_t inactiveBulletIdx = this->bullets.getInactiveEnemyBullet();

                            if (inactiveBulletIdx != NO_INACTIVE_BULLET_FOUND) {

                                Bullet &bullet = this->bullets.getEnemyBullet(inactiveBulletIdx);
                                bullet.setBullet(sprite.getX() + xOffsets[static_cast<uint8_t>(direction)], sprite.getY() + yOffsets[static_cast<uint8_t>(direction)], direction, Object::FireBall, BULLET_FIREBALL_FRAMES);
                                this->enemyBulletDelay = random(ENEMY_BULLET_DELAY_MIN, ENEMY_BULLET_DELAY_MAX);

                            }

                        }
                        
                    }

                }

            }

            break;

        case Object::Cyclop:   
            {
                switch (sprite.getFrame()) {

                    case -100 ... -15:
                    case -13 ... -1:
                        sprite.incFrame();
                        break;

                    case -14:    // launch sparks
                        {
                            sprite.incFrame();

                            for (uint8_t x = 0; x < 8; x++) {

                                Bullet &bullet = this->bullets.getEnemyBullet(ENEMY_BULLET_MAX + x);
                                bullet.setBullet(sprite.getX(), sprite.getY() + 10, static_cast<Direction>(x), Object::Sparks, CYCLOP_SPARK_FRAMES);
                                if (this->shake == 0) this->shake = 7;

                            }
                            
                        }
                        break;

                    case 0 ... 100:
                        {
                            spriteAI_UpdateFrame(sprite, 4, 2);
                            Direction direction = spriteAI_CheckForMove(map, player, sprite, location, 15);

                            if (direction != Direction::None && this->launchCyclopsDelay == 0) {


                                // Should the cyclops strike his club ?

                                sprite.setFrame(-CYCLOPS_FRAME_MAX + 1);
                                this->launchCyclopsDelay = random(LAUNCH_CYCLOPS_DELAY_MIN, LAUNCH_CYCLOPS_DELAY_MAX);
                                this->launchCyclopsDirection = direction;

                            }

                        }
                        break;

                }

            }
            break;

        case Object::Beholder:   
            {
                if (sprite.getFrame() < 0) {

                    sprite.incFrame();

                }
                else {

                    spriteAI_UpdateFrame(sprite, 4, 2);
                    Direction direction = spriteAI_CheckForMove(map, player, sprite, location, 15);

                    if (direction != Direction::None) {


                        // Should the enemy shoot a bullet?

                        if (this->enemyBulletDelay == 0 && random(0, 4) == 0 && direction != Direction::None) {

                            const int32_t xOffsets[8] = { 0, 12, 12, 12, 0, -12, -12, -12 };
                            const int32_t yOffsets[8] = { -12, -12, 0, 12, 12, 12, 0, -12 };

                            uint8_t inactiveBulletIdx = this->bullets.getInactiveEnemyBullet();

                            if (inactiveBulletIdx != NO_INACTIVE_BULLET_FOUND) {

                                Bullet &bullet = this->bullets.getEnemyBullet(inactiveBulletIdx);
                                bullet.setBullet(sprite.getX() + xOffsets[static_cast<uint8_t>(direction)], sprite.getY() + yOffsets[static_cast<uint8_t>(direction)], direction, Object::FireBall, BULLET_FIREBALL_FRAMES);
                                this->enemyBulletDelay = random(ENEMY_BULLET_DELAY_MIN, ENEMY_BULLET_DELAY_MAX);

                            }

                        }
                        
                    }

                }

            }

            break;

        case Object::SpikeLHS: 
        case Object::SpikeRHS: 

            sprite.decCountdown();

            if (sprite.getCountdown() <= 24) {

                sprite.setFrame(sprite.getFrame() + 1); 

                if (sprite.getCountdown() == 0) {

                    sprite.setCountdown(random(70, 120));
                    sprite.setFrame(0);

                }

            }

            break;

        case Object::FireTOP: 
        case Object::FireBOT: 

            sprite.decCountdown();

            if (sprite.getCountdown() <= 16) {

                sprite.setFrame(sprite.getFrame() + 1); 

                if (sprite.getCountdown() == 0) {

                    sprite.setCountdown(random(40, 75));
                    sprite.setFrame(0);

                }

            }

            break;

        case Object::Guide01 ... Object::Guide15:
            spriteAI_UpdateFrame(sprite, 2, 96);
            break;

    }

    sprite.setPosition(location.x, location.y);

}

void Game::spriteAI_UpdateFrame(Sprite &sprite, uint8_t frameMultiple, uint8_t frameMax) {

    if (Pokitto::Core::frameCount % frameMultiple == 0) { 
        sprite.setFrame(sprite.getFrame() + 1); 
        sprite.setFrame(sprite.getFrame() % frameMax);
    } 

}


Direction Game::spriteAI_CheckForMove(MapInformation &map, Player &player, Sprite &sprite, Point &location, uint8_t dist) {

    Direction direction = Direction::None;
    uint8_t multiplier = (this->player.getWeapon() == Object::IceSpell ? 2 : 1);

    if (this->map.getDistance(location.x, location.y, player.getX(), player.getY()) <= dist) {

        if ((this->player.getWeapon() == Object::IceSpell && this->player.getWeaponCount() % 2 == 0) || this->player.getWeapon() != Object::IceSpell) {

            switch (sprite.getType()) {

                case Object::Cyclop:
                    if (PC::frameCount % (2 * multiplier) == 0) {
                        direction = this->spriteAI_UpdateEnemy(location, map, player, sprite);
                    }
                    break;

                case Object::Beholder:
                    if (PC::frameCount % (4 * multiplier) == 0) {
                        direction = this->spriteAI_UpdateEnemy(location, map, player, sprite);
                    }
                    break;

                case Object::Necromancer: 
                case Object::BigSpider:
                    if (PC::frameCount % (4 * multiplier) == 0) {
                        direction = this->spriteAI_UpdateEnemy(location, map, player, sprite);
                    }
                    break;

                case Object::Hobgoblin:
                    if (PC::frameCount % (2 * multiplier) == 0) {
                        direction = this->spriteAI_UpdateEnemy(location, map, player, sprite);
                    }
                    break;

                default:
                    direction = this->spriteAI_UpdateEnemy(location, map, player, sprite);
                    break;

            }

        }

    }

    return direction;

}

Direction Game::spriteAI_UpdateEnemy(Point &point, MapInformation &map, Player &player, Sprite &enemy) {

    return spriteAI_UpdateEnemy(point, map, player, enemy, 1);

}

Direction Game::spriteAI_UpdateEnemy(Point &point, MapInformation &map, Player &player, Sprite &enemy, uint8_t movement) {

    Direction direction = Direction::None;

    if (map.getDistance(point.x, point.y, player.getX(), player.getY()) <= 5) {
    
        if (point.x < player.getX() && map.isWalkable(point.x + movement, point.y, Direction::Right, enemy.getWidth(), enemy.getHeight()) != WalkType::Stop && !isBlockedByPlayer(player, enemy, point.x + movement, point.y)) { 
            direction = Direction::Right;
            point.x++; 
        }

        if (point.x > player.getX() && map.isWalkable(point.x - movement, point.y, Direction::Left, enemy.getWidth(), enemy.getHeight()) != WalkType::Stop && !isBlockedByPlayer(player, enemy, point.x - movement, point.y)) { 
            point.x--; 
            direction = Direction::Left;
        }

        if (point.y < player.getY() && map.isWalkable(point.x, point.y + movement, Direction::Down, enemy.getWidth(), enemy.getHeight()) != WalkType::Stop && !isBlockedByPlayer(player, enemy, point.x, point.y + movement)) { 

            point.y++; 

            switch (direction) {

                case Direction::None:
                    direction = Direction::Down;
                    break;

                case Direction::Right:
                    direction = Direction::DownRight;
                    break;

                case Direction::Left:
                    direction = Direction::DownLeft;
                    break;

            }

        }

        if (point.y > player.getY() && map.isWalkable(point.x, point.y - movement, Direction::Up, enemy.getWidth(), enemy.getHeight()) != WalkType::Stop && !isBlockedByPlayer(player, enemy, point.x, point.y - movement)) { 

            point.y--; 

            switch (direction) {

                case Direction::None:
                    direction = Direction::Up;
                    break;

                case Direction::Right:
                    direction = Direction::UpRight;
                    break;

                case Direction::Left:
                    direction = Direction::UpLeft;
                    break;

            }
            
        }

    }

    return direction;

}
