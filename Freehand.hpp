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
#include "XmlWriteHelpers.hpp"
#include <limits>
#include <stack>

#define PIXEL_DRAW_DIST_THRESHOLD 3
#define SHAPE_COMPLETION_DIST_THRESHOLD 10

class Freehand : public GuiElement {
    private:
        std::vector<ivec2> points;
        bool hasFirstPoint = false;
        ivec2 lastDrawnPoint; 
        bool finished = false;
        bool isFreehandShape = false;
        ivec3 color;
    public:
        Freehand();
        Freehand(ivec3 color, bool isFreehandShape = false);
        Freehand(const Freehand& cp);
        Freehand(ElementParameters ep);
        void draw(Screen *screen);
        void floodFill(ivec2 start, Screen* screen);
        GuiElement* clone() const;
        void writeXml(std::ostream& out, int depth) const;
        bool resolveEvent(Event *e);
        bool validateAndNormalize(ElementParameters& ep);
        bool isFinished() const;
        bool isFreehandShapeMode() const;
};

#endif