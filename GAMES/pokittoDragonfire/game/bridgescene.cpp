#include "bridgescene.h"

#include <algorithm>

#include "../core/rendersystem.h"
#include "../core/controls.h"
#include "../core/controls.cpp"
#include "../core/audiosystem.h"
#include "../core/audiosystem.cpp"

#include "../game/constants.h"
#include "../game/gamedata.h"
#include "../game/gamedata.cpp"
#include "../game/highscores.h"
#include "../game/sprites.h"

BridgeScene::BridgeData BridgeScene::s_bridge_data;

const int screenbaseline = 112;

void updateVelocityBridge(float &v, float target, float speedrate, float slowrate, float mult) {
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

void BridgeScene::go()
{
    s_bridge_data.reset();

    s_bridge_data.fire_bot_x = -120 - (asCounts(float(rand() % 60) / playerBaseSpeed));
    const float distances[] = {0, 0, 0, 0, 0, 80, 88, 95, 240, 250};
    s_bridge_data.fire_top_x = s_bridge_data.fire_bot_x  + 80 - distances[(rand() % 10)];

    RenderSystem::clear(0);

    // left tower
    RenderSystem::drawRect(0, screenbaseline - 82, 32, 32, 12);
    RenderSystem::drawRect(8, screenbaseline - 82, 8, 24, 0);

    RenderSystem::drawRect(0, screenbaseline - 96, 40, 16, 12);
    RenderSystem::drawRect(8, screenbaseline - 96, 8, 8, 0);
    RenderSystem::drawRect(24, screenbaseline - 96, 8, 8, 0);

    // right tower
    RenderSystem::drawRect(220-32, screenbaseline - 82, 33, 32, 12);
    RenderSystem::drawRect(220-8-8, screenbaseline - 82, 8, 24, 0);

    RenderSystem::drawRect(220-40, screenbaseline - 96, 41, 16, 12);
    RenderSystem::drawRect(220-8-8, screenbaseline - 96, 8, 8, 0);
    RenderSystem::drawRect(220-24-8, screenbaseline - 96, 8, 8, 0);

    RenderSystem::drawLine(0, screenbaseline, 220, screenbaseline, 12);

    RenderSystem::drawRect(0, screenbaseline + 1, 221, 176 - screenbaseline, 13);
    RenderSystem::drawRect(40, screenbaseline + 16, 62, 32, 0);
    RenderSystem::drawRect(110 + 8, screenbaseline + 16, 62, 32, 0);

    RenderSystem::drawRect(40, screenbaseline + 32, 62, 32, 7);
    RenderSystem::drawRect(110 + 8, screenbaseline + 32, 62, 32, 7);

    for(int i = 0; i < 3; ++i) {
        RenderSystem::sprite(44 + i * 20, screenbaseline + 2, ui_dragonhead, 0);
        RenderSystem::sprite(124 + i* 20, screenbaseline + 2, ui_dragonhead, 0);
    }
}

void BridgeScene::update(FSM &fsm)
{
    s_bridge_data.waterlevel += s_bridge_data.watervel * physicsTimestep;
    if (s_bridge_data.watervel > 0 && s_bridge_data.waterlevel > 143) {
        s_bridge_data.watervel = -6.0f;
    } else if (s_bridge_data.watervel < 0 && s_bridge_data.waterlevel < 140) {
        s_bridge_data.watervel = 6.0f;
    }
    if (GameData::gameOver()) {
        if (HighScores::addScore(GameData::getScore())) {
            fsm.go(Screens::HighScoreScreen);
        } else {
            fsm.go(Screens::TitleScene);
        }
        return;
    }

    // dying animation
    if (s_bridge_data.dying > 0) {
        s_bridge_data.dying--;
        s_bridge_data.frame += 8.0f * physicsTimestep;
        while (s_bridge_data.frame >= 6.0f) s_bridge_data.frame -= 2.0f;
        if (s_bridge_data.dying == 0) {
            go();
            GameData::setDeath();
        }
        return;
    }

    s_bridge_data.ducking = Controls::getStatus().down.held();

    if (!s_bridge_data.ducking && s_bridge_data.player_y >= 0) {
        updateVelocityBridge(s_bridge_data.player_vel_x, GameData::playerSpeed() * Controls::getStatus().x, 8.0f, 8.0f, playerBaseSpeed);
    }
    if (!s_bridge_data.ducking || s_bridge_data.player_y < 0) s_bridge_data.player_x += s_bridge_data.player_vel_x * physicsTimestep;

    // check right edge
    if (s_bridge_data.player_x > 210) s_bridge_data.player_x = 210;

    // check left edge
    if (s_bridge_data.player_x < 24) {
        fsm.go(Screens::StoreroomScreen);
        return;
    }

    // handle jumps
    if (s_bridge_data.player_y >= 0 && Controls::getStatus().a.pressed()) {
        s_bridge_data.player_vel_y = -120;
        AudioSystem::play(sfxJump);
    }
    s_bridge_data.player_vel_y += 500 * physicsTimestep;
    s_bridge_data.player_y += s_bridge_data.player_vel_y * physicsTimestep;
    if (s_bridge_data.player_y > 0) {
        s_bridge_data.player_y = 0;
        s_bridge_data.player_vel_y = 0;
    }

    // update fire
    s_bridge_data.bot_frame += 6.0f * physicsTimestep;
    while (s_bridge_data.bot_frame >= 2.0f) s_bridge_data.bot_frame -= 2.0f;
    s_bridge_data.fire_bot_x += playerBaseSpeed * physicsTimestep;
    if (s_bridge_data.fire_bot_x > 380) {
        s_bridge_data.fire_bot_x = -20 - (rand() % asCounts(20 / playerBaseSpeed));
        AudioSystem::play(sfxFire);
    }
    s_bridge_data.fire_top_x += GameData::upperFlameSpeed() * physicsTimestep;
    s_bridge_data.top_frame += 6.0f * physicsTimestep;
    while (s_bridge_data.top_frame >= 2.0f) s_bridge_data.top_frame -= 2.0f;
    if (s_bridge_data.fire_top_x > 380) {
        s_bridge_data.fire_top_x = -40 - (rand() % asCounts(120 / playerBaseSpeed));
        AudioSystem::play(sfxFire);
    }

    // check for player death
    if (s_bridge_data.player_x < 196) {
        if (s_bridge_data.player_y > -7) { // check lower flame
            if (std::abs(s_bridge_data.player_x - s_bridge_data.fire_bot_x) < 12) {
                s_bridge_data.dying = asCounts(1.0f);
                AudioSystem::play(sfxDie);
                return;
            }
        }
        if ((s_bridge_data.player_y + (s_bridge_data.ducking ? 2 : 0)) <= 0) { // check upper flame
            if (std::abs(s_bridge_data.player_x - s_bridge_data.fire_top_x) < 12) {
                s_bridge_data.dying = asCounts(1.0f);
                AudioSystem::play(sfxDie);
                s_bridge_data.frame = 4;
                return;
            }
        }
    }

    if (s_bridge_data.ducking) {
        s_bridge_data.frame = 3;
    } else if (s_bridge_data.player_vel_x != 0) {
        s_bridge_data.frame += 20.0f * physicsTimestep;
        while (s_bridge_data.frame > 3.0f) {
            s_bridge_data.frame -= 3.0f;
            AudioSystem::play(sfxStep);
        }
    } else {
        s_bridge_data.frame = 0;
    }
}

void BridgeScene::draw()
{
    RenderSystem::drawRect(0, screenbaseline - 50, 221, 50, 0);

    if (!s_bridge_data.ducking || s_bridge_data.dying > 0) RenderSystem::sprite(s_bridge_data.player_x - 7, screenbaseline + s_bridge_data.player_y - 21, player[int(s_bridge_data.frame)], 0, s_bridge_data.player_vel_x > 0);
    else RenderSystem::sprite(s_bridge_data.player_x - 7, screenbaseline + s_bridge_data.player_y - 21, player[int(s_bridge_data.frame)], 0, s_bridge_data.player_vel_x > 0);

    if (s_bridge_data.fire_bot_x > 4) RenderSystem::sprite(s_bridge_data.fire_bot_x - 6, screenbaseline - 12, fireball_side[int(s_bridge_data.top_frame)], 0);
    if (s_bridge_data.fire_top_x > 4) RenderSystem::sprite(s_bridge_data.fire_top_x - 6, screenbaseline - 22, fireball_side[int(s_bridge_data.bot_frame)], 0);

    RenderSystem::drawRect(0, screenbaseline - 50, 24, 50, 12);
    RenderSystem::drawRect(220-24, screenbaseline - 50, 25, 50, 12);
    RenderSystem::drawLine(0, screenbaseline - 8, 16, screenbaseline-8, 0);
    RenderSystem::drawLine(0, screenbaseline - 24, 16,screenbaseline-24, 0);

    RenderSystem::drawRect(40, 140, 62, 16, 7);
    RenderSystem::drawRect(118, 140, 62, 16, 7);
    RenderSystem::drawRect(40, 140, 62, s_bridge_data.waterlevel - 140, 0);
    RenderSystem::drawRect(118, 140, 62, s_bridge_data.waterlevel - 140, 0);

    GameData::drawUI();
}
