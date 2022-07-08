#pragma once

#include "../utils/Enums.h"

namespace Images {

    #include "title/Title.h"

    #ifdef NEW_GRAPHICS
        #include "title/HighScore_New.h"
        #include "title/Scenario_New.h"
    #else
        #include "title/HighScore.h"
        #include "title/Scenario.h"
    #endif

}