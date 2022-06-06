#include "Pokitto.h"
#include "Game.h"
#include "Interface.h"
#include "Font.h"
#include "Generated/Palette.inc.h"
#include "ESP_EEPROM.h"
//#include <File>

using PC = Pokitto::Core;
using PD = Pokitto::Display;

const char* saveGameName = "MICROCITY.SAV";
const char saveHeader[4] = { 'C', 'T', 'Y', '1' };

uint8_t GetInput()
{
  uint8_t result = 0;
  
  if(PC::buttons.aBtn())
  {
    result |= INPUT_B;  
  }
  if(PC::buttons.bBtn())
  {
    result |= INPUT_A;  
  }
  if(PC::buttons.cBtn())
  {
    result |= INPUT_START;  
  }
  if(PC::buttons.upBtn())
  {
    result |= INPUT_UP;  
  }
  if(PC::buttons.downBtn())
  {
    result |= INPUT_DOWN;  
  }
  if(PC::buttons.leftBtn())
  {
    result |= INPUT_LEFT;  
  }
  if(PC::buttons.rightBtn())
  {
    result |= INPUT_RIGHT;  
  }

  return result;
}


void PutPixel(uint8_t x, uint8_t y, uint8_t colour)
{
    PD::drawPixel(x, y, colour);
}


#define EEPROM_OFFSET 20

void SaveCity()
{
 EEPROM.put(EEPROM_OFFSET, saveHeader);
 EEPROM.put(EEPROM_OFFSET+sizeof(saveHeader), State);
 EEPROM.commit();
 //   File file;
 //   if(file.openRW(saveGameName, true, false))
 //   {
 //       file.write(saveHeader, 4);
 //       file.write(&State, sizeof(GameState));
 //   }
}


bool LoadCity(){
 char saveHeaderTemp[4];
  EEPROM.get(EEPROM_OFFSET, saveHeaderTemp);
  if (saveHeaderTemp[0] != saveHeader[0] || saveHeaderTemp[1] != saveHeader[1])
    return false;
  EEPROM.get(EEPROM_OFFSET+sizeof(saveHeader), State);
  return(true);
  /*
    File file;
    if(file.openRO(saveGameName))
    {
        char readHeader[4];
        file.read(readHeader, 4);
        for(int n = 0; n < 4; n++)
        {
            if(readHeader[n] != saveHeader[n])
            {
                return false;
            }
        }
        file.read(&State, sizeof(GameState));
        return true;
    }*/
    //return false;
    
}

uint8_t* GetPowerGrid()
{
    // Just use display buffer as a temporary scratch space for power grid flood fill
    return (uint8_t*) PD::getBuffer();
}

uint8_t* GetScreenBuffer(void)
{
    return (uint8_t*) PD::getBuffer();
}


void setup(){
    EEPROM.begin(1000);
    PC::begin();
    PD::persistence = true;
    PD::load565Palette(MicroCityPalette);

  while(GetInput() != 0)
    {
        PC::update();
        PD::update();
        delay(1);
    }
    
    InitGame();
}


void loop(){
 if(PC::update()) {
    TickGame();
    PD::update();}
}
