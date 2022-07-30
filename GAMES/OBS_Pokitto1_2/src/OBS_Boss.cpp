#include "OBS.h"
#include "sounds/Sounds.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::moveBoss() {


    // Move Boss ..

    if (PC::frameCount % 2 == 0) {

        switch (this->gameState) {

            case GameState::Game_BossEntering:

                this->boss.setX(this->boss.getX() - 1);
                this->boss.incPathCounter();
                this->boss.setY(10 + Constants::Enemy_Path_Large[this->boss.getPathCounter()]);

                if (this->boss.getX() == 82) {
                    this->gameState = GameState::Game_Boss;
                }

                break;

            case GameState::Game_Boss:

                this->boss.incPathCounter();
                this->boss.setY(10 + Constants::Enemy_Path_Medium[this->boss.getPathCounter()]);

                break;

            case GameState::Game_BossLeaving:

                this->boss.setX(this->boss.getX() + 1);
                this->boss.incPathCounter();
                this->boss.setY(10 + Constants::Enemy_Path_Medium[this->boss.getPathCounter()]);
                
                break;

        }

    }


    // Boss fires bullet?

    switch (this->gameState) {

        case GameState::Game_BossEntering:
        case GameState::Game_Boss:
            {

                if ((this->boss.getTopHealth() > 0 || this->boss.getBottomHealth() > 0) && (random(0, Constants::Boss_Bullet_Random) == 0)) {

                    uint8_t bulletIdx = bossBullets.getInactiveBullet();

                    if (bulletIdx != Constants::Bullet_None) {

                        Bullet &bullet = bossBullets.bullets[bulletIdx];

                        bullet.setY(this->boss.getY() + (this->boss.getTopHealth() > 0 && this->boss.getBottomHealth() > 0 ? (bulletIdx % 2 == 0 ? 8 : 31) : this->boss.getTopHealth() > 0 ? 8 : 31));
                        bullet.setX(82);
                        bullet.setDirection(static_cast<Direction>(random(static_cast<uint8_t>(Direction::UpLeft), static_cast<uint8_t>(Direction::DownLeft) + 1)));
                        bullet.setActive(true);

                    }

                }

            }
            break;

    }

}


void Game::checkBossBulletCollision(Bullet &bullet) {


    // Has the bullet hit a large asteroid?

    Rect bulletRect = bullet.getRect(BulletType::BossBullet);

    for (Asteroid &largeAsteroid : largeAsteroids) {

        if (largeAsteroid.getActive()) {

            Rect asteroidRect = largeAsteroid.getLargeAsteroidRect();

            if (collide(bulletRect, asteroidRect)) {
                bullet.setHitObject(HitObject::LargeAsteroid);
                bullet.setHitCount(1);
                bullet.setMuzzleIndex(0);
                bullet.setX(largeAsteroid.getX() + 17);
            }

        }

    }


    // Has the bullet hit the player?

    Rect playerRect = player.getRect();

    if (collide(bulletRect, playerRect)) {

        bullet.setHitObject(HitObject::Player);
        bullet.setHitCount(1);
        bullet.setMuzzleIndex(0);
        bullet.setX(22);

        if (player.getHealth() > 0)  {

            player.decHealth(5);

            #ifdef SOUNDS
                playSoundEffect(SoundEffect::Mini_Explosion);
            #endif
        
            if (player.getHealth() == 0) {

                player.setExplodeCounter(21);
                this->explode(14, player.getY() + 3, ExplosionSize::Medium, this->gameScreenVars.getColor());
                

                #ifdef SOUNDS
//                                        tunes.playScore(Sounds::PlayerDies);
                #endif  
            }

        }


        #ifdef SOUNDS
            playSoundEffect(SoundEffect::Mini_Explosion);
        #endif            

    }

}


void Game::launchBoss() {

    gameState = GameState::Game_EnemyLeaving;
    gameScreenVars.bossColor = (gameScreenVars.bossColor == BossColor::Green) ? BossColor::Blue : BossColor::Green;

    #ifdef SOUNDS
        this->playTheme(Theme::Boss, true);
    #endif

    for (Enemy &enemy : this->enemies) {

        if (enemy.getX() > 110) {

            enemy.setActive(false);
            enemy.setX(Constants::Enemy_OffScreen);

        }
        
    }

    for (Asteroid &largeAsteroid : largeAsteroids) {

        if (largeAsteroid.getX() > 110) {

            largeAsteroid.setActive(false);
                
        }
        
    }

    this->boss.reset();

}

    