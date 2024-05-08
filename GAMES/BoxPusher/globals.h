#define levWidth 128
#define levHeight 128
#define tileSize 32
#define STEPSIZE 2
#define WALKSPEED 8

#define FLOOR 0
#define WALL 1
#define BUTTON 4

int myVolume = 5;
//char currentTune[128];
uint8_t hwVol;

long int totalSteps;
bool renderSprites=true;

int xScroll = 0;
int yScroll = 0;
int numButtons;
int boxesOnButtons;

int levNum;
int levToLoad;
int stLev=0;
int levCursorX;
int levCursorY;

//DigitalOut backlight = DigitalOut(P2_2);
int lightCount=0;
int bright = 255;
uint8_t *moveHistory; // 1kb of undo data
int moveNumber;
int gameMode=0;
char *tempText;
int totalNumberOfLevels;
int totalNumberOfWorlds;

uint8_t *curLevel;
uint8_t *guiBG; // GUI background layer
uint8_t *guiLineHasText;

float intro_timer = 0;
int IT=0;
bool okToChangeBoxState = true;

bool gamePaused = false;

long int fpsCount;
long int fpsCounter;
long int lastMillis;

class GameCookie : public Pokitto::Cookie {
public:
    int level;
    int volume=10;
    int isEmu;
};
/* create instance */
GameCookie cookie;
int currentLevel=0;
int levCount = 0;


long int worldOffset;

struct PAUSEMENU_STUFF{
    int item;
    bool volType;
} pm;


#ifndef POK_SIM
// set hardware volume quite low
//SoftwareI2C swvolpot(P0_4, P0_5); //swapped SDA,SCL
#endif

struct TITLESCREEN_STUFF{
    int px;
    int py;
    int frm;
    bool dir=0;
    bool movingBox;
    uint8_t boxNum;
} ts;

struct PLAYER_DATA {
    int x;  // x postition
    int y;  // y position
    int steps;
    int walking;
    int direction;
    int stepFrame;
} player;

struct BOX_DATA {
    int x;  // x postition
    int y;  // y position
    int steps;
    bool walking;
    int direction;
    int frame;
};

BOX_DATA *boxes;

int numBoxes = 0;
int currentBox = 0; // which box is currently moving

// for my own sprite renderer
#define NUMSPRITES 48
struct SPRITE_DATA {
    const uint16_t *paletteData; // palette data
    const uint8_t *imageData; // image data
    int x;  // x postition
    int y;  // y position
    int hFlip;
    int offset; // tile render pixel offset
    uint8_t bit;
};
SPRITE_DATA *sprites;

int spriteCount = 0;
int *spriteLine;
