#pragma once

namespace Images {

    #include "hud/HUD.h"
    #include "hud/HUD_Bottom.h"
    #include "hud/Live.h"
    #include "hud/Live_Grey.h"

    PROGMEM const uint8_t * const Lives[] = { 
        Live_Grey,
        Live,
    };
    
};