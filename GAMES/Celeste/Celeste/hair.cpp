#include "hair.h"
#include "object.h"

Hair::Hair()
{
}

void Hair::create_hair(Object * obj)
{
  for (int i = 0; i < 5; i++)
  {
    hair[i].x = obj->x;
    hair[i].y = obj->y;
    hair[i].size = max(1, min (2, 3 - i));
  }
}

void Hair::draw_hair(Object * obj, int facing, int djump)
{
  int color = djump == 1 ? 8 : (djump == 2 ? 7 + ((frames / 3) % 2) * 4 : 12);

  float hx = obj->x + 4 - (facing * 2);
  float hy = obj->y + (btn(k_down) ? 4 : 3);

  for (int i = 0; i < 5; i++)
  {
    Node & node = hair[i];
    node.x += (hx - node.x) / 1.5;
    node.y += (hy + 0.5 - node.y) / 1.5;

    circfill(node.x, node.y, node.size, color);

    hx = node.x;
    hy = node.y;
  }
}


