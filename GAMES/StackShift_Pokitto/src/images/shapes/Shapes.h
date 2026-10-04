#pragma once

namespace Images {

    #include "Green_00.h"
    #include "Green_01.h"
    #include "Green_02.h"
    #include "Green_03.h"
    #include "Red_00.h"
    #include "Red_01.h"
    #include "Red_02.h"
    #include "Red_03.h"
    #include "Yellow_00.h"
    #include "Yellow_01.h"
    #include "Yellow_02.h"
    #include "Yellow_03.h"
    #include "Green_Clear_00.h"
    #include "Green_Clear_01.h"
    #include "Green_Clear_02.h"
    #include "Green_Clear_03.h"
    #include "Red_Clear_00.h"
    #include "Red_Clear_01.h"
    #include "Red_Clear_02.h"
    #include "Red_Clear_03.h"
    #include "Yellow_Clear_00.h"
    #include "Yellow_Clear_01.h"
    #include "Yellow_Clear_02.h"
    #include "Yellow_Clear_03.h"
    #include "Rock_00.h"
    #include "Rock_01.h"
    #include "Rock_02.h"
    #include "grey/Grey_Green_Clear_00.h"
    #include "grey/Grey_Green_Clear_01.h"
    #include "grey/Grey_Green_Clear_02.h"
    #include "grey/Grey_Green_Clear_03.h"
    #include "grey/Grey_Red_Clear_00.h"
    #include "grey/Grey_Red_Clear_01.h"
    #include "grey/Grey_Red_Clear_02.h"
    #include "grey/Grey_Red_Clear_03.h"
    #include "grey/Grey_Yellow_Clear_00.h"
    #include "grey/Grey_Yellow_Clear_01.h"
    #include "grey/Grey_Yellow_Clear_02.h"
    #include "grey/Grey_Yellow_Clear_03.h"
    
    const uint8_t * const Symbols[8][4] = { 
        { Green_00, Green_01, Green_02, Green_03 },
        { Red_00, Red_01, Red_02, Red_03 },
        { Yellow_00, Yellow_01, Yellow_02, Yellow_03 },
        { Rock_02, Rock_01, Rock_00, Rock_02 },
        { Green_Clear_00, Green_Clear_01, Green_Clear_02, Green_Clear_03 },
        { Red_Clear_00, Red_Clear_01, Red_Clear_02, Red_Clear_03 },
        { Yellow_Clear_00, Yellow_Clear_01, Yellow_Clear_02, Yellow_Clear_03 },
        { Rock_02, Rock_02, Rock_02, Rock_02 },
    };

    const uint8_t * const GreySymbols[3][4] = { 
        { Grey_Green_Clear_00, Grey_Green_Clear_01, Grey_Green_Clear_02, Grey_Green_Clear_03 },
        { Grey_Red_Clear_00, Grey_Red_Clear_01, Grey_Red_Clear_02, Grey_Red_Clear_03 },
        { Grey_Yellow_Clear_00, Grey_Yellow_Clear_01, Grey_Yellow_Clear_02, Grey_Yellow_Clear_03 },
    };

    const uint8_t * const Rocks[3] = { 
        Rock_00, Rock_01, Rock_02
    };

};