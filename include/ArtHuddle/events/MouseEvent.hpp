#ifndef __MOUSE_EVENT_HPP__
#define __MOUSE_EVENT_HPP__

#include "ArtHuddle/events/Event.hpp"
#include "ArtHuddle/core/vec2.hpp"

class MouseEvent : public Event {
protected:
    ivec2 coords;
public:
    MouseEvent(EventType type, ivec2 coords);
    ivec2 getCoords() const;
};

#endif