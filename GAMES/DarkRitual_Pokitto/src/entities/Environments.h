#pragma once

#include "Pokitto.h"
#include "Environment.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


class Environments {

    public:

        Environments() {};  

        Environment & getEnvironment(uint8_t index);
        uint8_t getEnvironmentNum();

        void setEnvironmentNum(uint8_t eNum);

        void update();
        void render();

    private:

        Environment environments[MAXENVIROMENT];
        uint8_t eNum = 0;

};




 

