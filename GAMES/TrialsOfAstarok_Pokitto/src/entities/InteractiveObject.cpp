#include "InteractiveObject.h"
#include "../AstarokGame.h"

void InteractiveObject::deactivate(bool explode) {

    if (!explode) {

        this->explodeCounter = 0;
        this->x = -1;
        this->y = -1;

    }
    else {

        this->explodeCounter = 21;

    }

}

ObjectTypes InteractiveObject::getType() {

    return this->type;

}

void InteractiveObject::updateExplosion() {

    if (this->explodeCounter > 0) {

        this->explodeCounter--;

        if (this->explodeCounter == 0) {

            this->x = -1;
            this->y = -1;

        }

    }

}

bool InteractiveObject::getActive() {

    return (this->x >= 0 && this->explodeCounter == 0);

}