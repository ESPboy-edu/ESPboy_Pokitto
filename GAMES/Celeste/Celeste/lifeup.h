#ifndef LIFE_UP_H
#define LIFE_UP_H

#include "object.h"

class LifeUp : public Object
{
public:
  LifeUp();

  void init();
  void update();
  void draw();

private:
  int duration;
  int flash;
};

#endif


