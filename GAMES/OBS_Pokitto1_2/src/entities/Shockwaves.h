
#pragma once

#include "Shockwave.h"

class Shockwaves {

    public:

        Shockwave shockwaves[Constants::Shockwave_Count];

    public:
        
        void reset() {

            for (Shockwave &shockwave : this->shockwaves) {

                shockwave.reset();

            }

        }

        uint8_t getInactiveShwave() {

            for (uint8_t i = 0; i < Constants::Shockwave_Count; i++) {

                Shockwave &shockwave = this->shockwaves[i];

                if (!shockwave.getActive()) {

                    return i;

                }

            }

            return Constants::Shockwave_None;

        }

        
};
