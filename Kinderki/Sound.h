#pragma once
#include <irrklang/irrKlang.h>
using namespace irrklang;


class Sound {
public:
    ISoundEngine* SoundEngine;
    const char* data;
    Sound(const char* file)
    {
        data = file;
        SoundEngine = createIrrKlangDevice();
    }

    ~Sound()
    {
        SoundEngine->drop();
    }

    void play() {
        SoundEngine->play2D(data);
    }

    void playLooped()
    {
        SoundEngine->play2D(data,true);
    }
};