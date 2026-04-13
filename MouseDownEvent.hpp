#ifndef __MOUSE_DOWN_EVENT_HPP__
#define __MOUSE_DOWN_EVENT_HPP__

#include "MouseEvent.hpp"

class MouseDownEvent : public MouseEvent {
    public:
        MouseDownEvent(ivec2 coords);
};

#endif