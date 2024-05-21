#include "game.h"
#include "ESP8266WiFi.h"
Game game;
void setup()
{
  WiFi.forceSleepBegin();
  delay(5);  
  pb.begin();
  //Serial.begin(115200);
  pb.setFrameRate(100);
  pb.display.setFont(pico8);
  game.init();
  pb.sound.globalVolume=7;
  pb.sound.playMusicStream("celeste.raw");
}

void loop()
{
  if(pb.update())
  {
    pb.display.setTextColor(WHITE);
    game.update();
    game.draw();
    pb.display.setCursor(92,0);
    pb.display.setTextColor(WHITE,BLACK);
    pb.display.printf("%d FPS",1000000/pb.frameDurationMicros);
  }
}
