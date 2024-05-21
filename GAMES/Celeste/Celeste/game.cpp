#include "game.h"
#include "fakewall.h"
#include "playerspawn.h"
#include "player.h"
#include "roomtitle.h"
#include "fallfloor.h"
#include "balloon.h"
#include "platform.h"
#include "spring.h"
#include "bigchest.h"
#include "fruit.h"
#include "flyfruit.h"
#include "key.h"
#include "chest.h"
#include "message.h"
#include "flag.h"

#undef max
#undef min
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

extern "C"
{
    #include "Tiles.h"
};


// STATIC //

uint32_t seconds = 0;
uint32_t minutes = 0;
uint32_t start_time=0;
uint32_t total_time=0;

// PARTICLES //

struct DeadParticle
{
  int x;
  int y;
  Vec2d spd;
};

#define DEAD_PARTICLES_COUNT 8
DeadParticle dead_particles[DEAD_PARTICLES_COUNT];
int dead_particles_timer = 0;

// CLOUDS //

struct Cloud
{
  int x;
  int y;
  int spd;
  int w;
};

#define CLOUDS_COUNT 12
Cloud clouds[CLOUDS_COUNT];

struct  Particle
{
  int8_t x;
  int8_t y;
  uint8_t s;
  uint8_t spd;
  uint8_t off;
  uint8_t c;
};

#define PARTICLES_COUNT 16
Particle particles[PARTICLES_COUNT];


// GAME //

Object * objects[MAX_OBJECTS];
int objects_count = 0;

Object * deleted_objects[MAX_OBJECTS];
int deleted_objects_count = 0;
void deleteDeadObjects();
void cleanupNullObjects();

void psfx(int num)
{
    if (sfx_timer <= 0)
        sfx(num);
};

bool got_fruit[32];

int max_djump;
int room = 0;
int goto_room = -1;
bool will_restart = false;
int delay_restart = 0;
bool has_dashed = false;
bool has_key = false;
int freeze = 0;
int frames = 0;
bool pause_player = false;
int deaths = 0;
int sfx_timer=0;

int start_game_flash=0;
bool start_game=false;

Game * game_instance = 0;

bool menu=false;
int menu_selected=0;

/* Save Cookie */

class CelesteSave : public Pokitto::Cookie {
public:
  uint32_t total_time;
  uint32_t current_room;
  uint32_t deaths;
  uint32_t fruits;

  CelesteSave() {
    total_time=0;
    current_room=0;
    deaths=0;
    fruits=0;
  }
};

CelesteSave celesteSave;

void SaveGame()
{
    celesteSave.current_room=room;
    celesteSave.deaths=deaths;
    for(int i=0;i<32;i++)
        celesteSave.fruits |= got_fruit[i] << i;
    celesteSave.total_time=total_time;
    celesteSave.saveCookie();
}

void LoadSave()
{
    room=celesteSave.current_room;
    deaths=celesteSave.deaths;
    for(int i=0;i<32;i++)
        got_fruit[i]=(celesteSave.fruits >> i)&0x1;
};

void ResetSave()
{
    celesteSave.current_room=0;
    celesteSave.deaths=0;
    celesteSave.fruits=0;
    celesteSave.total_time=0;
    celesteSave.saveCookie();
};

Game::Game()
{
  game_instance = this;
  state = MAINMENU;
  celesteSave.begin("Celeste",celesteSave);
}

void Game::init()
{

  for(int i=0;i<CLOUDS_COUNT;i++)
    {
        clouds[i].x=rnd(128);
        clouds[i].y=rnd(128-12);
        clouds[i].spd=1+rnd(4);
        clouds[i].w=32+rnd(32);
    }

    for(int i=0; i<PARTICLES_COUNT;i++)
    {
       particles[i].x=rnd(128);
       particles[i].y=rnd(128);
       particles[i].s=1 + rnd(1);
       particles[i].spd=1+rnd(5);
       particles[i].off=rnd(3);
       particles[i].c=6+rnd(1);
    }

  for (int i = 0; i < 32; i++)
  {
    got_fruit[i] = false;
  }

  LoadSave();

  music(40);
  load_room(31);

  max_djump = 1;

}

