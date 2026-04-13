#ifndef __ELLIPSE_HPP__
#define __ELLIPSE_HPP__

#include "GuiElement.hpp"
#include "ElementParameters.hpp"
#include "Event.hpp"
#include "ClickEvent.hpp"
#include "vec2.hpp"
#include "vec3.hpp"

class Ellipse : public GuiElement {
    private:
        ivec2 center;
        int radiusX;
        int radiusY;
        ivec3 color;
        TagType centerType = TagType::IVec;
        TagType colorType = TagType::IVec;

    public:
        Ellipse();
        Ellipse(ivec2 center, int radius, ivec3 color);
        Ellipse(ivec2 center, int radiusX, int radiusY, ivec3 color);
        Ellipse(const Ellipse& cp);
        Ellipse& operator=(const Ellipse& rhs);
        Ellipse(ElementParameters ep);
        ~Ellipse();

        void draw(Screen* screen);
        GuiElement* clone() const;
        void writeXml(std::ostream& out, int depth) const;
        bool validateAndNormalize(ElementParameters& ep);

        ivec2 getCenter();
        int getRadiusX();
        int getRadiusY();
        bool isInside(ivec2 coordinates);
};

#endif