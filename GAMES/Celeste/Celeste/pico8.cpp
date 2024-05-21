#include "pico8.h"
#include "Tiles.h"
#include "Map.h"
#include "Sfx.h"
#include "music0.h"

#include "libs/LibAudio/LibAudio.h"
Audio::Sink<2, 11000> audio;

uint8_t _color=WHITE;
int16_t _cameraX=0;
int16_t _cameraY=0;


#ifdef POKITTO
uint8_t _palette[16*3] = {0,0,0, 29,43,83, 126,37,83, 0,135,81, 171,82,54, 95,87,79, 194,195,199, 255,241,232, 255,0,77, 255,163,0, 255,240,36, 0,231,86, 41,173,255, 131,118,156, 255,119,168, 255,204,170 };
#elif defined PICOBOY
uint16_t _palette[16]={0x0000,0x194A,0x792A,0x042A,0xAA86,0x5AA9,0xC618,0xFF9D,0xF809,0xFD00,0xFF84,0x072A,0x2D7F,0x83B3,0xFBB5,0xFE75};
#endif // POKITTO

#ifdef POKITTO
    void updateCamera(int playerX,int playerY)
    {
        if (pb.display.width >= 128) {
          _cameraX = -(pb.display.width-128)/2;
        } else {
          _cameraX = (playerX + 4)  - pb.display.width / 2;
          _cameraX = constrain(_cameraX, 0, 128  - pb.display.width);
        }

        if (pb.display.height >= 128) {
          _cameraY = -(pb.display.height-128)/2;
        } else {
          _cameraY = (playerY + 4)  - pb.display.height / 2;
          _cameraY = constrain(_cameraY, 0, 128  - pb.display.height - 4);
        }
}
#endif // POKITTO

/*--------------------------------------------------------------------------------------------
	Graphics
--------------------------------------------------------------------------------------------*/


uint8_t pget (uint8_t x,uint8_t y)
{
    return pb.display.getPixel(x-_cameraX,y-_cameraY);
};


void pset (uint8_t x,uint8_t y,uint8_t col)
{
    #ifdef POKITTO
    pb.display.setColor(col==0xFF?_color:col);
    pb.display.drawPixel(x-_cameraX,y-_cameraY);
    #elif defined PICOBOY
    pb.display.drawPixel(x-_cameraX,y-_cameraY,col==0xFF?_color:col);
    #endif // POKITTO
};


uint8_t sget (uint8_t x,uint8_t y)
{
    //TODO
    return 0;
};


uint8_t fget (uint8_t n,uint8_t f)
{
    if(f<8)
        return _gff[n] & 1<<f;

    return _gff[n];
};


void print (char *str)
{
    #ifdef POKITTO
    pb.display.setColor(_color);
    #elif defined PICOBOY
    pb.display.setTextColor(_color);
    #endif // POKITTO
    pb.display.print(str);
};


void print (char *str ,uint8_t x ,uint8_t y ,uint8_t col)
{
    pb.display.setCursor(x-_cameraX,y-_cameraY);
    #ifdef POKITTO
    pb.display.setColor(col==0xFF?_color:col);
    #elif defined PICOBOY
    pb.display.setTextColor(col==0xFF?_color:col);
    #endif // POKITTO
    pb.display.print(str);
};



void color (uint8_t col)
{
    _color=col;
};


void cls (int8_t col)
{
    pb.display.fillScreen(col);
};


void camera (int16_t x, int16_t y)
{
    _cameraX=x;
    _cameraY=y;
};


void circ (uint8_t x,uint8_t y,uint8_t r,uint8_t col)
{
    #ifdef POKITTO
    pb.display.setColor(col==0xFF?_color:col);
    pb.display.drawCircle(x-_cameraX,y-_cameraY,r);
    #elif defined PICOBOY
    pb.display.drawCircle(x-_cameraX,y-_cameraY,r,col==0xFF?_color:col);
    #endif // POKITTO
};


void circfill (uint8_t x,uint8_t y,uint8_t r,uint8_t col)
{
    #ifdef POKITTO
    pb.display.setColor(col==0xFF?_color:col);
    pb.display.fillCircle(x-_cameraX,y-_cameraY,r);
    #elif defined PICOBOY
    pb.display.fillCircle(x-_cameraX,y-_cameraY,r,col==0xFF?_color:col);
    #endif // POKITTO
};


void line (uint8_t x0, uint8_t y0, uint8_t x1 ,uint8_t y1, uint8_t col)
{
    #ifdef POKITTO
    pb.display.setColor(col==0xFF?_color:col);
    pb.display.drawLine(x0-_cameraX,y0-_cameraY,x1-_cameraX,y1-_cameraY);
    #elif defined PICOBOY
    pb.display.drawLine(x0-_cameraX,y0-_cameraY,x1-_cameraX,y1-_cameraY,col==0xFF?_color:col);
    #endif // POKITTO
};


