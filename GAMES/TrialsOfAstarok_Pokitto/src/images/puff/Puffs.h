#pragma once

#include "Pokitto.h"

namespace Images {

    #include "Puff_00_Night.h"
    #include "Puff_01_Night.h"
    #include "Puff_02_Night.h"
    #include "Puff_03_Night.h"
    #include "Puff_04_Night.h"
    #include "Puff_05_Night.h"
    #include "Puff_06_Night.h"
    #include "Puff_00_Day.h"
    #include "Puff_01_Day.h"
    #include "Puff_02_Day.h"
    #include "Puff_03_Day.h"
    #include "Puff_04_Day.h"
    #include "Puff_05_Day.h"
    #include "Puff_06_Day.h"

    #include "Pixel_01.h"
    #include "Pixel_02.h"
    #include "Pixel_03.h"

    const uint8_t * const Puffs[] = { 
        Puff_00_Night,
        Puff_00_Day,
        Puff_01_Night,
        Puff_01_Day,
        Puff_02_Night,
        Puff_02_Day,
        Puff_03_Night,
        Puff_03_Day,
        Puff_04_Night,
        Puff_04_Day,
        Puff_05_Night,
        Puff_05_Day,
        Puff_06_Night,
        Puff_06_Day,
    };

};
