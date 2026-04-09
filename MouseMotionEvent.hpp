#ifndef __MOUSE_MOTION_EVENT_HPP
#define __MOUSE_MOTION_EVENT_HPP

#include "MouseEvent.hpp"

class MouseMotionEvent : public MouseEvent {
    private:
        bool mouseDown;
        ivec2 previousCoords;
    public:
        MouseMotionEvent(ivec2 coords, ivec2 previousCoords, bool mouseDown);
        ivec2 getPreviousCoords();
        bool isMouseDown();
}


#endif