void rect (uint8_t x0, uint8_t y0, uint8_t x1 ,uint8_t y1, uint8_t col)
{
    #ifdef POKITTO
    pb.display.setColor(col==0xFF?_color:col);
    pb.display.drawRect(x0-_cameraX,y0-_cameraY,abs((x1-_cameraX)-(x0-_cameraX)),abs((y1-_cameraY)-(y0-_cameraY)));
    #elif defined PICOBOY
    pb.display.drawRect(x0-_cameraX,y0-_cameraY,abs((x1-_cameraX)-(x0-_cameraX)),abs((y1-_cameraY)-(y0-_cameraY)),col==0xFF?_color:col);
    #endif // POKITTO
};


void rectfill (uint8_t x0, uint8_t y0, uint8_t x1 ,uint8_t y1, uint8_t col)
{
    #ifdef POKITTO
    pb.display.setColor(col==0xFF?_color:col);
    pb.display.fillRect(x0-_cameraX,y0-_cameraY,abs((x1-_cameraX)-(x0-_cameraX)),abs((y1-_cameraY)-(y0-_cameraY)));
    #elif defined PICOBOY
    pb.display.fillRect(x0-_cameraX,y0-_cameraY,abs((x1-_cameraX)-(x0-_cameraX)),abs((y1-_cameraY)-(y0-_cameraY)),col==0xFF?_color:col);
    #endif // POKITTO
};


void pal(uint8_t c0,uint8_t c1,uint8_t p)
{
    if(p==0)
    {
        #ifdef POKITTO
        _palette[c0*3]=palettePico[c1*3];
        _palette[c0*3+1]=palettePico[c1*3+1];
        _palette[c0*3+2]=palettePico[c1*3+2];
        pb.display.loadRGBPalette(_palette);
        #elif defined PICOBOY
        _palette[c0]=palettePico[c1];
        pb.display.load565Palette(_palette);
        #endif // POKITTO
    }
    //else
    //unsupported
};


void palt (uint8_t c, bool t)
{
    if(t)
    {
        #ifdef POKITTO
        _palette[c*3]=palettePico[pb.display.getInvisibleColor()*3];
        _palette[c*3+1]=palettePico[pb.display.getInvisibleColor()*3+1];
        _palette[c*3+1]=palettePico[pb.display.getInvisibleColor()*3+2];
        pb.display.loadRGBPalette(_palette);
        #elif defined PICOBOY
        _palette[c]=palettePico[pb.display.getTransparentColor()];
        pb.display.load565Palette(_palette);
        #endif // POKITTO
    }else
    {
        #ifdef POKITTO
        _palette[c*3]=palettePico[c*3];
        _palette[c*3+1]=palettePico[c*3+1];
        _palette[c*3+1]=palettePico[c*3+2];
        pb.display.loadRGBPalette(_palette);
        #elif defined PICOBOY
        _palette[c]=palettePico[c];
        pb.display.load565Palette(_palette);
        #endif // POKITTO
    }
};

void pal ()
{
    #ifdef POKITTO
        pb.display.loadRGBPalette(palettePico);
    #elif defined PICOBOY
        pb.display.load565Palette(palettePico);
    #endif // POKITTO
};

void palt ()
{
    #ifdef POKITTO
        pb.display.setInvisibleColor(BLACK);
    #elif defined PICOBOY
        pb.display.setTransparentColor(BLACK);
    #endif // POKITTO
};
void _spr(uint8_t n, int x, int y ,uint8_t w ,uint8_t h ,bool flip_x, bool flip_y)
{
    // TO DO
}

void _spr(uint8_t n, int x, int y ,bool flip_x, bool flip_y)
{
    if((x-_cameraX+8)<0)
        return;
    if((y-_cameraY+8)<0)
        return;
#ifdef POKITTO
    if((x-_cameraX)>pb.display.width)
        return;
    if((y-_cameraY)>pb.display.height)
        return;
#else ifdef PICOBOY
    if((x-_cameraX)>pb.display.width())
        return;
    if((y-_cameraY)>pb.display.height())
        return;
#endif
    uint8_t flip=0;
    if(flip_x)
      flip |= 1;
    if(flip_y)
      flip |= 2;
   if(flip)
   {
    #ifdef POKITTO
       pb.display.drawBitmap(x-_cameraX,y-_cameraY,_gfx[n],0,flip);
    #elif defined PICOBOY
       pb.display.drawBitmapRot(x-_cameraX,y-_cameraY,_gfx[n],0,flip);
    #endif
   }
   else
    pb.display.drawBitmap(x-_cameraX,y-_cameraY,_gfx[n]);
}


