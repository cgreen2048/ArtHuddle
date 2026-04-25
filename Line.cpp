#include "Line.hpp"
#include "XmlWriteHelpers.hpp"

Line::Line() : start({0, 0}), end({0, 0}), color({0, 0, 0}) {}

Line::Line(ivec2 start, ivec2 end, ivec3 color) {
    this->start = start;
    this->end = end;
    this->color = color;
    setPoints();
    this->setBounds();
}

Line::Line(ElementParameters ep) {
    if (!validateAndNormalize(ep)) {
        throw -1;
    }
    this->start = ep.start;
    this->end = ep.end;
    this->color = ep.color;
    this->startType = ep.startType;
    this->endType = ep.endType;
    this->colorType = ep.colorType;
    this->name = ep.name;
    setPoints();
    this->setBounds();
}

Line::Line(const Line& cp) : Line() {
    this->start = cp.start;
    this->end = cp.end;
    this->color = cp.color;
    this->startType = cp.startType;
    this->endType = cp.endType;
    this->colorType = cp.colorType;
    this->name = cp.name;
    this->points = cp.points;
    this->setBounds();
}

Line& Line::operator=(const Line& cp) {
    this->start = cp.start;
    this->end = cp.end;
    this->color = cp.color;
    this->startType = cp.startType;
    this->endType = cp.endType;
    this->colorType = cp.colorType;
    this->name = cp.name;
    this->points = cp.points;
    this->setBounds();
    return *this;
}

bool Line::operator==(Line rhs) {
    if ((this->start != rhs.start) || (this->end != rhs.end) || (this->color != rhs.color) || (this->colorType != rhs.colorType)) {
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

GuiElement* Line::clone() const {
    return new Line(*this);
}


void Line::setStart(const ivec2& v, TagType t){
    this->start = v;
    this->startType = t;
    this->setBounds();
    this->setPoints();
}

void Line::setEnd(const ivec2& v, TagType t){
    this->end = v;
    this->endType = t;
    this->setBounds();
    this->setPoints();
}

void Line::setColor(const ivec3& v, TagType t){
    this->color = v;
    this->colorType = t;
}

ivec2 Line::getStart() {
    return this->start;
}

ivec2 Line::getEnd() {
    return this->end;
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

bool Line::validateAndNormalize(ElementParameters& ep) {
    if ((ep.start.x == std::numeric_limits<int>::lowest()) || (ep.start.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.end.x == std::numeric_limits<int>::lowest()) || (ep.end.y == std::numeric_limits<int>::lowest())) {
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
    for (auto point : this->points) {
        int dx = coordinates.x - point.x;
        int dy = coordinates.y - point.y;
        if ((dx * dx + dy * dy) <= (PADDING * PADDING)) {  
            return true;
        }
    }
    return false;
}

ElementParameters Line::getParameters() {
    ElementParameters ep;
    ep.start = this->start;
    ep.end = this->end;
    ep.color = this->color;
    ep.startType = this->startType;
    ep.endType = this->endType;
    ep.colorType = this->colorType;
    ep.name = this->name;
    ep.points = this->points;
    return ep;
}

guiElement Line::getType() {
    return guiElement::LINE;
}

void Line::setPoints() {
    this->points.clear();
    int x0 = this->start.x;
    int y0 = this->start.y;
    int x1 = this->end.x;
    int y1 = this->end.y;
    int dx = std::abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -std::abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;
    while (true) {
        this->points.push_back(ivec2(x0, y0));
        if (x0 == x1 && y0 == y1) {
            break;
        }
        int e2 = 2 * error;
        if (e2 >= dy){
            error += dy;
            x0 += sx;
        }
        if (e2 <= dx){
            error += dx;
            y0 += sy;
        }
    }
}

void Line::modifyColor(ivec3 newColor) {
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

void Line::setBounds() {
    this->minBound.x = std::min(this->start.x, this->end.x);
    this->minBound.y = std::min(this->start.y, this->end.y);
    this->maxBound.x = std::max(this->start.x, this->end.x);
    this->maxBound.y = std::max(this->start.y, this->end.y);
}

std::vector<ivec2> Line::getBounds() {
    return {this->minBound, this->maxBound};
}