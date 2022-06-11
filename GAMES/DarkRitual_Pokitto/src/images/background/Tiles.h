#pragma once

namespace Images {

    #include "Tile_00.h"
    // #include "Tile_01.h"
    // #include "Tile_02.h"
    #include "Tile_03.h"
    #include "Tile_04.h"
    #include "Tile_05.h"
    // #include "Tile_06.h"
    // #include "Tile_07.h"
    #include "Tile_08.h"
    #include "Tile_09.h"
    #include "Tile_10.h"
    #include "Tile_11.h"
    // #include "Tile_12.h"
    // #include "Tile_13.h"
    #include "Tile_14.h"
    // #include "Tile_15.h"
    #include "Tile_16.h"
    #include "Tile_17.h"
    #include "Tile_18.h"
    #include "Tile_19.h"
    // #include "Tile_20.h"
    #include "orig/Tile_21.h"
    #include "orig/Tile_22.h"
    #include "orig/Tile_23.h"
    #include "orig/Tile_24.h"
    #include "orig/Tile_25.h"
    #include "orig/Tile_26.h"
    #include "orig/Tile_27.h"
    #include "orig/Tile_28.h"
    // #include "Tile_29.h"
    // #include "Tile_30.h"
    // #include "Tile_31.h"
    // #include "Tile_32.h"
    #include "Tile_33.h"
    #include "orig/Tile_34.h"
    #include "orig/Tile_35.h"
    #include "orig/Tile_36.h"
    #include "orig/Tile_37.h"
    #include "orig/Tile_38.h"
    #include "Tile_39.h"
    #include "Tile_40.h"
    #include "Tile_41.h"
    #include "Tile_42.h"
    #include "Tile_43.h"
    #include "Tile_44.h"
    #include "Tile_45.h"
    #include "Tile_46.h"
    #include "Tile_47.h"
    #include "Tile_48.h"
    // #include "Tile_49.h"
    // #include "Tile_50.h"
    // #include "Tile_51.h"
    // #include "Tile_52.h"
    #include "Tile_53.h"
    #include "Tile_54.h"
    #include "Tile_55.h"
    #include "Tile_56.h"
    #include "Tile_57.h"
    #include "Tile_58.h"
    #include "Tile_59.h"
    #include "Tile_60.h"
    #include "Tile_61.h"
    #include "Tile_62.h"
    #include "Tile_63.h"
    #include "Tile_64.h"
    #include "orig/Tile_65.h"
    #include "orig/Tile_66.h"
    #include "orig/Tile_67.h"
    #include "orig/Tile_68.h"
    #include "orig/Tile_69.h"
    #include "orig/Tile_70.h"
    #include "orig/Tile_71.h"
    #include "orig/Tile_72.h"
    #include "Tile_73.h"
    #include "Tile_74.h"
    #include "Tile_75.h"
    #include "Tile_76.h"
    #include "Tile_77.h"
    #include "Tile_78.h"
    #include "Tile_79.h"
    #include "Tile_80.h"
    #include "Tile_81.h"
    #include "Tile_82.h"
    #include "Tile_83.h"
    #include "Tile_84.h"
    #include "Tile_85.h"
    #include "Tile_86.h"
    #include "Tile_89.h"
    #include "Tile_90.h"
    #include "Tile_91.h"
    #include "Tile_92.h"
    #include "Tile_93.h"
    #include "Tile_94.h"
    #include "Tile_95.h"
    #include "Tile_97.h"
    #include "Tile_99.h"
    #include "Tile_100.h"

    #include "orig/CornerFillTL.h"
    #include "orig/CornerFillTR.h"
    #include "orig/CornerFillLL.h"
    #include "orig/CornerFillLR.h"
    #include "boss/CornerFillTL_Boss.h"
    #include "boss/CornerFillTR_Boss.h"
    #include "boss/CornerFillLL_Boss.h"
    #include "boss/CornerFillLR_Boss.h"

    #include "boss/Tile_21_Boss.h"
    #include "boss/Tile_22_Boss.h"
    #include "boss/Tile_23_Boss.h"
    #include "boss/Tile_24_Boss.h"
    #include "boss/Tile_25_Boss.h"
    #include "boss/Tile_26_Boss.h"
    #include "boss/Tile_27_Boss.h"
    #include "boss/Tile_28_Boss.h"
    #include "boss/Tile_34_Boss.h"
    #include "boss/Tile_35_Boss.h"
    #include "boss/Tile_36_Boss.h"
    #include "boss/Tile_37_Boss.h"
    #include "boss/Tile_38_Boss.h"
    #include "boss/Tile_65_Boss.h"
    #include "boss/Tile_66_Boss.h"
    #include "boss/Tile_67_Boss.h"
    #include "boss/Tile_68_Boss.h"
    #include "boss/Tile_69_Boss.h"
    #include "boss/Tile_70_Boss.h"
    #include "boss/Tile_71_Boss.h"
    #include "boss/Tile_72_Boss.h"

