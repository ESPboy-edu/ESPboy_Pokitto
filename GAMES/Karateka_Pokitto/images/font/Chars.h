#pragma once

namespace Images {

    #include "Char_a.h"
    #include "Char_b.h"
    #include "Char_c.h"
    #include "Char_d.h"
    #include "Char_e.h"
    #include "Char_f.h"
    #include "Char_g.h"
    #include "Char_h.h"
    #include "Char_i.h"
    #include "Char_j.h"
    #include "Char_k.h"
    #include "Char_l.h"
    #include "Char_m.h"
    #include "Char_n.h"
    #include "Char_o.h"
    #include "Char_p.h"
    #include "Char_q.h"
    #include "Char_r.h"
    #include "Char_s.h"
    #include "Char_t.h"
    #include "Char_u.h"
    #include "Char_v.h"
    #include "Char_w.h"
    #include "Char_x.h"
    #include "Char_y.h"
    #include "Char_z.h"
    #include "Char_comma.h"
    #include "Char_period.h"
    #include "Char_colon.h"
    #include "Char_dash.h"
    #include "Char_spacer.h"
    #include "Char_border.h"

    #include "Char_0.h"
    #include "Char_1.h"
    #include "Char_2.h"
    #include "Char_3.h"
    #include "Char_4.h"
    #include "Char_5.h"
    #include "Char_6.h"
    #include "Char_7.h"
    #include "Char_8.h"
    #include "Char_9.h"
    #include "Char_colon2.h"


    PROGMEM const uint8_t *const Chars[] = { 
        Char_a,
        Char_b,
        Char_c,
        Char_d,
        Char_e,
        Char_f,
        Char_g,
        Char_h,
        Char_i,
        Char_j,
        Char_k,
        Char_l,
        Char_m,
        Char_n,
        Char_o,
        Char_p,
        Char_q,
        Char_r,
        Char_s,
        Char_t,
        Char_u,
        Char_v,
        Char_w,
        Char_x,
        Char_y,
        Char_z,
        Char_comma,
        Char_period,
        Char_colon,
        Char_dash,
       
    };

    PROGMEM const uint8_t Char_Spacing[] = { 
        9,      // A
        10,     // B
        9,      // C
        9,      // D
        8,      // E
        8,      // F
        9,      // G
        9,      // H
        4,      // I
        5,      // J
        10,     // K
        5,      // L
        14,     // M
        10,     // N
        9,      // O
        10,     // P
        9,      // Q
        10,     // R
        7,      // S
        8,      // T
        10,     // U
        11,     // V
        16,     // W
        10,     // X
        11,     // Y
        9,      // Z
        6,      // Comma
        8,      // Period
        6,      // Colon
        4,      // Dash
    };
    
    
    PROGMEM const uint8_t *const Number[] = { 
        Char_0,
        Char_1,
        Char_2,
        Char_3,
        Char_4,
        Char_5,
        Char_6,
        Char_7,
        Char_8,
        Char_9,
        Char_colon2,
    };

    PROGMEM const uint8_t Number_Spacing[] = { 
        8,      // 0
        4,      // 1
        8,      // 2
        7,      // 3
        7,      // 4
        8,      // 5
        8,      // 6
        8,      // 7
        8,      // 8
        9,      // 9
        3,     // Colon2
    };


};



