#define PROJ_SCREENMODE TASMODE
#define PROJ_FPS 100

// Choose how to use Pokitto's "extra" 4kb of RAM.
// Optional. Can be:
//   HIGH_RAM_OFF   - Needed for USB to work
//   HIGH_RAM_ON    - Simply enable the RAM hardware
//   HIGH_RAM_MUSIC - Enable and move the soud buffers to high RAM
// Default is HIGH_RAM_OFF.
#define PROJ_HIGH_RAM HIGH_RAM_MUSIC

// ---- SECTION: SOUND ----
// Choose whether to enable sound or not.
// Optional. Can be 0 or 1. Default is 1.
#define PROJ_ENABLE_SOUND 1
// Enable Pokitto::Sound::playSFX
// Optional. Comment to disable.
#define PROJ_ENABLE_SFX
// Enable streaming music from SD
// Optional. Comment to disable.
#define PROJ_ENABLE_SD_MUSIC
// Defines the rate your audio has been encoded with.
// A higher rate sounds better but takes up more CPU
// and Flash space.
// Optional. Default is 22050.
#define PROJ_AUD_FREQ 22050
// Automatically restart streaming music when it ends.
// Optional. Default is 1.
//#define PROJ_STREAM_LOOP 1
// Tell the sound system which SD library to use.
// If you use one of these libraries, it's important that sound
// is streamed using the same one.
// Optional. Default is PokittoDisk (PFFS).
// #define PROJ_SDFS_STREAMING
#define PROJ_FILE_STREAMING


// Enable Synth
// Optional. Can be 0 or 1. Default is 0.
#define PROJ_ENABLE_SYNTH 0
#define PROJ_LINE_FILLERS TAS::NOPFiller, TAS::NOPFiller, TAS::NOPFiller
