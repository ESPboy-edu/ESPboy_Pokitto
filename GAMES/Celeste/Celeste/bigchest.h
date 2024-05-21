#ifndef BIG_CHEST_H
#define BIG_CHEST_H

#include "object.h"

class BigChest : public Object
{
public:
  BigChest();
  
  void init();
  void update();
  void draw();

private:
  int state;
  int timer;
};

#endif


