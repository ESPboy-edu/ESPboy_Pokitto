#include "fruit.h"
#include "player.h"
#include "lifeup.h"

Fruit::Fruit()
  : Object(fruit)
{
  spr = 26;
  if_not_fruit = true;
}

void Fruit::init()
{
  start = y;
  off = 0;
}

void Fruit::update()
{
  Object * hit = collide(player, 0, 0);
  if (hit)
  {
    sfx_timer=20;
    sfx(13);
    static_cast<Player*>(hit)->djump = max_djump;
    got_fruit[1+level_index()] = true;

    LifeUp * lifeup = new LifeUp;
    init_object(lifeup, x, y);

    destroy_object(this);
  }

  off += 1;
  y = start + sin(off / 20.f) * 2.5;
}


