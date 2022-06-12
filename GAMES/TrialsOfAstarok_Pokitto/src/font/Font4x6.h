#pragma once

namespace Font {

  #define CHAR_EXCLAMATION 33
  #define CHAR_PERIOD 46
  #define CHAR_SPACE 32
  #define CHAR_LETTER_A 65
  #define CHAR_LETTER_Z 90
  #define CHAR_LETTER_A_LOWER 97
  #define CHAR_LETTER_Z_LOWER 122
  #define CHAR_NUMBER_0 48
  #define CHAR_NUMBER_9 57

  #define FONT_EXCLAMATION_INDEX 62
  #define FONT_PERIOD_INDEX 63
  #define FONT_SPACE_INDEX 64
  #define FONT_NUMBER_INDEX 52

  uint8_t static getIndex(const char c) {

    int8_t idx = -1;

    switch (c) {
      
      case CHAR_LETTER_A ... CHAR_LETTER_Z:
        idx = c - CHAR_LETTER_A;
        break;
    
      case CHAR_LETTER_A_LOWER ... CHAR_LETTER_Z_LOWER:
        idx = c - CHAR_LETTER_A_LOWER + 26;
        break;

      case CHAR_NUMBER_0 ... CHAR_NUMBER_9:
        idx = c - CHAR_NUMBER_0 + FONT_NUMBER_INDEX;
        break;
        
      case CHAR_EXCLAMATION:
        idx = FONT_EXCLAMATION_INDEX;
        break;
        
      case CHAR_PERIOD:
        idx = FONT_PERIOD_INDEX;
        break;
  
      case CHAR_SPACE:
        idx = FONT_SPACE_INDEX;
        break;

    }

    return idx;

  }

  #include "Font4x6_Upper_A.h"
  #include "Font4x6_Upper_B.h"
  #include "Font4x6_Upper_C.h"
  #include "Font4x6_Upper_D.h"
  #include "Font4x6_Upper_E.h"
  #include "Font4x6_Upper_F.h"
  #include "Font4x6_Upper_G.h"
  #include "Font4x6_Upper_H.h"
  #include "Font4x6_Upper_I.h"
  #include "Font4x6_Upper_J.h"
  #include "Font4x6_Upper_K.h"
  #include "Font4x6_Upper_L.h"
  #include "Font4x6_Upper_M.h"
  #include "Font4x6_Upper_N.h"
  #include "Font4x6_Upper_O.h"
  #include "Font4x6_Upper_P.h"
  #include "Font4x6_Upper_Q.h"
  #include "Font4x6_Upper_R.h"
  #include "Font4x6_Upper_S.h"
  #include "Font4x6_Upper_T.h"
  #include "Font4x6_Upper_U.h"
  #include "Font4x6_Upper_V.h"
  #include "Font4x6_Upper_W.h"
  #include "Font4x6_Upper_X.h"
  #include "Font4x6_Upper_Y.h"
  #include "Font4x6_Upper_Z.h"

  #include "Font4x6_Lower_A.h"
  #include "Font4x6_Lower_B.h"
  #include "Font4x6_Lower_C.h"
  #include "Font4x6_Lower_D.h"
  #include "Font4x6_Lower_E.h"
  #include "Font4x6_Lower_F.h"
  #include "Font4x6_Lower_G.h"
  #include "Font4x6_Lower_H.h"
  #include "Font4x6_Lower_I.h"
  #include "Font4x6_Lower_J.h"
  #include "Font4x6_Lower_K.h"
  #include "Font4x6_Lower_L.h"
  #include "Font4x6_Lower_M.h"
  #include "Font4x6_Lower_N.h"
  #include "Font4x6_Lower_O.h"
  #include "Font4x6_Lower_P.h"
  #include "Font4x6_Lower_Q.h"
  #include "Font4x6_Lower_R.h"
  #include "Font4x6_Lower_S.h"
  #include "Font4x6_Lower_T.h"
  #include "Font4x6_Lower_U.h"
  #include "Font4x6_Lower_V.h"
  #include "Font4x6_Lower_W.h"
  #include "Font4x6_Lower_X.h"
  #include "Font4x6_Lower_Y.h"
  #include "Font4x6_Lower_Z.h"

  #include "Font4x6_Number_0.h"
  #include "Font4x6_Number_1.h"
  #include "Font4x6_Number_2.h"
  #include "Font4x6_Number_3.h"
  #include "Font4x6_Number_4.h"
  #include "Font4x6_Number_5.h"
  #include "Font4x6_Number_6.h"
  #include "Font4x6_Number_7.h"
  #include "Font4x6_Number_8.h"
  #include "Font4x6_Number_9.h"

  #include "Font4x6_Exclaim.h"
  #include "Font4x6_Period.h"
  #include "Font4x6_Space.h"

  const uint8_t * const Images[] = { 
    Font4x6_Upper_A,
    Font4x6_Upper_B,
    Font4x6_Upper_C,
    Font4x6_Upper_D,
    Font4x6_Upper_E,
    Font4x6_Upper_F,
    Font4x6_Upper_G,
    Font4x6_Upper_H,
    Font4x6_Upper_I,
    Font4x6_Upper_J,
    Font4x6_Upper_K,
    Font4x6_Upper_L,
    Font4x6_Upper_M,
    Font4x6_Upper_N,
    Font4x6_Upper_O,
    Font4x6_Upper_P,
    Font4x6_Upper_Q,
    Font4x6_Upper_R,
    Font4x6_Upper_S,
    Font4x6_Upper_T,
    Font4x6_Upper_U,
    Font4x6_Upper_V,
    Font4x6_Upper_W,
    Font4x6_Upper_X,
    Font4x6_Upper_Y,
    Font4x6_Upper_Z,
    Font4x6_Lower_A,
    Font4x6_Lower_B,
    Font4x6_Lower_C,
    Font4x6_Lower_D,
    Font4x6_Lower_E,
    Font4x6_Lower_F,
    Font4x6_Lower_G,
    Font4x6_Lower_H,
    Font4x6_Lower_I,
    Font4x6_Lower_J,
    Font4x6_Lower_K,
    Font4x6_Lower_L,
    Font4x6_Lower_M,
    Font4x6_Lower_N,
    Font4x6_Lower_O,
    Font4x6_Lower_P,
    Font4x6_Lower_Q,
    Font4x6_Lower_R,
    Font4x6_Lower_S,
    Font4x6_Lower_T,
    Font4x6_Lower_U,
    Font4x6_Lower_V,
    Font4x6_Lower_W,
    Font4x6_Lower_X,
    Font4x6_Lower_Y,
    Font4x6_Lower_Z,
    Font4x6_Number_0,
    Font4x6_Number_1,
    Font4x6_Number_2,
    Font4x6_Number_3,
    Font4x6_Number_4,
    Font4x6_Number_5,
    Font4x6_Number_6,
    Font4x6_Number_7,
    Font4x6_Number_8,
    Font4x6_Number_9,
    Font4x6_Exclaim,
    Font4x6_Period,
    Font4x6_Space,
  };


};