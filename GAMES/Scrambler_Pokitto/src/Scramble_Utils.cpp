#include "Scramble.h"
#include "../libs/LibAudio/LibAudio.h"
#include "Sounds/Sounds.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


Audio::Sink<2, PROJ_AUD_FREQ> audio;

//#undef SOUNDS


void Game::playTheme(Themes theme) {

    #ifdef SOUNDS
    static uint8_t dummy[3]={0,0,0};
    static auto& music = Audio::play<0>(dummy);

    //constexpr char themes[2][19] = { "music/Scram_01.raw", "music/Scram_02.raw" };

    switch (this->cookie->sfx) {

        case SoundEffects::Music:
        case SoundEffects::Both:

            //if (this->mainThemeFile.openRO(themes[static_cast<uint8_t>(theme)])) {
            //    auto& music = Audio::play<0>(this->mainThemeFile);

                switch (theme) {

                    case Themes::Main:
                        music = Audio::play<0>(Sounds::mus_Scram_01);
                        music.setLoop(true);
                        break;

                    case Themes::StageComplete:
                        music = Audio::play<0>(Sounds::mus_Scram_02);
                        music.setLoop(false);
                        break;

                //}
            }

            break;

        case SoundEffects::SFX:
        case SoundEffects::None:
            this->muteTheme();
    }
    #endif

}

void Game::muteTheme() {

    #ifdef SOUNDS
    Audio::stop<0>();
    #endif

}


void Game::playSoundEffect(SoundEffect soundEffect) {

    #ifdef SOUNDS

    switch (this->cookie->sfx) {

        case SoundEffects::SFX:
        case SoundEffects::Both:
                
            switch (soundEffect) {
                
                case SoundEffect::PlayerLaser: 
                    &Audio::play<1>(Sounds::sfx_PlayerLaser); break;
                
                case SoundEffect::PlayerBomb: 
                    &Audio::play<1>(Sounds::sfx_PlayerBomb); break;
                
                case SoundEffect::Explosion_00: 
                    &Audio::play<1>(Sounds::sfx_Explosion_00); break;
                
                case SoundEffect::Explosion_01: 
                    &Audio::play<1>(Sounds::sfx_Explosion_01); break;
                
                case SoundEffect::Explosion_02: 
                    &Audio::play<1>(Sounds::sfx_Explosion_02); break;
                
                case SoundEffect::RocketLaunch: 
                    &Audio::play<1>(Sounds::sfx_RocketLaunch); break;
                
                case SoundEffect::SurfaceToAir: 
                    &Audio::play<1>(Sounds::sfx_SurfaceToAir); break;
                
                case SoundEffect::FuelUp: 
                    &Audio::play<1>(Sounds::sfx_FuelUp); break;
            }
            break;
        default: break; 
    }  
    #endif
}    


bool Game::collide(Rect rect1, Rect rect2) {

   return !(rect2.x                >= rect1.x + rect1.width  ||
            rect2.x + rect2.width  <= rect1.x                ||
            rect2.y                >= rect1.y + rect1.height ||
            rect2.y + rect2.height <= rect1.y);

}


bool Game::collide(Point point, Rect rect) {

   return ((point.getX() >= rect.x) && (point.getX() < rect.x + rect.width) &&
       (point.getY() >= rect.y) && (point.getY() < rect.y + rect.height));

}


