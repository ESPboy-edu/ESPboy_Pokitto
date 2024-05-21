#ifndef PLATFORM_H
#define PLATFORM_H

#include "object.h"

class Platform : public Object
{
public:
  Platform(int dir);

  void init();
  void update();
  void draw();

private:
  int dir;
  int last;
};

#endif


