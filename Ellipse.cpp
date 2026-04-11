#include "Ellipse.hpp"
#include "XmlWriteHelpers.hpp"

Ellipse::Ellipse() : center{0,0}, radiusX{0}, radiusY{0}, color{0,0,0} {}

Ellipse::Ellipse(ivec2 center, int radius, ivec3 color) : center{center}, radiusX{radius}, radiusY{radius}, color{color} {}

Ellipse::Ellipse(ivec2 center, int radiusX, int radiusY, ivec3 color) : center{center}, radiusX{radiusX}, radiusY{radiusY}, color{color} {}

Ellipse::Ellipse(const Ellipse& cp) : Ellipse() {
    this->center = cp.center;
    this->radiusX = cp.radiusX;
    this->radiusY = cp.radiusY;
    this->color = cp.color;
}

Ellipse& Ellipse::operator=(const Ellipse& rhs) {
    this->center = rhs.center;
    this->radiusX = rhs.radiusX;
    this->radiusY = rhs.radiusY;
    this->color = rhs.color;
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

bool Ellipse::resolveEvent(Event* e) {
    if (e->getType() == EventType::CLICK) {
        ClickEvent* click = dynamic_cast<ClickEvent*>(e);
        if (isInside(ivec2(click->getMouseX(), click->getMouseY()))) {
            // Handle selecting the element
            // Try selecting child components of element first for greater specificity
        }
    }
    return false;
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

bool Ellipse::isInside(ivec2 coordinates) {
    if ((this->getParentStart().x > coordinates.x) || (this->getParentStart().y > coordinates.y) || (this->getParentEnd().x <= coordinates.x) || (this->getParentEnd().y <= coordinates.y)) {
        return false;
    }
    return (
        (coordinates.x > center.x - radiusX) 
        && (coordinates.x < center.x + radiusX)
        && (coordinates.y > center.y - radiusY)
        && (coordinates.y < center.y + radiusY)
    );
}