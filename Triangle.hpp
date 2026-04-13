#ifndef __TRIANGLE_HPP
#define __TRIANGLE_HPP

#include "GuiElement.hpp"
#include "vec2.hpp"
#include "vec3.hpp"

class Triangle : public GuiElement {
    private:
        ivec2 a;
        ivec2 b;
        ivec2 c;
        ivec3 color;
        TagType aType = TagType::Vec;
		TagType bType = TagType::Vec;
        TagType cType = TagType::Vec;
		TagType colorType = TagType::Vec;
    
    public:
        Triangle();
        Triangle(ivec2 a, ivec2 b, ivec2 c, ivec3 color);
        Triangle(ElementParameters ep);
        Triangle(const Triangle& cp);
        Triangle& operator=(const Triangle& cp);
        bool operator==(Triangle rhs);
        bool operator!=(Triangle rhs);
        ~Triangle();
        void draw(Screen *screen);
        GuiElement* clone() const;
        void setA(const ivec2& v, TagType t);
		void setB(const ivec2& v, TagType t);
        void setC(const ivec2& v, TagType t);
		void setColor(const ivec3& v, TagType t);
		void writeXml(std::ostream& out, int depth) const;
        ivec2 getA();
        ivec2 getB();
        ivec2 getC();
        bool isInside(ivec2 coordinates);
        bool validateAndNormalize(ElementParameters& ep);
};

#endif