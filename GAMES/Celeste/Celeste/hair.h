#ifndef HAIR_H
#define HAIR_H

class Object;
class Hair
{
public:
  Hair();

  void create_hair(Object * obj);
  void draw_hair(Object * obj, int facing, int djump);

private:
  struct Node {
    float x;
    float y;
    int size;
  };
  Node hair[5];
};

#endif


