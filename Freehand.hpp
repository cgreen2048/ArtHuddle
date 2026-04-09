#ifndef __FREEHAND_HPP__
#define __FREEHAND_HPP__

#include "GuiElement.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Event.hpp"
#include "ClickEvent.hpp"
#include "MouseDownEvent.hpp"
#include "MouseUpEvent.hpp"
#include "MouseMotionEvent.hpp"
#include "ElementParameters.hpp"

class Freehand : public GuiElement {
    private:
        std::vector<GuiElement*> elements;
        bool hasFirstPoint = false;
        ivec2 lastDrawnPoint; 
        bool finished = false;
        ivec3 color;
    public:
        Freehand();
        Freehand(ivec3 color);
        Freehand(const Freehand& cp);
        void draw(Screen *screen);
        GuiElement* clone() const;
        void writeXml(std::ostream& out, int depth) const;
        bool resolveEvent(Event *e);
        bool isValid(ElementParameters ep);
};

#endif