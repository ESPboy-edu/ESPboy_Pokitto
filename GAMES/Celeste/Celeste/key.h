#ifndef KEY_H
#define KEY_H

#include "object.h"

class Key : public Object
{
public:
  Key();
  
  void update();

private:
  float off_spr;
};

#endif


