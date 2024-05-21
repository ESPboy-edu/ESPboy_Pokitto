#include "lifeup.h"

LifeUp::LifeUp()
  : Object(life_up)
{
}

void LifeUp::init()
{
  spd.y = -0.25;
  duration = 30;
  x -= 2;
  y -= 4;
  flash = 0;
  solids = false;
}

void LifeUp::update()
{
  Object::update();
  
  duration--;
  if (duration <= 0)
  {
    destroy_object(this);
  }
}

void LifeUp::draw()
{
  flash++;
  print("1000", x - 2, y, 7 + (flash / 2) % 2);
}


