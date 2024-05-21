#ifndef OBJECT_H
#define OBJECT_H

#include "constants.h"

class Object
{
public:
  virtual ~Object();

  virtual void init();
  virtual void update();
  virtual void draw();

  virtual void setPosition(int new_x, int new_y);

  bool collideable ;
  bool solids;
  Hitbox hitbox;
  Vec2d spd;
  Vec2d rem;
  Type type;
  int spr;
  Bools flip;
  int x;
  int y;
  bool if_not_fruit;
  
  bool is_solid(int ox, int oy);
  bool is_ice(int ox, int oy);
  Object * collide(Type type, int ox, int oy);
  bool check(Type type, int ox, int oy);
  void move(float ox, float oy);
  void move_x(float amount, float start);
  void move_y(float amount);

protected:
  Object(Type type);
};

#endif


