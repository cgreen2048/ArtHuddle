#ifndef __ELEMENT_PARAMETERS_HPP__
#define __ELEMENT_PARAMETERS_HPP__

#include <limits>
#include "vec2.hpp"
#include "vec3.hpp"
#include "GuiElement.hpp"

// enum class TagType { Vec, IVec };
class GuiElement;
enum class TagType { Vec, IVec };

struct ElementParameters {
    std::string name;
    ivec2 point1;
    ivec2 point2;
    ivec2 point3;
    ivec3 color;
    Screen* screen;
    ivec2 parentStart = ivec2(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
    ivec2 parentEnd = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    bool hasParentStart;
    bool hasParentEnd;
    std::vector<GuiElement*> elements;
    bool active;
    TagType point1Type;
    TagType point2Type;
    TagType point3Type;
    TagType colorType;
    vec2 layoutStart;
    vec2 layoutEnd;
};

#endif