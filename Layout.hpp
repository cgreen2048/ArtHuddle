#ifndef __LAYOUT_HPP__
#define __LAYOUT_HPP__

#include <iostream>
#include <vector>
#include "Screen.hpp"
#include "GuiElement.hpp"
#include "vec2.hpp"

class Layout : public GuiElement {
    private:
        float startX;
        float startY;
        float endX;
        float endY;
        ivec2 parentStart;
        ivec2 parentEnd;
        std::vector<GuiElement*> elements;
        bool active;
    public:
        Layout();
        ~Layout();
        void setParentStart(const ivec2& start);
        void setParentEnd(const ivec2& end);
        void setStartX(float sX);
        void setStartY(float sY);
        void setEndX(float eX);
        void setEndY(float eY);
        void setActive(bool value);
        bool isActive();
        void addElement(GuiElement *element);
        void draw();
        void writeXml(std::ostream& out) const;
        const std::vector<GuiElement*>& getElements() const;
};