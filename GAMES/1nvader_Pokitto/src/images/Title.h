#pragma once

#include "../utils/Enums.h"

namespace Images {
    
    namespace Landscape {

        #include "title/landscape/SurvivalMode.h"
        #include "title/landscape/TugOfWarMode.h"
        #include "title/landscape/VSMode.h"
        #include "title/landscape/SurvivalMode_Grey.h"
        #include "title/landscape/TugOfWarMode_Grey.h"
        #include "title/landscape/VSMode_Grey.h"

        #include "title/landscape/Ground.h"
        #include "title/landscape/HighScore.h"
        #include "title/landscape/Invader.h"
        #include "title/landscape/LeftArrow_00.h"
        #include "title/landscape/LeftArrow_01.h"
        #include "title/landscape/LeftArrow_02.h"
        #include "title/landscape/Lock.h"

        #include "title/landscape/Mountain_New.h"

        #include "title/landscape/Rotate.h"
        #include "title/landscape/WaveCleared_00.h"
        #include "title/landscape/WaveCleared_01.h"
        #include "title/landscape/WaveCleared_02.h"
        #include "title/landscape/WaveCleared_03.h"
        #include "title/landscape/WaveCleared_04.h"
        #include "title/landscape/WaveCleared_05.h"
        #include "title/landscape/WaveCleared_06.h"

        const uint8_t * const LeftArrow[] = { 
            LeftArrow_00,
            LeftArrow_01,
            LeftArrow_02,
        };

        const uint8_t * const WaveCleared[] = { 
            WaveCleared_00,
            WaveCleared_01,
            WaveCleared_02,
            WaveCleared_03,
            WaveCleared_04,
            WaveCleared_05,
            WaveCleared_06,
        };

    };

    namespace Portrait {

        #include "title/portrait/SurvivalMode.h"
        #include "title/portrait/TugOfWarMode.h"
        #include "title/portrait/VSMode.h"

        #include "title/portrait/SurvivalMode_Grey.h"
        #include "title/portrait/TugOfWarMode_Grey.h"
        #include "title/portrait/VSMode_Grey.h"

        #include "title/portrait/Ground_Bot.h"
        #include "title/portrait/Ground_Top.h"
        #include "title/portrait/HighScore.h"
        #include "title/portrait/Invader.h"
        #include "title/portrait/DownArrow_00.h"
        #include "title/portrait/DownArrow_01.h"
        #include "title/portrait/DownArrow_02.h"
        #include "title/portrait/Lock.h"
        #include "title/portrait/Rotate.h"
        #include "title/portrait/WaveCleared_00.h"
        #include "title/portrait/WaveCleared_01.h"
        #include "title/portrait/WaveCleared_02.h"
        #include "title/portrait/WaveCleared_03.h"
        #include "title/portrait/WaveCleared_04.h"
        #include "title/portrait/WaveCleared_05.h"
        #include "title/portrait/WaveCleared_06.h"

        #include "title/portrait/Mountain_Top_New.h"
        #include "title/portrait/Mountain_Bot_New.h"

        const uint8_t * const DownArrow[] = { 
            DownArrow_00,
            DownArrow_01,
            DownArrow_02,
        };

        const uint8_t * const WaveCleared[] = { 
            WaveCleared_00,
            WaveCleared_01,
            WaveCleared_02,
            WaveCleared_03,
            WaveCleared_04,
            WaveCleared_05,
            WaveCleared_06,
        };

    };

}