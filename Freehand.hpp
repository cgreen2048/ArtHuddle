#ifndef __FREEHAND_HPP__
#define __FREEHAND_HPP__

#include "GuiElement.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Event.hpp"

class Freehand : public GuiElement {
    private:
        std::vector<GuiElement*> elements;
        bool hasFirstPoint = false;
        ivec2 lastDrawnPoint; 
        bool finished = false;
    public:
        Freehand();
        Freehand(const Freehand& cp);
        void draw(Screen *screen);
        void writeXml(std::ostream& out, int depth) const;
        bool resolveEvent(Event *e);
};

#endif