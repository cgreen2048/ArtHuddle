#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include "ArtHuddle/elements/GuiElement.hpp"
#include "ArtHuddle/elements/Point.hpp"
#include "ArtHuddle/elements/Line.hpp"
#include "ArtHuddle/elements/Box.hpp"
#include "ArtHuddle/elements/Triangle.hpp"
#include "ArtHuddle/elements/Layout.hpp"
#include "ArtHuddle/elements/Button.hpp"
#include "ArtHuddle/elements/TextBox.hpp"
#include "ArtHuddle/elements/InputTextBox.hpp"
#include "ArtHuddle/elements/Ellipse.hpp"
#include "ArtHuddle/elements/Arrow.hpp"
#include "ArtHuddle/elements/Freehand.hpp"
#include "ArtHuddle/core/ElementParameters.hpp"

extern GuiElement* factory(guiElement e, ElementParameters ep);


#endif
