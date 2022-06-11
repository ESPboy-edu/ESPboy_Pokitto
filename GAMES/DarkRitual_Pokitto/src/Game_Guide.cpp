#include "Pokitto.h"
#include "Game.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


PROGMEM const char message01_01[] = "Dark Ritual";
PROGMEM const char message01_02[] = "";
PROGMEM const char message01_03[] = "You have entered";
PROGMEM const char message01_04[] = "a dungeon system";
PROGMEM const char message01_05[] = "full of surprises,";
PROGMEM const char message01_06[] = "challenges and, of";
PROGMEM const char message01_07[] = "course, rewards. ";
PROGMEM const char message01_08[] = "";
PROGMEM const char message01_09[] = "Battle your way to";
PROGMEM const char message01_10[] = "the last level and";
PROGMEM const char message01_11[] = "make an offering at";
PROGMEM const char message01_12[] = "the altar to buy";
PROGMEM const char message01_13[] = "back your freedom.";
PROGMEM const char message01_14[] = "";
PROGMEM const char message01_15[] = "You must complete";
PROGMEM const char message01_16[] = "each level in the";
PROGMEM const char message01_17[] = "alloted time - if";
PROGMEM const char message01_18[] = "you fail to do so";
PROGMEM const char message01_19[] = "you will perish.";
PROGMEM const char message01_20[] = "";
PROGMEM const char message01_21[] = "You will discover";
PROGMEM const char message01_22[] = "runes or win them";
PROGMEM const char message01_23[] = "by killing enemies";
PROGMEM const char message01_24[] = "- there are six in";
PROGMEM const char message01_25[] = "all to collect and";
PROGMEM const char message01_26[] = "you will need all";
PROGMEM const char message01_27[] = "of them before you";
PROGMEM const char message01_28[] = "make your offering";
PROGMEM const char message01_29[] = "at the altar.";
PROGMEM const char message01_30[] = "";
PROGMEM const char message01_31[] = "You will find more";
PROGMEM const char message01_32[] = "information in this";
PROGMEM const char message01_33[] = "first level as you";
PROGMEM const char message01_34[] = "approach new items";
PROGMEM const char message01_35[] = "or enemies. After";
PROGMEM const char message01_36[] = "that, you will be";
PROGMEM const char message01_37[] = "on your own ..";

PROGMEM const char message02_01[] = "As you travel, you";
PROGMEM const char message02_02[] = "will come across ";
PROGMEM const char message02_03[] = "coins, food, magic";
PROGMEM const char message02_04[] = "potions and spells.";
PROGMEM const char message02_05[] = "";
PROGMEM const char message02_06[] = "You can only carry";
PROGMEM const char message02_07[] = "a handful of items";
PROGMEM const char message02_08[] = "so you must choose";
PROGMEM const char message02_09[] = "carefully.";
PROGMEM const char message02_10[] = "";
PROGMEM const char message02_11[] = "You can view your";
PROGMEM const char message02_12[] = "items by pressing";
PROGMEM const char message02_13[] = "the C button. From";
PROGMEM const char message02_14[] = "there you can use";
PROGMEM const char message02_15[] = "items or drop those";
PROGMEM const char message02_16[] = "you no longer need.";

PROGMEM const char message03_01[] = "Chests and barrels";
PROGMEM const char message03_02[] = "can sometimes hide";
PROGMEM const char message03_03[] = "goodies. Opening or";
PROGMEM const char message03_04[] = "shooting them will";
PROGMEM const char message03_05[] = "reveal any items";
PROGMEM const char message03_06[] = "they may be hiding.";
PROGMEM const char message03_07[] = "";
PROGMEM const char message03_08[] = "Some doors require";
PROGMEM const char message03_09[] = "keys to unlock them.";
PROGMEM const char message03_10[] = "Search the nearby ";
PROGMEM const char message03_11[] = "rooms, barrels and";
PROGMEM const char message03_12[] = "chests to find one.";

PROGMEM const char message04_01[] = "Other doors can be";
PROGMEM const char message04_02[] = "activated by using";
PROGMEM const char message04_03[] = "a lever or standing";
PROGMEM const char message04_04[] = "on a pressure plate";
PROGMEM const char message04_05[] = "";
PROGMEM const char message04_06[] = "Some levers may be";
PROGMEM const char message04_07[] = "broken but you will";
PROGMEM const char message04_08[] = "be able to fix them";
PROGMEM const char message04_09[] = "using tools lying";
PROGMEM const char message04_10[] = "nearby.";
PROGMEM const char message04_11[] = "";
PROGMEM const char message04_12[] = "To navigate some";
PROGMEM const char message04_13[] = "rooms, you may need";
PROGMEM const char message04_14[] = "to use two or more";
PROGMEM const char message04_15[] = "levers to arrange";
PROGMEM const char message04_16[] = "the doors to allow";
PROGMEM const char message04_17[] = "passage.";

