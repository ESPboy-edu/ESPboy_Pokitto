#include "Pokitto.h"
#include "Game.h"

#include "utils/Stack.h"
#include "utils/PlayerStances.h"
#include "utils/EnemyStances.h"
#include "images/images.h"
#include "utils/Enums.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

//                                 0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31 
const char introText_Line_00[] = { ' ', ' ', ' ', 'h', 'i', 'g', 'h', ' ', 'a', 't', 'o', 'p', ' ', ' ', 'a', '+', };
const char introText_Line_01[] = { 'c', 'r', 'a', 'g', 'g', 'y', ' ', 'c', 'l', 'i', 'f', 'f', '+', };
const char introText_Line_02[] = { 'g', 'u', 'a', 'r', 'd', 'e', 'd', ' ', 'b', 'y', ' ', 'a', 'n', '+',};
const char introText_Line_03[] = { 'a', 'r', 'm', 'y', ' ', 'o', 'f', '+', };
const char introText_Line_04[] = { 'f', 'i', 'e', 'r', 'c', 'e', '+', };
const char introText_Line_05[] = { 'w', 'a', 'r', 'r', 'i', 'o', 'r', 's', ',', '+', };
const char introText_Line_06[] = { 's', 't', 'a', 'n', 'd', 's', ' ', 't', 'h', 'e', '+', };
const char introText_Line_07[] = { 'f', 'o', 'r', 't', 'r', 'e', 's', 's', '+', };
const char introText_Line_08[] = { 'o', 'f', ' ', 't', 'h', 'e', ' ', 'e', 'v', 'i', 'l', '+' };
const char introText_Line_09[] = { '=' };
const char introText_Line_10[] = { 'w', 'a', 'r', 'l', 'o', 'r', 'd', '+' };
const char introText_Line_11[] = { 'a', 'k', 'u', 'm', 'a', '.', 'd', 'e', 'e', 'p', '+' };
const char introText_Line_12[] = { 'i', 'n', ' ', 't', 'h', 'e', '+' };
const char introText_Line_13[] = { 'd', 'a', 'r', 'k', 'e', 's', 't', '+' };
const char introText_Line_14[] = { 'd', 'u', 'n', 'g', 'e', 'o', 'n', '+' };
const char introText_Line_15[] = { 'o', 'f', ' ', 't', 'h', 'e', '+' };
const char introText_Line_16[] = { 'c', 'a', 's', 't', 'l', 'e', ',', 'a', 'k', 'u', 'm', 'a', '+' };
const char introText_Line_17[] = { 'g', 'l', 'o', 'a', 't', 's', ' ', 'o', 'v', 'e', 'r', '+' };
const char introText_Line_18[] = { 'h' ,'i', 's', ' ', 'l', 'o', 'v', 'e', 'l', 'y', '+',  };
const char introText_Line_19[] = { 'c', 'a', 'p', 't', 'i', 'v', 'e', ',', 't', 'h', 'e', '+',  };
const char introText_Line_20[] = { 'p', 'r', 'i', 'n', 'c', 'e', 's', 's', '+' };
const char introText_Line_21[] = { 'm', 'a', 'r', 'i', 'k', 'o', '.', '+' };
const char introText_Line_22[] = { '=' };
const char introText_Line_23[] = { 'y', 'o', 'u', ' ', 'a', 'r', 'e', ' ', 'o', 'n', 'e', '+' };
const char introText_Line_24[] = { 't', 'r', 'a', 'i', 'n', 'e', 'd', '+' };
const char introText_Line_25[] = { 'i', 'n', ' ', 't', 'h', 'e', ' ', 'w', 'a', 'y', '+' };
const char introText_Line_26[] = { 'o', 'f', ' ', 'k', 'a', 'r', 'a', 't', 'e', ':', '+' }; 
const char introText_Line_27[] = { 'a', ' ', 'k', 'a', 'r', 'a', 't', 'e', 'k', 'a', '.', '+' };
const char introText_Line_28[] = { 'a', 'l', 'o', 'n', 'e', ' ', 'a', 'n', 'd', '+' };
const char introText_Line_29[] = { 'u', 'n', 'a', 'r', 'm', 'e', 'd', '+' };
const char introText_Line_30[] = { '=' };
const char introText_Line_31[] = { 'y', 'o', 'u', ' ', 'm', 'u', 's', 't', '+' };
const char introText_Line_32[] = { 'd', 'e', 'f', 'e', 'a', 't', ' ', 'a', 'k', 'u', 'm', 'a', '+' };
const char introText_Line_33[] = { 'a', 'n', 'd', ' ', 'r', 'e', 's', 'c', 'u', 'e', '+' };
const char introText_Line_34[] = { 't', 'h', 'e', ' ', 'b', 'e', 'a', 'u', 't', 'i', 'f', 'u', 'l', '+' }; 
const char introText_Line_35[] = { 'm', 'a', 'r', 'i', 'k', 'o', '.', '+' };
const char introText_Line_36[] = { '=' };
const char introText_Line_37[] = { 'p', 'u', 't', ' ', 'f', 'e', 'a', 'r', ' ', 'a', 'n', 'd', '+' };
const char introText_Line_38[] = { 's', 'e', 'l', 'f', '-', 'c', 'o', 'n', 'c', 'e', 'r', 'n', '+' };
const char introText_Line_39[] = { 'b', 'e', 'h', 'i', 'n', 'd', ' ', 'y', 'o', 'u', '.', '+' };
const char introText_Line_40[] = { 'f', 'o', 'c', 'u', 's', ' ', 'y', 'o', 'u', 'r', '+' };
const char introText_Line_41[] = { 'w', 'i', 'l', 'l', ' ', 'o', 'n', ' ', 'y', 'o', 'u', 'r', '+' };
const char introText_Line_42[] = { 'o', 'b', 'j', 'e', 'c', 't', 'i', 'v', 'e', ',', '+' };
const char introText_Line_43[] = { 'a', 'c', 'c', 'e', 'p', 't', 'i', 'n', 'g', '+' };
const char introText_Line_44[] = { 'd', 'e', 'a', 't', 'h', ' ', 'a', 's', ' ', 'a', '+' }; 
const char introText_Line_45[] = { 'p', 'o', 's', 's', 'i', 'b', 'i', 'l', 'i', 't', 'y', '.', '+' }; 
const char introText_Line_46[] = { 't', 'h', 'i', 's', ' ', 'i', 's', ' ', 't', 'h', 'e','+' };
const char introText_Line_47[] = { 'w', 'a', 'y', ' ', 'o', 'f', ' ', 't', 'h', 'e', '+' };
const char introText_Line_48[] = { 'k', 'a', 'r', 'a', 't', 'e', 'k', 'a', '.', '+' };
const char introText_Line_99[] = { '#' };

