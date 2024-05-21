#ifndef FLY_FRUIT_H
#define FLY_FRUIT_H 

#include "object.h"

class FlyFruit : public Object
{
public:
  FlyFruit();

  void init();
  void update();
  void draw();

private:
  int start;
  bool fly;
  float step;
};

#endif


