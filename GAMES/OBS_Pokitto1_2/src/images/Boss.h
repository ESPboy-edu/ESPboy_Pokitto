#pragma once

namespace Images {

    #include "boss/Green/Boss_Green_00.h"
    #include "boss/Green/Boss_Green_01.h"
    #include "boss/Green/Boss_Green_02.h"
    #include "boss/Green/Boss_Green_03.h"

    #include "boss/Blue/Boss_Blue_00.h"
    #include "boss/Blue/Boss_Blue_01.h"
    #include "boss/Blue/Boss_Blue_02.h"
    #include "boss/Blue/Boss_Blue_03.h"

    #include "boss/Boss_04_Red.h"
    #include "boss/Boss_Health.h"

    PROGMEM const uint8_t * const Bosses_Green[] = { 
        Boss_Green_00,
        Boss_Green_01,
        Boss_Green_02,
        Boss_Green_03,
    };

    PROGMEM const uint8_t * const Bosses_Blue[] = { 
        Boss_Blue_00,
        Boss_Blue_01,
        Boss_Blue_02,
        Boss_Blue_03,
    };

};
