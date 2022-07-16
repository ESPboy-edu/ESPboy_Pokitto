#pragma once

#include "../utils/Enums.h"

namespace Images {

    namespace Portrait {
            
        namespace Normal {

            #include "mothership/portrait/normal/MotherShip_04.h"
            #include "mothership/portrait/normal/MotherShip_05.h"

            #include "mothership/portrait/normal/MotherShip_04_Red.h"
            #include "mothership/portrait/normal/MotherShip_05_Red.h"

            #include "mothership/portrait/normal/Exclaim_Up_00.h"
            #include "mothership/portrait/normal/Exclaim_Up_01.h"
            #include "mothership/portrait/normal/Exclaim_Up_02.h"
            #include "mothership/portrait/normal/Exclaim_Up_03.h"

            #include "mothership/portrait/normal/Exclaim_Down_00.h"
            #include "mothership/portrait/normal/Exclaim_Down_01.h"
            #include "mothership/portrait/normal/Exclaim_Down_02.h"
            #include "mothership/portrait/normal/Exclaim_Down_03.h"

            const uint8_t * const Mothership[] = { 
                MotherShip_04,
                MotherShip_05,
                MotherShip_04_Red,
                MotherShip_05_Red,
            };

            const uint8_t * const Exclaim_Up[] = { 
                Exclaim_Up_03,
                Exclaim_Up_02,
                Exclaim_Up_01,
                Exclaim_Up_00,
            };

            const uint8_t * const Exclaim_Down[] = { 
                Exclaim_Down_03,
                Exclaim_Down_02,
                Exclaim_Down_01,
                Exclaim_Down_00,
            };

        }

        namespace Rotated {
            
            #include "mothership/portrait/rotated/MotherShip_04.h"
            #include "mothership/portrait/rotated/MotherShip_05.h"
            
            #include "mothership/portrait/rotated/MotherShip_04_Red.h"
            #include "mothership/portrait/rotated/MotherShip_05_Red.h"

            const uint8_t * const Mothership[] = { 
                MotherShip_04,
                MotherShip_05,
                MotherShip_04_Red,
                MotherShip_05_Red,
            };

        }

        namespace SIZE_3X3 {

            #include "mothership/portrait/3x3/MotherShip_Title_04.h"
            #include "mothership/portrait/3x3/MotherShip_Title_05.h"

            const uint8_t * const Mothership_Title[] = { 
                MotherShip_Title_04,
                MotherShip_Title_05,
            };

        }

        namespace SIZE_2X2 {
            
            #include "mothership/portrait/2x2/MotherShip_Title_04.h"
            #include "mothership/portrait/2x2/MotherShip_Title_05.h"

            const uint8_t * const Mothership_Title[] = { 
                MotherShip_Title_04,
                MotherShip_Title_05,
            };

        }

        #include "mothership/portrait/Bomb.h"

    }

    namespace Landscape {
    
        #include "mothership/landscape/MotherShip_04.h"
        #include "mothership/landscape/MotherShip_05.h"
    
        #include "mothership/landscape/MotherShip_04_Red.h"
        #include "mothership/landscape/MotherShip_05_Red.h"

        #include "mothership/landscape/Exclaim_Left_00.h"
        #include "mothership/landscape/Exclaim_Left_01.h"
        #include "mothership/landscape/Exclaim_Left_02.h"
        #include "mothership/landscape/Exclaim_Left_03.h"

        #include "mothership/landscape/Exclaim_Right_00.h"
        #include "mothership/landscape/Exclaim_Right_01.h"
        #include "mothership/landscape/Exclaim_Right_02.h"
        #include "mothership/landscape/Exclaim_Right_03.h"

        const uint8_t * const Mothership[] = { 
            MotherShip_04,
            MotherShip_05,
            MotherShip_04_Red,
            MotherShip_05_Red,
        };

        const uint8_t * const Exclaim_Left[] = { 
            Exclaim_Left_03,
            Exclaim_Left_02,
            Exclaim_Left_01,
            Exclaim_Left_00,
        };

        const uint8_t * const Exclaim_Right[] = { 
            Exclaim_Right_03,
            Exclaim_Right_02,
            Exclaim_Right_01,
            Exclaim_Right_00,
        };

        namespace SIZE_3X3 {

            #include "mothership/landscape/3x3/MotherShip_Title_04.h"
            #include "mothership/landscape/3x3/MotherShip_Title_05.h"

            const uint8_t * const Mothership_Title[] = { 
                MotherShip_Title_04,
                MotherShip_Title_05,
            };

        }

        namespace SIZE_2X2 {

            #include "mothership/landscape/2x2/MotherShip_Title_04.h"
            #include "mothership/landscape/2x2/MotherShip_Title_05.h"

            const uint8_t * const Mothership_Title[] = { 
                MotherShip_Title_04,
                MotherShip_Title_05,
            };

        }

        #include "mothership/landscape/Bomb.h"

    }

};
