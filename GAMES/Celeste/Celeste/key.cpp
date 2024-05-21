#include "key.h"

Key::Key()
  : Object(key)
{
  spr = 8;
  if_not_fruit = true;
  off_spr = 0;
}

void Key::update()
{
  int was = floor(off_spr);
  off_spr = 9 + (sin(frames / 30.0f) + 0.5);
  int is = floor(off_spr);
  spr = is;
  if (is == 10 && is != was)
  {
    flip.x = !flip.x;
  }
  if (check(player, 0, 0))
  {
    sfx(23);
    sfx_timer=10;
    destroy_object(this);
    has_key = true;
  }
}


