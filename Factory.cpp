#include "Factory.hpp"

// GuiElement* factory(guiElement e, ivec2 point1, ivec3 color, ivec2 point2 = ivec2(), ivec2 point3 = ivec2(), Screen* screen = nullptr, bool hasParentStart = false, bool hasParentEnd = false, std::vector<GuiElement*> elements = std::vector<GuiElement*>(), bool active = false, TagType coord1Type = TagType::Vec, TagType coord2Type = TagType::Vec, TagType coord3Type = TagType::Vec, TagType colorType = TagType::Vec) {
GuiElement* factory(guiElement e, ElementParameters ep) {
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
		default: {
			return nullptr;
		}
	}
	return nullptr;
}