void Game::update()
{
  if(menu)
  {
      if(pb.buttons.released(BTN_B))
        menu=false;
      if(pb.buttons.repeat(BTN_UP,10))
        menu_selected--;
      if(pb.buttons.repeat(BTN_DOWN,10))
        menu_selected++;
      if(menu_selected < 0)
        menu_selected=0;
      if(menu_selected > 2)
        menu_selected=2;

      if(pb.buttons.released(BTN_A))
        {
            if(menu_selected==0)
                restart_room();
            if(menu_selected==1)
                SaveGame();
            menu=false;
        }
      return;
  }
  total_time=celesteSave.total_time+pb.getTime()-start_time;

  if (goto_room != -1)
  {
    load_room(goto_room);
    goto_room = -1;
  }



  frames = (frames + 1) % 30;
  if (state == PLAYING)
  {
    if (pb.buttons.pressed(BTN_C))
    {
        menu=true;
        menu_selected=0;
    }

    if (level_index() < 30)
    {
      seconds = (total_time/1000) % 60;
      minutes = (total_time/60/1000) % 60;

    }

    if(sfx_timer > 0)
        sfx_timer-=1;

    if (freeze > 0)
    {
      freeze--;
      return;
    }

    // restart (soon)
    if (will_restart && delay_restart > 0)
    {
      delay_restart--;
      if (delay_restart <= 0)
      {
        will_restart = false;
        load_room(room);
      }
    }

    // update each object
    for (int i = 0; i < objects_count; i++)
    {
        if(objects[i]==NULL)
            continue;
#ifdef POKITTO
      if(objects[i]->type==player)
      {
            updateCamera(objects[i]->x,objects[i]->y);
      }
#endif // POKITTO
      objects[i]->update();
    }
  }
  else if (state == MAINMENU)
  {
    if ((pb.buttons.held(BTN_A,1)) && !start_game)
    {
      start_game_flash=50;
      start_game=true;
      sfx(38);
    }
    if ((pb.buttons.held(BTN_C,1)) && !start_game)
    {
      start_game_flash=50;
      start_game=true;
      sfx(38);
      ResetSave();
    }
    if(start_game)
    {
        start_game_flash--;
        if(start_game_flash < -30)
        {

            frames = 0;
            start_game=false;
            pal();
            music(0);
            load_room(celesteSave.current_room);
            state = PLAYING;
            start_time=pb.getTime();
        }
    }
  }

}



void Game::draw()
{
  uint8_t roomx=room%8;
  uint8_t roomy=room>>3;

  uint8_t scrW=128;
  #ifdef POKITTO
    scrW=pb.display.width;
  #endif // POKITTO


  if(start_game)
  {
      pal();
      int c=10;
      if(start_game_flash > 10)
      {
          if((frames%10) < 5)
              c=7;

      }else if(start_game_flash>5)
          c=2;
       else if(start_game_flash > 0 )
          c=1;
       else
          c=0;

        if(c <10 )
        {
            pal(6,c);
            pal(12,c);
            pal(13,c);
            pal(5,c);
            pal(1,c);
            pal(7,c);
        }
  }

  // Clouds //
  if(!is_title())
  {
      for(int i=0;i<CLOUDS_COUNT;i++)
      {
          clouds[i].x+=clouds[i].spd;
          rectfill(clouds[i].x,clouds[i].y,clouds[i].x+clouds[i].w,clouds[i].y+4+(1-clouds[i].w/(scrW>>1))*8,1);
          if((clouds[i].x+clouds[i].w)>=scrW)
          {
              clouds[i].x=-clouds[i].w;
              clouds[i].y=rnd(scrW-12);
          }
      }
  }

  // draw bg terrain
  map(roomx * 16,roomy * 16,0,0,16,16,4);
  // draw terrain
  map(roomx * 16,roomy * 16,0,0,16,16,2);

  // draw fg terrain
  map(roomx * 16,roomy * 16,0,0,16,16,8);

  for (int i = 0; i < objects_count; i++)
  {
    if (objects[i])
      objects[i]->draw();
  }

  if(menu)
  {
      pb.display.setColor(BLACK);
      pb.display.fillRect(18,20,75,30);
      pb.display.setColor(WHITE);
      pb.display.drawRect(18,20,75,30);
      pb.display.fillRect(22,26+menu_selected*7,3,3);
      pb.display.setCursor(30+(menu_selected==0),25);
      pb.display.print("reset level");
      pb.display.setCursor(30+(menu_selected==1),32);
      pb.display.print("save");
      pb.display.setCursor(30+(menu_selected==2),39);
      pb.display.print("back");
      return;
  }

  for(int i=0; i<PARTICLES_COUNT;i++)
    {
       particles[i].x+=particles[i].spd;
       particles[i].y+=(rnd(2))*rnd(2);
       //particles[i].off+=min(0,particles[i].spd>>1);
       rectfill(particles[i].x,particles[i].y,particles[i].x+particles[i].s,particles[i].y+particles[i].s,particles[i].c);
       if(particles[i].x > scrW+4)
       {
           particles[i].x=0;
           particles[i].y=rnd(scrW);
       }
    }

  if (dead_particles_timer > 0)
  {
    dead_particles_timer--;

    for (int i = 0; i < DEAD_PARTICLES_COUNT; i++)
    {
      DeadParticle & p = dead_particles[i];
      p.x += p.spd.x;
      p.y += p.spd.y;

      int diff = dead_particles_timer / 5;
      rectfill(p.x - diff, p.y - diff, p.x + diff, p.y + diff, 14 + dead_particles_timer % 2);
    }
  }

  if (state == MAINMENU)
  {
#ifdef POKITTO
      updateCamera(10+pb.display.width/2,25+pb.display.height/2);
#endif // POKITTO

    pb.display.drawBitmap(44-_cameraX,32-_cameraY, celeste_logo);

    if(!start_game)
        if(celesteSave.total_time==0)
        {
            print("A: New game", 48, 80, 6);
        }
        else
        {
            print("A: Continue", 48, 80, 6);
            print("C: New game ", 48, 87, 6);
        }


    print("noel berry & matt thorson", 22, 102, 5);
    print("@bl_ackrain 2019", 38, 109, 5);
  }

  deleteDeadObjects();
  cleanupNullObjects();

}

