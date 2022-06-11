#pragma once

namespace Images {

    #include "Bread.h"
    #include "Chicken.h"
    #include "SackOCash.h"
    #include "Tools.h"
    #include "Tonic.h"
    #include "IceSpell.h"
    #include "GreenSpell.h"
    #include "RedSpell.h"
    #include "MauveSpell.h"

    #include "Key_00.h"
    #include "Key_01.h"
    #include "Key_02.h"
    #include "Key_03.h"
    #include "Key_04.h"
    #include "Key_05.h"


    PROGMEM const uint8_t * const Keys[] = { 
        Key_00,
        Key_01,
        Key_02,
        Key_03,
        Key_04,
        Key_05,
        Key_04,
        Key_03,
        Key_02,
        Key_01,
    };

};