PROGMEM const char message05_01[] = "By now, you have";
PROGMEM const char message05_02[] = "probably worked";
PROGMEM const char message05_03[] = "out that you can";
PROGMEM const char message05_04[] = "cast spells.";
PROGMEM const char message05_05[] = "";
PROGMEM const char message05_06[] = "The dungeons are";
PROGMEM const char message05_07[] = "full of enemies";
PROGMEM const char message05_08[] = "that will kill you";
PROGMEM const char message05_09[] = "if you do not kill";
PROGMEM const char message05_10[] = "them first.";
PROGMEM const char message05_11[] = "";
PROGMEM const char message05_12[] = "You can use barrels";
PROGMEM const char message05_13[] = "and chests to hide";
PROGMEM const char message05_14[] = "behind and you will";
PROGMEM const char message05_15[] = "find additional";
PROGMEM const char message05_16[] = "spells that you";
PROGMEM const char message05_17[] = "should conserve";
PROGMEM const char message05_18[] = "until needed.";

PROGMEM const char message06_01[] = "Hopefully you have";
PROGMEM const char message06_02[] = "been collecting ";
PROGMEM const char message06_03[] = "all the coins you";
PROGMEM const char message06_04[] = "have seen in your";
PROGMEM const char message06_05[] = "travels.";
PROGMEM const char message06_06[] = "";
PROGMEM const char message06_07[] = "You can visit the";
PROGMEM const char message06_08[] = "shops that you will";
PROGMEM const char message06_09[] = "discover scattered";
PROGMEM const char message06_10[] = "around to buy the ";
PROGMEM const char message06_11[] = "items you will need";
PROGMEM const char message06_12[] = "to restore your";
PROGMEM const char message06_13[] = "health or to equip";
PROGMEM const char message06_14[] = "you to battle the";
PROGMEM const char message06_15[] = "stronger enemies";
PROGMEM const char message06_16[] = "found in higher";
PROGMEM const char message06_17[] = "levels.";

PROGMEM const char message07_01[] = "Congratulations!";
PROGMEM const char message07_02[] = "";
PROGMEM const char message07_03[] = "Although you have";
PROGMEM const char message07_04[] = "seen some of the";
PROGMEM const char message07_05[] = "enemies and items";
PROGMEM const char message07_06[] = "to be found in the";
PROGMEM const char message07_07[] = "dungeons, there are";
PROGMEM const char message07_08[] = "plenty more to ";
PROGMEM const char message07_09[] = "find and battle as";
PROGMEM const char message07_10[] = "you explore.";
PROGMEM const char message07_11[] = "";
PROGMEM const char message07_12[] = "Good luck!";

PROGMEM const char message08_01[] = "You may think you";
PROGMEM const char message08_02[] = "have collected";
PROGMEM const char message08_03[] = "everything from a";
PROGMEM const char message08_04[] = "room but watch";
PROGMEM const char message08_05[] = "those enemies as";
PROGMEM const char message08_06[] = "they are thieves!";

PROGMEM const char message09_01[] = "Barrels seem to";
PROGMEM const char message09_02[] = "just block your way";
PROGMEM const char message09_03[] = "but can be a great";
PROGMEM const char message09_04[] = "shield. Sometimes";
PROGMEM const char message09_05[] = "they can contain a";
PROGMEM const char message09_06[] = "treasure.";

PROGMEM const char message10_01[] = "Did you know that";
PROGMEM const char message10_02[] = "certain treasures";
PROGMEM const char message10_03[] = "can surprise you?";
PROGMEM const char message10_04[] = "You might end up";
PROGMEM const char message10_05[] = "being chased by";
PROGMEM const char message10_06[] = "some.";

PROGMEM const char message11_01[] = "Find all the runes";
PROGMEM const char message11_02[] = "in order to perform";
PROGMEM const char message11_03[] = "the secret ritual";
PROGMEM const char message11_04[] = "before our rivals.";
PROGMEM const char message11_05[] = "We must be the ones,";
PROGMEM const char message11_06[] = "the chosen ones.";

PROGMEM const char message12_01[] = "They say sometimes";
PROGMEM const char message12_02[] = "you can hear bones";
PROGMEM const char message12_03[] = "shattering loudly";
PROGMEM const char message12_04[] = "underground. Cries.";
PROGMEM const char message12_05[] = "Screams. Must be ";
PROGMEM const char message12_06[] = "the necromancers.. ";