void Game::checkPlayerBulletCollision(Bullet &bullet) {

    Rect bulletRect = bullet.getRect();


    // Collide with scenery?

    for (uint16_t x = bulletRect.x; x < bulletRect.x + bulletRect.width; x = x + 2) {

        Point point;
        point.setX(x);
        point.setY(this->gameScreenVars.scenery.top[x - this->gameScreenVars.distance]);


        // Collide with top ?

        if (this->collide(point, bulletRect)) {

            this->explode(bullet.getX() + (Constants::Player_Bullet_Width / 2), bullet.getY() + (Constants::Player_Bullet_Height / 2), ExplosionSize::Small, this->gameScreenVars.getColor());
            bullet.setActive(false);

            #ifdef SOUNDS
                playSoundEffect(SoundEffect::Explosion_02);
            #endif

            return;

        }


        // Collide with bottom ?

        point.setY(this->gameScreenVars.scenery.top[x - this->gameScreenVars.distance] + this->gameScreenVars.scenery.bot[x - this->gameScreenVars.distance]);

        if (this->collide(point, bulletRect)) {

            this->explode(bullet.getX() + (Constants::Player_Bullet_Width / 2), bullet.getY() + (Constants::Player_Bullet_Height / 2), ExplosionSize::Small, this->gameScreenVars.getColor());
            bullet.setActive(false);

            #ifdef SOUNDS
                playSoundEffect(SoundEffect::Explosion_02);
            #endif

            return;

        }

    }


    // Collide with enemy?

    for (Enemy &enemy : this->enemies.enemies) {

        if (enemy.getActive()) {

            Rect enemyRect = enemy.getRect();

            if (this->collide(enemyRect, bulletRect)) {

                switch (enemy.getEnemyType()) {

                    case EnemyType::Rocket:
                        this->explode(bullet.getX() + (Constants::Player_Bullet_Width / 2), bullet.getY() + (Constants::Player_Bullet_Height / 2), ExplosionSize::Medium, this->gameScreenVars.getColor());
                        this->gameScreenVars.score = this->gameScreenVars.score + 20;
                        break;

                    case EnemyType::FuelDepot:
                        this->explode(bullet.getX() + (Constants::Player_Bullet_Width / 2), bullet.getY() + (Constants::Player_Bullet_Height / 2), ExplosionSize::Large, this->gameScreenVars.getColor());
                        this->gameScreenVars.score = this->gameScreenVars.score + 100;
                        this->player.incFuel(random(10, 25));
                        break;

                    case EnemyType::GroundPod:
                        this->explode(bullet.getX() + (Constants::Player_Bullet_Width / 2), bullet.getY() + (Constants::Player_Bullet_Height / 2), ExplosionSize::Medium, this->gameScreenVars.getColor());
                        this->gameScreenVars.score = this->gameScreenVars.score + 75;
                        break;

                    case EnemyType::SurfaceAir:
                        this->explode(bullet.getX() + (Constants::Player_Bullet_Width / 2), bullet.getY() + (Constants::Player_Bullet_Height / 2), ExplosionSize::Medium, this->gameScreenVars.getColor());
                        this->gameScreenVars.score = this->gameScreenVars.score + 100;
                        break;

                    case EnemyType::Mine:
                        this->explode(bullet.getX() + (Constants::Player_Bullet_Width / 2), bullet.getY() + (Constants::Player_Bullet_Height / 2), ExplosionSize::Medium, this->gameScreenVars.getColor());
                        this->gameScreenVars.score = this->gameScreenVars.score + 25;
                        break;

                    case EnemyType::FuelCan:
                        this->explode(bullet.getX() + (Constants::Player_Bullet_Width / 2), bullet.getY() + (Constants::Player_Bullet_Height / 2), ExplosionSize::Medium, this->gameScreenVars.getColor());
                        break;

                    case EnemyType::Eighter:
                    case EnemyType::Circler:
                        this->explode(bullet.getX() + (Constants::Player_Bullet_Width / 2), bullet.getY() + (Constants::Player_Bullet_Height / 2), ExplosionSize::Small, this->gameScreenVars.getColor());
                        this->gameScreenVars.score = this->gameScreenVars.score + 20;
                        break;

                }

                #ifdef SOUNDS
                    playSoundEffect(SoundEffect::Explosion_01);
                #endif

                enemy.setActive(false);
                bullet.setActive(false);
                return;

            }

        }

    }

}


void Game::checkEnemyBulletCollision(Bullet &bullet) {

    Rect bulletRect = bullet.getRect();


    // Collide with scenery?

    for (uint16_t x = bulletRect.x; x < bulletRect.x + bulletRect.width; x = x + 2) {

        Point point;
        point.setX(x);
        point.setY(this->gameScreenVars.scenery.top[x - this->gameScreenVars.distance]);


        // Collide with top ?

        if (this->collide(point, bulletRect)) {

            this->explode(bullet.getX() + (Constants::Enemy_Bullet_Width / 2), bullet.getY() + (Constants::Enemy_Bullet_Height / 2), ExplosionSize::Small, this->gameScreenVars.getColor());
            bullet.setActive(false);
            return;

        }


        // Collide with bottom ?

        point.setY(this->gameScreenVars.scenery.top[x - this->gameScreenVars.distance] + this->gameScreenVars.scenery.bot[x - this->gameScreenVars.distance]);

        if (this->collide(point, bulletRect)) {

            this->explode(bullet.getX() + (Constants::Enemy_Bullet_Width / 2), bullet.getY() + (Constants::Enemy_Bullet_Height / 2), ExplosionSize::Small, this->gameScreenVars.getColor());
            bullet.setActive(false);
            return;

        }

    }

}


