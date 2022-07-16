#pragma once

namespace Images {

    #include "explosion/Particle.h"
    #include "explosion/Particle_Red.h"

    namespace Portrait {

        #include "explosion/portrait/Explosion_00.h"
        #include "explosion/portrait/Explosion_01.h"

        const uint8_t * const Explosion[] = { 
            Explosion_00,
            Explosion_01,
        };

    };

    namespace Landscape {

        #include "explosion/landscape/Explosion_00.h"
        #include "explosion/landscape/Explosion_01.h"

        const uint8_t * const Explosion[] = { 
            Explosion_00,
            Explosion_01,
        };

    };

};
