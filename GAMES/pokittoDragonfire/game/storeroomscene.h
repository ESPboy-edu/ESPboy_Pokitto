#ifndef STOREROOMSCENE_H
#define STOREROOMSCENE_H

#include "../core/utilities/babyfsm.h"
#include "../core/utilities/rect.h"

class StoreroomScene
{
    enum Items : uint8_t {
        Lamp = 0,
        Jug = 1,
        Goblet = 2,
        Helmet = 3,
        Candelabra = 4,
        Chest = 5,
        Harp = 6,
        Diamond = 7,
        Crown = 8
    };

    struct FireBall {
        float y;
        int x;
        bool alive = false;

        void fireAt(float px) {
            x = int(px) - 4;
            y = 120;
            alive = true;
        }


    };

    struct Treasure {
        uint8_t x = 12 + 12 * (rand() % 15);
        uint8_t y = 20 + 12 * (rand() % 8);
        bool acquired = false;
        uint8_t tier = 0;
        Items type = Lamp;
    };

    struct StoreData {
        FireBall fires[8];
        Treasure treasures[8];

        int dying = 0;

        float player_pos_x = 220;
        float player_vel_x = 0;
        float player_pos_y = 110;
        float player_vel_y = 0;
        float frame = 0;
        bool going_right = false;

        float dragon_pos_x = 4;
        float dragon_vel_x = 0;
        int dragon_eval_timer = 60;
        int dragon_fire_timer = 30;
        float dragon_frame = 0;
        float dragon_target = 180.0f;

        uint8_t next_fireball = 0;

        bool dragon_running = false;
        bool in_door = true;
        bool exit_open = false;

        void reset() {
            dying = 0;

            player_pos_x = 220;
            player_vel_x = 0;
            player_pos_y = 110;
            player_vel_y = 0;
            frame = 0;
            going_right = false;

            dragon_pos_x = 4;
            dragon_vel_x = 0;
            dragon_eval_timer = 60;
            dragon_fire_timer = 30;
            dragon_frame = 0;
            dragon_target = 180.0f;

            next_fireball = 0;

            dragon_running = false;
            in_door = true;
            exit_open = false;
            for(int i = 0; i < 8; ++i) {
                fires[i].alive = false;
                treasures[i] = Treasure();
            }
        }
    } static s_storeroom_data;

public:
    static void go();
    static void update(FSM &fsm);
    static void draw();
};

#endif // STOREROOMSCENE_H