void Game::checkPlayerCollision() {

    if (player.getActive()) {

        Rect playerRect = { this->player.getX() + 1, this->player.getY() + 1, Constants::Player_Width, Constants::Player_Height };

        for (uint16_t x = this->player.getX() - this->gameScreenVars.distance + 1; x < this->player.getX() - this->gameScreenVars.distance + Constants::Player_Width; x = x + 2) {

            Point point;
            point.setX(x + this->gameScreenVars.distance);
            point.setY(this->gameScreenVars.scenery.top[x]);


            // Top scenery ..

            if (this->collide(point, playerRect)) {

                if (this->gameScreenVars.stageTransition == 0) {

                    this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Huge, this->gameScreenVars.getColor());
                    this->player.setActive(false);
                    this->player.setCountdown(1);
                    this->player.decLives();

                    #ifdef SOUNDS
                        playSoundEffect(SoundEffect::Explosion_00);
                    #endif

                    break;

                }
                else {

                    this->player.incY(2);

                    if (this->player.getY() - this->gameScreenVars.viewY > 176 - 90) {
                        this->gameScreenVars.viewY = this->gameScreenVars.viewY + 1;
                    }

                    break;

                }

            }


            // Bottom scenery ..

            point.setY(this->gameScreenVars.scenery.top[x] + this->gameScreenVars.scenery.bot[x]);

            if (this->collide(point, playerRect)) {

                if (this->gameScreenVars.stageTransition == 0) {

                    this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Huge, this->gameScreenVars.getColor());
                    this->player.setActive(false);
                    this->player.setCountdown(1);
                    this->player.decLives();

                    #ifdef SOUNDS
                        playSoundEffect(SoundEffect::Explosion_00);
                    #endif

                    break;

                }
                else {

                    this->player.decY(2);

                    if (this->player.getY() - this->gameScreenVars.viewY < 70) {
                        this->gameScreenVars.viewY = this->gameScreenVars.viewY - 1;
                    }

                    break;

                }

            }

        }



        // Has the player collided with an enemy?

        if (this->gameScreenVars.stageTransition == 0) {

            for (Enemy &enemy : this->enemies.enemies) {

                if (enemy.getActive()) {

                    Rect enemyRect = enemy.getRect();

                    if (collide(enemyRect, playerRect)) {

                        enemy.setActive(false);

                        switch (enemy.getEnemyType()) {

                            case EnemyType::FuelCan:
                                this->explode(enemy.getX() + (Constants::FuelCan_Width / 2), enemy.getY() + (Constants::FuelCan_Height / 2), ExplosionSize::Small, this->gameScreenVars.getColor());
                                this->player.incFuel(random(0, 50) + 30);
                                
                                #ifdef SOUNDS
                                    playSoundEffect(SoundEffect::FuelUp);
                                #endif

                                break;

                            default:
                                this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Huge, this->gameScreenVars.getColor());
                                this->player.setActive(false);
                                this->player.setCountdown(1);
                                this->player.decLives();

                                #ifdef SOUNDS
                                    playSoundEffect(SoundEffect::Explosion_00);
                                #endif

                                break;

                        }

                        break;

                    }

                }

            }


            // Has the player collided with an enemy bullet?

            for (Bullet &enemyBullet : this->bullets.enemyBullets) {

                if (enemyBullet.getActive()) {

                    Rect enemyBulletRect = enemyBullet.getRect();

                    if (collide(enemyBulletRect, playerRect)) {

                        this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Huge, this->gameScreenVars.getColor());
                        this->player.setActive(false);
                        this->player.decLives();
                        this->player.setCountdown(1);
                        enemyBullet.setActive(false);

                        #ifdef SOUNDS
                            playSoundEffect(SoundEffect::Explosion_00);
                        #endif

                        break;

                    }

                }

            }

        }

    }

}