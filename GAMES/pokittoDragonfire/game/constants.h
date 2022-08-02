#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <algorithm>

static constexpr int physicsTimestepMs = 16;
static constexpr float physicsTimestep = float(physicsTimestepMs) / 1000.0f;

constexpr int asCounts(float time) {
    return int(time / physicsTimestep);
}

constexpr float playerBaseSpeed = 110.0f;

enum Screens {
    TitleScene = 0,
    HighScoreScreen = 1,
    BridgeScreen = 2,
    StoreroomScreen = 3
};

#ifdef DEBUGS
#include <iostream>
#define SYSPRINT(v) std::cout << v << std::endl;
#else
#define SYSPRINT(v)
#endif

#endif // CONSTANTS_H
