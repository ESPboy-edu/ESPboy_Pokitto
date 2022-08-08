#include "Scramble.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::game_Init() {

    this->muteTheme();
    this->gameState = GameState::Game_Start;

    this->player.reset(true);
    this->enemies.reset();
    this->bullets.reset();
    this->stars.reset();
    this->shockwaves.reset();
    this->particles.reset();

    this->gameScreenVars.reset(true);
    this->gameScreenVars.resetAnimation(GameState::Game_Start);
    this->gameScreenVars.stageTransition  = static_cast<uint16_t>(TransitionMode::Sequence_End);

}   


void Game::game() {

    // Process player actions ..

    if (player.getActive()) {

        this->playerActions();

    }


    // Move bullets and check for collisions ..

    this->movePlayerBullets();
    this->movePlayerBombs();
    this->moveEnemyBullets();


    // Update Surface to Air missiles and Rockets ..

    this->redirectSurfaceToAir();
    this->launchRockets();
    this->launchMines();
    this->launchFuelCans();
    this->launchEighterOrCircler();


    // Has the player collided with anything ?

    this->checkPlayerCollision();
    

    // Move scenery ..

    if (this->player.getMoveScenery()) {

        // Decrease stage counter ..

        if (this->gameScreenVars.stageCount > 0 && this->gameScreenVars.stageTransition == 0) {

            if (this->gameScreenVars.distance % 168 == 0) {
                this->gameScreenVars.stageCount--;
            }

            if (this->gameScreenVars.stageCount == 0) {
                this->gameScreenVars.stageTransition = static_cast<uint16_t>(TransitionMode::Sequence_End);
                this->gameScreenVars.score = this->gameScreenVars.score + 250;

                #ifdef SOUNDS
                    this->playTheme(Themes::Main);
                #endif

            }

        }

        this->stars.moveX(this->gameScreenVars.viewY);
        this->moveScenery(2);
        this->createScenery(218);
        this->createScenery(219);
        this->gameScreenVars.distance = this->gameScreenVars.distance + 2;
        this->player.incX(2);

        if (this->gameScreenVars.distance % 64 == 0 && this->gameScreenVars.stageTransition == 0) {

            this->player.decFuel();

            if (this->player.getFuel() == 0) {

                this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Huge, this->gameScreenVars.getColor());
                this->player.setActive(false);
                this->player.setCountdown(1);
                this->player.decLives();

                #ifdef SOUNDS
                    playSoundEffect(SoundEffect::Explosion_00);
                #endif

            }

        }

        for (Enemy &enemy : this->enemies.enemies) {

            if (enemy.getActive()) {

                switch (enemy.getEnemyType()) {

                    case EnemyType::Mine:
                    case EnemyType::Eighter:
                    case EnemyType::Circler:
                        enemy.move(this->gameScreenVars.distance);
                        break;

                }

                if (enemy.getX() < this->gameScreenVars.distance - Constants::Enemy_Max_Width) {

                    enemy.setActive(false);

                }

            }

        }


        if (PC::frameCount % Constants::Distance == 0) {

            this->gameScreenVars.score++;

        }

    }


    // End of life or end of game?

    if (!this->player.getActive()) {

        if (this->player.getCountdown() == Constants::GrindToHalt) {

            if (this->player.getLives() > 0) {

                this->player.reset(false);
                this->enemies.reset();
                this->bullets.reset();
                this->gameScreenVars.reset(false);

            }
            else {

                this->gameState = GameState::GameOver;

                if (PC::buttons.pressed(BTN_A)) {

                    this->gameState = GameState::HighScore_Init;
                    uint32_t index = cookie->setLastScore(this->gameScreenVars.score);
                    
                }

            }

        }

    }

    this->player.updateCounter();


    // ----------------------------------------------------------------------------------------------------
    // Render page ..
    // ----------------------------------------------------------------------------------------------------

    this->renderStars(true);
    this->renderScenery();
    this->renderEnemies();

    switch (this->gameState) {

        case GameState::Game_Start:
            this->renderStageStart();
            break;

        case GameState::GameOver:
            this->renderGameOver();
            break;

        default:
            this->renderStageComplete();
            break;

    }


    // Render player ..

    if (this->player.getActive()) {
        PD::drawBitmap(this->player.getX() - this->gameScreenVars.distance, this->player.getY() - this->gameScreenVars.viewY, Images::PlayerShip);
        PD::drawBitmap(this->player.getX() - this->gameScreenVars.distance - 8, this->player.getY() - this->gameScreenVars.viewY + 5, Images::PlayerFlame[PC::frameCount % 16 / 4]);
    }


    // Render bullets and bombs ..

    this->renderPlayerBullets();
    this->renderPlayerBombs();
    this->renderEnemyBullets();


    // Render shockwaves and particles ..

    this->renderShockwave(this->gameScreenVars.distance, this->gameScreenVars.viewY);
    this->renderParticles(this->gameScreenVars.distance, this->gameScreenVars.viewY);


    // Render HUD ..

    this->renderHUD();

}


