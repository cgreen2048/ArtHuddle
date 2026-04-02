#ifndef __ELEMENT_PARAMETERS_HPP__
#define __ELEMENT_PARAMETERS_HPP__

#include <limits>
#include "vec2.hpp"
#include "vec3.hpp"
#include "GuiElement.hpp"

class GuiElement;
enum class TagType { Vec, IVec };

struct ElementParameters {
    std::string name;
    ivec2 point1 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 point2 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 point3 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec3 color = ivec3(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    Screen* screen = nullptr;
    ivec2 parentStart = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 parentEnd = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    bool hasParentStart = false;
    bool hasParentEnd = false;
    std::vector<GuiElement*> elements;
    bool active = false;
    TagType point1Type = TagType::Vec;
    TagType point2Type = TagType::Vec;
    TagType point3Type = TagType::Vec;
    TagType colorType = TagType::Vec;
    vec2 layoutStart = vec2(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());
    vec2 layoutEnd = vec2(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());
};

#endif