/*--------------------------------------------------------------------------------------------
	Input
--------------------------------------------------------------------------------------------*/
bool btn (uint8_t i, uint8_t p)
{
    #ifdef POKITTO
        switch(i)
        {
        case 0:
            return pb.buttons.repeat(BTN_LEFT,0);
         case 1:
            return pb.buttons.repeat(BTN_RIGHT,0);
        case 2:
            return pb.buttons.repeat(BTN_UP,0);
        case 3:
            return pb.buttons.repeat(BTN_DOWN,0);
        case 4:
            return pb.buttons.repeat(BTN_A,0);
        case 5:
            return pb.buttons.repeat(BTN_B,0);
        case 6:
            return pb.buttons.repeat(BTN_C,0);
        }
    #elif defined PICOBOY
        return pb.buttons.repeat(i,0);
    #endif // POKITTO
  return 0;
};


bool pbtn (uint8_t i, uint8_t p)
{
    #ifdef POKITTO
        switch(i)
        {
        case 0:
            return pb.buttons.leftBtn();
         case 1:
            return pb.buttons.rightBtn();
        case 2:
            return pb.buttons.upBtn();
        case 3:
            return pb.buttons.downBtn();
        case 4:
            return pb.buttons.aBtn();
        case 5:
            return pb.buttons.bBtn();
        case 6:
            return pb.buttons.cBtn();
        }
    #elif defined PICOBOY
        return pb.buttons.pressed(i);
    #endif // POKITTO
 return 0;
};


/*--------------------------------------------------------------------------------------------
	Audio
--------------------------------------------------------------------------------------------*/
void sfx (uint8_t n, uint8_t channel , int16_t offset , uint16_t length)
{

#ifdef POKITTO
    switch(n)
    {
    case 0:
        Audio::play(_sfx0);
        //Pokitto::Sound::playSFX(_sfx0,sizeof(_sfx0));
        break;
    case 1:
        Audio::play(_sfx1);
        //Pokitto::Sound::playSFX(_sfx1,sizeof(_sfx1));
        break;
    case 2:
        Audio::play(_sfx2);
        //Pokitto::Sound::playSFX(_sfx2,sizeof(_sfx2));
        break;
    case 3:
        Audio::play(_sfx3);
        //Pokitto::Sound::playSFX(_sfx3,sizeof(_sfx3));
        break;
    case 4:
        Audio::play(_sfx4);
        //Pokitto::Sound::playSFX(_sfx4,sizeof(_sfx4));
        break;
    case 5:
        Audio::play(_sfx5);
        //Pokitto::Sound::playSFX(_sfx5,sizeof(_sfx5));
        break;
    case 6:
        Audio::play(_sfx6);
        //Pokitto::Sound::playSFX(_sfx6,sizeof(_sfx6));
        break;
    case 7:
        Audio::play(_sfx7);
        //Pokitto::Sound::playSFX(_sfx7,sizeof(_sfx7));
        break;
    case 8:
        Audio::play(_sfx8);
        //Pokitto::Sound::playSFX(_sfx8,sizeof(_sfx8));
        break;
    case 9:
        Audio::play(_sfx9);
        //Pokitto::Sound::playSFX(_sfx9,sizeof(_sfx9));
        break;
    case 13:
        Audio::play(_sfx13);
        //Pokitto::Sound::playSFX(_sfx13,sizeof(_sfx13));
        break;
    case 14:
        Audio::play(_sfx14);
        //Pokitto::Sound::playSFX(_sfx14,sizeof(_sfx14));
        break;
    case 15:
        Audio::play(_sfx15);
        //Pokitto::Sound::playSFX(_sfx15,sizeof(_sfx15));
        break;
    case 16:
        Audio::play(_sfx16);
        //Pokitto::Sound::playSFX(_sfx16,sizeof(_sfx16));
        break;
    case 23:
        Audio::play(_sfx23);
        //Pokitto::Sound::playSFX(_sfx23,sizeof(_sfx23));
        break;
    case 35:
        Audio::play(_sfx35);
        //Pokitto::Sound::playSFX(_sfx35,sizeof(_sfx35));
        break;
    case 37:
        Audio::play(_sfx37);
        //Pokitto::Sound::playSFX(_sfx37,sizeof(_sfx37));
        break;
    case 38:
        Audio::play(_sfx38);
        //Pokitto::Sound::playSFX(_sfx38,sizeof(_sfx38));
        break;
    case 51:
        Audio::play(_sfx51);
        //Pokitto::Sound::playSFX(_sfx51,sizeof(_sfx51));
        break;
    case 54:
        Audio::play(_sfx54);
        //Pokitto::Sound::playSFX(_sfx54,sizeof(_sfx54));
        break;
    case 55:
        Audio::play(_sfx55);
        //Pokitto::Sound::playSFX(_sfx55,sizeof(_sfx55));
        break;
    }
#endif

#ifdef PICOBOY
    switch(n)
    {
    case 0:
        pb.sound.playSFX(_sfx0,sizeof(_sfx0));
        break;
    case 1:
        pb.sound.playSFX(_sfx1,sizeof(_sfx1));
        break;
    case 2:
        pb.sound.playSFX(_sfx2,sizeof(_sfx2));
        break;
    case 3:
        pb.sound.playSFX(_sfx3,sizeof(_sfx3));
        break;
    case 4:
        pb.sound.playSFX(_sfx4,sizeof(_sfx4));
        break;
    case 5:
        pb.sound.playSFX(_sfx5,sizeof(_sfx5));
        break;
    case 6:
        pb.sound.playSFX(_sfx6,sizeof(_sfx6));
        break;
    case 7:
        pb.sound.playSFX(_sfx7,sizeof(_sfx7));
        break;
    case 8:
        pb.sound.playSFX(_sfx8,sizeof(_sfx8));
        break;
    case 9:
        pb.sound.playSFX(_sfx9,sizeof(_sfx9));
        break;
    case 13:
        pb.sound.playSFX(_sfx13,sizeof(_sfx13));
        break;
    case 14:
        pb.sound.playSFX(_sfx14,sizeof(_sfx14));
        break;
    case 15:
        pb.sound.playSFX(_sfx15,sizeof(_sfx15));
        break;
    case 16:
        pb.sound.playSFX(_sfx16,sizeof(_sfx16));
        break;
    case 23:
        pb.sound.playSFX(_sfx23,sizeof(_sfx23));
        break;
    case 35:
        pb.sound.playSFX(_sfx35,sizeof(_sfx35));
        break;
    case 37:
        pb.sound.playSFX(_sfx37,sizeof(_sfx37));
        break;
    case 38:
        pb.sound.playSFX(_sfx38,sizeof(_sfx38));
        break;
    case 51:
        pb.sound.playSFX(_sfx51,sizeof(_sfx51));
        break;
    case 54:
        pb.sound.playSFX(_sfx54,sizeof(_sfx54));
        break;
    case 55:
        pb.sound.playSFX(_sfx55,sizeof(_sfx55));
        break;
    }
#endif
};


