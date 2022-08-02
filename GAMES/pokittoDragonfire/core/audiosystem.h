#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

enum SFX {
    sfxStep = 0,
    sfxDie = 1,
    sfxFire = 2,
    sfxDing1 = 3,
    sfxDing2 = 4,
    sfxDing3 = 5,
    sfxDing4 = 6,
    sfxJump = 7
};

const int sfx_count = 8;

enum Song {
    musNone = 0
};

const int song_count = 1;

class AudioSystem
{
public:

    static void initialize();

    static void setMusicFraction(float fraction);

    static void setVolume(float value);

    static float getVolume();

    static void play(SFX);

    static void playSong(Song);
};

#endif // AUDIOSYSTEM_H
