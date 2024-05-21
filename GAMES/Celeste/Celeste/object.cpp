#include "object.h"

Object::Object(Type type)
  : type(type)
{
  spd.x = 0;
  spd.y = 0;
  rem.x = 0;
  rem.y = 0;
  flip.x = false;
  flip.y = false;
  hitbox.x = 0;
  hitbox.y = 0;
  hitbox.w = 8;
  hitbox.h = 8;
  collideable = true;
  solids = true;
  if_not_fruit = false;
  spr = 0;
  x = 0;
  y = 0;
}

Object::~Object()
{
}

void Object::setPosition(int new_x, int new_y)
{
  x = new_x;
  y = new_y;
}

void Object::init()
{
}
void Object::update()
{
  move(spd.x, spd.y);
}

void Object::draw()
{
  _spr(spr, x, y, flip.x, flip.y);
}

bool Object::is_solid(int ox, int oy)
{
  if (oy > 0 && !check(platform, ox, 0) && check(platform, ox, oy))
  {
    return true;
  }

  return solid_at(x + hitbox.x + ox, y + hitbox.y + oy, hitbox.w, hitbox.h)
          || check(fall_floor, ox, oy)
          || check(fake_wall, ox, oy);
}

bool Object::is_ice(int ox, int oy)
{
  return ice_at(x + hitbox.x + ox, y + hitbox.y + oy, hitbox.w, hitbox.h);
}

Object * Object::collide(Type type, int ox, int oy)
{
  for (int i = 0; i < objects_count; i++)
  {
    Object * other = objects[i];
    if (other && other->type == type && other != this && other->collideable
      && other->x + other->hitbox.x + other->hitbox.w > x + hitbox.x + ox
      && other->y + other->hitbox.y + other->hitbox.h > y + hitbox.y + oy
      && other->x + other->hitbox.x < x + hitbox.x + hitbox.w + ox
      && other->y + other->hitbox.y < y + hitbox.y + hitbox.h + oy)
      {
        return other;
      }
  }
  return NULL;
}

bool Object::check(Type type, int ox, int oy)
{
  return collide(type, ox, oy) != NULL;
}
void Object::move(float ox, float oy)
{
  rem.x += ox;
  float amount = floor(rem.x + 0.5f);
  rem.x -= amount;
  move_x(amount, 0);

  rem.y += oy;
  amount = floor(rem.y + 0.5f);
  rem.y -= amount;
  move_y(amount);
}

void Object::move_x(float amount, float start)
{
  if (solids)
  {
    int step = sign(amount);
    for (int i = start; i <= abs(amount); i++)
    {
      if (!is_solid(step, 0))
      {
        x += step;
      }
      else
      {
        spd.x = 0;
        rem.x = 0;
        break;
      }
    }
  }
  else
  {
    x += amount;
  }
}

void Object::move_y(float amount)
{
  if (solids)
  {
    int step = sign(amount);
    for (int i = 0; i <= abs(amount); i++)
    {
      if (!is_solid(0, step))
      {
        y += step;
      }
      else
      {
        spd.y = 0;
        rem.y = 0;
        break;
      }
    }
  }
  else
  {
    y += amount;
  }
}


