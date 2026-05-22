#ifndef __MOUSE_MOTION_EVENT_HPP
#define __MOUSE_MOTION_EVENT_HPP

#include "ArtHuddle/events/MouseEvent.hpp"

class MouseMotionEvent : public MouseEvent {
    private:
        bool mouseDown;

    public:
        MouseMotionEvent(ivec2 coords, bool mouseDown);
        bool isMouseDown() const;
};

#endif