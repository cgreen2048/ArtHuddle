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
    
    public:
        Triangle();
        Triangle(ivec2, ivec2, ivec2, ivec3);
        ~Triangle();
        void draw();
};

#endif