#include "Line.hpp"
#include "XmlWriteHelpers.hpp"

Line::Line() : start({0, 0}), end({0, 0}), color({0, 0, 0}) {}

Line::Line(ivec2 start, ivec2 end, ivec3 color) {
    this->start = start;
    this->end = end;
    this->color = color;
}

Line::Line(const Line& cp) : Line() {
    this->start = cp.start;
    this->end = cp.end;
    this->color = cp.color;
}

Line& Line::operator=(const Line& cp) {
    this->start = cp.start;
    this->end = cp.end;
    this->color = cp.color;
    return *this;
}

bool Line::operator==(Line rhs) {
    if ((this->start != rhs.start) || (this->end != rhs.end) || (this->color != rhs.color)) {
        return false;
    }
    return true;
}

bool Line::operator!=(Line rhs) {
    return !(*this == rhs);
}

Line::~Line() {}

void Line::draw() {
    this->screen->drawBresenhamLine(this->start, this->end, this->color);
}

void Line::setStart(const ivec2& v, TagType t){
    this->start = v;
    this->startType = t;
}

void Line::setEnd(const ivec2& v, TagType t){
    this->end = v;
    this->endType = t;
}

void Line::setColor(const ivec3& v, TagType t){
    this->color = v;
    this->colorType = t;
}

void Line::writeXml(std::ostream& out) const {
    out << "  <line>\n";

    if (startType == TagType::IVec) {
        writeIVec2(out, start);
    } else {
        writeVec2(out, toVec2(start));
    }

    if (endType == TagType::IVec) {
        writeIVec2(out, end);
    }
    else {
        writeVec2(out, toVec2(end));
    }

    if (colorType == TagType::IVec) {
        writeIVec3(out, color);
    }
    else {
        writeVec3(out, toVec3(color));
    }

    out << "  </line>\n";
}