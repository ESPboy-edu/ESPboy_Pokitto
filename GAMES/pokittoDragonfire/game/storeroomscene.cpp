#include "storeroomscene.h"

#include <algorithm>
#include <cstring>

#include "../core/rendersystem.h"
#include "../core/controls.h"
#include "../core/audiosystem.h"

#include "../game/gamedata.h"
#include "../game/constants.h"
#include "../game/sprites.h"
#include "../game/highscores.h"

StoreroomScene::StoreData StoreroomScene::s_storeroom_data;

const int door_in_x = 192;
const int door_in_y = 118;

const int door_out_x = 8;
const int door_out_y = 26;

const int dragon_y = 132;

void updateVelocity(float &v, float target, float speedrate, float slowrate, float mult) {
    speedrate *= mult;
    slowrate *= mult;
    if (std::abs(target) < 0.001f) {
        if (v > 0) {
            v -= slowrate * physicsTimestep;
            if (v < 0) v = 0;
        } else {
            v += slowrate * physicsTimestep;
            if (v > 0) v = 0;
        }
    } else if (v * target < 0) {
        if (v > target) {
            v -= slowrate * physicsTimestep;
            if (v < target) v = target;
        } else {
            v += slowrate * physicsTimestep;
            if (v > target) v = target;
        }
    } else {
        if (v > target) {
            v -= speedrate * physicsTimestep;
            if (v < target) v = target;
        } else {
            v += speedrate * physicsTimestep;
            if (v > target) v = target;
        }
    }
}

float getClamped(float p, float v, float min, float max) {
    p += v * physicsTimestep;
    if (p < min) p = min;
    if (p > max) p = max;
    return p;
}

void StoreroomScene::go()
{
    s_storeroom_data.reset();

    SYSPRINT(s_storeroom_data.dying)

    RenderSystem::clear(0);
    RenderSystem::drawRect(0, 12, 221, 12, 12);
    for(int i = 0; i < 220; i += 12) {
        RenderSystem::drawRect(i, 12, 4, 4, 0);
    }

    int level = GameData::getLevel();
    bool locations[15 * 8];
    std::memset(locations, 1, 15 * 8 * sizeof(bool));
    for(int i = 0; i < 8; ++i) {
        bool valid = false;

        int x = rand() % 15;
        int y = rand() % 8;
        valid = locations[x + y * 15];
        while (!valid) {
            x = rand() % 15;
            y = rand() % 8;
            valid = locations[x + y * 15];
        }
        locations[x + y * 15] = false;
        s_storeroom_data.treasures[i].x = x * 12 + (y % 2) * 3 + 12;
        s_storeroom_data.treasures[i].y = y * 12 + (y % 2) * 3 + 20;
        valid = false;

        StoreroomScene::Items choice;
        while (!valid) {
            choice = StoreroomScene::Items(rand() % 9);
            s_storeroom_data.treasures[i].type = choice;
            switch(choice) {
            case Lamp:
                s_storeroom_data.treasures[i].tier = 0;
                valid = true;
                break;
            case Jug:
                s_storeroom_data.treasures[i].tier = 0;
                valid =  (level < 6 || level >= 9);
                break;
            case Goblet:
                s_storeroom_data.treasures[i].tier = 0;
                valid = level < 9;
                break;
            case Helmet:
                s_storeroom_data.treasures[i].tier = 1;
                valid = true;
                break;
            case Candelabra:
                s_storeroom_data.treasures[i].tier = 1;
                valid = level < 8;
                break;
            case Chest:
                s_storeroom_data.treasures[i].tier = 2;
                valid = level > 2;
                break;
            case Harp:
                s_storeroom_data.treasures[i].tier = 2;
                valid = level > 4;
                break;
            case Diamond:
                s_storeroom_data.treasures[i].tier = 3;
                valid = level > 6;
                break;
            case Crown:
                s_storeroom_data.treasures[i].tier = 3;
                valid = level > 7;
                break;
            default:
                valid = true;
                break;
            }
        }
    }
}

