#ifndef SPRING_H
#define SPRING_H

#include "object.h"

class Spring : public Object
{
public:
  Spring();

  void init();
  void update();

  void break_spring();

private:
  int hide_in;
  int hide_for;
  int delay;
};

#endif


