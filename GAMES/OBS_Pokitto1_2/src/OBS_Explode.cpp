#include "OBS.h"

#include "sounds/Sounds.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

float Game::getRandomFloat(int8_t min, int8_t max) {

    return min + ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * (max - min));

}

void Game::explode(int16_t x, int16_t y, ExplosionSize explosionSize, ExplosionColor explosionColor) {

    bool isBlue = false;

    PROGMEM static const uint8_t sizeMax[] = { 3, 4, 12 };
    PROGMEM static const uint8_t deltaMax[] = { 4, 6, 8 };
    PROGMEM static const uint8_t ageMax[] = { 10, 7, 12 };
    PROGMEM static const uint8_t ageStart[] = { 2, 3, 5 };
    PROGMEM static const uint8_t particlesToLaunch[] = { 20, 30, 75 };
    PROGMEM static const uint8_t shockwaveRadius[] = { 0, 40, 55 };

    for (uint8_t i = 0; i < particlesToLaunch[static_cast<uint8_t>(explosionSize)]; i++) {

        uint8_t particleIdx = this->particles.getInactiveParticle();

        if (particleIdx != Constants::Particle_None) {

            Part &particle = this->particles.particles[particleIdx];

            particle.setX(x);
            particle.setY(y);
            particle.setDeltaX(this->getRandomFloat(-deltaMax[static_cast<uint8_t>(explosionSize)], deltaMax[static_cast<uint8_t>(explosionSize)]));
            particle.setDeltaY(this->getRandomFloat(-deltaMax[static_cast<uint8_t>(explosionSize)], deltaMax[static_cast<uint8_t>(explosionSize)]));
            particle.setAge(random(0, ageStart[static_cast<uint8_t>(explosionSize)]));
            particle.setMaxAge(ageMax[static_cast<uint8_t>(explosionSize)] + random(0, ageMax[static_cast<uint8_t>(explosionSize)]));
            particle.setColor(explosionColor);
            particle.setActive(true);

            if (i > particlesToLaunch[static_cast<uint8_t>(explosionSize)] /2) {

                particle.setSize(1);

            }
            else {

                particle.setSize(this->getRandomFloat(1, sizeMax[static_cast<uint8_t>(explosionSize)]));

            }

        }

    }

    if (shockwaveRadius[static_cast<uint8_t>(explosionSize)] > 0) {  

        createShockwave(x, y, shockwaveRadius[static_cast<uint8_t>(explosionSize)]);

    }
    
}


void Game::createShockwave(int16_t x, int16_t y, uint8_t maxRadius) {

    uint8_t shockwaveIdx = this->shockwaves.getInactiveShwave();

    if (shockwaveIdx != Constants::Shockwave_None) {

        Shockwave &shockwave = this->shockwaves.shockwaves[shockwaveIdx];

        shockwave.setX(x);
        shockwave.setY(y);
        shockwave.setRadius(3);
        shockwave.setMaxRadius(maxRadius);
        shockwave.setSpeed(3);
        shockwave.setActive(true);
        
    }

}


void Game::renderShockwave() {

    for (Shockwave &shockwave : this->shockwaves.shockwaves) {

        if (shockwave.getActive()) {

            uint8_t color = 7 - ((shockwave.getRadius() + 1) / (shockwave.getMaxRadius() / 3));
            if (color == 4) color = 5;

            PD::setColor(color);
            PD::drawCircle(shockwave.getX(), shockwave.getY(), shockwave.getRadius());        

            shockwave.setRadius(shockwave.getRadius() + shockwave.getSpeed());

            if (shockwave.getRadius() > shockwave.getMaxRadius()) {

                shockwave.setActive(false);

            }

        }

    }
 
}

void Game::renderParticles() {

    for (Part &particle : this->particles.particles) {

        if (particle.getActive()) {

            uint8_t color = 7;

            switch (particle.getColor()) {

                case ExplosionColor::Blue:
                    color = this->getBlueShade(particle.getAge());
                    break;

                case ExplosionColor::Red:
                    color = this->getRedShade(particle.getAge());
                    break;

            }
            
            if (static_cast<uint8_t>(particle.getSize()) <= 1) {

                PD::setColor(color);
                PD::drawPixel(particle.getX(), particle.getY());

            }
            else {

                PD::setColor(color);
                PD::fillCircle(particle.getX(), particle.getY(), static_cast<uint8_t>(particle.getSize()));

            }


            particle.setX(particle.getX() + particle.getDeltaX());
            particle.setY(particle.getY() + particle.getDeltaY());

            particle.setDeltaX(particle.getDeltaX() * 0.65);
            particle.setDeltaY(particle.getDeltaY() * 0.65);
            particle.incAge();

            if (particle.getAge() > particle.getMaxAge()) {

                particle.setSize(particle.getSize() - 0.5);

            }

            if (particle.getSize() < 0) {

                particle.setActive(false);

            }
  
        }

    }  

}

uint8_t Game::getRedShade(uint8_t page) {

    switch (page) {

        case 6 ... 7:
            return 10;

        case 8 ... 10:
            return 9;

        case 11 ... 12:
            return 8;

        case 13 ... 15:
            return 2;

        case 16 ... 255:
            return 5;

        default:
            return 7;
    }

}

uint8_t Game::getBlueShade(uint8_t page) {

    switch (page) {

        case 6 ... 7:
            return 6;

        case 8 ... 10:
            return 12;

        case 11 ... 12:
            return 13;

        case 13 ... 15:
            return 1;

        case 16 ... 255:
            return 1;

        default:
            return 7;

    }

}
