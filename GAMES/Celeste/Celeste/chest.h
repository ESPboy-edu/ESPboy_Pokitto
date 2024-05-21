#ifndef CHEST_H
#define CHEST_H

#include "object.h"

class Chest : public Object
{
public:
  Chest();
  
  void init();
  void update();

private:
  int start;
  int timer;
};

#endif


