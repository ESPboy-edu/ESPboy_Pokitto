#define POKITTO 1

/*
Mode 15
Name: Hi-res 16-color mode
Useful for: High resolution with 16 colors, but high RAM usage
Type: Raster, Screen Buffer
Resolution: 220x176 rescaling to 128x128
Bit Depth: 4 bpp
Colours: 16
RAM Usage: 19360 bytes
My_settings.h: PROJ_SCREENMODE = 15
Screen Mode Define: MODE15
*/
#define PROJ_MODE15 1              

/*
Mode 16
Name: Hi-res 16-color mode
Useful for: High resolution with 16 colors, but high RAM usage
Type: Raster, Screen Buffer
Resolution: 220x176 clipping to 128x128
Bit Depth: 4 bpp
Colours: 16
RAM Usage: 19360 bytes
My_settings.h: PROJ_SCREENMODE = 15
Screen Mode Define: MODE15
*/
#define PROJ_MODE16_OFFSET_X ((220-128)/2)
#define PROJ_MODE16_OFFSET_Y ((176-128)/2)
//#define PROJ_MODE16 1   

/*
Mode 2
Name: Lores mode / fast 16 color mode
Useful for: Fast 16 colors with low screen buffer RAM usage
Type: Raster, Screen Buffer
Resolution: 110x88
Bit Depth: 4 bpp
Colours: 16
RAM Usage: 4840 bytes
My_settings.h: PROJ_SCREENMODE = 2 or PROJ_HIRES = 0 (deprecated)
Screen Mode Define: MODE_FAST_16COLOR
*/
//#define PROJ_SCREENMODE MODE_FAST_16COLOR

/*
Mode 13
Name: Mode 13
Useful for: 256 colors, medium ram usage, very fast
Type: Raster, Screen Buffer
Resolution: 110x88
Bit Depth: 8 bpp
Colours: 256
RAM Usage: 9680 bytes
My_settings.h: PROJ_SCREENMODE = 13 or PROJ_MODE13 = 1 (deprecated)
Screen Mode Define: MODE13
*/
//#define PROJ_SCREENMODE MODE13

#define PROJ_FPS 40
#define PROJ_HIGH_RAM HIGH_RAM_MUSIC
#define PROJ_PERSISTENCE true
#define PROJ_ENABLE_SOUND 0     // 0 = all sound functions disabled
#define PROJ_ENABLE_SYNTH 0
#define POK_ENABLE_SD 0
#define PROJ_AUD_FREQ 8000