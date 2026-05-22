#ifndef __ELLIPSE_HPP__
#define __ELLIPSE_HPP__

#include "ArtHuddle/elements/GuiElement.hpp"
#include "ArtHuddle/core/ElementParameters.hpp"
#include "ArtHuddle/events/Event.hpp"
#include "ArtHuddle/events/ClickEvent.hpp"
#include "ArtHuddle/core/vec2.hpp"
#include "ArtHuddle/core/vec3.hpp"

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
        void setCenter(ivec2 point, TagType pointType);
        void setRadiusX(int radX);
        void setRadiusY(int radY);
        void setColor(ivec3 color, TagType colorType);
        bool isInside(ivec2 coordinates);
        ElementParameters getParameters();
        guiElement getType();
        void modifyColor(ivec3 newColor);
        void setBounds();
		std::vector<ivec2> getBounds();
};

#endif