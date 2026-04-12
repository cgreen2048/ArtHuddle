#ifndef __ELEMENT_PARAMETERS_HPP__
#define __ELEMENT_PARAMETERS_HPP__

#include <limits>
#include <vector>
#include "vec2.hpp"
#include "vec3.hpp"
#include "GuiElement.hpp"
#include <functional>
#include <string>

class GuiElement;
enum class TagType { Vec, IVec };

struct ElementParameters {
    std::string name;
    ivec2 coords = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 start = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 end = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 min = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 max = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 pointA = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 pointB = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 pointC = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec3 color = ivec3(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec3 textColor = ivec3(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    Screen* screen = nullptr;
    ivec2 parentStart = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 parentEnd = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    bool hasParentStart = false;
    bool hasParentEnd = false;
    std::vector<GuiElement*> elements;
    bool active = false;
    TagType coordsType = TagType::Vec;
    TagType startType = TagType::Vec;
    TagType endType = TagType::Vec;
    TagType minType = TagType::Vec;
    TagType maxType = TagType::Vec;
    TagType pointAType = TagType::Vec;
    TagType pointBType = TagType::Vec;
    TagType pointCType = TagType::Vec;
    TagType colorType = TagType::Vec;
    TagType textColorType = TagType::Vec;
    vec2 layoutStart = vec2(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());
    vec2 layoutEnd = vec2(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());
    std::function<void()> callback = []() {};
    std::string callbackName = "";
    std::string text = "";
    ivec2 center = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    int radiusX = std::numeric_limits<int>::lowest();
    int radiusY = std::numeric_limits<int>::lowest();
    TagType centerType = TagType::Vec;
};

#endif