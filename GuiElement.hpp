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
		// {
		// 	std::cout << "GuiElement constructor\n";
		// }
		virtual ~GuiElement();
		// {
		// 	std::cout << "GuiElement destroyed\n";
		// }
		virtual void draw();
		// {
		// 	std::cout << "Draw\n";
		// }
		void setScreen(Screen*);
};








#endif
