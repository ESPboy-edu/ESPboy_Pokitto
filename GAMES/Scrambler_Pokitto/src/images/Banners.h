#pragma once

namespace Images {

    #include "banners/Countdown_00.h"
    #include "banners/Countdown_01.h"
    #include "banners/Countdown_02.h"
    #include "banners/Countdown_03.h"

    PROGMEM const uint8_t * const Countdown[] = { 
        Countdown_03,
        Countdown_02,
        Countdown_01,
        Countdown_00,
    };

};