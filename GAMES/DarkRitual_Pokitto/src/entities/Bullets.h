
#pragma once

#include "Pokitto.h"
#include "Bullet.h"
#include "Player.h"
#include "../../My_settings.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


class Bullets {

    public:

        Bullets() {}  

        Bullet & getBullet(uint8_t index);
        Bullet & getPlayerBullet(uint8_t index);
        Bullet & getEnemyBullet(uint8_t index);
        Bullet & getBossBullet(uint8_t index);

        uint8_t getInactivePlayerBullet();
        uint8_t getInactiveEnemyBullet();
        uint8_t getInactiveBossBullet();

        void render(Player &player);


    private:

        Bullet bullets[PLAYER_BULLET_MAX + ENEMY_BULLET_MAX + BOSS_BULLET_MAX];

};
