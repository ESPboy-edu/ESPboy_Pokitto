
#pragma once

#include "Part.h"

class Particles {

    public:

        Part particles[Constants::Particle_Count];

    public:
        
        void reset() {

            for (Part &particle : this->particles) {

                particle.reset();

            }

        }

        uint8_t getInactiveParticle() {

            for (uint8_t i = 0; i < Constants::Particle_Count; i++) {

                Part &particle = this->particles[i];

                if (!particle.getActive()) {

                    return i;

                }

            }

            return Constants::Particle_None;

        }

};
