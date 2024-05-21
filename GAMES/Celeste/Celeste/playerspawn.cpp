#include "playerspawn.h"
#include "player.h"

PlayerSpawn::PlayerSpawn()
  : Object(player_spawn)
{
  state = 0;
  target = 0;
  delay = 0;
}

void PlayerSpawn::init()
{
  sfx(4);
  spr = 3;
  y = 128;
  spd.y = -4;
  state = 0;
  delay = 0;
  solids = false;


  hair.create_hair(this);
}

void PlayerSpawn::update()
{
  Object::update();

  // jumping
  if (state == 0)
  {
    if (y < target + 16)
    {
      state = 1;
      delay = 3;
    }
  }
  // falling
  else if (state == 1)
  {
    spd.y += 0.5;
    if (spd.y > 0 && delay > 0)
    {
      spd.y = 0;
      delay--;
    }
    if (spd.y > 0 && y > target)
    {
      y = target;
      spd.x = 0;
      spd.y = 0;
      state = 2;
      delay = 5;
      sfx(5);
    }
  }
  // landing
  else if (state == 2)
  {
    delay--;
    spr = 6;
    if (delay < 0)
    {
      destroy_object(this);
      Player * p = new Player;
      init_object(p, x, y);
    }
  }
}

void PlayerSpawn::draw()
{
  hair.draw_hair(this, 1, max_djump);
  _spr(spr, x, y, flip.x, flip.y);
}

void PlayerSpawn::setPosition(int new_x, int new_y)
{
  setTarget(new_x, new_y);
}

void PlayerSpawn::setTarget(int tx, int ty)
{
  x = tx;
  target = ty;
}



