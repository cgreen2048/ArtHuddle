#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include "GuiElement.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Box.hpp"
#include "Triangle.hpp"
#include "Layout.hpp"

extern GuiElement* factory(guiElement);

#endif
