#include "Box.hpp"
#include "XmlWriteHelpers.hpp"

Box::Box() : min({0, 0}), max({0, 0}), color({0, 0, 0}) {}

Box::Box(ivec2 min, ivec2 max, ivec3 color) {
    this->min = min;
    this->max = max;
    this->color = color;
}

Box::Box(const Box& cp) : Box() {
    this->min = cp.min;
    this->max = cp.max;
    this->color = cp.color;
}

Box& Box::operator=(const Box& cp) {
    this->min = cp.min;
    this->max = cp.max;
    this->color = cp.color;
    return *this;
}

bool Box::operator==(Box rhs) {
    if ((this->min != rhs.min) || (this->max != rhs.max) || (this->color != rhs.color)) {
        return false;
    }
    return true;
}

bool Box::operator!=(Box rhs) {
    return !(*this == rhs);
}

Box::~Box() {}

void Box::draw() {
    this->screen->drawBox(this->min, this->max, this->color);
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

void Box::writeXml(std::ofstream& out) const {
    out << "  <box>\n";

    if (minType == TagType::IVec) {
        writeIVec2(out, min);
    } else {
        writeVec2(out, toVec2(min));
    }

    if (maxType == TagType::IVec) {
        writeIVec2(out, max);
    }
    else {
        writeVec2(out, toVec2(max));
    }

    if (colorType == TagType::IVec) {
        writeIVec3(out, color);
    }
    else {
        writeVec3(out, toVec3(color));
    }

    out <<box "  </box>\n";
}