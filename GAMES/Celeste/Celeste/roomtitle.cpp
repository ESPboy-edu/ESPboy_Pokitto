#include "roomtitle.h"
#include "constants.h"

RoomTitle::RoomTitle()
  : Object(room_title)
{
}

void RoomTitle::init()
{
  delay = 5;
}

void RoomTitle::draw()
{
  delay--;
  if (delay < -30)
  {
    destroy_object(this);
  }
  else if (delay < 0)
  {
    #ifdef POKITTO
    int offset=-15;
    #else
    int offset=0;
    #endif // POKITTO
    rectfill(24+offset, 58, 104, 70, 0);
    if (level_index() == 11)
    {
      print("old site", 48+offset/2, 62, 7);
    }
    else if (level_index() == 30)
    {
      print("summit", 52+offset/2, 62, 7);
    }
    else
    {
      int level = (1 + level_index()) * 100;
      char message[8] = {0};
      sprintf(message, "%d m", level);
      print(message, 52+offset/2 + (level < 1000 ? 2 : 0), 62, 7);
    }

    draw_time(4, 4);
  }
}


