#ifndef __POINT_HPP__
#define __POINT_HPP__

#include "GuiElement.hpp"

class Point : public GuiElement {
	private:
		vec2 coords;
		vec3 color;
	
	public:
		Point();
        Point(vec2, vec3);
		~Point();
		void draw();
};

#endif