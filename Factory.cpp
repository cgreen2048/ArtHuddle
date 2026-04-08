#include "Factory.hpp"
#include <iostream>

GuiElement* factory(guiElement e, ElementParameters ep) {
	try {
		switch (e) {
			case guiElement::LAYOUT: {
				return new Layout(ep);
			}
			case guiElement::POINT: {
				return new Point(ep);
			}
			case guiElement::LINE: {
				return new Line(ep);

			}
			case guiElement::BOX: {
				return new Box(ep);
			}
			case guiElement::TRIANGLE: {
				return new Triangle(ep);
			}
			case guiElement::BUTTON: {
				return new Button(ep);
			}
			case guiElement::ELLIPSE: {
				return new Ellipse(ep);
			}
			default: {
				return nullptr;
			}
		}
	}
	catch (...) {
		std::cerr << "Invalid parameters for element type " << static_cast<int>(e) << "\n";
	}
	
	return nullptr;
}

