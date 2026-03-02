#ifndef __BOX_HPP__
#define __BOX_HPP__

#include "GuiElement.hpp"

class Box : public GuiElement {
	private:
		vec2 min;
        vec2 max;
		vec3 color;
    
    public:
		Box();
        
        Box(vec2, vec2, vec3);
		// {
		// 	std::cout << "Box constructor\n";
		// }
		~Box();
		// {
		// 	std::cout << "Box destroyed\n";
		// }
		void draw();
		// {
		// 	std::cout << "box!\n";
		// }
};

#endif