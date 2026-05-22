#include "ArtHuddle/utility/Sound.hpp"

Sound::Sound(Uint8* bufferData, Uint32 soundLength, std::string soundName) {
    this->audioBuffer = bufferData;
    this->audioLength = soundLength;
    this->filePath = soundName;
}

Sound::~Sound() {

}

std::string Sound::getName() {
    return this->filePath;
}

Uint8* Sound::getBuffer() {
    return this->audioBuffer;
}

Uint32 Sound::getLength() {
    return this->audioLength;
}