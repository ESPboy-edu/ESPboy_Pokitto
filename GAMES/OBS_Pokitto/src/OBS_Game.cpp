#include "OBS.h"
#include "sounds/Sounds.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

PROGMEM const int8_t xOffsets[] = { -2, 1, 2, 0 };
PROGMEM const int8_t yOffsets[] = { 0, -2, 1, 2 };

void Game::game_Init() {

    for (Asteroid &smallAsteroid : smallAsteroids) {

        smallAsteroid.x = random(110, 256);
        smallAsteroid.y = random(0, 80);
        
    }

    for (Asteroid &largeAsteroid : largeAsteroids) {

        launchLargeAsteroid(largeAsteroid);
        
    }

    for (Enemy &enemy : enemies) {

        launchEnemy(enemy);
        
    }

    bullets.reset();

    player.reset();
    gameState = GameState::Game;
    gameScreenVars.reset();
    PC::setFrameRate(50);

}   

void Game::game() {


    // Move player ..

    switch (gameState) {
    
        case GameState::Game:
            {

                // Increase score based on distance travelled ..

                if (PC::frameCount % Constants::ScoreDistance == 0) {

                    player.score++;

                }

                player.y = player.y + static_cast<int8_t>(player.direction);

                if (player.direction == Direction::Up && player.y == 0) {
                    player.direction = Direction::None;
                }

                if (player.direction == Direction::Down && player.y == 78) {
                    player.direction = Direction::None;
                }

                if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B) || PC::buttons.pressed(BTN_LEFT) || PC::buttons.pressed(BTN_RIGHT) || PC::buttons.pressed(BTN_UP) || PC::buttons.pressed(BTN_DOWN)) {
                    
                    uint8_t bulletIdx = bullets.getInactiveBullet();

                    if (bulletIdx != Constants::Bullet_None) {

                        Bullet &bullet = bullets.bullets[bulletIdx];

                        switch (player.direction) {

                            case Direction::Up:
                                player.direction = Direction::Down;
                                break;

                            case Direction::Down:
                                player.direction = Direction::Up;
                                break;

                            default:

                                switch (player.y) {

                                    case 0:
                                        player.direction = Direction::Down;
                                        break;

                                    case 78:
                                        player.direction = Direction::Up;
                                        break;

                                    default:
                                        if (random(0,2) == 0) {
                                            player.direction = Direction::Up;
                                        }
                                        else {
                                            player.direction = Direction::Down;
                                        }
                                        break;

                                }

                                break;
                                
                        }

                        bullet.x = 24;
                        bullet.y = player.y + 2;
                        bullet.muzzleIndex = 8;

                        #ifdef SOUNDS
                            playSoundEffect(SoundEffect::Laser);
                        #endif
                        bullet.hitObject = HitObject::None;

                    }

                }

                for (Bullet &bullet : bullets.bullets) {
                        
                    if (bullet.hitCount > 0) {

                        bullet.hitCount++;

                        if (bullet.hitCount > 3) {
                            bullet.reset();
                        }

                    }

                    if (bullet.x > 0 && bullet.hitCount == 0) {

                        if (bullet.muzzleIndex > 0) {

                            bullet.muzzleIndex--;

                        }
                        else {

                            bullet.x = bullet.x + 4;

                            if (bullet.x >= 110) {

                                bullet.x = -1;

                            }

                        }

                        if (bullet.x != -1) checkBulletCollision(bullet);

                    }

                    if (bullet.hitObject == HitObject::LargeAsteroid) {

                        bullet.x--;

                    }

                }


                // Has the player hit a asteroid?

                bool collision = false;
                Rect playerRect = { 10, player.y + 1, 12, 8 };

                for (Asteroid &largeAsteroid : largeAsteroids) {

                    Rect asteroidRect = { largeAsteroid.x + 1, largeAsteroid.y + 1, 17, 17 };

                    if (collide(playerRect, asteroidRect)) {

                        if (player.health > 0)  {
                            player.health--;

                            #ifdef SOUNDS
                                playSoundEffect(SoundEffect::Player_Hit);
                            #endif                            
                            
                            if (player.health == 0) {
                                player.explodeCounter = 21;

                                #ifdef SOUNDS
                                    playSoundEffect(SoundEffect::Mini_Explosion);
                                #endif         
                            }

                        }

                        collision = true;
                        break;

                    }

                }

                if (collision) {

                    gameScreenVars.offsetCount++;

                    if (gameScreenVars.offsetCount > 4) {

                        gameScreenVars.offsetCount = 1;

                    }

                    gameScreenVars.xOffset = xOffsets[gameScreenVars.offsetCount - 1];
                    gameScreenVars.yOffset = yOffsets[gameScreenVars.offsetCount - 1];
                    
                    // arduboy.invert(offsetCount % 2);

                }
                else {


                    // Has the player hit an enemy ?

                    for (Enemy &enemy : enemies) {

                        Rect enemyRect = { enemy.x + 1, enemy.y + 1, 10, 11 };
                        if (collide(playerRect, enemyRect)) {

                            if (player.health > 0)  {
                                player.health--;

                                #ifdef SOUNDS
                                    playSoundEffect(SoundEffect::Mini_Explosion);
                                #endif
                            
                                if (player.health == 0) {
                                    player.explodeCounter = 21;

                                    #ifdef SOUNDS
//                                        tunes.playScore(Sounds::PlayerDies);
                                    #endif  
                                }

                            }
                                
                            collision = true;
                            break;

                        }

                    }

                    if (collision) {

                        gameScreenVars.offsetCount++;

                        if (gameScreenVars.offsetCount > 4) {

                            gameScreenVars.offsetCount = 1;

                        }

                        gameScreenVars.xOffset = xOffsets[gameScreenVars.offsetCount - 1];
                        gameScreenVars.yOffset = yOffsets[gameScreenVars.offsetCount - 1];
                        
                        // arduboy.invert(offsetCount % 2);

                    }
                    else {

                        gameScreenVars.offsetCount = 0;
                        gameScreenVars.xOffset = 0;
                        gameScreenVars.yOffset = 0;
                        // arduboy.invert(false);

                    }

                }

            }

            break;

        case GameState::Score:

            if (gameScreenVars.highScoreCounter == 0) {

                if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B) || PC::buttons.pressed(BTN_LEFT) || PC::buttons.pressed(BTN_RIGHT) || PC::buttons.pressed(BTN_UP) || PC::buttons.pressed(BTN_DOWN)) {

                    gameState = GameState::Title_Init;

                }

            }
            else {

                gameScreenVars.highScoreCounter--;

            }


            // Clear scores ..

            if (PC::buttons.pressed(BTN_C) || PC::buttons.repeat(BTN_C, 1)) {

                gameScreenVars.clearScores++;

                switch (gameScreenVars.clearScores) {

                    case 21 ... 60:
                        //arduboy.setRGBled(128 - (clearScores * 2), 0, 0);
                        break;

                    case 61:
                        gameScreenVars.clearScores = 0;
                        gameScreenVars.scoreIndex = 255;
                        player.score = 0;
                        //arduboy.setRGBled(0, 0, 0);
                        cookie->reset();

                        #ifdef SOUNDS
                            playSoundEffect(SoundEffect::KeyPress);
                        #endif
                        
                        return;

                }

            }
            else {

                if (gameScreenVars.clearScores > 0) {
                
                    //arduboy.setRGBled(0, 0, 0);
                    gameScreenVars.clearScores = 0;

                }
            
            }

            break;

        default:

            break;

    }
  

    // Move and render starfield and asteroids ..

    moveRenderStarfield();
    moveRenderSmallAsteroids(false);
    moveRenderLargeAsteroids(false);


    // Move and render enemies ..

    for (Enemy &enemy : enemies) {

        switch (enemy.motion) {

            case Motion::Slow:

                if (PC::frameCount % 2 == 0) {

                    switch (enemy.path) {

                        case Path::Small:

                            enemy.pathCount++;
                            if (enemy.pathCount == 36) enemy.pathCount = 0;

                            enemy.x--;                    
                            enemy.y = Constants::Enemy_Path_Small[enemy.pathCount];
                            break;

                        case Path::Medium:

                            enemy.pathCount++;
                            if (enemy.pathCount == 70) enemy.pathCount = 0;

                            enemy.x--;                    
                            enemy.y = Constants::Enemy_Path_Medium[enemy.pathCount];
                            break;

                        case Path::Large:

                            enemy.pathCount++;
                            if (enemy.pathCount == 91) enemy.pathCount = 0;

                            enemy.x--;                    
                            enemy.y = Constants::Enemy_Path_Large[enemy.pathCount] + enemy.yOffset;
                            break;

                        default:
                            break;

                    }

                }

                break;


            case Motion::Fast:

                if (PC::frameCount % 3 < 2) {

                    switch (enemy.path) {

                        case Path::Small:

                            enemy.pathCount++;
                            if (enemy.pathCount == 36) enemy.pathCount = 0;

                            enemy.x--;                    
                            enemy.y = Constants::Enemy_Path_Small[enemy.pathCount] + enemy.yOffset;
                            break;

                        case Path::Medium:

                            enemy.pathCount++;
                            if (enemy.pathCount == 70) enemy.pathCount = 0;

                            enemy.x--;                    
                            enemy.y = Constants::Enemy_Path_Medium[enemy.pathCount] + enemy.yOffset;
                            break;

                        case Path::Large:

                            enemy.pathCount++;
                            if (enemy.pathCount == 91) enemy.pathCount = 0;

                            enemy.x--;                    
                            enemy.y = Constants::Enemy_Path_Large[enemy.pathCount];
                            break;

                        default:
                            break;

                    }

                }

                break;

        }


        if (enemy.x == -19) {

            launchEnemy(enemy);

        }

        if (enemy.getActive() || enemy.explodeCounter > 16) {

            PD::drawBitmap(enemy.x + gameScreenVars.xOffset, enemy.y + gameScreenVars.yOffset, Images::Enemy);

        }

        if (enemy.explodeCounter > 0) {

            PD::drawBitmap(enemy.x +gameScreenVars. xOffset - 3, enemy.y + gameScreenVars.yOffset, Images::Puffs[(21 - enemy.explodeCounter) / 3]);

        }
        
        if (enemy.updateExplosion()) {
        
            launchEnemy(enemy);

        }

    }


    switch (gameState) {

        case GameState::Game:
            {

                // Render player ..

                if (player.health > 0 || player.explodeCounter > 16) {

                    PD::drawBitmap(9 + gameScreenVars.xOffset, player.y + gameScreenVars.yOffset, Images::PlayerShip);
                    PD::drawBitmap(gameScreenVars.xOffset, player.y + 3 + gameScreenVars.yOffset, Images::ShipParticle[PC::frameCount % 8 < 4]);

                }
                
                if (player.explodeCounter > 0) {

                    PD::drawBitmap(6, player.y + gameScreenVars.yOffset, Images::Puffs[(21 - player.explodeCounter) / 3]);

                }
                
                if (player.updateExplosion()) {
                
                    gameState = GameState::Score;
                    gameScreenVars.highScoreCounter = 64;
                    gameScreenVars.scoreIndex = cookie->saveScore(player.score);

                }


                // Render player bullets ..
                
                for (Bullet &bullet : bullets.bullets) {
                                            
                    if (bullet.x > 0) {
                            
                        if (bullet.muzzleIndex > 1) {

                            PD::drawBitmap(bullet.x + gameScreenVars.xOffset, bullet.y + gameScreenVars.yOffset, Images::Muzzle[3 - (bullet.muzzleIndex / 2)]);

                        }
                        else {

                            switch (bullet.hitCount) {

                                case 0:
                                    PD::drawBitmap(bullet.x + gameScreenVars.xOffset, bullet.y + gameScreenVars.yOffset, Images::Bullet);
                                    break;

                                default:
                                    PD::drawBitmap(bullet.x + gameScreenVars.xOffset, bullet.y - 5 + gameScreenVars.yOffset, Images::Hit[bullet.hitCount - 1]);
                                    break;

                            }

                        }

                    }

                }


                // Render the HUD ..

                PD::setColor(0);
                PD::fillRect(88, 81, 22, 7);
                PD::setColor(6);

                uint8_t health_Bar = player.health / Constants::Health_Factor;
                uint8_t digits[5] = {};
                extractDigits(digits, player.score);
                uint8_t location = 106;

                for (uint8_t j = 0; j < 5; ++j, location -= 4) {

                    PD::drawBitmap(location, 82, Images::Numbers[digits[j]]);

                }

                PD::drawBitmap(66, 0, Images::Shield);
                PD::setColor(6);
                PD::drawLine(91, 2, 91 + health_Bar, 2);

            }

            break;

        case GameState::Score:
            {
                #ifdef NEW_GRAPHICS
                    PD::setColor(11);
                    PD::drawBitmap(3, 16, Images::HighScore_New);
                #else
                    PD::setColor(9);
                    PD::drawBitmap(3, 16, Images::HighScore);
                #endif

                PD::setCursor(15, 25);
                PD::print("Your Score  ");

                if (PC::frameCount % 48 < 24 || player.score == 0) {
                    printScore(88, 25, player.score);
                }

                PD::setCursor(15, 38);
                PD::print("Top Scores");

                if (gameScreenVars.scoreIndex != 0 || PC::frameCount % 48 < 24) {
                    this->printScore(88, 38, this->cookie->score[0]);
                }

                if (gameScreenVars.scoreIndex != 1 || PC::frameCount % 48 < 24) {
                    this->printScore(88, 47, this->cookie->score[1]);
                }

                if (gameScreenVars.scoreIndex != 2 || PC::frameCount % 48 < 24) {
                    this->printScore(88, 56, this->cookie->score[2]);
                }

            }

            break;

        default:

            break;

    }

}

