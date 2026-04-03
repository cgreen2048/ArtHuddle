#ifndef __SOUND_EVENT_HPP__
#define __SOUND_EVENT_HPP__

#include "Event.hpp"
#include <string>

enum class SoundActionType {
    PLAY,
    PAUSE,
    STOP
};


class SoundEvent : public Event {
    private:
        // Can be either a path to a file or a name for a sound in the system
        std::string soundName;
        SoundActionType action;
        bool loop = false;
    public:
        SoundEvent(const std::string& name);
        SoundEvent(const std::string& name, SoundActionType act, bool shouldLoop);
        const std::string& getSoundName();
        SoundActionType getAction();
        bool shouldLoop();
};


#endif