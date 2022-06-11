
#pragma once

namespace Images {

    #include "Brick.h"
    #include "Edge1.h"
    #include "Empty.h"
    #include "Fuel1.h"
    #include "Gate1.h"
    #include "Gate2.h"
    #include "Grass.h"
    #include "Leve1.h"
    #include "Leve2.h"
    #include "Metal.h"
    #include "Meta2.h"
    #include "Plat1.h"
    #include "Rocks.h"
    #include "Sand1.h"
    #include "Sign1.h"
    #include "SpikesDown.h"
    #include "SpikesUp.h"
    #include "Water.h"
    #include "WaterAlt.h"

    #include "Empty_Stars1.h"
    #include "Empty_Stars2.h"
    #include "Empty_Stars3.h"
    #include "Empty_Stars4.h"

    const uint8_t * const Tiles_Large[] PROGMEM = { 
        Empty, // 0
        Plat1,
        Edge1,
        Water,
        Sign1, // 4
        Gate1,
        Metal,
        Meta2,
        Rocks, // 8
        Brick,
        Grass,
        Fuel1,
        Sand1, // 12
        SpikesUp,
        SpikesDown,
        Leve1,
        Gate2, // 16
        Leve2,
        WaterAlt
    };

    const uint8_t * const Empty_With_Stars[] PROGMEM = {
        Empty_Stars1,
        Empty_Stars2,
        Empty_Stars4,
        Empty_Stars3
    };

};