#include "Box.hpp"
#include "XmlWriteHelpers.hpp"

Box::Box() : min({0, 0}), max({0, 0}), color({0, 0, 0}) {}

Box::Box(ivec2 min, ivec2 max, ivec3 color) {
    if ((min.x > max.x) || (min.y > max.y)) {
        ivec2 holder = min;
        min = max;
        max = holder;
    }
    this->min = min;
    this->max = max;
    this->color = color;
}

Box::Box(ElementParameters ep) {
    if (!validateAndNormalize(ep)) {
        throw -1;
    }
    this->min = ep.min;
    this->max = ep.max;
    this->color = ep.color;
    this->minType = ep.minType;
    this->maxType = ep.maxType;
    this->colorType = ep.colorType;
    this->name = ep.name;
}

Box::Box(const Box& cp) : Box() {
    this->min = cp.min;
    this->max = cp.max;
    this->color = cp.color;
    this->minType = cp.minType;
    this->maxType = cp.maxType;
    this->colorType = cp.colorType;
    this->name = cp.name;
}

Box& Box::operator=(const Box& cp) {
    this->min = cp.min;
    this->max = cp.max;
    this->color = cp.color;
    this->minType = cp.minType;
    this->maxType = cp.maxType;
    this->colorType = cp.colorType;
    this->name = cp.name;
    return *this;
}

bool Box::operator==(Box rhs) {
    if ((this->min != rhs.min) || (this->max != rhs.max) || (this->color != rhs.color) || (this->colorType != rhs.colorType)) {
        return false;
    }
    return true;
}

bool Box::operator!=(Box rhs) {
    return !(*this == rhs);
}

Box::~Box() {}

void Box::draw(Screen *screen) {
    screen->drawBox(this->min, this->max, this->color, this->getParentStart(), this->getParentEnd());
}

GuiElement* Box::clone() const {
    return new Box(*this);
}

void Box::setMin(const ivec2& v, TagType t){
    this->min = v;
    this->minType = t;
}

void Box::setMax(const ivec2& v, TagType t){
    this->max = v;
    this->maxType = t;
}

void Box::setColor(const ivec3& v, TagType t){
    this->color = v;
    this->colorType = t;
}

ivec2 Box::getMin() {
    return this->min;
}

ivec2 Box::getMax() {
    return this->max;
}

void Box::writeXml(std::ostream& out, int depth) const {
    std::string pad = std::string(depth * 2, ' ');

    out << pad << "<box " << "name=\"" << name << "\">\n";
    if (minType == TagType::IVec) {
        writeIVec2(out, min, pad);
    } else {
        writeVec2(out, toVec2(min), pad);
    }

    if (maxType == TagType::IVec) {
        writeIVec2(out, max, pad);
    }
    else {
        writeVec2(out, toVec2(max), pad);
    }

    if (colorType == TagType::IVec) {
        writeIVec3(out, color, pad);
    }
    else {
        writeVec3(out, toVec3(color), pad);
    }
    out << pad << "</box>\n";
}

bool Box::validateAndNormalize(ElementParameters& ep) {
    if ((ep.min.x == std::numeric_limits<int>::lowest()) || (ep.min.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.max.x == std::numeric_limits<int>::lowest()) || (ep.max.y == std::numeric_limits<int>::lowest())) {
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

bool Box::inBounds(const ivec2& point) const {
    if ((point.x < min.x) || (point.x > max.x) || (point.y < min.y) || (point.y > max.y)) {
        return false;
    }
    return true;
}

bool Box::isInside(ivec2 coordinates) {
    if ((this->getParentStart().x > coordinates.x) || (this->getParentStart().y > coordinates.y) || (this->getParentEnd().x <= coordinates.x) || (this->getParentEnd().y <= coordinates.y)) {
        return false;
    }
    return this->inBounds(coordinates);
}