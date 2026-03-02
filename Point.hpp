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
		// {
		// 	std::cout << "Point created\n";
		// }
		~Point();
		// {
		// 	std::cout << "Point destroyed\n";
		// }
		void draw();
		// {
		// 	std::cout << "point!\n";
		// }
};

#endif