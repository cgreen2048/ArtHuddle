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
        ivec2 parentStart;
        ivec2 parentEnd;
        bool hasParentStart = false;
        bool hasParentEnd = false;
        std::vector<GuiElement*> elements;
        bool active;
    public:
        Layout();
        ~Layout();
        void setStart(const vec2& start);
        void setEnd(const vec2& end);
        void setParentStart(const ivec2& start);
        void setParentEnd(const ivec2& end);
        void setActive(bool value);
        bool isActive();
        void addElement(GuiElement *element);
        void draw();
        void writeXml(std::ostream& out) const;
        const std::vector<GuiElement*>& getElements() const;
        int getAbsoluteStartX();
        int getAbsoluteStartY();
        int getAbsoluteEndX();
        int getAbsoluteEndY();
};