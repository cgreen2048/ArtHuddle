#include "Factory.hpp"

// GuiElement* factory(guiElement e, ivec2 point1, ivec3 color, ivec2 point2 = ivec2(), ivec2 point3 = ivec2(), Screen* screen = nullptr, bool hasParentStart = false, bool hasParentEnd = false, std::vector<GuiElement*> elements = std::vector<GuiElement*>(), bool active = false, TagType coord1Type = TagType::Vec, TagType coord2Type = TagType::Vec, TagType coord3Type = TagType::Vec, TagType colorType = TagType::Vec) {
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
	}
	return nullptr;
}

