#include "message.h"
#include "player.h"

const char* text[] = {
  "-- celeste mountain --",
  "this memorial to those",
  " perished on the climb"
};
const int text_size = 66;
char tmp_text[23];
const int tmp_text_size = 22;

Message::Message()
  : Object(message)
{
  spr = 86;
  last = 0;
  index = 0;
}

void Message::draw()
{
  _spr(spr, x, y);

  if (check(player, 4, 0))
  {
    if (index < text_size)
    {
      // in lua it's index += 0.5, so I changed it to "+1" every other frame.
      if (frames % 2)
        index += 1;
      if (index >= last + 1)
      {
        last++;
        sfx(35);
      }
    }
    Point off;
    off.x = 20;
    off.y = 53;//96

    for (int i = 0; i < 3; i++)
    {
      if (index > i * tmp_text_size)
      {
        int tmp_index = min(22, index - i * tmp_text_size);
        memcpy(tmp_text, text[i], tmp_index);
        tmp_text[tmp_index] = '\0';
        rectfill(off.x - 2, off.y - 2, off.x + 2 + (4 * tmp_index), off.y + 8, 7);
        print(tmp_text, off.x, off.y, 5);

        off.y += 7;
      }
    }
  }
  else
  {
    index = 0;
    last = 0;
  }
}


