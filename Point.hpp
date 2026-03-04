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
		Point(const Point&);
		Point& operator=(const Point&);
		bool operator==(Point);
		bool operator!=(Point);
		~Point();
		void draw();
};

#endif