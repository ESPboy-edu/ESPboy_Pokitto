#ifndef TITLE_H
#define TITLE_H

#include "../core/utilities/babyfsm.h"

class Title
{
    static float intro_position;
    static bool first_run;
public:

    static void update(FSM &fsm);
    static void draw();
    static void go();
};

#endif // TITLE_H
