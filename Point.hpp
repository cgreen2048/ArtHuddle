#ifndef __POINT_HPP__
#define __POINT_HPP__

#include "GuiElement.hpp"

class Point : public GuiElement {
	private:
		ivec2 coords;
		ivec3 color;
	
	public:
		Point();
        Point(ivec2, ivec3);
		~Point();
		void draw();
};

#endif