void StoreroomScene::update(FSM &fsm)
{
    if (GameData::gameOver()) {
        if (HighScores::addScore(GameData::getScore())) {
            fsm.go(Screens::HighScoreScreen);
        } else {
            fsm.go(Screens::TitleScene);
        }
        return;
    }

    // update dragon target/running
    s_storeroom_data.dragon_eval_timer--;
    if (s_storeroom_data.dragon_eval_timer == 0) {
        s_storeroom_data.dragon_eval_timer = GameData::getDragonEvalTime();
        s_storeroom_data.dragon_target = s_storeroom_data.in_door ? s_storeroom_data.dragon_vel_x > 0 ? 168 : 0 : s_storeroom_data.player_pos_x > s_storeroom_data.dragon_pos_x ? 168.0f : 0.0f;
        s_storeroom_data.dragon_running = !s_storeroom_data.in_door && std::abs(s_storeroom_data.player_pos_x + 4 - s_storeroom_data.dragon_pos_x - 20) > 55;
    }

    // update dragon movement
    if (s_storeroom_data.dragon_target > s_storeroom_data.dragon_pos_x) {
        updateVelocity(s_storeroom_data.dragon_vel_x, GameData::dragonSpeed(s_storeroom_data.dragon_running), 20.0f, 14.0f, playerBaseSpeed);
        s_storeroom_data.dragon_pos_x = getClamped(s_storeroom_data.dragon_pos_x, s_storeroom_data.dragon_vel_x, 1, 168);
        if (s_storeroom_data.dragon_pos_x > 167.99f) {
            s_storeroom_data.dragon_target = 0.0f;
        }
    } else {
        updateVelocity(s_storeroom_data.dragon_vel_x, -GameData::dragonSpeed(s_storeroom_data.dragon_running), 20.0f, 14.0f, playerBaseSpeed);
        s_storeroom_data.dragon_pos_x = getClamped(s_storeroom_data.dragon_pos_x, s_storeroom_data.dragon_vel_x, 1, 168);
        if (s_storeroom_data.dragon_pos_x < 1.01f) {
            s_storeroom_data.dragon_target = 180.0f;
        }
    }
    s_storeroom_data.dragon_frame += physicsTimestep * 12.0f;
    while (s_storeroom_data.dragon_frame >= 2.0f) s_storeroom_data.dragon_frame -= 2.0f;

    // update dragon fireballs
    s_storeroom_data.dragon_fire_timer--;
    if (s_storeroom_data.dragon_fire_timer <= 0) {
        if (std::abs(s_storeroom_data.player_pos_x + 4 - s_storeroom_data.dragon_pos_x - 32 + (s_storeroom_data.dragon_vel_x < 0 ? 28 : 0)) < 12) {
            AudioSystem::play(sfxFire);
            s_storeroom_data.dragon_fire_timer = GameData::getDragonFireTime();
            s_storeroom_data.fires[s_storeroom_data.next_fireball].fireAt(s_storeroom_data.dragon_pos_x + (s_storeroom_data.dragon_vel_x > 0 ? 44 : 8));
            s_storeroom_data.next_fireball = (s_storeroom_data.next_fireball + 1) % 8;
        }
    }
    for(int i = 0; i < 8; ++i) {
        if(s_storeroom_data.fires[i].alive) {
            s_storeroom_data.fires[i].y = getClamped(s_storeroom_data.fires[i].y, GameData::getStoreroomFireballSpeed(), 0, 180);
            if (s_storeroom_data.fires[i].y <= 6.01f) {
                s_storeroom_data.fires[i].alive = false;
            }

            if (!s_storeroom_data.in_door
                && std::abs(s_storeroom_data.player_pos_x - s_storeroom_data.fires[i].x) < 12
                && std::abs(s_storeroom_data.player_pos_y - s_storeroom_data.fires[i].y) < 12) {
                s_storeroom_data.dying = asCounts(1.0f);
                AudioSystem::play(sfxDie);
                s_storeroom_data.frame = 4;
                s_storeroom_data.in_door = true;
            }
        }
    }

    // dying animation
    if (s_storeroom_data.dying > 200) {
        s_storeroom_data.dying = 0;
    }
    if (s_storeroom_data.dying > 0) {
        s_storeroom_data.dying--;
        s_storeroom_data.frame += 8.0f * physicsTimestep;
        while (s_storeroom_data.frame >= 6.0f) s_storeroom_data.frame -= 2.0f;
        if (s_storeroom_data.dying == 0) {
            GameData::setDeath();
        }
        return;
    }

    // update player position
    ControlStatus stat = Controls::getStatus();
    if (stat.left.held()) {
        s_storeroom_data.going_right = false;
    } else if (stat.right.held()) {
        s_storeroom_data.going_right = true;
    }
    if (s_storeroom_data.in_door) {
        if (stat.left.held()) {
            s_storeroom_data.in_door = false;
            s_storeroom_data.player_pos_x = door_in_x - 6;
            s_storeroom_data.player_pos_y = door_in_y + 3;
            s_storeroom_data.player_vel_x = 0;
            s_storeroom_data.player_vel_y = 0;
        }
    } else {
        updateVelocity(s_storeroom_data.player_vel_x, GameData::playerSpeed() * stat.x, 20.0f, 8.0f, playerBaseSpeed);
        updateVelocity(s_storeroom_data.player_vel_y, playerBaseSpeed * stat.y, 14.0f, 8.0f, playerBaseSpeed);

        s_storeroom_data.frame += 20.0f * physicsTimestep;
        while (s_storeroom_data.frame >= 3.0f) {
            s_storeroom_data.frame -= 3.0f;
            AudioSystem::play(sfxStep);
        }
        if (std::abs(s_storeroom_data.player_vel_x) < 0.1f && std::abs(s_storeroom_data.player_vel_y) < 0.1f) s_storeroom_data.frame = 0.0f;

        s_storeroom_data.player_pos_x = getClamped(s_storeroom_data.player_pos_x, s_storeroom_data.player_vel_x, 10, 200);
        s_storeroom_data.player_pos_y = getClamped(s_storeroom_data.player_pos_y, s_storeroom_data.player_vel_y, door_out_y + 2, dragon_y - 18);

        // hide in entrance door
        if (stat.right.held() && std::abs(s_storeroom_data.player_pos_x - door_in_x) < 8 && std::abs(s_storeroom_data.player_pos_y - door_in_y) < 8) {
            s_storeroom_data.in_door = true;
            return;
        }

        //
        if (s_storeroom_data.exit_open && std::abs(s_storeroom_data.player_pos_x - door_out_x) < 8 && std::abs(s_storeroom_data.player_pos_y - door_out_y) < 8) {
            GameData::goNextLevel();
            go();
            fsm.go(Screens::BridgeScreen);
            return;
        }
    }

    // check treasure collection
    int count = 0;
    for(int i = 0; i < 8; ++i) {
        count += s_storeroom_data.treasures[i].acquired ? 0 : 1;
        if (!s_storeroom_data.treasures[i].acquired
                && std::abs(float(s_storeroom_data.treasures[i].x) - s_storeroom_data.player_pos_x) < 12
                && std::abs(float(s_storeroom_data.treasures[i].y) - s_storeroom_data.player_pos_y) < 12)
        {
            s_storeroom_data.treasures[i].acquired = true;
            GameData::getTreasure(s_storeroom_data.treasures[i].tier);
        }
    }
    s_storeroom_data.exit_open = count == 0;
}