    PROGMEM const uint8_t * const CornerFills[] = { 
    CornerFillTL,
    CornerFillTR,
    CornerFillLL,
    CornerFillLR,
    CornerFillTL_Boss,
    CornerFillTR_Boss,
    CornerFillLL_Boss,
    CornerFillLR_Boss,
    };

    PROGMEM const uint8_t * const Tiles[] = { 
    Tile_00,
    nullptr,
    nullptr,
    Tile_03,
    Tile_04,
    Tile_05,
    nullptr,
    nullptr,
    Tile_08,
    Tile_09,
    Tile_10,
    Tile_11,
    nullptr,
    nullptr,
    Tile_14,
    nullptr,
    Tile_16,
    Tile_17,
    Tile_18,
    Tile_19,
    nullptr,
    Tile_21,
    Tile_22,
    Tile_23,
    Tile_24,
    Tile_25,
    Tile_26,
    Tile_27,
    Tile_28,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Tile_33,
    Tile_34,
    Tile_35,
    Tile_36,
    Tile_37,
    Tile_38,
    Tile_39,
    Tile_40,
    Tile_41,
    Tile_42,
    Tile_43,
    Tile_44,
    Tile_45,
    Tile_46,
    Tile_47,
    Tile_48,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Tile_53,
    Tile_54,
    Tile_55,
    Tile_56,
    Tile_57,
    Tile_58,
    Tile_59,
    Tile_60,
    Tile_61,
    Tile_62,
    Tile_63,
    Tile_64,
    Tile_65,
    Tile_66,
    Tile_67,
    Tile_68,
    Tile_69,
    Tile_70,
    Tile_71,
    Tile_72,
    Tile_73,
    Tile_74,
    Tile_75,
    Tile_76,
    Tile_77,
    Tile_78,
    Tile_79,
    Tile_80,
    Tile_81,
    Tile_82,
    Tile_83,
    Tile_84,
    Tile_85,
    Tile_86,
    Tile_08, //87 is chest random same as 08.
    Tile_08, //88 is chest random same as 08.
    Tile_89,
    Tile_90,
    Tile_91,
    Tile_92,
    Tile_93,
    Tile_94,
    Tile_95,
    Tile_08, //96 is chest random same as 08.
    Tile_97,
    Tile_00, //98 Filler
    Tile_99, // 3 Skulls
    Tile_100, // Shadow
    };

    PROGMEM const uint8_t * const Tiles_Boss[] = { 
    Tile_00,
    nullptr,
    nullptr,
    Tile_03,
    Tile_04,
    Tile_05,
    nullptr,
    nullptr,
    Tile_08,
    Tile_09,
    Tile_10,
    Tile_11,
    nullptr,
    nullptr,
    Tile_14,
    nullptr,
    Tile_16,
    Tile_17,
    Tile_18,
    Tile_19,
    nullptr,
    Tile_21_Boss,
    Tile_22_Boss,
    Tile_23_Boss,
    Tile_24_Boss,
    Tile_25_Boss,
    Tile_26_Boss,
    Tile_27_Boss,
    Tile_28_Boss,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Tile_33,
    Tile_34_Boss,
    Tile_35_Boss,
    Tile_36_Boss,
    Tile_37_Boss,
    Tile_38_Boss,
    Tile_39,
    Tile_40,
    Tile_41,
    Tile_42,
    Tile_43,
    Tile_44,
    Tile_45,
    Tile_46,
    Tile_47,
    Tile_48,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Tile_53,
    Tile_54,
    Tile_55,
    Tile_56,
    Tile_57,
    Tile_58,
    Tile_59,
    Tile_60,
    Tile_61,
    Tile_62,
    Tile_63,
    Tile_64,
    Tile_65_Boss,
    Tile_66_Boss,
    Tile_67_Boss,
    Tile_68_Boss,
    Tile_69_Boss,
    Tile_70_Boss,
    Tile_71_Boss,
    Tile_72_Boss,
    Tile_73,
    Tile_74,
    Tile_75,
    Tile_76,
    Tile_77,
    Tile_78,
    Tile_79,
    Tile_80,
    Tile_81,
    Tile_82,
    Tile_83,
    Tile_84,
    Tile_85,
    Tile_86,
    Tile_08, //87 is chest random same as 08.
    Tile_08, //88 is chest random same as 08.
    Tile_89,
    Tile_90,
    Tile_91,
    Tile_92,
    Tile_93,
    Tile_94,
    Tile_95,
    Tile_08, //96 is chest random same as 08.
    Tile_97,
    Tile_00, //98 Filler
    Tile_99, // 3 Skulls
    Tile_100, // Shadow
    };

};