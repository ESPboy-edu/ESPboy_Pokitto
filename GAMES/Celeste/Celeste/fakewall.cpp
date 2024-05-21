#include "fakewall.h"
#include "constants.h"
#include "player.h"
#include "fruit.h"

FakeWall::FakeWall()
  : Object(fake_wall)
{
  spr = 64;
  if_not_fruit = true;
}

void FakeWall::init()
{
  hitbox.x = 0;
  hitbox.y = 0;
  hitbox.w = 16;
  hitbox.h = 16;
}

void FakeWall::update()
{
  hitbox.x = -1;
  hitbox.y = -1;
  hitbox.w = 18;
  hitbox.h = 18;

  Object * hit = collide(player, 0, 0);
  if (hit && static_cast<Player*>(hit)->dash_effect_time > 0)
  {
    sfx_timer=20;
    sfx(16);
    hit->spd.x = -sign(hit->spd.x) * 1.5;
    hit->spd.y = -1.5;
    static_cast<Player*>(hit)->dash_time = -1;
    destroy_object(this);
    Fruit * fruit = new Fruit;
    init_object(fruit, x+4, y+4);
  }

  hitbox.x = 0;
  hitbox.y = 0;
  hitbox.w = 16;
  hitbox.h = 16;
}

void FakeWall::draw()
{
  _spr(64, x,     y);
  _spr(65, x + 8, y);
  _spr(80, x,     y + 8);
  _spr(81, x + 8, y + 8);
}


