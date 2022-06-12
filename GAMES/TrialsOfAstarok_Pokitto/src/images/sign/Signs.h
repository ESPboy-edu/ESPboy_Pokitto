#pragma once

#include "Pokitto.h"
#include "../../utils/Constants.h"

namespace Images {

    #include "SignPost_AboveGround.h"
    #include "SignPost_BelowGround.h"
    #include "SignPost_Large.h"

    const uint8_t * const SignPost[] = { 
        SignPost_BelowGround,
        SignPost_AboveGround,
    };
    
};
