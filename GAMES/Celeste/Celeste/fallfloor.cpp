#include "fallfloor.h"
#include "spring.h"

FallFloor::FallFloor()
  : Object(fall_floor)
{
}

void FallFloor::init()
{
  state = 0;
  delay = 0;
}

void FallFloor::update()
{
  if (state == 0)
  {
    if (check(player, 0, -1) || check(player, -1, 0) || check(player, 1, 0))
    {
      break_fall_floor();
    }
  }
  else if (state == 1)
  {
    delay--;
    if (delay <= 0)
    {
      state = 2;
      delay = 60;
      collideable = false;
    }
  }
  else if(state == 2)
  {
    delay--;
    if (delay <= 0 && !check(player, 0, 0))
    {
      psfx(7);
      state = 0;
      collideable = true;
    }
  }
}

void FallFloor::draw()
{
  if (state == 0)
  {
    _spr(23, x, y);
  }
  else if (state == 1)
  {
    _spr(23 + (15 - delay) / 5, x, y);
  }
}

void FallFloor::break_fall_floor()
{
  if (state == 0)
  {
    psfx(15);
    state = 1;
    delay = 15;
    Object * hit = collide(spring, 0, -1);
    if (hit)
    {
      static_cast<Spring*>(hit)->break_spring();
    }
  }
}