void music (int8_t n, uint8_t fade_len ,uint8_t channel_mask)
{
#ifdef POKITTO
    switch(n)
    {
    case -1:
        Audio::stop<1>();
        //Pokitto::Sound::pauseMusicStream();
        break;
    case 0:
    case 10:
    case 20:
    case 30:
    case 40:
        auto& music = Audio::play<1>(music0);
        music.setLoop(true);
        //Pokitto::Sound::pauseMusicStream();
        //Pokitto::Sound::playMusicStream("Celeste/music/music0.raw",0);
        break;
   /*
    case 10:
        //Pokitto::Sound::pauseMusicStream();
        //Pokitto::Sound::playMusicStream("Celeste/music/music10.raw",0);
        break;
    case 20:
        //Pokitto::Sound::pauseMusicStream();
        //Pokitto::Sound::playMusicStream("Celeste/music/music20.raw",0);
        break;
    case 30:
        //Pokitto::Sound::pauseMusicStream();
        //Pokitto::Sound::playMusicStream("Celeste/music/music30.raw",0);
        break;
    case 40:
        //Pokitto::Sound::pauseMusicStream();
        //Pokitto::Sound::playMusicStream("Celeste/music/music40.raw",0);
        break;
    */
    }
#endif
};

/*--------------------------------------------------------------------------------------------------------
	Map
--------------------------------------------------------------------------------------------------------*/
uint8_t mget (uint8_t x,uint8_t y)
{
    return _map[y][x];
};
void mset (uint8_t x,uint8_t y, uint8_t v)
{
    //unsupported
};
void map(uint8_t cel_x, uint8_t cel_y, uint8_t x, uint8_t y, uint8_t cel_w, uint8_t cel_h, uint8_t layer)
{
    for(uint8_t i=0; i< cel_h; i++)
            for(uint8_t j=0; j<cel_w; j++)
            {
                uint8_t tile=_map[cel_y+i][cel_x+j];
                if(tile==0)
                  continue;

                if(layer==0)
                  pb.display.drawBitmap(x+(j*8)-_cameraX,y+(i*8)-_cameraY,_gfx[tile]);
                else
                {
                  uint8_t flag = fget(tile);
                  for(uint8_t k=1; k<9; k++)
                  {
                    if((flag&layer)&(1<<(k-1))){
                      pb.display.drawBitmap(x+(j*8)-_cameraX,y+(i*8)-_cameraY,_gfx[tile]);
                      break;
                    }
                  }
                }
            }
};

/*--------------------------------------------------------------------------------------------------------
	Math
-------------------------------------------------------------------------------------------------------*/
int16_t rnd(int16_t x)
{
    return random(0,x);
};
