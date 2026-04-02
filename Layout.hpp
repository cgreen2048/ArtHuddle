#ifndef __LAYOUT_HPP__
#define __LAYOUT_HPP__

#include <iostream>
#include <vector>
#include "Screen.hpp"
#include "GuiElement.hpp"
#include "vec2.hpp"


class Layout : public GuiElement {
    private:
        vec2 start;
        vec2 end;
        bool hasParentStart = false;
        bool hasParentEnd = false;
        std::vector<GuiElement*> elements;
        bool active;
    public:
        Layout();
        Layout(ElementParameters ep);
        ~Layout();
        vec2 getStart() const;
        vec2 getEnd() const;
        void setStart(const vec2& start);
        void setEnd(const vec2& end);
        void setParentStart(const ivec2& start);
        void setParentEnd(const ivec2& end);
        void setActive(bool value);
        bool isActive();
        void addElement(GuiElement *element);
        void draw(Screen *screen);
        void writeXml(std::ostream& out, int depth = 0) const;
        bool resolveEvent(Event* e);
        const std::vector<GuiElement*>& getElements() const;
        int getAbsoluteStartX();
        int getAbsoluteStartY();
        int getAbsoluteEndX();
        int getAbsoluteEndY();
        bool isValid(ElementParameters ep);
};

#endif