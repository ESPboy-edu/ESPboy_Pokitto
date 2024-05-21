#ifndef ROOM_TITLE_H
#define ROOM_TITLE_H

#include "object.h"

class RoomTitle : public Object
{
public:
  RoomTitle();
  
  void init();
  void draw();

private:
  int delay;
};

#endif