void deleteDeadObjects()
{
  for (int i = 0; i < deleted_objects_count; i++)
  {
    delete deleted_objects[i];
  }
  deleted_objects_count = 0;
}

void cleanupNullObjects()
{
  for (int i = 0; i < objects_count; i++)
  {
    if (objects[i] == NULL)
    {
      objects[i] = objects[objects_count - 1];
      objects_count--;
    }
  }
}

void Game::load_room(int index)
{
  has_dashed = false;
  has_key = false;

  room = index;

  //background.clear();
  pb.display.clear();

  for (int i = 0; i < objects_count; i++)
  {
    delete objects[i];
  }
  objects_count = 0;

  deleteDeadObjects();

  for (int y = 0; y < 16; y++)
  {
    for (int x = 0; x < 16; x++)
    {
      uint8_t roomx=room%8;
      uint8_t roomy=room>>3;
      int tile =mget(roomx*16+x, roomy*16+y);

      Object * new_object = 0;

      switch (tile)
      {
        case  1: new_object = new PlayerSpawn; break;
        case  8: new_object = new Key; break;
        case 11: new_object = new Platform(-1); break;
        case 12: new_object = new Platform(1); break;
        case 18: new_object = new Spring; break;
        case 20: new_object = new Chest; break;
        case 22: new_object = new Balloon; break;
        case 23: new_object = new FallFloor; break;
        case 26: new_object = new Fruit; break;
        case 28: new_object = new FlyFruit; break;
        case 64: new_object = new FakeWall; break;
        case 86: new_object = new Message; break;
        case 96: new_object = new BigChest; break;
        case 118:new_object = new Flag; break;
        case 97:
        case 112:
        case 113:
          tile = 0;
      }
      if (new_object)
      {
        bool b = (tile == 96);

        init_object(new_object, x * 8, y * 8);

        if(tile==1)
        {
            //update camera
    #ifdef POKITTO
            updateCamera(x*8,y*8);
    #endif // POKITTO
        }
      }
      tile = 0;
      _spr(tile, x*8,y*8);

    }
  }

  if (!is_title())
  {
    RoomTitle * title = new RoomTitle;
    init_object(title, 0, 0);
  }
}

// UTILS //


int clamp(int val, int a, int b)
{
  return max(a, min(b, val));
}

float clamp(float val, float a, float b)
{
  return max(a, min(b, val));
}

int appr(int val, int target, int amount)
{
  return val > target ? max(val - amount, target) : min(val + amount, target);
}

