#ifndef __LINE_HPP__
#define __LINE_HPP__

#include "GuiElement.hpp"

class Line : public GuiElement {
	private:
		ivec2 start;
		ivec2 end;
		ivec3 color;

    public:
		Line();
        Line(ivec2, ivec2, ivec3);
		~Line();
		void draw();
};

#endif