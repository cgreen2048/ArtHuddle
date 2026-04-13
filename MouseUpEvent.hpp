#ifndef __MOUSE_UP_EVENT_HPP__
#define __MOUSE_UP_EVENT_HPP__

#include "MouseEvent.hpp"

class MouseUpEvent : public MouseEvent {
    public:
        MouseUpEvent(ivec2 coords);
};

#endif