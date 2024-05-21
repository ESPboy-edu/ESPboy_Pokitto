#ifndef FALL_FLOOR_H
#define FALL_FLOOR_H

#include "object.h"

class FallFloor : public Object
{
public:
  FallFloor();

  void init();
  void update();
  void draw();

  void break_fall_floor();

private:
  int state;
  int delay;
};

#endif


