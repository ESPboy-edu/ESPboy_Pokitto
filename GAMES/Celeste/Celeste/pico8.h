#ifndef PICO8_H
#define PICO8_H

#include "platform_Pokitto.h"

extern int16_t _cameraX;
extern int16_t _cameraY;

#ifdef POKITTO
    void updateCamera(int playerX,int playerY);
#endif // POKITTO

/*--------------------------------------------------------------------------------------------
	Graphics
--------------------------------------------------------------------------------------------*/

//void clip(uint8_t x,uint8_t y, uint8_t w,uint8_t h);
uint8_t pget (uint8_t x,uint8_t y);
void pset (uint8_t x,uint8_t y,uint8_t col=0xFF);
uint8_t sget (uint8_t x,uint8_t y);

uint8_t fget (uint8_t n,uint8_t f=0xFF);

void print (char *str);
void print (char *str ,uint8_t x ,uint8_t y ,uint8_t col=0xFF);

void color (uint8_t col);
void cls (int8_t col=BLACK);
void camera (int16_t x=0, int16_t y=0);
void circ (uint8_t x,uint8_t y,uint8_t r,uint8_t col=0xFF);
void circfill (uint8_t x,uint8_t y,uint8_t r,uint8_t col=0xFF);
void line (uint8_t x0, uint8_t y0, uint8_t x1 ,uint8_t y1, uint8_t col=0xFF);
void rect (uint8_t x0, uint8_t y0, uint8_t x1 ,uint8_t y1, uint8_t col=0xFF);
void rectfill (uint8_t x0, uint8_t y0, uint8_t x1 ,uint8_t y1, uint8_t col=0xFF);
void pal(uint8_t c0,uint8_t c1,uint8_t p=0);
void pal ();
void palt (uint8_t c, bool t=true);
void palt ();
void _spr(uint8_t n, int x, int y ,uint8_t w ,uint8_t h ,bool flip_x=false, bool flip_y=false);
void _spr(uint8_t n, int x, int y ,bool flip_x=false, bool flip_y=false);



/*--------------------------------------------------------------------------------------------
	Input
--------------------------------------------------------------------------------------------*/
bool btn (uint8_t i, uint8_t p=0);
bool pbtn (uint8_t i, uint8_t p=0);


/*--------------------------------------------------------------------------------------------
	Audio
--------------------------------------------------------------------------------------------*/
void sfx (uint8_t n, uint8_t channel=0 , int16_t offset=0 , uint16_t length=0);
void music (int8_t n=-1, uint8_t fade_len=0 ,uint8_t channel_mask=0);

/*--------------------------------------------------------------------------------------------------------
	Map
--------------------------------------------------------------------------------------------------------*/
uint8_t mget (uint8_t x,uint8_t y);
void mset (uint8_t x,uint8_t y, uint8_t v);
void map(uint8_t cel_x, uint8_t cel_y, uint8_t x, uint8_t y, uint8_t cel_w, uint8_t cel_h, uint8_t layer=0);

/*--------------------------------------------------------------------------------------------------------
	Math
-------------------------------------------------------------------------------------------------------*/
int16_t rnd(int16_t x);

void _init();
void _update();
void _draw();
#endif // PICO8_H
