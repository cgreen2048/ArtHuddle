#include "Point.hpp"
#include "XmlWriteHelpers.hpp"

Point::Point() : coords({0, 0}), color({0, 0, 0}) {}

Point::Point(ivec2 coords, ivec3 color) {
    this->coords = coords; 
    this->color = color;
}

Point::Point(const Point& cp) : Point() {
    this->coords = cp.coords;
    this->color = cp.color;
    this->coordsType = cp.coordsType;
    this->colorType = cp.colorType;
}

Point& Point::operator=(const Point& cp) {
    this->coords = cp.coords;
    this->color = cp.color;
    this->coordsType = cp.coordsType;
    this->colorType = cp.colorType;
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
