#ifndef BALLOON_H
#define BALLOON_H

#include "object.h"

class Balloon : public Object
{
public:
  Balloon();

  void init();
  void update();
  void draw();

private:
  float offset;
  int start;
  int timer;
};

#endif


