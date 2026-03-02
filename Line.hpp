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
		// {
		// 	std::cout << "Line constructor\n";
		// }
		~Line();
		// {
		// 	std::cout << "Line destroyed\n";
		// }
		void draw();
		// {
		// 	std::cout << "line!\n";
		// }
};

#endif