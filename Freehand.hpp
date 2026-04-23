#ifndef __FREEHAND_HPP__
#define __FREEHAND_HPP__

#include "GuiElement.hpp"
#include "Event.hpp"
#include "ElementParameters.hpp"

#define PIXEL_DRAW_DIST_THRESHOLD 3
#define SHAPE_COMPLETION_DIST_THRESHOLD 10
// #define FREEHAND_PADDING 10

class Freehand : public GuiElement {
    private:
        std::vector<ivec2> points;
        bool hasFirstPoint = false;
        ivec2 lastDrawnPoint; 
        bool finished = false;
        bool isFreehandShape = false;
        ivec3 color;
        // ivec2 minBound;
        // ivec2 maxBound;
        bool hasBounds = false;
    public:
        Freehand();
        Freehand(ivec3 color, bool isFreehandShape = false);
        Freehand(const Freehand& cp);
        Freehand(ElementParameters ep);
        void draw(Screen *screen);
        void floodFill(ivec2 start, Screen* screen);
        void updateBounds(const ivec2& point);
        GuiElement* clone() const;
        void writeXml(std::ostream& out, int depth) const;
        bool resolveEvent(Event *e);
        bool validateAndNormalize(ElementParameters& ep);
        bool isInside(ivec2 coordinates);
        bool isFinished() const;
        bool isFreehandShapeMode() const;
        std::vector<ivec2>& getPoints();
        ivec2 getMinBound() const;
        ivec2 getMaxBound() const;
        bool hasDrawBounds() const;
        ElementParameters getParameters();
        guiElement getType();
        void setPoints();
        void modifyColor(ivec3 newColor);
        void setBounds();
		std::vector<ivec2> getBounds();
};

#endif