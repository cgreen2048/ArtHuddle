#include "Ellipse.hpp"
#include "XmlWriteHelpers.hpp"

Ellipse::Ellipse() : center{0,0}, radiusX{0}, radiusY{0}, color{0,0,0} {
    this->setBounds();
}

Ellipse::Ellipse(ivec2 center, int radius, ivec3 color) : center{center}, radiusX{radius}, radiusY{radius}, color{color} {
    this->setBounds();
}

Ellipse::Ellipse(ivec2 center, int radiusX, int radiusY, ivec3 color) : center{center}, radiusX{radiusX}, radiusY{radiusY}, color{color} {
    this->setBounds();
}

Ellipse::Ellipse(const Ellipse& cp) : Ellipse() {
    this->center = cp.center;
    this->radiusX = cp.radiusX;
    this->radiusY = cp.radiusY;
    this->color = cp.color;
    this->setBounds();
}

Ellipse& Ellipse::operator=(const Ellipse& rhs) {
    this->center = rhs.center;
    this->radiusX = rhs.radiusX;
    this->radiusY = rhs.radiusY;
    this->color = rhs.color;
    this->setBounds();
    return *this;

}

Ellipse::Ellipse(ElementParameters ep) {
    if (!validateAndNormalize(ep)) {
        throw -1;
    }

    this->center = ep.center;
    this->radiusX = ep.radiusX;
    this->radiusY = ep.radiusY;
    this->color = ep.color;
    this->name = ep.name;
    this->setBounds();
}

Ellipse::~Ellipse() {}
    
void Ellipse::draw(Screen* screen) {
    screen->drawEllipse(center, radiusX, radiusY, color, parentStart, parentEnd);
}

GuiElement* Ellipse::clone() const {
    return new Ellipse(*this);
}

void Ellipse::writeXml(std::ostream& out, int depth) const {
    std::string pad = std::string(depth * 2, ' ');

    out << pad << "<ellipse "
        << "name=\"" << name << "\" "
        << "rx=\"" << radiusX << "\" "
        << "ry=\"" << radiusY << "\">\n";

    if (centerType == TagType::IVec) {
        writeIVec2(out, center, pad);
    } else {
        writeVec2(out, toVec2(center), pad);
    }

    if (colorType == TagType::IVec) {
        writeIVec3(out, color, pad);
    } else {
        writeVec3(out, toVec3(color), pad);
    }

    out << pad << "</ellipse>\n";
}

bool Ellipse::validateAndNormalize(ElementParameters& ep) {
    if ((ep.center.x == std::numeric_limits<int>::lowest()) || (ep.center.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if (ep.radiusX == std::numeric_limits<int>::lowest()) {
        return false;
    }
    if (ep.radiusY == std::numeric_limits<int>::lowest()) {
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
    if (ep.elementType != guiElement::ELLIPSE) {
        ep.elementType == guiElement::ELLIPSE;
    }
    return true;
}

ivec2 Ellipse::getCenter() {
    return this->center;
}

int Ellipse::getRadiusX() {
    return this->radiusX;
}

int Ellipse::getRadiusY() {
    return this->radiusY;
}

void Ellipse::setCenter(ivec2 point, TagType pointType) {
    this->center = point;
    this->centerType = pointType;
}

void Ellipse::setRadiusX(int radX) {
    this->radiusX = radX;
}

void Ellipse::setRadiusY(int radY) {
    this->radiusY = radY;
}

void Ellipse::setColor(ivec3 color, TagType colorType) {
    this->color = color;
    this->colorType = colorType;
}

bool Ellipse::isInside(ivec2 coordinates) {
    if ((this->getParentStart().x > coordinates.x) || (this->getParentStart().y > coordinates.y) || (this->getParentEnd().x <= coordinates.x) || (this->getParentEnd().y <= coordinates.y)) {
        return false;
    }
    float newXRadius = (float)radiusX + PADDING;
    float newYRadius = (float)radiusY + PADDING;
    float dx = (float)coordinates.x - center.x;
    float dy = (float)coordinates.y - center.y;
    return (((dx * dx) / (newXRadius * newXRadius) + (dy * dy) / (newYRadius * newYRadius)) <= 1.0f);
}

ElementParameters Ellipse::getParameters() {
    ElementParameters ep;
    ep.center = this->center;
    ep.radiusX = this->radiusX;
    ep.radiusY = this->radiusY;
    ep.color = this->color;
    ep.name = this->name;
    return ep;
}

guiElement Ellipse::getType() {
    return guiElement::ELLIPSE;
}

void Ellipse::modifyColor(ivec3 newColor) {
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

void Ellipse::setBounds() {
    this->minBound = ivec2(center.x - this->radiusX, center.y - this->radiusY);
    this->maxBound = ivec2(center.x + this->radiusX, center.y + this->radiusY);
}

std::vector<ivec2> Ellipse::getBounds() {
    return {this->minBound, this->maxBound};
}