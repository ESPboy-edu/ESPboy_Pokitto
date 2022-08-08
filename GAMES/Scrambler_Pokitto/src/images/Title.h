#pragma once

namespace Images {

    #include "title/Title.h"
    #include "title/Title_A.h"
    #include "title/Title_B.h"
    #include "title/Title_C.h"
    #include "title/Title_E.h"
    #include "title/Title_G.h"
    #include "title/Title_H.h"
    #include "title/Title_I.h"
    #include "title/Title_L.h"
    #include "title/Title_M.h"
    #include "title/Title_O.h"
    #include "title/Title_R.h"
    #include "title/Title_S.h"
    #include "title/Title_V.h"
    #include "title/Title_T.h"
    #include "title/Title_P.h"
    #include "title/Title_N.h"

    #include "title/Title_Left.h"
    #include "title/Title_Mid.h"
    #include "title/Title_Right.h"

    #include "title/HighScore.h"
    #include "title/GameOver.h"

    PROGMEM const uint8_t * const TitleLetters[] = { 
        Title_A, //0
        Title_B, //1
        Title_C, //2
        Title_E, //3
        Title_G, //4
        Title_H, //5
        Title_I, //6
        Title_L, //7
        Title_M, //8
        Title_O, //9
        Title_R, //10
        Title_S, //11
        Title_V, //12
        Title_T, //13
        Title_P, //14
        Title_N, //15
    };
};