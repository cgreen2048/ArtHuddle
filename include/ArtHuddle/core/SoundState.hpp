#ifndef __SOUND_STATE_HPP__
#define __SOUND_STATE_HPP__

#include <SDL3/SDL_stdinc.h>
#include <string>

struct SoundState {
    std::string filePath;
    Uint8* buffer;
    Uint32 audioLength;
    Uint8* bufferStart;
    Uint32 originalLength;
    bool loop;
};

#endif