#ifndef FLAG_H
#define FLAG_H

#include "object.h"

class Flag : public Object
{
public:
  Flag();
  
  void init();
  void draw();

private:
  int score;
  bool show;
};

#endif


