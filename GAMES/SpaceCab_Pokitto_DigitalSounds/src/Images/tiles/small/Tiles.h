
#pragma once

namespace Images {

    #include "Brick_Sml.h"
    #include "Edge1_Sml.h"
    #include "Empty_Sml.h"
    #include "Fuel1_Sml.h"
    #include "Gate1_Sml.h"
    #include "Gate2_Sml.h"
    #include "Grass_Sml.h"
    #include "Leve1_Sml.h"
    #include "Leve2_Sml.h"
    #include "Metal_Sml.h"
    #include "Meta2_Sml.h"
    #include "Plat1_Sml.h"
    #include "Rocks_Sml.h"
    #include "Sand1_Sml.h"
    #include "Sign1_Sml.h"
    #include "SpikesDown_Sml.h"
    #include "SpikesUp_Sml.h"
    #include "Water_Sml.h"

    const uint8_t * const Tiles_Small[] PROGMEM = { 
        Empty_Sml,
        Plat1_Sml,
        Edge1_Sml,
        Water_Sml,
        Sign1_Sml,
        Gate1_Sml,
        Metal_Sml,
        Meta2_Sml,
        Rocks_Sml,
        Brick_Sml,
        Grass_Sml,
        Fuel1_Sml,
        Sand1_Sml,
        SpikesUp_Sml,
        SpikesDown_Sml,
        Leve1_Sml,
        Gate2_Sml,
        Leve2_Sml
    };

};