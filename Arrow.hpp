#ifndef __ARROW_HPP__
#define __ARROW_HPP__

#include "Box.hpp"
#include "Triangle.hpp"

class Arrow : public GuiElement {
    private:
        Box stem;
        Triangle point;
        ivec3 color;
        
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
        bool isValid(ElementParameters ep);
};

#endif