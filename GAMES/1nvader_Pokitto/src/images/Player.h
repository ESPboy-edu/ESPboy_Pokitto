#pragma once

#include "../utils/Enums.h"

namespace Images {

    namespace Portrait {
            
        namespace Normal {

            #include "player/portrait/normal/Player_Explosion_00.h"
            #include "player/portrait/normal/Player_Explosion_01.h"
            #include "player/portrait/normal/Player_Explosion_02.h"
            #include "player/portrait/normal/Player_New.h"
            #include "player/portrait/normal/Player2_New.h"

            const uint8_t * const Player_Explosion[] = { 
                Player_Explosion_00,
                Player_Explosion_01,
                Player_Explosion_02,
            };

        };

        namespace Rotated {

            #include "player/portrait/rotated/Player_Explosion_00.h"
            #include "player/portrait/rotated/Player_Explosion_01.h"
            #include "player/portrait/rotated/Player_Explosion_02.h"
            #include "player/portrait/rotated/Player_New.h"
            #include "player/portrait/rotated/Player2_New.h"

            const uint8_t * const Player_Explosion[] = { 
                Player_Explosion_00,
                Player_Explosion_01,
                Player_Explosion_02,
            };

        };

        #include "player/portrait/Laser.h"

    };

    namespace Landscape {

        #include "player/landscape/Player_Explosion_00.h"
        #include "player/landscape/Player_Explosion_01.h"
        #include "player/landscape/Player_Explosion_02.h"
        #include "player/landscape/Player_New.h"
        #include "player/landscape/Player2_New.h"

        const uint8_t * const Player_Explosion[] = { 
            Player_Explosion_00,
            Player_Explosion_01,
            Player_Explosion_02,
        };

        #include "player/landscape/Laser.h"

    };

};
