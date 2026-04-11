#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include "GuiElement.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Box.hpp"
#include "Triangle.hpp"
#include "Layout.hpp"
#include "Button.hpp"
#include "Ellipse.hpp"
#include "Arrow.hpp"
#include "Freehand.hpp"
#include "ElementParameters.hpp"

extern GuiElement* factory(guiElement e, ElementParameters ep);


#endif
