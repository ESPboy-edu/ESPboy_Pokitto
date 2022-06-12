#pragma once

#include "Pokitto.h"
#include "../../utils/Constants.h"

namespace Images {

    #include "Sky_Background.h"
    #include "Underground_Brick.h"
    #include "Underground_Chain.h"
    #include "Outside_Exit_00.h"
    #include "Outside_Exit_01.h"
    #include "Underground_Exit_00.h"
    #include "Underground_Exit_01.h"
    #include "Platform_00.h"
    #include "Platform_01.h"
    #include "TBrick_Outside.h"
    #include "TBrick_Underground.h"
    #include "Water.h"

    const uint8_t * const Tile_Brick[] = { 
        TBrick_Underground,
        TBrick_Outside,
    };

    const uint8_t * const Platform[] = { 
        Platform_01,
        Platform_00,
    };

};
