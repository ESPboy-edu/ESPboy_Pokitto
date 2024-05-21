#include "orb.h"
#include "player.h"

Orb::Orb()
  : Object(orb)
{
}

void Orb::init()
{
  spd.y = -4;
  solids = false;
}

void Orb::draw()
{
  spd.y = appr(spd.y, 0.f, 0.5f);
  Object * hit = collide(player, 0, 0);
  if (spd.y == 0 && hit)
  {
    sfx(51);
    freeze = 10;
    destroy_object(this);
    max_djump = 2;
    static_cast<Player*>(hit)->djump = 2;
  }

  _spr(102, x, y);
  float off = frames / 30;
  for (int i = 0; i < 8; i++)
  {
    circfill(x + 4 + cos((off + i/8.f) * 360) * 8, y + 4 + sin((off + i / 8.f) * 360) * 8, 1, 7);
  }
}


