#ifndef PLAYERSPAWN_H
#define PLAYERSPAWN_H

#include "object.h"
#include "hair.h"

class PlayerSpawn : public Object
{
public:
  PlayerSpawn();

  void init();
  void update();
  void draw();

  void setPosition(int new_x, int new_y);
  void setTarget(int tx, int ty);

private:
  int state;
  int target;
  int delay;

  Hair hair;
};

#endif


