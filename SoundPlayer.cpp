#include "SoundPlayer.hpp"

SoundPlayer::SoundPlayer() {
    this->spec.format = SDL_AUDIO_F32;
    this->spec.channels = 1;
    this->spec.freq = 44100;
    this->stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &this->spec, SoundPlayer::streamLoader, this);
    if (!(this->stream)) {
        std::cerr << SDL_GetError();
    }

    bool unpause = SDL_ResumeAudioStreamDevice(this->stream);
    if (!unpause) {
        std::cerr << SDL_GetError();
    }
}

SoundPlayer::~SoundPlayer() {
    bool pause = SDL_PauseAudioStreamDevice(this->stream);
    if (!pause) {
        std::cerr << SDL_GetError();
    }
    this->soundBank.clear();
    this->playback.clear();
    SDL_DestroyAudioStream(this->stream);
}

void SoundPlayer::togglePlayback() {
    bool isPaused = SDL_AudioStreamDevicePaused(this->stream);
    if (isPaused) {
        bool unpause = SDL_ResumeAudioStreamDevice(this->stream);
        if (!unpause) {
            std::cerr << SDL_GetError() << '\n';
        }
    }
    else {
        bool pause = SDL_PauseAudioStreamDevice(this->stream);
        if (!pause) {
            std::cerr << SDL_GetError() << '\n';
        }
    }
}

bool SoundPlayer::loadSound(std::string filePath) {
    for (Sound itr : this->soundBank) {
        if (itr.getName() == filePath) {
            return true;
        }
    }
    Uint8* audioBuf;
    Uint32 audioLen;
    SDL_AudioSpec fileSpec;
    bool loaded = SDL_LoadWAV(filePath.c_str(), &fileSpec, &audioBuf, &audioLen);
    if (!loaded) {
        std::cerr << SDL_GetError() << '\n';
        return false;
    }
    
    int convertedLength = 0;
    bool convert = SDL_ConvertAudioSamples(&fileSpec, audioBuf, audioLen, &this->spec, &audioBuf, &convertedLength);
    if (!convert) {
        std::cerr << SDL_GetError() << '\n';
        return false;
    }
    audioLen = static_cast<Uint32>(convertedLength);
    this->soundBank.push_back(Sound(audioBuf, audioLen, filePath));
    return true;
}

bool SoundPlayer::playSound(std::string filePath, bool loop) {
    for (Sound itr : this->soundBank) {
        if (itr.getName() == filePath) {
            SoundState soundData;
            soundData.filePath = itr.getName();
            soundData.buffer = itr.getBuffer();
            soundData.bufferStart = itr.getBuffer();
            soundData.audioLength = itr.getLength();
            soundData.originalLength = itr.getLength();
            this->playback.push_back(soundData);
            return true;
        }
    }
    
    bool loaded = this->loadSound(filePath);
    if (loaded) {
        for (Sound itr : this->soundBank) {
            if (itr.getName() == filePath) {
                SoundState soundData;
                soundData.filePath = itr.getName();
                soundData.buffer = itr.getBuffer();
                soundData.bufferStart = itr.getBuffer();
                soundData.audioLength = itr.getLength();
                soundData.originalLength = itr.getLength();
                this->playback.push_back(soundData);
                return true;
            }
        }
    }
    std::cerr << filePath + " could not be played\n";
    return false;
}

bool SoundPlayer::stopSound(std::string filePath) {
    for (auto itr = this->playback.begin(); itr != this->playback.end(); ++itr) {
        if (itr->filePath == filePath) {
            this->playback.erase(itr);
            return true;
        }
    }
    std::cerr << filePath + " is not currently playing\n";
    return false;
}

std::vector<Sound> SoundPlayer::getSoundBank() {
    return this->soundBank;
}

void SoundPlayer::streamLoader(void* userData, SDL_AudioStream* stream, int amount, int x) {
    SoundPlayer* player = static_cast<SoundPlayer*>(userData);
    Uint8* audioMix = new Uint8[amount]();
    auto audioSample = player->playback.begin();
    while (audioSample != player->playback.end()) {
        Uint32 mixData = std::min(audioSample->audioLength, (Uint32)amount);
        if (mixData > 0) {
            SDL_MixAudio(audioMix, audioSample->buffer, player->spec.format, mixData, 1.0);
            audioSample->buffer += mixData;
            audioSample->audioLength -= mixData;
            if (audioSample->audioLength <= 0 && !audioSample->loop) {
                player->playback.erase(audioSample);
            }
            else if (audioSample->audioLength <= 0 && audioSample->loop) {
                audioSample->buffer = audioSample->bufferStart;
                audioSample->audioLength = audioSample->originalLength;
            }
            else {
                ++audioSample;
            }
        }
    }
    SDL_PutAudioStreamData(stream, audioMix, amount);
    if (audioMix) {
        delete[] audioMix;
    }
}