void Game::movePlayerBullets() {


    // Process player bullets ..

    for (Bullet &bullet : bullets.bullets) {

        if (bullet.getX() > 0) {

            if (bullet.getMuzzleIndex() > 0) {

                bullet.decMuzzleIndex();
                bullet.setX(this->player.getX() + Constants::Player_Width + 4);

            }
            else {

                bullet.setX(bullet.getX() + 6);

                if (bullet.getX() - this->gameScreenVars.distance >= 220) {

                    bullet.setActive(false);

                }

            }

            if (bullet.getActive()) checkPlayerBulletCollision(bullet);

        }

    }

}

void Game::movePlayerBombs() {


    // Process player bombs ..

    for (Bullet &bomb : bullets.bombs) {
            
        if (bomb.getX() > 0) {

            if (bomb.getMuzzleIndex() > 0) {

                bomb.decMuzzleIndex();
                bomb.setX(this->player.getX() + (Constants::Player_Width / 2) - 3);

            }
            else {

                bomb.move();

                if (bomb.getY() - this->gameScreenVars.viewY >= 176) {

                    bomb.setActive(false);

                }

            }

            if (bomb.getActive()) checkPlayerBulletCollision(bomb);

        }

    }

}

void Game::moveEnemyBullets() {

    // Process enemy bullets ..

    for (Bullet &enemyBullet : bullets.enemyBullets) {
           
        if (enemyBullet.getX() > 0) {

            if (enemyBullet.getMuzzleIndex() > 0) {

                enemyBullet.decMuzzleIndex();

            }
            else {

                enemyBullet.move();

                if (enemyBullet.getY() - this->gameScreenVars.viewY < -30 || enemyBullet.getY() - this->gameScreenVars.viewY > 220) {

                    enemyBullet.setActive(false);

                }

            }

            if (enemyBullet.getActive()) checkEnemyBulletCollision(enemyBullet);

        }

    }

}

void Game::redirectSurfaceToAir() {


    // Redirect surface to air missiles ..

    for (Enemy &enemy : this->enemies.enemies) {

        if (enemy.getActive() && enemy.getEnemyType() == EnemyType::SurfaceAir) {

            switch (enemy.getX() - this->player.getX()) {

                case -999 ... 30:
                    enemy.setDirection(Direction::Right);
                    break;

                case 31 ... 60:
                    enemy.setDirection(Direction::Up);
                    break;

                default:
                    enemy.setDirection(Direction::Left);
                    break;

            }


            if (random(0, 96) == 0) {

                uint8_t bulletIdx = this->bullets.getInactiveEnemyBullet();

                if (bulletIdx != Constants::Bullet_None) {

                    Bullet &bullet = this->bullets.enemyBullets[bulletIdx];
                    bullet.setActive(true);
                    bullet.setBulletType(BulletType::EnemyBullet);
                    bullet.setMuzzleIndex(8);
                    bullet.setDirection(enemy.getDirection());

                    switch (enemy.getDirection()) {

                        case Direction::Left:
                            bullet.setX(enemy.getX() - 1);
                            bullet.setY(enemy.getY() + 1);
                            break;

                        case Direction::Up:
                            bullet.setX(enemy.getX() + (Constants::SurfaceAir_Width / 2) - 1);
                            bullet.setY(enemy.getY() - 2);
                            break;

                        case Direction::Right:
                            bullet.setX(enemy.getX() + Constants::SurfaceAir_Width - 1);
                            bullet.setY(enemy.getY() + 1);
                            break;

                    }

                    #ifdef SOUNDS
                        playSoundEffect(SoundEffect::SurfaceToAir);
                    #endif

                }

            }

        }

    }

}

