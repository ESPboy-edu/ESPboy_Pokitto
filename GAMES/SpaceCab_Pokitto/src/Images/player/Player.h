#pragma once

namespace Images {

    #include "SpaceTaxi_OutOfFuel_1L.h"
    #include "SpaceTaxi_OutOfFuel_2L.h"
    #include "SpaceTaxi_OutOfFuel_3L.h"
    #include "SpaceTaxi_OutOfFuel_4L.h"

    #include "SpaceTaxi_OutOfFuel_1R.h"
    #include "SpaceTaxi_OutOfFuel_2R.h"
    #include "SpaceTaxi_OutOfFuel_3R.h"
    #include "SpaceTaxi_OutOfFuel_4R.h"

    #include "SpaceCabWithRamp_Left.h"
    #include "SpaceCabWithRamp_Right.h"
    #include "SpaceCab_Sml.h"
    #include "SpaceCab_Sml_Grey.h"

    #include "SpaceTaxi_facingLeft.h"
    #include "SpaceTaxi_facingRight.h"

    #include "ThrusterLeft_Frame0.h"
    #include "ThrusterLeft_Frame1.h"
    #include "ThrusterRight_Frame0.h"
    #include "ThrusterRight_Frame1.h"

    const uint8_t * const SpaceTaxi_LandingGear[] = { 
        SpaceCabWithRamp_Right,
        SpaceCabWithRamp_Left,
    };

    const uint8_t * const SpaceTaxi[] = { 
        SpaceTaxi_facingRight,
        SpaceTaxi_facingLeft,
    };

    const uint8_t * const SpaceTaxi_OutOfFuel_1[] = { 
        SpaceTaxi_OutOfFuel_1R,
        SpaceTaxi_OutOfFuel_1L,
    };

    const uint8_t * const SpaceTaxi_OutOfFuel_2[] = { 
        SpaceTaxi_OutOfFuel_2R,
        SpaceTaxi_OutOfFuel_2L,
    };

    const uint8_t * const SpaceTaxi_OutOfFuel_3[] = { 
        SpaceTaxi_OutOfFuel_3R,
        SpaceTaxi_OutOfFuel_3L,
    };

    const uint8_t * const SpaceTaxi_OutOfFuel_4[] = { 
        SpaceTaxi_OutOfFuel_4R,
        SpaceTaxi_OutOfFuel_4L,
    };

    const uint8_t * const ThrusterLeft[] = { 
        ThrusterLeft_Frame0,
        ThrusterLeft_Frame1,
    };

    const uint8_t * const ThrusterRight[] = { 
        ThrusterRight_Frame0,
        ThrusterRight_Frame1,
    };

};