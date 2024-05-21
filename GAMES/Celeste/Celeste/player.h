#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "hair.h"

class Player : public Object
{
public:
  Player();
  
  void init();
  void update();
  void draw();

  int djump;
  Vec2d dash_target;
  Vec2d dash_accel;
  bool p_jump;
  bool p_dash;
  int grace;
  int jbuffer;
  int dash_time;
  int dash_effect_time;
  float spr_off;
  bool was_on_ground;
  Hair hair;
};

#endif


