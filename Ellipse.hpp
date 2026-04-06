#ifndef __ELLIPSE_HPP__
#define __ELLIPSE_HPP__

#include "GuiElement.hpp"

class Ellipse : public GuiElement {
    private:
        ivec2 center;
        int radiusX;
        int radiusY;

    public:
        Ellipse();
        Ellipse(ivec2 center, int radius);
        Ellipse(ivec2 center, int radiusX, int radiusY);
        Ellipse(const Ellipse& cp);
        Ellipse& operator=(const Ellipse& rhs);
        ~Ellipse();

        void draw(Screen* screen);
        void writeXml(std::ostream& out, int depth) const;
        bool resolveEvent(Event* e);
        bool isValid(ElementParameters ep);
};