#ifndef __ARROW_HPP__
#define __ARROW_HPP__

#include "GuiElement.hpp"

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
        bool validateAndNormalize(ElementParameters& ep);
        ElementParameters getParameters();
        guiElement getType();
};

#endif