const char * const introTextLines[] = {introText_Line_00, introText_Line_01, introText_Line_02, introText_Line_03, introText_Line_04, introText_Line_05, introText_Line_06, 
                                       introText_Line_07, introText_Line_08, introText_Line_09, introText_Line_10, introText_Line_11, introText_Line_12, introText_Line_13,
                                       introText_Line_14, introText_Line_15, introText_Line_16, introText_Line_17, introText_Line_18, introText_Line_19, 
                                       introText_Line_20, introText_Line_21, introText_Line_22, introText_Line_23, introText_Line_24, introText_Line_25, 
                                       introText_Line_26, introText_Line_27, introText_Line_28, introText_Line_29, introText_Line_30, introText_Line_31, 
                                       introText_Line_32, introText_Line_33, introText_Line_34, introText_Line_35, introText_Line_36, introText_Line_37, 
                                       introText_Line_38, introText_Line_39, introText_Line_40, introText_Line_41, introText_Line_42, introText_Line_43, 
                                       introText_Line_44, introText_Line_45, introText_Line_46, introText_Line_47, introText_Line_48,  
                                       introText_Line_99 };

void Game::introText() {

    uint16_t cx = 0;
    uint16_t cy = 0;
    uint16_t x = 0;
    int16_t y = this->introTextVariables.y-90;
    int16_t cxx=0;


    if (PC::buttons.pressed(BTN_A)) this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE);


    //if (PC::frameCount % 2 == 0) {

        this->introTextVariables.y = this->introTextVariables.y - 1;

        if (this->introTextVariables.y == -1100) {
            this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE);
        }

        while (cy < 999) {

            while (cx < 999) {

                const char *introText_Line_To_Read = introTextLines[cy];
                uint8_t character = introText_Line_To_Read[cx];

                switch (character) {

                    case '+':       //The end of a line ..
    cy++;
    cxx=0;
    introText_Line_To_Read = introTextLines[cy];
    for(uint8_t i=0; i<30; i++){
      char chr = introText_Line_To_Read[i];
      if (chr=='+' || chr=='=') break;
      else if (chr==' ') {cxx+=4; continue;}
      else if (chr==',') chr = 26;
      else if (chr=='.') chr = 27;
      else if (chr==':') chr = 28;
      else if (chr=='-') chr = 29;
      cxx += Images::Char_Spacing[(uint8_t)chr-(uint8_t)97];
    }
                        x=(110-cxx)/2;
                        //x = 0;
                        y = y + 21;
                        cx = 999;
                    
                        break;

                    case '=':       //The end of a paragraph ..
    cy++;
    cxx=0;
    introText_Line_To_Read = introTextLines[cy];
    for(uint8_t i=0; i<30; i++){
      char chr = introText_Line_To_Read[i];
      if (chr=='+' || chr=='=') break;
      else if (chr==' ') {cxx+=4; continue;}
      else if (chr==',') chr = 26;
      else if (chr=='.') chr = 27;
      else if (chr==':') chr = 28;
      else if (chr=='-') chr = 29;
      cxx += Images::Char_Spacing[(uint8_t)chr-(uint8_t)97];
    }

                        x=(110-cxx)/2;
                        //x = 0;
                        y = y + 42;
                        cx = 999;
                       
                        break;

                    case '#':       // The end of text ..
                        cx = 999;
                        cy = 999;
                        break;

                    case '1' ... '9':       // The end of text ..
                        x = x + (character - 48) * 2;
                        break;

                    case ' ':
                        x = x + 4;
                        break;

                    case ',':
                        if (y > -20 && y < 176) PD::drawBitmap(x, y, Images::Chars[26]);
                        x = x + Images::Char_Spacing[26];
                        break;

                    case '.':
                        if (y > -20 && y < 176) PD::drawBitmap(x, y, Images::Chars[27]);
                        x = x + Images::Char_Spacing[27];
                        break;

                    case ':':
                        if (y > -20 && y < 176) PD::drawBitmap(x, y, Images::Chars[28]);
                        x = x + Images::Char_Spacing[28];
                        break;

                    case '-':
                        if (y > -20 && y < 176) PD::drawBitmap(x, y, Images::Chars[29]);
                        x = x + Images::Char_Spacing[29];
                        break;

                    default:
                        if (y > -20 && y < 176) PD::drawBitmap(x, y, Images::Chars[character - 97]);
                        x = x + Images::Char_Spacing[character - 97];
                        break;

                }

                cx = cx + 1;

            }

            cx = 0;

        }

    //}

}