void Game::launchRockets() {


    // Launch rockets?

    for (Enemy &enemy : this->enemies.enemies) {

        if (enemy.getActive() && enemy.getEnemyType() == EnemyType::Rocket) {

            if (!enemy.getInFlight()) {

                enemy.setSpeed(random(1, 4));
                    
                switch (enemy.getX() - this->player.getX()) {

                    case -999 ... 0:
                        enemy.setInFlight(true);
                        break;

                    case 1 ... 30:
                        enemy.setInFlight(random(0, 4) == 0);
                        break;

                    case 31 ... 40:
                        enemy.setInFlight(random(0, 16) == 0);
                        break;

                    case 41 ... 50:
                        enemy.setInFlight(random(0, 32) == 0);
                        break;

                    case 51 ... 60:
                        enemy.setInFlight(random(0, 64) == 0);
                        break;

                    case 61 ... 100:
                        enemy.setInFlight(random(0, 128) == 0);
                        break;

                    case 101 ... 150:
                        enemy.setInFlight(random(0, 256) == 0);
                        break;

                    case 151 ... 210:
                        enemy.setInFlight(random(0, 768) == 0);
                        break;

                }

                if (enemy.getInFlight()) {
                    #ifdef SOUNDS
                        playSoundEffect(SoundEffect::RocketLaunch);
                    #endif
                }

            }
            else {


                // Move the rocket accoring to the random speed ..

                enemy.setY(enemy.getY() - enemy.getSpeed());


                // Has the rocket hit the ceiling?

                Rect enemyRect = enemy.getRect();

                for (uint16_t x = enemyRect.x; x < enemyRect.x + enemyRect.width; x = x + 2) {

                    Point point;
                    point.setX(x);
                    point.setY(this->gameScreenVars.scenery.top[x - this->gameScreenVars.distance]);


                    // Collide with top ?

                    if (this->collide(point, enemyRect)) {

                        this->explode(enemy.getX() + (Constants::Player_Bullet_Width / 2), enemy.getY() + (Constants::Player_Bullet_Height / 2), ExplosionSize::Small, this->gameScreenVars.getColor());
                        enemy.setActive(false);

                        #ifdef SOUNDS
                            playSoundEffect(SoundEffect::Explosion_02);
                        #endif

                        return;

                    }

                }

            }
            
        }

    }

}

void Game::launchMines() {

    if (this->gameScreenVars.score > 500 && this->gameScreenVars.distance > 750) {

        uint16_t rand = 512 - (this->gameScreenVars.score < 256000 ? (this->gameScreenVars.score / 1000) : 256);

        if (random(0, rand) == 0) {

            uint8_t idx = this->enemies.getInactiveEnemy();

            if (idx != Constants::Enemy_None) {

                Enemy &enemy = this->enemies.enemies[idx];

                enemy.setEnemyType(EnemyType::Mine);
                enemy.setX(this->gameScreenVars.distance + 220);
                enemy.setY(this->gameScreenVars.scenery.top[219] + (this->gameScreenVars.scenery.bot[219] / 2));
                enemy.setActive(true);
                enemy.setScenery(&this->gameScreenVars.scenery);

            }

        }

    }

}

void Game::launchFuelCans() {

   if (this->gameScreenVars.score > 500 && this->gameScreenVars.distance > 750) {

        if (random(0, 800) == 0 && this->gameScreenVars.scenery.bot[219] > 150) {

            uint8_t idx = this->enemies.getInactiveEnemy();

            if (idx != Constants::Enemy_None) {

                Enemy &enemy = this->enemies.enemies[idx];

                enemy.setEnemyType(EnemyType::FuelCan);
                enemy.setX(this->gameScreenVars.distance + 220);
                enemy.setY(this->gameScreenVars.scenery.top[219] + (this->gameScreenVars.scenery.bot[219] / 2));
                enemy.setActive(true);

            }

        }

    }

}

void Game::launchEighterOrCircler() {

    if (this->gameScreenVars.score > 750 && this->gameScreenVars.distance > 1000) {
    //if (true) {

        if (random(0, 512) == 0) {
        // if (random(0, 64) == 0) {

            uint8_t idx = this->enemies.getInactiveEnemy();
                
            if (idx != Constants::Enemy_None) {

                if (this->gameScreenVars.scenery.bot[219] > 150) {

                    Enemy &enemy = this->enemies.enemies[idx];

                    enemy.setEnemyType(EnemyType::Eighter);
                    enemy.setX(this->gameScreenVars.distance + 220);
                    enemy.setY(this->gameScreenVars.scenery.top[219] + (this->gameScreenVars.scenery.bot[219] / 2) - 32);
                    enemy.setActive(true);
 
                }
                else {

                    Enemy &enemy = this->enemies.enemies[idx];
                    enemy.setEnemyType(EnemyType::Circler);
                    enemy.setX(this->gameScreenVars.distance + 220);
                    enemy.setY(this->gameScreenVars.scenery.top[219] + (this->gameScreenVars.scenery.bot[219] / 2) - 20);
                    enemy.setActive(true);

                }

            }

        }

    }

}