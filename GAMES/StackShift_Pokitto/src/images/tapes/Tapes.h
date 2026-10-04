#pragma once

namespace Images {

    #include "BlueTape_00.h"
    #include "BlueTape_01.h"
    #include "BlueTape_02.h"
    #include "BlueTape_Shadow.h"

    #include "GreenTape_00.h"
    #include "GreenTape_01.h"
    #include "GreenTape_02.h"
    #include "GreenTape_Shadow.h"

    #include "RedTape_00.h"
    #include "RedTape_01.h"
    #include "RedTape_02.h"
    #include "RedTape_Shadow.h"

    #include "Pause.h"
    #include "ArrowLeft.h"
    #include "ArrowRight.h"

    const uint8_t * const Tapes[3][3] = { 
        GreenTape_00,
        GreenTape_01,
        GreenTape_02,
        RedTape_00,
        RedTape_01,
        RedTape_02,
        BlueTape_00,
        BlueTape_01,
        BlueTape_02,
    };

    const uint8_t * const Tapes_Shadow[3] = { 
        GreenTape_Shadow,
        RedTape_Shadow,
        BlueTape_Shadow,
    };

};