#include "Environments.h"
#include "../images/Images.h"

Environment & Environments::getEnvironment(uint8_t index) {

    return this->environments[index];
    
}

uint8_t Environments::getEnvironmentNum() {

    return this->eNum;

}

void Environments::setEnvironmentNum(uint8_t eNum) {

    this->eNum = eNum;

}