#ifndef __EVENT_HPP__
#define __EVENT_HPP__

#include "ArtHuddle/core/EventTypes.hpp"

class Event {
    private: 
        EventType type;
    public:
        Event();
        Event(EventType t);
        Event(const Event& cp);
        Event& operator=(const Event& rhs);
        virtual ~Event();

        EventType getType() const;
};

#endif