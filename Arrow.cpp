#include "Arrow.hpp"
#include "XmlWriteHelpers.hpp"

Arrow::Arrow() : min({0, 0}), max({0, 0}), pointA({0, 0}), pointB({0, 0}), pointC({0, 0}), color({0, 0, 0}) {}

Arrow::Arrow(ivec2 min, ivec2 max, ivec2 a, ivec2 b, ivec2 c, ivec3 color) {
    this->min = min;
    this->max = max;
    this->pointA = a;
    this->pointB = b;
    this->pointC = c;
    this->color = color;
}

Arrow::Arrow(ElementParameters ep) {
    if (!isValid(ep)) {
        throw -1;
    }
    this->min = ep.min;
    this->max = ep.max;
    this->pointA = ep.pointA;
    this->pointB = ep.pointB;
    this->pointC = ep.pointC;
    this->color = ep.color;
    this->minType = ep.minType;
    this->maxType = ep.maxType;
    this->pointAType = ep.pointAType;
    this->pointBType = ep.pointBType;
    this->pointCType = ep.pointCType;
    this->colorType = ep.colorType;
    this->name = ep.name;
}

Arrow::Arrow(const Arrow& cp) {
    this->min = cp.min;
    this->max = cp.max;
    this->pointA = cp.pointA;
    this->pointB = cp.pointB;
    this->pointC = cp.pointC;
    this->color = cp.color;
    this->minType = cp.minType;
    this->maxType = cp.maxType;
    this->pointAType = cp.pointAType;
    this->pointBType = cp.pointBType;
    this->pointCType = cp.pointCType;
    this->colorType = cp.colorType;
    this->name = cp.name;
}

Arrow& Arrow::operator=(const Arrow& cp) {
    this->min = cp.min;
    this->max = cp.max;
    this->pointA = cp.pointA;
    this->pointB = cp.pointB;
    this->pointC = cp.pointC;
    this->color = cp.color;
    this->minType = cp.minType;
    this->maxType = cp.maxType;
    this->pointAType = cp.pointAType;
    this->pointBType = cp.pointBType;
    this->pointCType = cp.pointCType;
    this->colorType = cp.colorType;
    this->name = cp.name;
    return *this;
}

bool Arrow::operator==(Arrow rhs) {
    if ((this->min != rhs.min) || (this->max != rhs.max) || (this->pointA != rhs.pointA) || (this->pointB != rhs.pointB) || (this->pointC != rhs.pointC) || (this->color != rhs.color)) {
        return false;
    }
    return true;
}

bool Arrow::operator!=(Arrow rhs) {
    return !(*this == rhs);
}

Arrow::~Arrow() {}

void Arrow::draw(Screen *screen) {
    screen->drawArrow(min, max, pointA, pointB, pointC, color, parentStart, parentEnd);
}

void Arrow::writeXml(std::ostream& out, int depth) const {
    std::string pad = std::string(depth * 2, ' ');

    out << pad << "<arrow " << "name=\"" << name << "\">\n";

    if (minType == TagType::IVec) {
        writeIVec2(out, min, pad);
    }
    else {
        writeVec2(out, toVec2(min), pad);
    }
    if (maxType == TagType::IVec) {
        writeIVec2(out, max, pad);
    }
    else {
        writeVec2(out, toVec2(max), pad);
    }
    if (pointAType == TagType::IVec) {
        writeIVec2(out, pointA, pad);
    }
    else {
        writeVec2(out, toVec2(pointA), pad);
    }
    if (pointBType == TagType::IVec) {
        writeIVec2(out, pointB, pad);
    }
    else {
        writeVec2(out, toVec2(pointB), pad);
    }
    if (pointCType == TagType::IVec) {
        writeIVec2(out, pointC, pad);
    }
    else {
        writeVec2(out, toVec2(pointC), pad);
    }
    if (colorType == TagType::IVec) {
        writeIVec3(out, color, pad);
    }
    else {
        writeVec3(out, toVec3(color), pad);
    }
    out << pad << "</arrow>\n";
}

bool Arrow::isValid(ElementParameters ep) {
    if ((ep.min.x == std::numeric_limits<int>::lowest()) || (ep.min.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.max.x == std::numeric_limits<int>::lowest()) || (ep.max.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.pointA.x == std::numeric_limits<int>::lowest()) || (ep.pointA.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.pointB.x == std::numeric_limits<int>::lowest()) || (ep.pointB.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.pointC.x == std::numeric_limits<int>::lowest()) || (ep.pointC.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if (ep.color.x == std::numeric_limits<int>::lowest()) {
        ep.color.x = 125;
    }
    if (ep.color.y == std::numeric_limits<int>::lowest()) {
        ep.color.y = 125;
    }
    if (ep.color.z == std::numeric_limits<int>::lowest()) {
        ep.color.z = 125;
    }

    return true;
}