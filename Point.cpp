#include "Point.hpp"
#include "XmlWriteHelpers.hpp"

Point::Point() : coords({0, 0}), color({0, 0, 0}) {}

Point::Point(ivec2 coords, ivec3 color) {
    this->coords = coords; 
    this->color = color;
    this->setBounds();
}

Point::Point(ElementParameters ep) {
    if (!validateAndNormalize(ep)) {
        throw -1;
    }
    this->coords = ep.coords;
    this->color = ep.color;
    this->coordsType = ep.coordsType;
    this->colorType = ep.colorType;
    this->name = ep.name;
    this->setBounds();
}

Point::Point(const Point& cp) : Point() {
    this->coords = cp.coords;
    this->color = cp.color;
    this->coordsType = cp.coordsType;
    this->colorType = cp.colorType;
    this->name = cp.name;
    this->setBounds();
}

Point& Point::operator=(const Point& cp) {
    this->coords = cp.coords;
    this->color = cp.color;
    this->coordsType = cp.coordsType;
    this->colorType = cp.colorType;
    this->name = cp.name;
    this->setBounds();
    return *this;
}

bool Point::operator==(Point rhs) {
    if ((this->coords != rhs.coords) || (this->color != rhs.color) || (this->colorType != rhs.colorType)) {
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

GuiElement* Point::clone() const {
    return new Point(*this);
}

void Point::setCoords(const ivec2& v, TagType t){
    this->coords = v;
    this->coordsType = t;
    this->setBounds();
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

bool Point::validateAndNormalize(ElementParameters& ep) {
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
    if (ep.elementType != guiElement::POINT) {
        ep.elementType = guiElement::POINT;
    }
    return true;
}

bool Point::isInside(ivec2 coordinates) {
    if ((this->getParentStart().x > coordinates.x) || (this->getParentStart().y > coordinates.y) || (this->getParentEnd().x <= coordinates.x) || (this->getParentEnd().y <= coordinates.y)) {
        return false;
    }
    int dx = coordinates.x - coords.x;
    int dy = coordinates.y - coords.y;
    if ((dx * dx + dy * dy) <= (PADDING * PADDING)) {  
        return true;
    }
    return false;
}

ElementParameters Point::getParameters() {
    ElementParameters ep;
    ep.elementType = guiElement::POINT;
    ep.coords = this->coords;
    ep.color = this->color;
    ep.coordsType = this->coordsType;
    ep.colorType = this->colorType;
    ep.name = this->name;
    return ep;
}

guiElement Point::getType() {
    return guiElement::POINT;
}

void Point::modifyColor(ivec3 newColor) {
    this->color += newColor;
    if (color.x < 0) {
        color.x = 0;
    }
    else if (color.x > 255) {
        color.x = 255;
    }
    if (color.y < 0) {
        color.y = 0;
    }
    else if (color.y > 255) {
        color.y = 255;
    }
    if (color.z < 0) {
        color.z = 0;
    }
    else if (color.z > 255) {
        color.z = 255;
    }
}

void Point::setBounds() {
    this->minBound = this->coords;
    this->maxBound = this->coords;
}

std::vector<ivec2> Point::getBounds() {
    return {this->minBound, this->maxBound};
}