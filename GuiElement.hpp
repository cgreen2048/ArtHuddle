#ifndef __GUI_ELEMENT_HPP__
#define __GUI_ELEMENT_HPP__

#include <iostream>
#include "Screen.hpp"

enum class guiElement {POINT, LINE, BOX, TRIANGLE};

class GuiElement {
	protected:
		Screen* screen;
		ivec2 parentStart;
		ivec2 parentEnd;
	public:
		GuiElement();
		
		virtual ~GuiElement();
		
		virtual void draw();

		virtual void writeXml(std::ostream& out) const;
		
		void setScreen(Screen*);

		void setParentStart(const ivec2& start);

        void setParentEnd(const ivec2& end);

		ivec2 getParentStart();

        ivec2 getParentEnd();

		Screen* getScreen();
};


#endif
