/*
ESPboy_Init class
for www.ESPboy.com project by RomanS
https://hackaday.io/project/164830-espboy-games-iot-stem-for-education-fun
v1.0
*/

#include "ESPboyInit.h"
#include "Pokitto_settings.h"

#if PROJ_SCREENMODE == MODE15_240x240
  #define DISPLAY240x240
  #define RES_X 240
  #define RES_Y 240
#else
  #define RES_X 128
  #define RES_Y 128
#endif



ESPboyInit::ESPboyInit(){};

void ESPboyInit::begin(const char *appName) {
  //Serial.begin(115200); //serial init
  WiFi.mode(WIFI_OFF); // to safe battery power

//DAC init and backlit off
  dac.begin(MCP4725address);
  delay (100);
  dac.setVoltage(0, false);

//mcp23017 init for buttons, LED LOCK and TFT Chip Select pins
  mcp.begin(MCP23017address);
  delay(100);
  for (int i=0;i<8;i++){  
     mcp.pinMode(i, INPUT);
     mcp.pullUp(i, HIGH);}

//LED init
  //myLED.begin(&this->mcp);
  //myLED.setRGB(0,0,0);

//sound init and test
  pinMode(SOUNDPIN, OUTPUT);
  //playTone(200, 100); 
  //delay(100);
  //playTone(100, 100);
  //delay(100);
  //noPlayTone();
  
//LCD TFT init
  mcp.pinMode(CSTFTPIN, OUTPUT);
  mcp.digitalWrite(CSTFTPIN, LOW);
  tft.begin();
  tft.setSwapBytes(true);
  delay(100);
  //tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

//draw ESPboylogo  
  tft.drawXBitmap((RES_X-68)/2, (RES_Y-80)/2, ESPboyLogo, 68, 64, TFT_YELLOW);
  tft.setTextSize(1);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString (appName, (RES_X-(strlen(appName)*6))/2, (RES_Y-80)/2+78);

//LCD backlit fading on
#ifndef DISPLAY240x240
  for (uint16_t bcklt=300; bcklt<4095; bcklt+=30){
    dac.setVoltage(bcklt, false);
    delay(10);}
#endif
  delay(1000);

//clear TFT and backlit on high

#ifndef DISPLAY240x240
  dac.setVoltage(4095, false);
  tft.fillScreen(TFT_BLACK);
#endif
};


void ESPboyInit::playTone(uint16_t frq, uint16_t dur) { tone(SOUNDPIN, frq, dur); }
void ESPboyInit::playTone(uint16_t frq) { tone(SOUNDPIN, frq); }

void ESPboyInit::noPlayTone() { noTone(SOUNDPIN); }

uint8_t ESPboyInit::getKeys() { return (~mcp.readGPIOAB() & 255); }
