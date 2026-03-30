#ifndef __SOUND_HPP__
#define __SOUND_HPP__

#include <vector>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>

class Sound {
    private:
        std::string filePath;
        Uint8* audioBuffer;
        Uint32 audioLength;

    public:
        Sound(Uint8* bufferData, Uint32 soundLength, std::string soundName);
        ~Sound();
        std::string getName();
        Uint8* getBuffer();
        Uint32 getLength();

};

#endif