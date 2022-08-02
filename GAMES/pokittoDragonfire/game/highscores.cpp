#include "highscores.h"

#include <cstdio>

#include "../core/rendersystem.h"
#include "../core/controls.h"
#include "../core/serialization.h"

#include "../game/constants.h"
#include "../game/sprites.h"
#include <ESP_EEPROM.h>


HighScores::Scores HighScores::s_scores;

float HighScores::timer = 0.0f;

void HighScores::initialize(){
    EEPROM.begin(1200);
    if (EEPROM.read(10)!='D' || EEPROM.read(11)!='B') {
        s_scores.scores[0] = 0;
        s_scores.scores[1] = 0;
        s_scores.scores[2] = 0;
    EEPROM.write(10, 'D');
    EEPROM.write(11, 'B');
    EEPROM.commit();      
    }
    else{
        s_scores.scores[0] = EEPROM.read(12);
        s_scores.scores[1] = EEPROM.read(13);
        s_scores.scores[2] = EEPROM.read(14);
    }
}


bool HighScores::addScore(int value)
{
    for(int i = 0; i < 3; ++i) {
        if (value > s_scores.scores[i]) {
            if (i < 2) {
                for (int j = i + 1; j < 3; ++j) {
                    s_scores.scores[j] = s_scores.scores[i];
                }
            }
            s_scores.scores[i] = value;
            EEPROM.write(12, s_scores.scores[0]);
            EEPROM.write(13, s_scores.scores[1]);
            EEPROM.write(14, s_scores.scores[2]);
            EEPROM.commit();
            return true;
        }
    }
    return false;
}

void HighScores::update(FSM &fsm)
{
    ControlStatus status = Controls::getStatus();
    if (status.a.pressed() || status.b.pressed() || status.c.pressed()) {
        fsm.go(Screens::TitleScene);
    }
    timer += physicsTimestep;
}

void HighScores::draw()
{
    RenderSystem::clear(0);
    char buffer[30];
    for(int i = 0; i < 3; ++i) {
        sprintf(buffer, "%d", s_scores.scores[i]);
        int l = RenderSystem::getLineLength(buffer, 2);
        RenderSystem::print(110 - l/2, 57 + i * 28, buffer, 13, 2);
    }
    RenderSystem::print(102, 168, "v1.1", 13);

    constexpr float fire_freq = 0.8f;
    float time = std::fmod(timer, fire_freq);
    RenderSystem::sprite(0, 151, dragon[time < 0.3f ? 2 : 0], 0);
    RenderSystem::sprite(170, 151, dragon[time < 0.3f ? 2 : 0], 0, true);

    constexpr float fire_velocity = playerBaseSpeed;
    constexpr float separation = fire_velocity * fire_freq;

    float start = time * fire_velocity;
    for(int i = 0; i < 2; ++i) {
        RenderSystem::sprite(2, 131 - start - separation * i, fireball_top[int(timer * 4.0f) % 2], 0);
        RenderSystem::sprite(206, 131 - start - separation * i, fireball_top[int(timer * 4.0f) % 2], 0);
    }

    RenderSystem::sprite(0, 15, hs_banner, 0);
}
