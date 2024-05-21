#include "flag.h"
#include "player.h"

Flag::Flag()
  : Object(flag)
{
}

void Flag::init()
{
  x += 5;
  score = 0;
  show = false;

  for (int i = 0; i < 32; i++)
  {
    if (got_fruit[i])
    {
      score++;
    }
  }
}

void Flag::draw()
{
  spr = 118 + static_cast<int>(frames / 5) % 3;
  _spr(spr, x, y);
  if (show)
  {
    #ifdef POKITTO
    int offset=12;
    #else
    int offset=0;
    #endif // POKITTO

    rectfill(32, 2+offset, 96, 31+offset, 0);
    _spr(26, 55, 6+offset);

    char text[16];
    sprintf(text, "x%d", score);
    print(text, 64, 9+offset, 7);
    char t[10];
    sprintf(t,"%02d:%02d:%02d", minutes/60, minutes, seconds);
    //draw_time(49, 16);
    print(t,49,17+offset,7);
    sprintf(text, "deaths:%d", deaths);
    print(text, 48, 24+offset, 7);
  }
  else if (check(player, 0, 0))
  {
    sfx(55);
    sfx_timer=30;
    show = true;
  }
}


