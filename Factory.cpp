#include "Factory.hpp"
#include "helperFunctions.hpp"
#include <iostream>

GuiElement* factory(guiElement e, ElementParameters ep) {
	if (ep.name.empty()) {
		ep.name = generateElementName();
	}
	
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
			case guiElement::ARROW: {
				return new Arrow(ep);
			}
			case guiElement::FREEHAND: {
				return new Freehand(ep);
			}
			case guiElement::TEXTBOX: {
				return new TextBox(ep);
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

