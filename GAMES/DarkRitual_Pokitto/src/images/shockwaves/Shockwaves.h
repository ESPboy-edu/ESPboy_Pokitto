#pragma once

namespace Images {

    #include "Pulse_TL_00.h"
    #include "Pulse_TL_01.h"
    #include "Pulse_TL_02.h"
    #include "Pulse_TL_03.h"
    #include "Pulse_TL_04.h"
    #include "Pulse_TL_05.h"
    #include "Pulse_TL_06.h"
    #include "Pulse_TL_07.h"

    #include "Pulse_TR_00.h"
    #include "Pulse_TR_01.h"
    #include "Pulse_TR_02.h"
    #include "Pulse_TR_03.h"
    #include "Pulse_TR_04.h"
    #include "Pulse_TR_05.h"
    #include "Pulse_TR_06.h"
    #include "Pulse_TR_07.h"

    PROGMEM const uint8_t * const Pulse_TL[] = { 
        Pulse_TL_00,
        Pulse_TL_01,
        Pulse_TL_02,
        Pulse_TL_03,
        Pulse_TL_04,
        Pulse_TL_05,
        Pulse_TL_06,
        Pulse_TL_07,
    };

    PROGMEM const uint8_t * const Pulse_TR[] = { 
        Pulse_TR_00,
        Pulse_TR_01,
        Pulse_TR_02,
        Pulse_TR_03,
        Pulse_TR_04,
        Pulse_TR_05,
        Pulse_TR_06,
        Pulse_TR_07,
    };

};