#ifndef FRUIT_H
#define FRUIT_H 

#include "object.h"

class Fruit : public Object
{
public:
  Fruit();

  void init();
  void update();

private:
  int start;
  int off;
};

#endif


