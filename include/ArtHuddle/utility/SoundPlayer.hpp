#ifndef __SOUND_PLAYER_HPP__
#define __SOUND_PLAYER_HPP__

#include <vector>
#include <string>
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>
#include "ArtHuddle/utility/Sound.hpp"
#include "ArtHuddle/core/SoundState.hpp"

class SoundPlayer {
    private:
        SDL_AudioStream* stream;
        SDL_AudioSpec spec;
        std::vector<Sound> soundBank;
        std::vector<SoundState> playback;
        bool muted = false;

        static void streamLoader(void* userData, SDL_AudioStream* stream, int amount, int x);

    public:
        SoundPlayer();
        ~SoundPlayer();
        void togglePlayback();
        bool loadSound(std::string filePath);
        bool playSound(std::string filePath, bool loop);
        bool stopSound(std::string filePath);
        std::vector<Sound> getSoundBank();
        bool isMuted();
        void toggleMute();
};

#endif