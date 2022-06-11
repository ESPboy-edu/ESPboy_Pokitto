#pragma once

namespace Images {
        
    #include "normal/Player_00_F0.h"
    #include "normal/Player_00_F1.h"
    #include "normal/Player_01_F0.h"
    #include "normal/Player_01_F1.h"
    #include "normal/Player_04_F0.h"
    #include "normal/Player_04_F1.h"
    #include "alternate/Player_00_Alt_F0.h"
    #include "alternate/Player_00_Alt_F1.h"
    #include "alternate/Player_01_Alt_F0.h"
    #include "alternate/Player_01_Alt_F1.h"
    #include "alternate/Player_04_Alt_F0.h"
    #include "alternate/Player_04_Alt_F1.h"
    #include "Tombstone.h"

    PROGMEM const uint8_t * const Players_Normal[] = { 
    Player_00_F0,
    Player_00_F1,
    Player_01_F0,
    Player_01_F1,
    Player_01_F0,
    Player_01_F1,
    Player_01_F0,
    Player_01_F1,
    Player_04_F0,
    Player_04_F1,
    Player_04_F0,
    Player_04_F1,
    Player_04_F0,
    Player_04_F1,
    Player_04_F0,
    Player_04_F1,
    };

    PROGMEM const uint8_t * const Players_Alt[] = { 
    Player_00_Alt_F0,
    Player_00_Alt_F1,
    Player_01_Alt_F0,
    Player_01_Alt_F1,
    Player_01_Alt_F0,
    Player_01_Alt_F1,
    Player_01_Alt_F0,
    Player_01_Alt_F1,
    Player_04_Alt_F0,
    Player_04_Alt_F1,
    Player_04_Alt_F0,
    Player_04_Alt_F1,
    Player_04_Alt_F0,
    Player_04_Alt_F1,
    Player_04_Alt_F0,
    Player_04_Alt_F1,
    };

};