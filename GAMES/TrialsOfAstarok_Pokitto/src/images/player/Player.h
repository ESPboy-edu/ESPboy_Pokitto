#pragma once

#include "Pokitto.h"

namespace Images {

    #include "male/left/MalePlayerIdle_Left_00.h"
    #include "male/left/MalePlayerIdle_Left_01.h"
    #include "male/left/MalePlayerIdle_Left_02.h"
    #include "male/right/MalePlayerIdle_Right_00.h"
    #include "male/right/MalePlayerIdle_Right_01.h"
    #include "male/right/MalePlayerIdle_Right_02.h"

    const uint8_t * const MalePlayer_Idle[] = { 
        MalePlayerIdle_Left_00,
        MalePlayerIdle_Left_01,
        MalePlayerIdle_Left_02,
        MalePlayerIdle_Right_00,
        MalePlayerIdle_Right_01,
        MalePlayerIdle_Right_02,
    };

    #include "male/left/MalePlayerWalking_Left_00.h"
    #include "male/left/MalePlayerWalking_Left_01.h"
    #include "male/left/MalePlayerWalking_Left_02.h"
    #include "male/left/MalePlayerWalking_Left_03.h"
    #include "male/right/MalePlayerWalking_Right_00.h"
    #include "male/right/MalePlayerWalking_Right_01.h"
    #include "male/right/MalePlayerWalking_Right_02.h"
    #include "male/right/MalePlayerWalking_Right_03.h"

    const uint8_t * const MalePlayer_Walking[] = { 
        MalePlayerWalking_Left_00,
        MalePlayerWalking_Left_01,
        MalePlayerWalking_Left_02,
        MalePlayerWalking_Left_03,
        MalePlayerWalking_Right_00,
        MalePlayerWalking_Right_01,
        MalePlayerWalking_Right_02,
        MalePlayerWalking_Right_03,
    };

    #include "male/left/MalePlayerJumpingUp_Left_00.h"
    #include "male/right/MalePlayerJumpingUp_Right_00.h"

    const uint8_t * const MalePlayer_Jumping[] = { 
        MalePlayerJumpingUp_Left_00,
        MalePlayerJumpingUp_Right_00,
    };

    #include "female/left/FemalePlayerIdle_Left_00.h"
    #include "female/left/FemalePlayerIdle_Left_01.h"
    #include "female/left/FemalePlayerIdle_Left_02.h"
    #include "female/right/FemalePlayerIdle_Right_00.h"
    #include "female/right/FemalePlayerIdle_Right_01.h"
    #include "female/right/FemalePlayerIdle_Right_02.h"

    const uint8_t * const FemalePlayer_Idle[] = { 
        FemalePlayerIdle_Left_00,
        FemalePlayerIdle_Left_01,
        FemalePlayerIdle_Left_02,
        FemalePlayerIdle_Right_00,
        FemalePlayerIdle_Right_01,
        FemalePlayerIdle_Right_02,
    };

    #include "female/left/FemalePlayerWalking_Left_00.h"
    #include "female/left/FemalePlayerWalking_Left_01.h"
    #include "female/left/FemalePlayerWalking_Left_02.h"
    #include "female/left/FemalePlayerWalking_Left_03.h"
    #include "female/right/FemalePlayerWalking_Right_00.h"
    #include "female/right/FemalePlayerWalking_Right_01.h"
    #include "female/right/FemalePlayerWalking_Right_02.h"
    #include "female/right/FemalePlayerWalking_Right_03.h"

    const uint8_t * const FemalePlayer_Walking[] = { 
        FemalePlayerWalking_Left_00,
        FemalePlayerWalking_Left_01,
        FemalePlayerWalking_Left_02,
        FemalePlayerWalking_Left_03,
        FemalePlayerWalking_Right_00,
        FemalePlayerWalking_Right_01,
        FemalePlayerWalking_Right_02,
        FemalePlayerWalking_Right_03,
    };

    #include "female/left/FemalePlayerJumpingUp_Left_00.h"
    #include "female/right/FemalePlayerJumpingUp_Right_00.h"

    const uint8_t * const FemalePlayer_Jumping[] = { 
        FemalePlayerJumpingUp_Left_00,
        FemalePlayerJumpingUp_Right_00,
    };

};
