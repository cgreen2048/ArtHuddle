#ifndef __GUI_ELEMENT_HPP__
#define __GUI_ELEMENT_HPP__

#include <iostream>
#include "Screen.hpp"

enum class guiElement {UNKNOWN, LAYOUT, POINT, LINE, BOX, TRIANGLE};

class GuiElement {
	protected:
		ivec2 parentStart;
		ivec2 parentEnd;
	public:
		GuiElement();
		
		virtual ~GuiElement();

		virtual void create();
		
		virtual void draw(Screen*);

		virtual void writeXml(std::ostream& out, int depth) const;

		virtual void setParentStart(const ivec2& start);

        virtual void setParentEnd(const ivec2& end);

		ivec2 getParentStart();

        ivec2 getParentEnd();
};


#endif
