#pragma once

#include "Pokitto.h"
#include "../libs/LibAudio/LibAudio.h"
#include "../libs/LibSchedule/LibSchedule.h"
#include "images/Images.h"
#include "utils/Constants.h"
#include "utils/Enums.h"
#include "utils/Structs.h"
#include "entities/Entities.h"
#include "utils/GameCookie.h"

using PC=Pokitto::Core;
using PD=Pokitto::Display;
using PB=Pokitto::Buttons;


class Game {

    private:

        Point starfield[Constants::StarField_Size];
        Asteroid smallAsteroids[Constants::SmallAsteroid_Size];
        Asteroid largeAsteroids[Constants::LargeAsteroid_Size];
        Enemy enemies[Constants::Enemy_Size];
        Player player;
        Bullets bullets;
        BossBullets bossBullets;
        Boss boss;
        Health health;

        Particles particles;
        Shockwaves shockwaves;

        File mainThemeFile;

        SplashScreenVars splashScreenVariables;
        TitleScreenVars titleScreenVars;
        GameScreenVars gameScreenVars;
        GameCookie *cookie;

        GameState gameState = GameState::Splash_Init;


    public:

        void setup(GameCookie *cookie);
        void loop();

    private:

        void splashScreen_Init();
        void splashScreen();
        void game_Init();
        void game();
        void title_Init();
        void title();

        void launchLargeAsteroid(Asteroid &asteroid);
        void launchEnemy(Enemy &enemy);
        void launchBoss();
        void launchHealth();

        void moveRenderStarfield();
        void moveRenderSmallAsteroids(bool alternate);
        void moveRenderLargeAsteroids(bool alternate);
        void moveBoss();
        void moveEnemies();
        void moveHealth();
        void checkBulletCollision(Bullet &bullet);
        void checkBossBulletCollision(Bullet &bullet);

        void introText(int8_t y);
        void playTheme(Theme theme, bool loop);
        void muteTheme();
        void playSoundEffect(SoundEffect soundEffect);
        bool collide(Rect rect1, Rect rect2);
        void printScore(uint8_t x, uint8_t y, uint16_t score);


        void explode(int16_t x, int16_t y, ExplosionSize explosionSize, ExplosionColor color);
        // void smol_shwave(int16_t shx, int16_t shy);
        void createShockwave(int16_t x, int16_t y, uint8_t maxRadius);
        // void smol_spark(int16_t xs, int16_t sy);
        void renderShockwave();
        void renderParticles();
        uint8_t getBlueShade(uint8_t page);
        uint8_t getRedShade(uint8_t page);
        float getRandomFloat(int8_t min, int8_t max);

};

