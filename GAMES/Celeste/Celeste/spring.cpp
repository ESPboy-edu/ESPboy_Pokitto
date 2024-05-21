#include "spring.h"
#include "player.h"
#include "fallfloor.h"

Spring::Spring()
  : Object(spring)
{
  spr = 18;
}

void Spring::init()
{
  hide_in = 0;
  hide_for = 0;
}

void Spring::update()
{
  if (hide_for > 0)
  {
    hide_for--;

    if (hide_for <= 0)
    {
      spr = 18;
      delay = 0;
    }
  }
  else if (spr == 18)
  {
    Object * hit = collide(player, 0, 0);
    if (hit && hit->spd.y >= 0)
    {
      spr = 19;
      hit->y = y - 4;
      hit->spd.x *= 0.2;
      hit->spd.y = -3;
      static_cast<Player*>(hit)->djump = max_djump;
      delay = 10;

      // breakable below us
      Object * below = collide(fall_floor, 0, 1);
      if (below)
      {
        static_cast<FallFloor*>(below)->break_fall_floor();
      }
      psfx(8);
    }
  }
  else if (delay > 0)
  {
    delay--;
    if (delay <= 0)
    {
      spr = 18;
    }
  }

  // begin hiding
  if (hide_in > 0)
  {
    hide_in--;
    if (hide_in <= 0)
    {
      hide_for = 60;
      spr = 0;
    }
  }
}

void Spring::break_spring()
{
  hide_in = 15;
}


