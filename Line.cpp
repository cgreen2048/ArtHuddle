#include "Line.hpp"
#include "XmlWriteHelpers.hpp"

Line::Line() : start({0, 0}), end({0, 0}), color({0, 0, 0}) {}

Line::Line(ivec2 start, ivec2 end, ivec3 color) {
    this->start = start;
    this->end = end;
    this->color = color;
}

Line::Line(ElementParameters ep) {
    if (!isValid(ep)) {
        throw -1;
    }
    this->start = ep.point1;
    this->end = ep.point2;
    this->color = ep.color;
    this->startType = ep.point1Type;
    this->endType = ep.point2Type;
    this->colorType = ep.colorType;
    this->name = ep.name;
}

Line::Line(const Line& cp) : Line() {
    this->start = cp.start;
    this->end = cp.end;
    this->color = cp.color;
    this->startType = cp.startType;
    this->endType = cp.endType;
    this->colorType = cp.colorType;
    this->name = cp.name;
}

Line& Line::operator=(const Line& cp) {
    this->start = cp.start;
    this->end = cp.end;
    this->color = cp.color;
    this->startType = cp.startType;
    this->endType = cp.endType;
    this->colorType = cp.colorType;
    this->name = cp.name;
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

void Line::draw(Screen *screen) {
    screen->drawBresenhamLine(this->start, this->end, this->color, this->getParentStart(), this->getParentEnd());
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

void Line::writeXml(std::ostream& out, int depth) const {
    std::string pad = std::string(depth * 2, ' ');

    out << pad << "<line " << "name=\"" << name << "\">\n";
    if (startType == TagType::IVec) {
        writeIVec2(out, start, pad);
    } else {
        writeVec2(out, toVec2(start), pad);
    }

    if (endType == TagType::IVec) {
        writeIVec2(out, end, pad);
    }
    else {
        writeVec2(out, toVec2(end), pad);
    }

    if (colorType == TagType::IVec) {
        writeIVec3(out, color, pad);
    }
    else {
        writeVec3(out, toVec3(color), pad);
    }
    out << pad << "</line>\n";
}

bool Line::isValid(ElementParameters ep) {
    if ((ep.point1.x == std::numeric_limits<int>::lowest()) || (ep.point1.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.point2.x == std::numeric_limits<int>::lowest()) || (ep.point2.y == std::numeric_limits<int>::lowest())) {
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

bool Line::isInside(ivec2 coordinates) {
    if ((this->getParentStart().x > coordinates.x) || (this->getParentStart().y > coordinates.y) || (this->getParentEnd().x <= coordinates.x) || (this->getParentEnd().y <= coordinates.y)) {
        return false;
    }
    // add check to see if point is on the line
    return false;
}