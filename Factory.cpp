#include "Factory.hpp"

GuiElement* factory(guiElement e) {
	switch (e) {
		case guiElement::LAYOUT: {
			return new Layout{};
		}
		case guiElement::POINT: {
			return new Point{};
		}
		case guiElement::LINE: {
			return new Line{};
		}
		case guiElement::BOX: {
			return new Box{};
		}
		case guiElement::TRIANGLE: {
			return new Triangle{};
		}
	}
	return nullptr;
}