String const finalText[40]={
"and so this",
"adventure",
"ends.",
"",
"the",
"evil akuma",
"lies", 
"vanquished",
"",
"the", 
"beautiful",
"mariko safe",
"in your",
"arms.",
"",
"for the first",
"time in memory,",
"the country",
"basks in the",
"sunlight of",
"peace.",
"",
"but beware",
"for the",
"karateka",
"there is",
"always a",
"next time.",
"",
"this attempt",
"took",
"*",
"min.",
"",
"try again",
"and see if",
"you can beat",
"this time",
"#"
};


void Game::extroText() {
 uint16_t cx = 0, cy = 0;
 uint16_t line, cntline;
 String curStr;
 uint32_t timeStmp;
 uint32_t waitTime;

  cntline=0;
  for(uint8_t i=0; i<10; i++)
    if(finalText[line+i] == "") break;
    else cntline++;
  cy = (88-cntline*14)/2;
  
  PD::clear();
  line=0;
  
  while(1){
    curStr=finalText[line];

    if (curStr == "*"){
      uint32_t sec = (this->timeEnd - this->timeStart) / 1000;
      char digits[3] = {255,255,255};
        itoa(sec/60, digits, 10);
        if(digits[0]!=255 && digits[0]!=0) PD::drawBitmap(40, cy, Images::Number[digits[0]-48]);
        if(digits[1]!=255 && digits[1]!=0) PD::drawBitmap(52, cy, Images::Number[digits[1]-48]);
        line++; cy += 17;
        delay(1000);
        continue;
     }
    
    if (curStr == "#" || curStr.length() == 0){
      PD::update();
      timeStmp = millis();
      if(curStr == "#") {waitTime=20000; line=0; curStr=finalText[line];}
      else waitTime=5000;
      while (millis()-timeStmp < waitTime){
        delay(10);
        PC::update();
        if(PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B)){
          this->gameStateDetails.setCurrState(GAME_STATE_FOLLOW_SEQUENCE);
          return;
        }
      }
      
      line++;
      cntline=0;
      for(uint8_t i=0; i<10; i++)
        if(finalText[line+i] == "") break;
        else cntline++;
      cy = (88-cntline*14)/2;
  
      PD::clear();
      continue;
    }

    int16_t cxx=0;
    for(uint8_t i=0; i<curStr.length(); i++){
      char chr = curStr[i];
      if (chr==',') chr = 26;
      else if (chr==' ') {cxx+=4; continue;}
      else if (chr=='.') chr = 27;
      else if (chr==':') chr = 28;
      else if (chr=='-') chr = 29;
      else chr -= 97;
      cxx += Images::Char_Spacing[chr];
    }
    
    cx = (110-cxx)/2;
    for(uint8_t i=0; i<curStr.length(); i++){
      char chr = curStr[i];
      if (chr==',') chr = 26;
      else if (chr==' ') {cx += 4;continue;}
      else if (chr=='.') chr = 27;
      else if (chr==':') chr = 28;
      else if (chr=='-') chr = 29;
      else chr -= 97;
      PD::drawBitmap(cx, cy, Images::Chars[chr]);
      cx += Images::Char_Spacing[chr];
    }
    line++;
    cy += 14;
  }
};