PROGMEM const char message13_01[] = "In the depth of the";
PROGMEM const char message13_02[] = "dungeons, even a";
PROGMEM const char message13_03[] = "master cultist like";
PROGMEM const char message13_04[] = "you could go insane";
PROGMEM const char message13_05[] = "Maybe it's the only";
PROGMEM const char message13_06[] = "way to ascend?";

PROGMEM const char message14_01[] = "Save some of your";
PROGMEM const char message14_02[] = "potions and spells";
PROGMEM const char message14_03[] = "for later levels -";
PROGMEM const char message14_04[] = "you will definitely";
PROGMEM const char message14_05[] = "need them!";

PROGMEM const char message15_01[] = "The cultists are all";
PROGMEM const char message15_02[] = "counting on you to";
PROGMEM const char message15_03[] = "free their souls. Go";
PROGMEM const char message15_04[] = "forth and conquer";
PROGMEM const char message15_05[] = "thise enemies!";

const uint8_t messageLengths[] = { 37, 16, 12, 17, 18, 17, 12, 6, 6, 6, 6, 6, 6, 5, 5 };

PROGMEM const char * const messages01[] = { 
message01_01,
message01_02,
message01_03,
message01_04,
message01_05,
message01_06,
message01_07,
message01_08,
message01_09,
message01_10,
message01_11,
message01_12,
message01_13,
message01_14,
message01_15,
message01_16,
message01_17,
message01_18,
message01_19,
message01_20,
message01_21,
message01_22,
message01_23,
message01_24,
message01_25,
message01_26,
message01_27,
message01_28,
message01_29,
message01_30,
message01_31,
message01_32,
message01_33,
message01_34,
message01_35,
message01_36,
message01_37,
};

PROGMEM const char * const messages02[] = { 
message02_01,
message02_02,
message02_03,
message02_04,
message02_05,
message02_06,
message02_07,
message02_08,
message02_09,
message02_10,
message02_11,
message02_12,
message02_13,
message02_14,
message02_15,
message02_16,
};

PROGMEM const char * const messages03[] = { 
message03_01,
message03_02,
message03_03,
message03_04,
message03_05,
message03_06,
message03_07,
message03_08,
message03_09,
message03_10,
message03_11,
message03_12,
};

PROGMEM const char * const messages04[] = { 
message04_01,
message04_02,
message04_03,
message04_04,
message04_05,
message04_06,
message04_07,
message04_08,
message04_09,
message04_10,
message04_11,
message04_12,
message04_13,
message04_14,
message04_15,
message04_16,
message04_17,
};

PROGMEM const char * const messages05[] = { 
message05_01,
message05_02,
message05_03,
message05_04,
message05_05,
message05_06,
message05_07,
message05_08,
message05_09,
message05_10,
message05_11,
message05_12,
message05_13,
message05_14,
message05_15,
message05_16,
message05_17,
message05_18,
};

PROGMEM const char * const messages06[] = { 
message06_01,
message06_02,
message06_03,
message06_04,
message06_05,
message06_06,
message06_07,
message06_08,
message06_09,
message06_10,
message06_11,
message06_12,
message06_13,
message06_14,
message06_15,
message06_16,
message06_17,
};

PROGMEM const char * const messages07[] = { 
message07_01,
message07_02,
message07_03,
message07_04,
message07_05,
message07_06,
message07_07,
message07_08,
message07_09,
message07_10,
message07_11,
message07_12,
};

PROGMEM const char * const messages08[] = { 
message08_01,
message08_02,
message08_03,
message08_04,
message08_05,
message08_06,
};

PROGMEM const char * const messages09[] = { 
message09_01,
message09_02,
message09_03,
message09_04,
message09_05,
message09_06,
};

PROGMEM const char * const messages10[] = { 
message10_01,
message10_02,
message10_03,
message10_04,
message10_05,
message10_06,
};

PROGMEM const char * const messages11[] = { 
message11_01,
message11_02,
message11_03,
message11_04,
message11_05,
message11_06,
};

PROGMEM const char * const messages12[] = { 
message12_01,
message12_02,
message12_03,
message12_04,
message12_05,
message12_06,
};

PROGMEM const char * const messages13[] = { 
message13_01,
message13_02,
message13_03,
message13_04,
message13_05,
message13_06,
};

PROGMEM const char * const messages14[] = { 
message14_01,
message14_02,
message14_03,
message14_04,
message14_05,
};

PROGMEM const char * const messages15[] = { 
message15_01,
message15_02,
message15_03,
message15_04,
message15_05,
};


