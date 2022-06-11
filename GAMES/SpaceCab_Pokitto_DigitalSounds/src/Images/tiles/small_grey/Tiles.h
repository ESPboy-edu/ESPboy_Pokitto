
#pragma once

namespace Images {

    #include "Brick_Sml_Grey.h"
    #include "Edge1_Sml_Grey.h"
    #include "Empty_Sml_Grey.h"
    #include "Fuel1_Sml_Grey.h"
    #include "Gate1_Sml_Grey.h"
    #include "Gate2_Sml_Grey.h"
    #include "Grass_Sml_Grey.h"
    #include "Leve1_Sml_Grey.h"
    #include "Leve2_Sml_Grey.h"
    #include "Metal_Sml_Grey.h"
    #include "Meta2_Sml_Grey.h"
    #include "Plat1_Sml_Grey.h"
    #include "Rocks_Sml_Grey.h"
    #include "Sand1_Sml_Grey.h"
    #include "Sign1_Sml_Grey.h"
    #include "SpikesDown_Sml_Grey.h"
    #include "SpikesUp_Sml_Grey.h"
    #include "Water_Sml_Grey.h"

    const uint8_t * const Tiles_Small_Grey[] PROGMEM = { 
        Empty_Sml_Grey,
        Plat1_Sml_Grey,
        Edge1_Sml_Grey,
        Water_Sml_Grey,
        Sign1_Sml_Grey,
        Gate1_Sml_Grey,
        Metal_Sml_Grey,
        Meta2_Sml_Grey,
        Rocks_Sml_Grey,
        Brick_Sml_Grey,
        Grass_Sml_Grey,
        Fuel1_Sml_Grey,
        Sand1_Sml_Grey,
        SpikesUp_Sml_Grey,
        SpikesDown_Sml_Grey,
        Leve1_Sml_Grey,
        Gate2_Sml_Grey,
        Leve2_Sml_Grey
    };

};