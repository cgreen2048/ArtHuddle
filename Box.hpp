#ifndef __BOX_HPP__
#define __BOX_HPP__

#include "GuiElement.hpp"

class Box : public GuiElement {
	private:
		ivec2 min;
		ivec2 max;
		ivec3 color;
    
    public:
		Box();
        Box(ivec2, ivec2, ivec3);
		Box(const Box&);
        Box& operator=(const Box&);
		bool operator==(Box);
        bool operator!=(Box);
		~Box();
		void draw();
};

#endif