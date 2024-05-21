#include "platform.h"

Platform::Platform(int dir)
  : Object(platform), dir(dir)
{
}

void Platform::init()
{
  x -= 4;
  solids = false;
  hitbox.w = 16;
  last = x;
}

void Platform::update()
{
  Object::update();

  spd.x = dir * 0.65;

  if (x < -16) x = 128;
  else if (x > 128) x = -16;

  if (!check(player, 0, 0))
  {
    Object * hit = collide(player, 0, -1);
    if (hit)
    {
      hit->move_x(x - last, 1);
    }
  }

  last = x;
}

void Platform::draw()
{
  _spr(11, x,     y - 1);
  _spr(12, x + 8, y - 1);
}


