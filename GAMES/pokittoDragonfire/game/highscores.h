#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include "../core/utilities/babyfsm.h"

class HighScores
{
    struct Scores {
        uint32_t scores[3] = { 0, 0, 0 };
    } static s_scores;

    static float timer;

public:
    static void initialize();
    static bool addScore(int value);
    static void update(FSM &fsm);
    static void draw();
};

#endif // HIGHSCORES_H
