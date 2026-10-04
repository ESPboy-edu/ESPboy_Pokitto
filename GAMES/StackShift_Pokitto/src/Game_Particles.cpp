#include "Pokitto.h"
#include "Game.h"
#include "utils/Consts.h"
#include "images/Images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::renderParticles() {

    for (int i = 0; i < PARTICLE_MAX; i++) {

        Particle &particle = this->particles[i];

        if (particle.isActive()) {                                                             // the dot should be rendered

            particle.update();
            uint8_t digits[5] = {};

            if (particle.render()) {

                switch (particle.getType()) {

                    case ParticleType::Score:

                        PD::setFont(fontC64);
                        PD::setColor(0, 15);

                        Utils::extractDigits(digits, particle.getScore());

                        switch (particle.getScore()) {

                            case 0 ... 9:

                                PD::drawBitmap(particle.getX() - 5, particle.getY() - 4, Images::ScoreBalloons_Sml[static_cast<uint8_t>(particle.getColour())]);
                                PD::setCursor(particle.getX(), particle.getY());
                                PD::print(particle.getScore(), 10);
                                break;

                            case 10 ... 99:

                                PD::drawBitmap(particle.getX() - 4, particle.getY() - 4, Images::ScoreBalloons_Med[static_cast<uint8_t>(particle.getColour())]);
                                for (uint8_t j = 2, x2 = particle.getX(); j > 0; --j, x2 += 8) {
                        
                                    PD::setCursor(x2, particle.getY());
                                    PD::print(digits[j - 1], 14);
                        
                                }                            
                                break;

                            case 100 ... 999:

                                PD::drawBitmap(particle.getX() - 3, particle.getY() - 4, Images::ScoreBalloons_Lrg[static_cast<uint8_t>(particle.getColour())]);
                                for (uint8_t j = 3, x2 = particle.getX(); j > 0; --j, x2 += 8) {
                        
                                    PD::setCursor(x2, particle.getY());
                                    PD::print(digits[j - 1], 14);
                        
                                }                            
                                break;

                        }

                        break;

                    default:
                        {
                            int pSize = particle.getSize();
                            const uint8_t colourCodes[10] = { 11, 3, 8, 14, 9, 10, 6, 7, 13, 14 };
                            
                            PD::setColor(colourCodes[(static_cast<uint8_t>(particle.getColour()) * 2) + (i%2)]);

                            if (pSize == 1) {

                                PD::drawPixel(particle.getX(), particle.getY(), 1);

                            } 
                            else {

                                PD::drawRectangle(particle.getX(), particle.getY(), pSize, pSize); //WHITE

                            }

                        }

                        break;

                }

            }

        }

    }

    PD::setColor(8, 0);

}


void Game::launchParticles(uint8_t col, uint8_t row, ExplosionSize explosionSize) {

    uint8_t launched = 0;
    const uint8_t maxParticles[3] = { 20, 30, 50 };

    for (Particle &particle : this->particles) {

        if (!particle.isActive()) {

            switch (explosionSize) {

                case ExplosionSize::Small:
                    particle.setX((col * PART_SIZE) + BOARD_X_OFFSET + random(PART_SIZE + 4));
                    particle.setY((row * PART_SIZE) + PART_SIZE + BOARD_Y_OFFSET);
                    particle.setVelX(random(-2, 3));
                    particle.setVelY(random(4));
                    particle.setCounter(random(10, 25));
                    particle.setSize(random(1, 3));
                    particle.setType(ParticleType::One);
                    particle.setColour(this->getColor(this->gameBoard[col][row]));
                    this->shake.explosionSize = ExplosionSize::Small;
                    this->shake.count = 1;
                    break;

                case ExplosionSize::Medium:
                    particle.setX((col * PART_SIZE) + BOARD_X_OFFSET + random(PART_SIZE + 4));
                    particle.setY((row * PART_SIZE) + random(PART_SIZE + 4) + BOARD_Y_OFFSET);
                    particle.setVelX(random(-3, 4));
                    particle.setVelY(random(6));
                    particle.setCounter(random(10, 46));
                    particle.setSize(random(1, 4));
                    particle.setType(ParticleType::One);
                    particle.setColour(this->getColor(this->gameBoard[col][row]));
                    this->shake.explosionSize = ExplosionSize::Medium;
                    this->shake.count = 5;     
                    break;

                case ExplosionSize::Large:
                    particle.setX(BOARD_X_OFFSET + random(BOARD_WIDTH * PART_SIZE));
                    particle.setY(((BOARD_HEIGHT - 1)*PART_SIZE) + random(PART_SIZE + 2) + BOARD_Y_OFFSET);
                    particle.setVelX(random(-7, 8));
                    particle.setVelY(random(4, 9));
                    particle.setCounter(random(20, 86));
                    particle.setSize(random(1, 5));
                    particle.setType(ParticleType::Zero);
                    particle.setColour(this->getColor(this->gameBoard[col][row]));
                    this->shake.explosionSize = ExplosionSize::Large;
                    this->shake.count = 10;
                    break;

            }

            launched++;

            if (launched == maxParticles[static_cast<uint8_t>(explosionSize)]) {

                break;

            }

        }

    }

}


void Game::launchPointsParticles(uint16_t points, Color color, uint8_t delay) {

    currentScore += points;
    uint8_t scoreCount = 90;

    const uint8_t size[3] = { 20, 26, 32 };
    const uint8_t counts[3] = { 60, 90, 100 };
    const uint8_t velY[3] = { 3, 5, 6 };

    for (Particle &particle : this->particles) {

        if (!particle.isActive()) {

            uint8_t nums = 0;

            if (points > 9)     nums = 1;
            if (points > 99)    nums = 2;

            uint8_t r = random(BOARD_X_OFFSET + (BOARD_WIDTH * PART_SIZE) + 4 + 16, 220 - size[nums]);
            particle.setX(r);
            particle.setY((BOARD_HEIGHT * PART_SIZE) + BOARD_Y_OFFSET);
            particle.setVelX(0);
            particle.setVelY(velY[nums]);
            particle.setCounter(counts[nums]);
            particle.setSize(1);
            particle.setType(ParticleType::Score);
            particle.setColour(color);
            particle.setScore(points);
            particle.setDelay(delay * 5);
            return;    

        }

    }

}



void Game::launchHighScoreParticles() {

    uint8_t launched = 0;

    for (Particle &particle : this->particles) {

        if (!particle.isActive()) {

            particle.setX(random(60, 160));
            particle.setY(random(80, 140));
            particle.setVelX(random(-7, 8));
            particle.setVelY(random(9));
            particle.setCounter(random(10, 66));
            particle.setSize(random(1, 5));
            particle.setType(ParticleType::Two);
            particle.setColour(static_cast<Color>(random(0, static_cast<uint8_t>(Color::Max))));

            launched++;

            if (launched == 20) {

                break;

            }

        }

    }

}
