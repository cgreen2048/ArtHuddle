#include "Point.hpp"
#include "XmlWriteHelpers.hpp"

Point::Point() : coords({0, 0}), color({0, 0, 0}) {}

Point::Point(ivec2 coords, ivec3 color) {
    this->coords = coords; 
    this->color = color;
}

Point::Point(ElementParameters ep) {
    if (!isValid(ep)) {
        throw -1;
    }
    this->coords = ep.coords;
    this->color = ep.color;
    this->coordsType = ep.coordsType;
    this->colorType = ep.colorType;
    this->name = ep.name;
}

Point::Point(const Point& cp) : Point() {
    this->coords = cp.coords;
    this->color = cp.color;
    this->coordsType = cp.coordsType;
    this->colorType = cp.colorType;
    this->name = cp.name;
}

Point& Point::operator=(const Point& cp) {
    this->coords = cp.coords;
    this->color = cp.color;
    this->coordsType = cp.coordsType;
    this->colorType = cp.colorType;
    this->name = cp.name;
    return *this;
}

bool Point::operator==(Point rhs) {
    if ((this->coords != rhs.coords) || (this->color != rhs.color)) {
        return false;
    }
    return true;
}

bool Point::operator!=(Point rhs) {
    return !(*this == rhs);
}

Point::~Point() {}

void Point::draw(Screen *screen) {
    screen->colorOnePixel(this->coords, this->color, this->getParentStart(), this->getParentEnd());
}

void Point::setCoords(const ivec2& v, TagType t){
    this->coords = v;
    this->coordsType = t;
}

void Point::setColor(const ivec3& v, TagType t){
    this->color = v;
    this->colorType = t;
}

ivec2 Point::getCoords() {
    return this->coords;
}

void Point::writeXml(std::ostream& out, int depth) const {
    std::string pad = std::string(depth * 2, ' ');

    out << pad << "<point " << "name=\"" << name << "\">\n";
    if (coordsType == TagType::IVec) {
        writeIVec2(out, coords, pad);
    } else {
        writeVec2(out, toVec2(coords), pad);
    }

    if (colorType == TagType::IVec) {
        writeIVec3(out, color, pad);
    }
    else {
        writeVec3(out, toVec3(color), pad);
    }
    out << pad << "</point>\n";
}

bool Point::isValid(ElementParameters ep) {
    if ((ep.coords.x == std::numeric_limits<int>::lowest()) || (ep.coords.y == std::numeric_limits<int>::lowest())) {
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

bool Point::isInside(ivec2 coordinates) {
    if ((this->getParentStart().x > coordinates.x) || (this->getParentStart().y > coordinates.y) || (this->getParentEnd().x <= coordinates.x) || (this->getParentEnd().y <= coordinates.y)) {
        return false;
    }
    if (this->coords == coordinates) {
        return true;
    }
    return false;
}