#ifndef FAKE_WALL_H
#define FAKE_WALL_H

#include "object.h"

class FakeWall : public Object
{
public:
  FakeWall();
  
  void init();
  void update();
  void draw();
};

#endif


