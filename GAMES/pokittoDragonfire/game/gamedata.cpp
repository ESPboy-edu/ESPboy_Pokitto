#include "gamedata.h"

#include <algorithm>
#include <cstdio>

#include "../core/rendersystem.h"
#include "../core/audiosystem.h"

#include "../game/constants.h"
#include "../game/sprites.h"

#include "../core/palettes.h"

constexpr float player_speed_scales[9] = { 0.8f, 0.85f, 0.9f, 0.95f, 1.0f, 1.05f, 1.1f, 1.15f, 1.2f};
constexpr float dragon_speed_scales[9] = { 0.6f, 0.9f, 1.3f, 1.4f, 1.5f, 1.6f, 1.65f, 1.7f, 1.75f};
constexpr float dragon_run_speeds[9] = {1.0f, 1.11f, 1.22f, 1.33f, 1.44f, 1.55f, 1.66f, 1.77f, 1.88f};

int level = 0;
int lives = 7;
int score = 0;

const uint16_t * palette_set[9] = {
    default_palette,
    palette_l2,
    palette_l3,
    palette_l4,
    palette_l5,
    palette_l6,
    palette_l7,
    palette_l8,
    palette_l9,
};

void GameData::reset()
{
    level = 0;
    lives = 7;
    score = 0;
    RenderSystem::setPalette(default_palette);
}

void GameData::getTreasure(int tier)
{
    if (tier < 0) tier = 0;
    if (tier > 3) tier = 3;
    int values[4] = {10, 60, 100, 400};
    AudioSystem::play(SFX(int(sfxDing1) + tier));
    score += values[tier];
}

void GameData::goNextLevel()
{
    AudioSystem::play(sfxDing2);
    if (level < 8) level++;
    score += 100;

    RenderSystem::setPalette(palette_set[std::min(8, level)]);
}

int GameData::getLevel()
{
    return level + 1;
}

int GameData::getScore()
{
    return score;
}

float GameData::playerSpeed()
{
    return playerBaseSpeed * player_speed_scales[std::min(level, 8)];
}

float GameData::dragonSpeed(bool running)
{
    float s = dragon_speed_scales[std::min(level, 8)] * playerBaseSpeed;
    if (running) return s * dragon_run_speeds[std::min(level, 8)];
    return s;
}

int GameData::getDragonEvalTime()
{
    return asCounts(1.0f - 0.05f * std::min(level, 8));
}

int GameData::getDragonFireTime()
{
    return asCounts(0.5f - 0.025f * float(std::min(level, 8)));
}

float GameData::getStoreroomFireballSpeed()
{
    return -playerBaseSpeed * (1.0f + float(std::min(level, 8)) * 0.0625f);
}

float GameData::upperFlameSpeed()
{
    return playerSpeed() * 1.5f;
}

void GameData::setDeath()
{
    lives--;
}

bool GameData::gameOver()
{
    return lives <= 0;
}

void GameData::drawUI()
{
    RenderSystem::drawRect(0, 154, 221, 22, 14);
    RenderSystem::drawLine(0, 158, 16, 158, 0);

    char scorestr[40];
    sprintf(scorestr, "%d", score);
    int len = RenderSystem::getLineLength(scorestr);
    int px = 76 + 5 * 13 - len * 2;
    RenderSystem::print(px, 154, scorestr, 9, 2);
    for(int i = 0; i < lives-1; ++i) {
        RenderSystem::sprite(70 + i * 13 - 2, 168, ui_lives, 5);
    }
}