float appr(float val, float target, float amount)
{
  return val > target ? max(val - amount, target) : min(val + amount, target);
}

int sign(int v)
{
  return (v < 0 ? -1 : (v > 0 ? 1 : 0));
}

float sign(float v)
{
  return (v < 0 ? -1 : (v > 0 ? 1 : 0));
}

bool maybe()
{
  return true;
}

bool solid_at(int x, int y, int w, int h)
{
  return tile_flag_at(x, y, w, h, 0);
}

bool ice_at(int x, int y, int w, int h)
{
  return tile_flag_at(x, y, w, h, 4);
}

bool tile_flag_at(int x, int y, int w, int h, u8 flag)
{
  for (int i = max(0, floor(x / 8.f)); i <= min(15, (x + w - 1) / 8.f); i++)
  {
    for (int j = max(0, floor(y / 8.f)); j <= min(15, (y + h - 1) / 8.f); j++)
    {
      if (fget(tile_at(i, j), flag))
      {
        return true;
      }
    }
  }
  return false;
}

int tile_at(int x, int y)
{
  uint8_t roomx=room%8;
  uint8_t roomy=room>>3;
  return mget(roomx*16+x, roomy*16+y);
}

bool spikes_at(int x, int y, int w, int h, int xspd, int yspd)
{
  for (int i=max(0,floor(x/8.f)); i < min(15,(x+w-1)/8.f); i++)
  {
    for (int j=max(0,floor(y/8.f)); j < min(15,(y+h-1)/8.f); j++)
    {
      int tile=tile_at(i,j);
      if (tile==17 and ((y+h-1)%8>=6 or y+h==j*8+8) and yspd>=0)
        return true;
      else if (tile==27 and y%8<=2 and yspd<=0)
        return true;
      else if (tile==43 and x%8<=2 and xspd<=0)
        return true;
      else if (tile==59 and ((x+w-1)%8>=6 or x+w==i*8+8) and xspd>=0)
        return true;
    }
  }
  return false;
}


void draw_time(int x, int y)
{
  int s = seconds;
  int m = minutes % 60;
  int h = minutes / 60;

  #ifdef POKITTO
    //rectfill(x-1, y-1, x + 32, y + 5, 0);
    pb.display.setColor(0);
    pb.display.fillRect(x-1,y-1,33,6);
    pb.display.setColor(7);
  #elif defined PICOBOY
    pb.display.setTextColor(WHITE,BLACK);
  #endif // POKITTO

  pb.display.setCursor(x , y);
  pb.display.printf("%02d:%02d:%02d", h, m, s);
}

int level_index()
{
  return room;
}

bool is_title()
{
  return level_index() == 31;
}

void next_room()
{
  goto_room = room + 1;
  uint8_t roomx=(room+1)%8;
  uint8_t roomy=(room+1)>>3;
  if(roomx==2 && roomy==1)
    music(30);
  else if(roomx==3 && roomy==1)
    music(20);
  else if(roomx==4 && roomy==2)
    music(30);
  else if(roomx==5 && roomy==3)
    music(30);
}

void restart_room()
{
  will_restart = true;
  delay_restart = 15;
}

void add_object(Object * obj)
{
  objects[objects_count++] = obj;
}

void destroy_object(Object * obj)
{
  for (int i = 0; i < objects_count; i++)
  {
    if (objects[i] == obj)
    {
      deleted_objects[deleted_objects_count++] = obj;
      objects[i] = NULL;
      break;
    }
  }
}

void kill_player(Player * player)
{
  sfx_timer=12;
  sfx(0);
  deaths++;
  for (int i = 0; i < DEAD_PARTICLES_COUNT; i++)
  {
    float angle = (i / 8.f) * 360;
    dead_particles[i].x = player->x + 4;
    dead_particles[i].y = player->y + 4;
    dead_particles[i].spd.x = sin(angle) * 3;
    dead_particles[i].spd.y = cos(angle) * 3;
  }
  dead_particles_timer = 10;

  destroy_object(player);
  restart_room();
}

void init_object(Object * object, int x, int y)
{
  if (object->if_not_fruit && got_fruit[1 + level_index()])
  {
    return;
  }

  object->setPosition(x, y);
  object->init();
  add_object(object);
}

float rnd(int x)
{
  return random(x * 100 + 1) / 100.f;
}
