#include "SoundEvent.hpp"

// Default to playing a sound when no event type given
SoundEvent::SoundEvent(const std::string& name) : Event(EventType::SOUND), soundName{name}, action{SoundActionType::PLAY} {}

SoundEvent::SoundEvent(const std::string& name, SoundActionType act, bool shouldLoop = false) : Event(EventType::SOUND), soundName{name}, action{act}, loop{shouldLoop} {}

const std::string& SoundEvent::getSoundName() {
    return this->soundName;
}

SoundActionType SoundEvent::getAction() {
    return this->action;
}

bool SoundEvent::shouldLoop() {
    return this->loop;
}