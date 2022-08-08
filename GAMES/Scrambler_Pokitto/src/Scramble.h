#pragma once

#include "Pokitto.h"
//#include <LibAudio>
#include "Utils/SFXVolumeSource.hpp"
#include "entities/Entities.h"
#include "images/Images.h"
#include "utils/Enums.h"
#include "utils/GameCookie.h"
//#include "sounds/Sounds.h"

using PC=Pokitto::Core;
using PD=Pokitto::Display;
using PB=Pokitto::Buttons;


class Game {

    private:

        SplashScreenVariables splashScreenVariables;
        TitleScreenVariables titleScreenVars;
        GameScreenVars gameScreenVars;
        GameState gameState = GameState::Splash;
        GameCookie *cookie;

        //File mainThemeFile;      

        Particles particles;
        Shockwaves shockwaves;
        Player player;

        Enemies enemies;
        Bullets bullets;
        Stars stars;

        uint8_t cursor;

    public:

        void setup(GameCookie *cookie);
        void loop();

    private:

        void splashScreen();
        void title_Init();
        void title();
        void scenario_Init();
        void scenario();
        void game_Init();
        void game();
        void highScore_Init();
        void highScore();

        bool collide(Rect rect1, Rect rect2);
        bool collide(Point point, Rect rect);
        void checkPlayerBulletCollision(Bullet &bullet);
        void checkEnemyBulletCollision(Bullet &bullet);
        void checkPlayerCollision();
        void playerActions();
        void redirectSurfaceToAir();
        void launchRockets();
        void launchMines();
        void launchFuelCans();
        void launchEighterOrCircler();
        void movePlayerBullets();
        void movePlayerBombs();
        void moveEnemyBullets();

        void renderScenery();
        void renderPlayerBullets();
        void renderPlayerBombs();
        void renderEnemyBullets();
        void renderEnemies();
        void renderHUD();
        void renderStars(bool incOffset);
        void renderGameOver();
        void renderStageStart();
        void renderStageComplete();


        // Music and sounds ..

        void playTheme(Themes theme);
        void muteTheme();
        void playSoundEffect(SoundEffect soundEffect);


        // Scenery ..

        uint16_t launchEnemy(EnemyType enemyType, uint16_t x, int16_t y);
        void createScenery(uint8_t x);
        void moveScenery(uint8_t x);
        // void resetScenery();
        uint8_t getScenerySpace(uint8_t rockets, uint8_t fuelDepots, uint8_t groundPods, uint8_t surfaceAir, uint8_t city);


        // Explosions ..

        void explode(int16_t x, int16_t y, ExplosionSize explosionSize, ExplosionColor color);
        void createShockwave(int16_t x, int16_t y, uint8_t maxRadius);
        void renderShockwave(uint16_t distTravelled, int16_t viewY);
        void renderParticles(uint16_t distTravelled, int16_t viewY);
        float getRandomFloat(int8_t min, int8_t max);
        uint8_t getBlueShade(uint8_t page);
        uint8_t getRedShade(uint8_t page);

};

