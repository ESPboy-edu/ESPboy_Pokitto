#include "flyfruit.h"
#include "player.h"
#include "lifeup.h"

FlyFruit::FlyFruit()
  : Object(fly_fruit)
{
  spr = 28;
  if_not_fruit = true;
}

void FlyFruit::init()
{
  start = y;
  fly = false;
  step = 0.5;
  solids = false;
}

void FlyFruit::update()
{
  Object::update();

  // fly away
  if (fly)
  {
    sfx_timer=20;
    sfx(14);
    spd.y = appr(spd.y, -3.5f, 0.25f);
    if (y < -16)
    {
      destroy_object(this);
    }
  }
  // wait
  else
  {
    if (has_dashed)
    {
      fly = true;
      step += 0.5;
      spd.y = sin(step) * 0.5;
    }
  }

  // collect
  Object * hit = collide(player, 0, 0);
  if (hit)
  {
    sfx_timer=20;
    sfx(13);
    static_cast<Player*>(hit)->djump = max_djump;
    got_fruit[1 + level_index()] = true;

    LifeUp * lifeup = new LifeUp;
    init_object(lifeup, x, y);

    destroy_object(this);
  }
}

void FlyFruit::draw()
{
  float off = 0;
  if (!fly)
  {
    float dir = sin(step);
    if (dir < 0)
    {
      off = 1 + max(0, sign (y - start));
    }
    else
    {
      off = static_cast<int>(off + 0.25) % 3;
    }
  }

  _spr(45 + off, x - 6, y - 2, true, false);
  _spr(spr, x, y);
  _spr(45 + off, x + 6, y - 2);
}


