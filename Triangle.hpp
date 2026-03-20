#ifndef __TRIANGLE_HPP
#define __TRIANGLE_HPP

#include "GuiElement.hpp"
#include "vec2.hpp"
#include "vec3.hpp"

class Triangle : public GuiElement {
   public:
		enum class TagType { Vec, IVec }; 
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
        Triangle(ivec2, ivec2, ivec2, ivec3);
        Triangle(const Triangle&);
        Triangle& operator=(const Triangle&);
        bool operator==(Triangle);
        bool operator!=(Triangle);
        ~Triangle();
        void draw();
        void setA(const ivec2& v, TagType t);
		void setB(const ivec2& v, TagType t);
        void setC(const ivec2& v, TagType t);
		void setColor(const ivec3& v, TagType t);
		void writeXml(std::ostream& out, int depth) const;
        ivec2 getA();
        ivec2 getB();
        ivec2 getC();
};

#endif