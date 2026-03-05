#ifndef __GUI_ELEMENT_HPP__
#define __GUI_ELEMENT_HPP__

#include <iostream>
#include "Screen.hpp"

enum class guiElement {POINT, LINE, BOX};

class GuiElement {
	protected:
		Screen* screen;
	public:
		GuiElement();
		
		virtual ~GuiElement();
		
		virtual void draw();

		virtual void writeXml(std::ostream& out) const;
		
		void setScreen(Screen*);

		Screen* getScreen();
};


#endif
