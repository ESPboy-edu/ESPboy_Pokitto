
#pragma once

#include "Star.h"

class Stars {

    public:

        Star stars[Constants::Star_Count];

    public:
        
        void reset() {

            for (Star &star : this->stars) {

                star.setX(random(0, 220));
                star.setY(random(0, 176));

            }

        }

        void moveX(uint16_t yOffset) {

            for (Star &star : this->stars) {

                star.setX(star.getX() - 2);

                if (star.getX() > 250) {

                    star.setX(220);
                    star.setY(yOffset + random(0, 176));

                }

            }

        }

        void moveY() {

            for (Star &star : this->stars) {

                star.setY(star.getY() + 2);

                if (star.getY() > 178) {

                    star.setY(0);
                    star.setX(random(0, 220));

                }

            }

        }

};
