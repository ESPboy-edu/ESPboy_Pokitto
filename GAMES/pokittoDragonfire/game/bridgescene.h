#ifndef BRIDGESCENE_H
#define BRIDGESCENE_H

#include "../core/utilities/babyfsm.h"

class BridgeScene
{
    struct BridgeData {
        float player_x = 188;
        float player_vel_x = 0;
        float player_y = 0;
        float player_vel_y = 0;
        bool ducking = false;
        float fire_top_x = -10;
        float top_frame = 0;
        float fire_bot_x = -10;
        float bot_frame = 0;
        int dying = 0;
        float frame = 0;
        float waterlevel = 140;
        float watervel = 20.0f;

        void reset() {
            player_x = 188;
            player_vel_x = 0;
            player_y = 0;
            player_vel_y = 0;
            ducking = false;
            fire_top_x = -10;
            top_frame = 0;
            fire_bot_x = -10;
            bot_frame = 0;
            dying = 0;
            frame = 0;
            waterlevel = 140;
            watervel = 20.0f;
        }
    } static s_bridge_data;

public:
    static void go();
    static void update(FSM &fsm);
    static void draw();
};

#endif // BRIDGESCENE_H
