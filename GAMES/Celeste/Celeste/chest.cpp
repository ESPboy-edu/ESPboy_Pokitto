#include "chest.h"
#include "fruit.h"

Chest::Chest()
  : Object(chest)
{
  spr = 20;
  if_not_fruit = true;
}

void Chest::init()
{
  x -= 4;
  start = x;
  timer = 20;
}

void Chest::update()
{
  if (has_key)
  {
    timer--;
    x = start - 1 + rnd(3);
    if (timer <= 0)
    {
      sfx_timer=20;
      sfx(16);
      Fruit * fruit = new Fruit;
      init_object(fruit, x, y - 4);
      destroy_object(this);
    }
  }
}


