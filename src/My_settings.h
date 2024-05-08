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
*/
//#define PROJ_SCREENMODE MODE15          

/*
Mode 15 for 240x240 display
Name: Hi-res 16-color mode
Useful for: High resolution with 16 colors, but high RAM usage
Type: Raster, Screen Buffer
Resolution: 220x176 
Bit Depth: 4 bpp
Colours: 16
RAM Usage: 19360 bytes
*/
//#define PROJ_SCREENMODE MODE15_240x240   

/*
Mode 16
Name: Hi-res 16-color mode
Useful for: High resolution with 16 colors, but high RAM usage
Type: Raster, Screen Buffer
Resolution: 220x176 clipping to 128x128
Bit Depth: 4 bpp
Colours: 16
RAM Usage: 19360 bytes
*/
//#define PROJ_SCREENMODE MODE16
#define PROJ_MODE16_OFFSET_X ((220-128)/2)
#define PROJ_MODE16_OFFSET_Y ((176-128)/2)

/*
Mode 2
Name: Lores mode / fast 16 color mode
Useful for: Fast 16 colors with low screen buffer RAM usage
Type: Raster, Screen Buffer
Resolution: 110x88
Bit Depth: 4 bpp
Colours: 16
RAM Usage: 4840 bytes
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
*/
//#define PROJ_SCREENMODE MODE13

/*
TAS Mode
Name: Tiles-And-Sprites (TAS) Mode
Useful for: High resolution, High color, Tile-based games. See this thread.
Type: Tiled mode
Resolution: 220x176
Bit Depth: 8 bpp
Colours: 256
RAM Usage: Configurable
*/
#define PROJ_SCREENMODE TASMODE
#define PROJ_MAX_SPRITES 100
#define PROJ_TILE_H 16
#define PROJ_TILE_W 16
#define MAX_TILE_COUNT 256
#define TAS_X_OFFSET ((220-128)/2)
#define TAS_Y_OFFSET ((176-128)/2)




#define NUM_CHANNELS 3
#define PROJ_FPS 50
#define PROJ_HIGH_RAM HIGH_RAM_MUSIC
#define PROJ_PERSISTENCE true
#define PROJ_ENABLE_SOUND 0  // 0 = all sound functions disabled DEPRICATED - NO NEED FOR LibAudio
#define PROJ_ENABLE_SYNTH 0 // DEPRICATED - NO NEED FOR LibAudio
#define POK_ENABLE_SD 0 //NOT USED IN ESPboy
#define PROJ_AUD_FREQ 8000
