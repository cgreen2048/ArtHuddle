#ifndef __LINE_HPP__
#define __LINE_HPP__

#include "GuiElement.hpp"

class Line : public GuiElement {
	private:
		vec2 start;
        vec2 end;
		vec3 color;

    public:
		Line();
        Line(vec2, vec2, vec3);
		~Line();
		void draw();
};

#endif