#include "bigchest.h"
#include "orb.h"

BigChest::BigChest()
  : Object(big_chest)
{
}

void BigChest::init()
{
  state = 0;
  hitbox.w = 16;
  timer = 0;
}

void BigChest::update()
{
  // empty
}

void BigChest::draw()
{
  if (state == 0)
  {
    Object * hit = collide(player, 0, 8);
    if (hit && hit->is_solid(0, 1))
    {
      music(-1);
      sfx(37);
      pause_player = true;
      hit->spd.x = 0;
      hit->spd.y = 0;
      state = 1;
      timer = 60;
    }

    _spr(96, x,     y);
    _spr(97, x + 8, y);
  }
  else if (state == 1)
  {
    timer--;
    if (timer < 0)
    {
      state = 2;

      Orb * orb = new Orb;
      init_object(orb, x, y);
      pause_player = false;
    }
  }

  _spr(112, x,     y + 8);
  _spr(113, x + 8, y + 8);
}


