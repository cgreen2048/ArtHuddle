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
		Line(const Line&);
        Line& operator=(const Line&);
		bool operator==(Line);
        bool operator!=(Line);
		~Line();
		void draw();
};

#endif