void Game::showGuide() {


    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B) || PC::buttons.pressed(BTN_C)) {

        PD::setColor(0, 0);
        gameState = GameState::Game; 
        this->player.setCultists(this->player.getCultists() + 1);
        this->guide->setPuffIndex(20);

    }

    if ((PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 2)) && this->guideTop > 0) {

        this->guideTop--; 

    }

    if ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 2)) && this->guideTop + 6 < messageLengths[this->guideNumber]) {

        this->guideTop++; 

    }


    // Render screen ..

    PD::fillScreen(0);
    this->renderEnvironment(!this->map.isBossLevel() && !this->map.isAltarLevel(), 0, 0);
    this->renderHud();

    PD::setColor(15);
    PD::fillRect(14, 8, 86, 60);

    PD::drawBitmap(7, 1, Images::AltarTOP_Wide);
    PD::drawBitmap(6, 8, Images::AltarLHS);
    PD::drawBitmap(96, 8, Images::AltarRHS);
    PD::drawBitmap(8, 64, Images::AltarBOT_Wide);


    PD::setColor(4, 15);
    PD::setFont(font3x5);

    uint8_t endLoop = (this->guideTop + 6 > messageLengths[this->guideNumber] ? messageLengths[this->guideNumber] : this->guideTop + 6);

    uint8_t xOffset = (endLoop > 6 ? 0 : 2);

    for (uint8_t x = this->guideTop; x < endLoop; x++) {

        switch (this->guideNumber) {

            case 0:
                {
                    const char * message = messages01[x];
                    showGuide_renderLine(x - this->guideTop, xOffset, message);
                }
                break;

            case 1:
                {
                    const char * message = messages02[x];
                    showGuide_renderLine(x - this->guideTop, xOffset, message);
                }
                break;

            case 2:
                {
                    const char * message = messages03[x];
                    showGuide_renderLine(x - this->guideTop, xOffset, message);
                }
                break;

            case 3:
                {
                    const char * message = messages04[x];
                    showGuide_renderLine(x - this->guideTop, xOffset, message);
                }
                break;

            case 4:
                {
                    const char * message = messages05[x];
                    showGuide_renderLine(x - this->guideTop, xOffset, message);
                }
                break;

            case 5:
                {
                    const char * message = messages06[x];
                    showGuide_renderLine(x - this->guideTop, xOffset, message);
                }
                break;

            case 6:
                {
                    const char * message = messages07[x];
                    showGuide_renderLine(x - this->guideTop, xOffset, message);
                }
                break;

            case 7:
                {
                    const char * message = messages08[x];
                    showGuide_renderLine(x - this->guideTop, xOffset, message);
                }
                break;

            case 8:
                {
                    const char * message = messages09[x];
                    showGuide_renderLine(x - this->guideTop, xOffset, message);
                }
                break;

            case 9:
                {
                    const char * message = messages10[x];
                    showGuide_renderLine(x - this->guideTop, xOffset, message);
                }
                break;         

            case 10:
                {
                    const char * message = messages11[x];
                    showGuide_renderLine(x - this->guideTop, xOffset, message);
                }
                break;               

            case 11:
                {
                    const char * message = messages12[x];
                    showGuide_renderLine(x - this->guideTop, xOffset, message);
                }
                break;       

            case 12:
                {
                    const char * message = messages13[x];
                    showGuide_renderLine(x - this->guideTop, xOffset, message);
                }
                break;              

            case 13:
                {
                    const char * message = messages14[x];
                    showGuide_renderLine(x - this->guideTop, xOffset, message);
                }
                break;              

            case 14:
                {
                    const char * message = messages15[x];
                    showGuide_renderLine(x - this->guideTop, xOffset, message);
                }
                break;                       

        }

    }


    // Draw scroll bar ..

    if (endLoop > 6) {
            
        PD::setColor(9);
        PD::drawRect(91, 13, 4, 43);

        if (messageLengths[this->guideNumber] > 6) {

            uint16_t length = 410 / messageLengths[this->guideNumber];

            PD::drawLine(93, 15 + ((this->guideTop * length) / 10), 93, 14 + ((this->guideTop + 6) * length) / 10);

            if (this->guideTop > 0) {
                PD::drawBitmap(91, 8, Images::ArrowUpEnabled);
            }
            else {
                PD::drawBitmap(91, 8, Images::ArrowUpDisabled);
            }

            if (this->guideTop + 6 == messageLengths[this->guideNumber]) {
                PD::drawBitmap(91, 58, Images::ArrowDownDisabled);
            }
            else {
                PD::drawBitmap(91, 58, Images::ArrowDownEnabled);
            }
            
        }
        else {

            PD::drawBitmap(91, 8, Images::ArrowUpDisabled);
            PD::drawBitmap(91, 58, Images::ArrowDownDisabled);

        }

    }

    PD::setFont(fontKoubit);

}

void Game::showGuide_renderLine(uint8_t line, uint8_t xOffset, const char message[]) {

    PD::setCursor(16 + xOffset, 13 + (line * 8));
    PD::print(message);

}