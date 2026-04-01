#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include "GuiElement.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Box.hpp"
#include "Triangle.hpp"
#include "Layout.hpp"
#include "ElementParameters.hpp"

// enum class TagType { Vec, IVec };
extern GuiElement* factory(guiElement e, ElementParameters ep);
// extern GuiElement* factory(guiElement e, ivec2 point1, ivec3 color, ivec2 point2, ivec2 point3, Screen* screen, bool hasParentStart, bool hasParentEnd, std::vector<GuiElement*> elements, bool active, TagType coord1Type, TagType coord2Type, TagType coord3Type, TagType colorType);

#endif
