#ifndef __ARROW_HPP__
#define __ARROW_HPP__

#include "ArtHuddle/elements/GuiElement.hpp"
#include "ArtHuddle/core/ElementParameters.hpp"

class Arrow : public GuiElement {
    private:
        ivec2 min;
        ivec2 max;
        ivec2 pointA;
        ivec2 pointB;
        ivec2 pointC;
        ivec3 color;
        TagType minType = TagType::Vec;
        TagType maxType = TagType::Vec;
        TagType pointAType = TagType::Vec;
        TagType pointBType = TagType::Vec;
        TagType pointCType = TagType::Vec;
        TagType colorType = TagType::Vec;
        
    public:
        Arrow();
        Arrow(ivec2 min, ivec2 max, ivec2 a, ivec2 b, ivec2 c, ivec3 color);
        Arrow(ElementParameters ep);
        Arrow(const Arrow& cp);
		Arrow& operator=(const Arrow& rhs);
		bool operator==(Arrow rhs);
		bool operator!=(Arrow rhs);
		~Arrow();
        void draw(Screen* screen);
        GuiElement* clone() const;
        void writeXml(std::ostream& out, int depth) const;
        bool isInside(ivec2 coordinates);
        ivec2 getMin();
        ivec2 getMax();
        ivec2 getA();
        ivec2 getB();
        ivec2 getC();
        void setMin(ivec2 point, TagType pointType);
        void setMax(ivec2 point, TagType pointType);
        void setA(ivec2 point, TagType pointType);
        void setB(ivec2 point, TagType pointType);
        void setC(ivec2 point, TagType pointType);
        void setColor(ivec3 color, TagType colorType);
        bool validateAndNormalize(ElementParameters& ep);
        ElementParameters getParameters();
        guiElement getType();
        void modifyColor(ivec3 newColor);
        void setBounds();
		std::vector<ivec2> getBounds();
};

#endif