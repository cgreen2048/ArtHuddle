#ifndef __CLICK_EVENT_HPP__
#define __CLICK_EVENT_HPP__

#include "ArtHuddle/events/Event.hpp"

class ClickEvent : public Event {
    private:
        int mouseX;
        int mouseY;
    public:
        ClickEvent(int x, int y);
        int getMouseX();
        int getMouseY();
};

#endif