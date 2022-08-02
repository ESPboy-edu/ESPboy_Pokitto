#ifndef GAMEDATA_H
#define GAMEDATA_H


class GameData
{
public:
    static void reset();

    static void getTreasure(int tier);
    static void goNextLevel();
    static int getLevel();
    static int getScore();

    static float playerSpeed();
    static float dragonSpeed(bool running = false);
    static int getDragonEvalTime();
    static int getDragonFireTime();
    static float getStoreroomFireballSpeed();
    static float upperFlameSpeed();

    static void setDeath();
    static bool gameOver();

    static void drawUI();
};

#endif // GAMEDATA_H