void Game::checkBulletCollision(Bullet &bullet) {

    // Has the bullet hit a large asteroid?

    Rect bulletRect = { bullet.x + 1, bullet.y + 1, 7, 5 };

    for (Asteroid &largeAsteroid : largeAsteroids) {

        Rect asteroidRect = { largeAsteroid.x + 1, largeAsteroid.y + 1, 17, 17 };

        if (collide(bulletRect, asteroidRect)) {
            bullet.hitObject = HitObject::LargeAsteroid;
            bullet.hitCount = 1;
            bullet.muzzleIndex = 0;
            bullet.x = largeAsteroid.x - 4;
        }

    }


    // Has the bullet hit an enemy?

    for (Enemy &enemy : enemies) {

        Rect enemyRect = { enemy.x + 1, enemy.y + 1, 10, 11 };

        if (enemy.active && collide(bulletRect, enemyRect)) {

            bullet.hitObject = HitObject::Enemy;
            bullet.hitCount = 1;
            bullet.muzzleIndex = 0;
            bullet.x = enemy.x - 4;

            enemy.explodeCounter = 21;
            enemy.active = false;
            player.score = player.score + 5;

            PC::setFrameRate(50 + (player.score / 24));

            #ifdef SOUNDS
                playSoundEffect(SoundEffect::Mini_Explosion);
            #endif            

        }

    }

}

void Game::printScore(uint8_t x, uint8_t y, uint16_t score) {

    uint8_t digits[5] = {};
    extractDigits(digits, score);

    for (uint8_t j = 0; j < 5; ++j) {

        PD::setCursor(x - (j * 5), y);
        PD::print(static_cast<char>(48 + digits[j]));

    }

}