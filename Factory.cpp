#include "Factory.hpp"

GuiElement* factory(guiElement e, ElementParameters ep) {
	switch (e) {
		case guiElement::LAYOUT: {
			try {
				return new Layout(ep);
			}
			catch (...) {
				return nullptr;
			}
		}
		case guiElement::POINT: {
			try {
				return new Point(ep);
			}
			catch (...) {
				return nullptr;
			}
		}
		case guiElement::LINE: {
			try {
				return new Line(ep);
			}
			catch (...) {
				return nullptr;
			}
		}
		case guiElement::BOX: {
			try {
				return new Box(ep);
			}
			catch (...) {
				return nullptr;
			}
		}
		case guiElement::TRIANGLE: {
			try {
				return new Triangle(ep);
			}
			catch (...) {
				return nullptr;
			}
		}
		default: {
			return nullptr;
		}
		case guiElement::BUTTON: {
			try {
				return new Button(ep);
			}
			catch (...) {
				return nullptr;
			}
		}
	}
	return nullptr;
}

