#ifndef __MOUSE_DOWN_EVENT_HPP__
#define __MOUSE_DOWN_EVENT_HPP__

#include "Event.hpp"
#include "vec2.hpp"

class MouseDownEvent : public Event {
    private:
        ivec2 coords;
    public:
        MouseDownEvent(ivec2 coords);
        ivec2 getCoords();
};

#endif