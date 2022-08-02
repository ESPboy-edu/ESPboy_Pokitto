#include "title.h"

#include <cmath>

#include "../core/rendersystem.h"
#include "../core/controls.h"

#include "../game/constants.h"
#include "../game/gamedata.h"
#include "../game/sprites.h"

float Title::intro_position = 176;
bool Title::first_run = true;

PROGMEM const char * intro[] = {
    "Dragons have driven the",
    "Royal Court from the",
    "Castle.",
    "",
    "",
    "\"O we are lost, lost\"",
    "laments the King.",
    "\"Without our vast",
    "treasures we cannot",
    "raise an army 'gainst",
    "these accursed dragons.",
    "Our kingdom must now",
    "languish under lizards!\"",
    "",
    "",
    "\"Nay, not so, my liege!\"",
    "replied the young Prince.",
    "\"None knows that Castle,",
    "those many bridges and",
    "storerooms, better than",
    "I. Give me leave and I",
    "shall loot those lizards",
    "of their plunder and",
    "restore my lord to his",
    "birthright.\"",
    "",
    "",
    "\"Brave boy,\" said the",
    "King, fully pleased. ",
    "\"But,\" he added darkly,",
    "\"beware dread dragonfire!\"",
    "",
    "",
    "",
    "",
};

constexpr float intro_velocity = 25.0f;

constexpr float scale_per_line = 18.0f;

constexpr float end_position = scale_per_line * 34;

void Title::update(FSM &fsm)
{
    intro_position -= physicsTimestep * intro_velocity;
    ControlStatus s = Controls::getStatus();
    if (s.a.held()) {
        intro_position -= physicsTimestep * intro_velocity * 4.0f;
    } else if (s.b.held()) {
        intro_position += physicsTimestep * intro_velocity;
    } else if (s.c.pressed()) {
        intro_position = -end_position;
    }
    if (intro_position < -end_position) {
        if (Controls::getStatus().a.pressed()) {
            GameData::reset();
            fsm.go(Screens::BridgeScreen);
        } else if (Controls::getStatus().b.pressed()) {
            fsm.go(Screens::HighScoreScreen);
        }
    }
}

void Title::draw()
{
    RenderSystem::clear(0);

    float pos = intro_position;
    int i = 0;
    while (pos < 176) {
        if (i < 34 && pos > -scale_per_line) {
            RenderSystem::print(10, pos, intro[i], 14, 2);
        }
        pos += scale_per_line;
        ++i;
    }
    float bannerpos = std::fmax(30, intro_position + end_position);
    if (bannerpos < 176) RenderSystem::sprite(0, bannerpos, banner, 0);
    if (bannerpos == 30.0f) {
        RenderSystem::print(42, 108, "A BUTTON  -  PLAY", 12, 2);
        RenderSystem::print(42, 130, "B BUTTON  -  SCORES", 12, 2);
    }
    if (intro_position < end_position * -2.0f) {
        intro_position = 176;
    }
}

void Title::go()
{
    if (first_run) {
        first_run = false;
    } else {
        intro_position = -end_position;
    }
}
