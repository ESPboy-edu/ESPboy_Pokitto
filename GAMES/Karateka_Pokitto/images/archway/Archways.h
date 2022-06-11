#pragma once

namespace Images {

    #include "Arch_LH1.h"
    #include "Arch_LH2.h"
    #include "Arch_LH3.h"
    #include "Arch_LH4.h"
    #include "Arch_LH5.h"
    #include "Arch_LH5_1.h"
    #include "Arch_LH5_2.h"
    #include "Arch_LH5_3.h"
    #include "Arch_LH5_4.h"
    #include "Arch_LH5_5.h"
    #include "Arch_LH5_6.h"
    #include "Arch_LH6.h"
    #include "Arch_LH7.h"

    #include "Arch_RH1.h"
    #include "Arch_RH2.h"
    #include "Arch_RH3.h"
    #include "Arch_RH4.h"
    #include "Arch_RH5.h"
    #include "Arch_RH5_1.h"
    #include "Arch_RH5_2.h"
    #include "Arch_RH5_3.h"
    #include "Arch_RH5_4.h"
    #include "Arch_RH5_5.h"
    #include "Arch_RH5_6.h"
    #include "Arch_RH6.h"

    #include "Arch_Door_00.h"
    #include "Arch_Door_01.h"
    #include "Arch_Door_02.h"
    #include "Arch_Door_03.h"
    #include "Stairs.h"

    const PROGMEM uint8_t * const Arch_LH5_Gates[] = { 
        Arch_LH5_1,
        Arch_LH5_2,
        Arch_LH5_3,
        Arch_LH5_4,
        Arch_LH5_5,
        Arch_LH5_6,
    };

    const PROGMEM uint8_t * const Arch_RH5_Gates[] = { 
        Arch_RH5_1,
        Arch_RH5_2,
        Arch_RH5_3,
        Arch_RH5_4,
        Arch_RH5_5,
        Arch_RH5_6,
    };

    const PROGMEM uint8_t * const Arch_Doors[] = { 
        Arch_Door_00,
        Arch_Door_01,
        Arch_Door_02,
        Arch_Door_03,
    };

};