void StoreroomScene::draw()
{
    RenderSystem::clear(0);

    if (s_storeroom_data.in_door) RenderSystem::sprite(door_in_x, door_in_y, door[0], 0);
    else RenderSystem::sprite(door_in_x, door_in_y, door[1], 0);

    if (s_storeroom_data.exit_open) RenderSystem::sprite(door_out_x, door_out_y, door[1], 0);

    for(int i = 0; i < 8; ++i) {
        if (!s_storeroom_data.treasures[i].acquired) {
            RenderSystem::sprite(s_storeroom_data.treasures[i].x, s_storeroom_data.treasures[i].y, items[int(s_storeroom_data.treasures[i].type)], 0);
        }
    }
    for(int i = 0; i < 8; ++i) {
        if (s_storeroom_data.fires[i].alive) {
            RenderSystem::sprite(s_storeroom_data.fires[i].x - 4, s_storeroom_data.fires[i].y - 4, fireball_top[int(s_storeroom_data.dragon_frame + i) % 2], 0);
        }
    }

    RenderSystem::sprite(s_storeroom_data.dragon_pos_x, dragon_y, dragon[int(s_storeroom_data.dragon_frame) + (s_storeroom_data.dragon_fire_timer > 5 ? 2 : 0)], 0, s_storeroom_data.dragon_vel_x > 0);

    if (!s_storeroom_data.in_door || s_storeroom_data.dying > 0) {
        RenderSystem::sprite(s_storeroom_data.player_pos_x - 7, s_storeroom_data.player_pos_y - 11, player[int(s_storeroom_data.frame)], 0, s_storeroom_data.going_right);
    }

    RenderSystem::drawRect(0, 4, 221, 8, 12);
    for(int i = 0; i < 220; i += 16) {
        RenderSystem::drawRect(i + 6, 12, 10, 4, 12);
    }

    GameData::drawUI();
}
