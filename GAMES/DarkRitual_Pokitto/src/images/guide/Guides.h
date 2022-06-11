#pragma once

namespace Images {

    #include "Guide.h"
    #include "Help_00.h"
    #include "Help_01.h" 
    #include "Help_02.h"
    #include "Help_03.h" 
    #include "SaveMe_00.h" 
    #include "SaveMe_01.h" 
    #include "SaveMe_02.h" 
    #include "SaveMe_03.h" 

    PROGMEM const uint8_t * const GuideCaption[] = { 
    Help_00,
    Help_01,
    Help_02,
    Help_03,
    SaveMe_00,
    SaveMe_01,
    SaveMe_02,
    SaveMe_03,
    };

};