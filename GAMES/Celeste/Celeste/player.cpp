#include "player.h"
extern "C" {
    #include "Tiles.h"
}


Player::Player()
  : Object(player)
{
}

void Player::init()
{
  p_jump = false;
  p_dash = false;
  grace = 0;
  jbuffer = 0;
  djump = max_djump;
  dash_time = 0;
  dash_effect_time = 0;
  dash_target.x = 0;
  dash_target.y = 0;
  dash_accel.x = 0;
  dash_accel.y = 0;
  spr_off = 0;
  hitbox.x = 1;
  hitbox.y = 3;
  hitbox.w = 6;
  hitbox.h = 5;
  spr = 1;
  spd.x = 0;
  spd.y = 0;

  hair.create_hair(this);
}

void Player::update()
{
  if (pause_player) return;

  Object::update();

  int input = (btn(k_right) ? 1 : (btn(k_left) ? -1 : 0));

  // spikes collide
  if (spikes_at(x + hitbox.x, y + hitbox.y, hitbox.w, hitbox.h, spd.x, spd.y))
  {
    kill_player(this);
    return;
  }

  // bottom death
  if (y > 128)
  {
    kill_player(this);
    return;
  }

  bool on_ground = is_solid(0, 1);
  bool on_ice = is_ice(0, 1);

  // smoke particles
  if (on_ground && !was_on_ground)
  {
    // TODO
    y = y / 8 * 8;
    spd.y = 0;
  }

  bool jump = btn(k_jump) && !p_jump;
  p_jump = btn(k_jump);
  if (jump)
  {
    jbuffer = 4;
  }
  else if(jbuffer > 0)
  {
    jbuffer--;
  }

  bool dash = btn(k_dash) && !p_dash;
  p_dash = btn(k_dash);

  if (on_ground)
  {
    grace = 6;
    if (djump < max_djump)
    {
      psfx(54);
      djump = max_djump;
    }
  }
  else if (grace > 0)
  {
    grace--;
  }

  dash_effect_time--;
  if (dash_time > 0)
  {
    dash_time--;
    spd.x = appr(spd.x, dash_target.x, dash_accel.x);
    spd.y = appr(spd.y, dash_target.y, dash_accel.y);
  }
  else
  {
    // move
    float maxrun = 1;
    float accel = 0.6;
    float deccel = 0.15;

    if (!on_ground)
    {
      accel = 0.4;
    }
    else if (on_ice)
    {
      accel = 0.05;
    }

    if (abs(spd.x) > maxrun)
    {
      spd.x = appr(spd.x, sign(spd.x) * maxrun, deccel);
    }
    else
    {
      spd.x = appr(spd.x, input * maxrun, accel);
    }

    // facing
    if (spd.x != 0)
    {
      flip.x = spd.x < 0;
    }

    // gravity
    float maxfall = 2;
    float gravity = 0.21;

    if (abs(spd.y) <= 0.15)
    {
      gravity *= 0.5;
    }

    // wall slide
    if (input != 0 && is_solid(input, 0) && !is_ice(input, 0))
    {
      maxfall = 0.4;
      //if (rnd(10) < 2)
      {
        // init smoke
      }
    }

    if (!on_ground)
    {
      spd.y = appr(spd.y, maxfall, gravity);
    }

    // jump
    if (jbuffer > 0)
    {
      if (grace > 0)
      {
        // normal jump
        jbuffer = 0;
        grace = 0;
        spd.y = -2;
        psfx(1);
      }
      else
      {
        // wall jump
        int wall_dir = is_solid(-3, 0) ? -1 : (is_solid(3, 0) ? 1 : 0);
        if (wall_dir != 0)
        {
          psfx(2);
          jbuffer = 0;
          spd.y = -2;
          spd.x = -wall_dir * (maxrun + 1);
        }
      }
    }

    // dash
    float d_full = 5;
    float d_half = d_full * 0.70710678118;

    if (djump > 0 && dash)
    {
      djump--;
      dash_time = 4;
      has_dashed = true;
      dash_effect_time = 10;

      int v_input = btn(k_up) ? -1 : (btn(k_down) ? 1 : 0);
      if (input != 0)
      {
        if (v_input != 0)
        {
          spd.x = input * d_half;
          spd.y = v_input * d_half;
        }
        else
        {
          spd.x = input * d_full;
          spd.y = 0;
        }
      }
      else if(v_input != 0)
      {
        spd.x = 0;
        spd.y = v_input * d_full;
      }
      else
      {
        spd.x = (flip.x ? -1 : 1);
        spd.y = 0;
      }
      psfx(3);
      freeze = 2;
      dash_target.x = 2 * sign(spd.x);
      dash_target.y = 2 * sign(spd.y);
      dash_accel.x = 1.5;
      dash_accel.y = 1.5;

      if (spd.y < 0)
      {
        dash_target.y *= 0.75;
      }

      if (spd.y != 0)
      {
        dash_accel.x *= 70710678118;
      }

      if (spd.x != 0)
      {
        dash_accel.x *= 70710678118;
      }
    }
    else if (dash && djump <= 0)
    {
      psfx(9);
      // init smoke
    }
  }

  // animation
  spr_off += 0.25;
  if (!on_ground)
  {
    if (is_solid(input, 0))
    {
      spr = 5;
    }
    else
    {
      spr = 3;
    }
  }
  else if (btn(k_down))
  {
    spr = 6;
  }
  else if (btn(k_up))
  {
    spr = 7;
  }
  else if (spd.x == 0 or (!btn(k_left) && !btn(k_right)))
  {
    spr = 1;
  }
  else
  {
    spr = 1 + (((int)spr_off) % 4);
  }

  // next level
  if (y < -4 && level_index() < 30)
  {
    next_room();
  }

  // was on the ground
  was_on_ground = on_ground;
}

void Player::draw()
{
  if (x < -1 || x > 121)
  {
    x = clamp(x, -1, 121);
    spd.x = 0;
  }

  hair.draw_hair(this, flip.x ? -1 : 1, djump);
  int color = djump == 1 ? 8 : (djump == 2 ? 7 + ((frames / 3) % 2) * 4 : 12);

  if(color==8)
    _spr(spr, x, y, flip.x, flip.y);
  else
  {
      uint8_t _flip=0;
      if(flip.x)
          _flip |= 1;
      if(flip.y)
          _flip |= 2;
      if(_flip)
       {
        #ifdef POKITTO
           if(color==7)
             pb.display.drawBitmap(x-_cameraX,y-_cameraY,player_white[spr-1],0,_flip);
           if(color==11)
             pb.display.drawBitmap(x-_cameraX,y-_cameraY,player_green[spr-1],0,_flip);
           if(color==12)
             pb.display.drawBitmap(x-_cameraX,y-_cameraY,player_blue[spr-1],0,_flip);
        #elif defined PICOBOY
           if(color==7)
             pb.display.drawBitmapRot(x-_cameraX,y-_cameraY,player_white[spr-1],0,_flip);
           if(color==11)
             pb.display.drawBitmapRot(x-_cameraX,y-_cameraY,player_green[spr-1],0,_flip);
           if(color==12)
             pb.display.drawBitmapRot(x-_cameraX,y-_cameraY,player_blue[spr-1],0,_flip);
        #endif
       }
       else
       {
           if(color==7)
             pb.display.drawBitmap(x-_cameraX,y-_cameraY,player_white[spr-1]);
           if(color==11)
             pb.display.drawBitmap(x-_cameraX,y-_cameraY,player_green[spr-1]);
           if(color==12)
             pb.display.drawBitmap(x-_cameraX,y-_cameraY,player_blue[spr-1]);
       }

  }
}


