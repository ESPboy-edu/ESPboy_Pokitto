#include "Bullets.h"
#include "../images/Images.h"

Bullet & Bullets::getBullet(uint8_t index) {

    return this->bullets[index];
    
}

Bullet & Bullets::getPlayerBullet(uint8_t index) {

    return this->bullets[index];
    
}

Bullet & Bullets::getEnemyBullet(uint8_t index) {

    return this->bullets[PLAYER_BULLET_MAX + index];
    
}

Bullet & Bullets::getBossBullet(uint8_t index) {

    return this->bullets[PLAYER_BULLET_MAX + ENEMY_BULLET_MAX + index];
    
}

uint8_t Bullets::getInactivePlayerBullet() {

    for (uint8_t j = 0; j < PLAYER_BULLET_MAX; j++) {

        auto bullet = this->bullets[j];

        if (!bullet.getActive()) {

            return j;

        }

    }

    return NO_INACTIVE_BULLET_FOUND;

}

uint8_t Bullets::getInactiveEnemyBullet() {

    for (uint8_t j = PLAYER_BULLET_MAX; j < PLAYER_BULLET_MAX + ENEMY_BULLET_MAX; j++) {

        auto bullet = this->bullets[j];

        if (!bullet.getActive()) {

            return j - PLAYER_BULLET_MAX;

        }

    }

    return NO_INACTIVE_BULLET_FOUND;

}

uint8_t Bullets::getInactiveBossBullet() {

    for (uint8_t j = PLAYER_BULLET_MAX + ENEMY_BULLET_MAX; j < PLAYER_BULLET_MAX + ENEMY_BULLET_MAX + BOSS_BULLET_MAX; j++) {

        auto bullet = this->bullets[j];

        if (!bullet.getActive()) {

            return j - PLAYER_BULLET_MAX - ENEMY_BULLET_MAX;

        }

    }

    return NO_INACTIVE_BULLET_FOUND;

}

void Bullets::render(Player &player) {

    for (uint8_t j = 0; j < PLAYER_BULLET_MAX + ENEMY_BULLET_MAX + BOSS_BULLET_MAX; j++) {

        auto bullet = this->bullets[j];

        if (bullet.getActive()) {

            int x = (player.getX() - bullet.getX());
            int y = (player.getY() - bullet.getY());
            uint8_t frame = bullet.getFrame();

            switch (bullet.getWeapon()) {

                case Object::FireBall:
                    PD::drawBitmap((CENTERX - 2) - x, (CENTERY - 2) - y, Images::Bullets[frame]);
                    break;

                case Object::IceSpell:
                    PD::drawBitmap((CENTERX - 2) - x, (CENTERY - 2) - y, Images::Bullets[frame + 4]);
                    break;

                case Object::GreenSpell:
                    PD::drawBitmap((CENTERX - 2) - x, (CENTERY - 2) - y, Images::Bullets[frame + 8]);
                    break;

                case Object::RedSpell:
                    PD::drawBitmap((CENTERX - 2) - x, (CENTERY - 2) - y, Images::Bullets[frame + 12]);
                    break;

                case Object::Sparks:

                    switch (bullet.getCountdown()) {

                        case 0 ... 2:
                            PD::drawBitmap((CENTERX - 1) - x, (CENTERY - 1) - y, Images::Bullets[frame + 16 + (4 * 2)]);
                            break;

                        case 3 ... 4:
                            PD::drawBitmap((CENTERX - 1) - x, (CENTERY - 1) - y, Images::Bullets[frame + 16 + (4 * 1)]);
                            break;

                        case 5 ... 255:
                            PD::drawBitmap((CENTERX - 1) - x, (CENTERY - 1) - y, Images::Bullets[frame + 16]);
                            break;

                    }

                    break;

                case Object::SpiderWeb:

                    switch (frame) {

                        case 0:
                            PD::drawBitmapXFlipped((CENTERX - 3) - x, (CENTERY - 3) - y, Images::SpiderWeb[frame]);
                            break;

                        case 1:
                            PD::drawBitmapXFlipped((CENTERX - 4) - x, (CENTERY - 4) - y, Images::SpiderWeb[frame]);
                            break;

                        case 2 ... 5:
                            PD::drawBitmapXFlipped((CENTERX - 8) - x, (CENTERY - 8) - y, Images::SpiderWeb[frame]);
                            break;

                    }
                    
                    break;

            }

        }

    }

}