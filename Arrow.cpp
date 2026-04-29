#include "Arrow.hpp"
#include "XmlWriteHelpers.hpp"

Arrow::Arrow() : min({0, 0}), max({0, 0}), pointA({0, 0}), pointB({0, 0}), pointC({0, 0}), color({0, 0, 0}) {}

Arrow::Arrow(ivec2 min, ivec2 max, ivec2 a, ivec2 b, ivec2 c, ivec3 color) {
    this->min = min;
    this->max = max;
    this->pointA = a;
    this->pointB = b;
    this->pointC = c;
    this->color = color;
    this->setBounds();
}

Arrow::Arrow(ElementParameters ep) {
    if (!validateAndNormalize(ep)) {
        throw -1;
    }
    this->min = ep.min;
    this->max = ep.max;
    this->pointA = ep.pointA;
    this->pointB = ep.pointB;
    this->pointC = ep.pointC;
    this->color = ep.color;
    this->minType = ep.minType;
    this->maxType = ep.maxType;
    this->pointAType = ep.pointAType;
    this->pointBType = ep.pointBType;
    this->pointCType = ep.pointCType;
    this->colorType = ep.colorType;
    this->name = ep.name;
    this->setBounds();
}

Arrow::Arrow(const Arrow& cp) {
    this->min = cp.min;
    this->max = cp.max;
    this->pointA = cp.pointA;
    this->pointB = cp.pointB;
    this->pointC = cp.pointC;
    this->color = cp.color;
    this->minType = cp.minType;
    this->maxType = cp.maxType;
    this->pointAType = cp.pointAType;
    this->pointBType = cp.pointBType;
    this->pointCType = cp.pointCType;
    this->colorType = cp.colorType;
    this->name = cp.name;
    this->setBounds();
}

Arrow& Arrow::operator=(const Arrow& cp) {
    this->min = cp.min;
    this->max = cp.max;
    this->pointA = cp.pointA;
    this->pointB = cp.pointB;
    this->pointC = cp.pointC;
    this->color = cp.color;
    this->minType = cp.minType;
    this->maxType = cp.maxType;
    this->pointAType = cp.pointAType;
    this->pointBType = cp.pointBType;
    this->pointCType = cp.pointCType;
    this->colorType = cp.colorType;
    this->name = cp.name;
    this->setBounds();
    return *this;
}

bool Arrow::operator==(Arrow rhs) {
    if ((this->min != rhs.min) || (this->max != rhs.max) || (this->pointA != rhs.pointA) || (this->pointB != rhs.pointB) || (this->pointC != rhs.pointC) || (this->color != rhs.color) || (this->colorType != rhs.colorType)) {
        return false;
    }
    return true;
}

bool Arrow::operator!=(Arrow rhs) {
    return !(*this == rhs);
}

Arrow::~Arrow() {}

void Arrow::draw(Screen *screen) {
    screen->drawArrow(min, max, pointA, pointB, pointC, color, parentStart, parentEnd);
}

GuiElement* Arrow::clone() const {
    return new Arrow(*this);
}

void Arrow::writeXml(std::ostream& out, int depth) const {
    std::string pad = std::string(depth * 2, ' ');

    out << pad << "<arrow " << "name=\"" << name << "\">\n";

    if (minType == TagType::IVec) {
        writeIVec2(out, min, pad);
    }
    else {
        writeVec2(out, toVec2(min), pad);
    }
    if (maxType == TagType::IVec) {
        writeIVec2(out, max, pad);
    }
    else {
        writeVec2(out, toVec2(max), pad);
    }
    if (pointAType == TagType::IVec) {
        writeIVec2(out, pointA, pad);
    }
    else {
        writeVec2(out, toVec2(pointA), pad);
    }
    if (pointBType == TagType::IVec) {
        writeIVec2(out, pointB, pad);
    }
    else {
        writeVec2(out, toVec2(pointB), pad);
    }
    if (pointCType == TagType::IVec) {
        writeIVec2(out, pointC, pad);
    }
    else {
        writeVec2(out, toVec2(pointC), pad);
    }
    if (colorType == TagType::IVec) {
        writeIVec3(out, color, pad);
    }
    else {
        writeVec3(out, toVec3(color), pad);
    }
    out << pad << "</arrow>\n";
}

bool Arrow::validateAndNormalize(ElementParameters& ep) {
    if ((ep.min.x == std::numeric_limits<int>::lowest()) || (ep.min.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.max.x == std::numeric_limits<int>::lowest()) || (ep.max.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.pointA.x == std::numeric_limits<int>::lowest()) || (ep.pointA.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.pointB.x == std::numeric_limits<int>::lowest()) || (ep.pointB.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.pointC.x == std::numeric_limits<int>::lowest()) || (ep.pointC.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    ivec2 newMin;
    ivec2 newMax;
    newMin.x = std::min(ep.min.x, ep.max.x);
    newMin.y = std::min(ep.min.y, ep.max.y);
    newMax.x = std::max(ep.min.x, ep.max.x);
    newMax.y = std::max(ep.min.y, ep.max.y);
    ep.min = newMin;
    ep.max = newMax;
    if (ep.color.x == std::numeric_limits<int>::lowest()) {
        ep.color.x = 125;
    }
    if (ep.color.y == std::numeric_limits<int>::lowest()) {
        ep.color.y = 125;
    }
    if (ep.color.z == std::numeric_limits<int>::lowest()) {
        ep.color.z = 125;
    }
    if (ep.elementType != guiElement::ARROW) {
        ep.elementType = guiElement::ARROW;
    }

    return true;
}

bool Arrow::isInside(ivec2 coordinates) {
    if ((this->getParentStart().x > coordinates.x) || (this->getParentStart().y > coordinates.y) || (this->getParentEnd().x <= coordinates.x) || (this->getParentEnd().y <= coordinates.y)) {
        return false;
    }

    bool insideBox = true;
    bool insideTriangle = true;
    if ((coordinates.x < min.x - PADDING) || (coordinates.x > max.x + PADDING) || (coordinates.y < min.y - PADDING) || (coordinates.y > max.y + PADDING)) {
        insideBox = false;
    }

    vec2 center = vec2((float)(this->pointA.x + this->pointB.x + this->pointC.x) / 3, (float)(this->pointA.y + this->pointB.y + this->pointC.y) / 3.0f);

    vec2 dirA = vec2(this->pointA.x, this->pointA.y) - center;
    vec2 dirB = vec2(this->pointB.x, this->pointB.y) - center;
    vec2 dirC = vec2(this->pointC.x, this->pointC.y) - center;

    vec2 newA = vec2(this->pointA.x, this->pointA.y) + dirA.unit() * (float)PADDING;
    vec2 newB = vec2(this->pointB.x, this->pointB.y) + dirB.unit() * (float)PADDING;
    vec2 newC = vec2(this->pointC.x, this->pointC.y) + dirC.unit() * (float)PADDING;
    
    vec2 ap = vec2(coordinates.x, coordinates.y) - newA;
    vec2 ab = newB - newA;
    vec2 bp = vec2(coordinates.x, coordinates.y) - newB;
    vec2 bc = newC - newB;
    vec2 cp = vec2(coordinates.x, coordinates.y) - newC;
    vec2 ca = newA - newC;

    float crossApAb = ap.cross(ab);
    float crossBpBc = bp.cross(bc);
    float crossCpCa = cp.cross(ca);

    bool hasPositive = crossApAb > 0.0f || crossBpBc > 0.0f || crossCpCa > 0.0f;
    bool hasNegative = crossApAb < 0.0f || crossBpBc < 0.0f || crossCpCa < 0.0f;

    insideTriangle = !(hasPositive && hasNegative);

    return insideBox || insideTriangle;
}

ivec2 Arrow::getMin() {
    return this->min;
}

ivec2 Arrow::getMax() {
    return this->max;
}

ivec2 Arrow::getA() {
    return this->pointA;
}

ivec2 Arrow::getB() {
    return this->pointB;
}

ivec2 Arrow::getC() {
    return this->pointC;
}

void Arrow::setMin(ivec2 point, TagType pointType) {
    this->min = point;
    this->minType = pointType;
}

void Arrow::setMax(ivec2 point, TagType pointType) {
    this->max = point;
    this->maxType = pointType;
}

void Arrow::setA(ivec2 point, TagType pointType) {
    this->pointA = point;
    this->pointAType = pointType;
}

void Arrow::setB(ivec2 point, TagType pointType) {
    this->pointB = point;
    this->pointBType = pointType;
}

void Arrow::setC(ivec2 point, TagType pointType) {
    this->pointC = point;
    this->pointCType = pointType;
}

void Arrow::setColor(ivec3 color, TagType colorType) {
    this->color = color;
    this->colorType = colorType;
}

ElementParameters Arrow::getParameters() {
    ElementParameters ep;
    ep.elementType = guiElement::ARROW;
    ep.min = this->min;
    ep.max = this->max;
    ep.pointA = this->pointA;
    ep.pointB = this->pointB;
    ep.pointC = this->pointC;
    ep.color = this->color;
    ep.minType = this->minType;
    ep.maxType = this->maxType;
    ep.pointAType = this->pointAType;
    ep.pointBType = this->pointBType;
    ep.pointCType = this->pointCType;
    ep.colorType = this->colorType;
    ep.name = this->name;
    return ep;
}

guiElement Arrow::getType() {
    return guiElement::ARROW;
}

void Arrow::modifyColor(ivec3 newColor) {
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

void Arrow::setBounds() {
    this->minBound.x = std::min(this->min.x, std::min(this->max.x, std::min(this->pointA.x, std::min(this->pointB.x, this->pointC.x))));
    this->minBound.y = std::min(this->min.y, std::min(this->max.y, std::min(this->pointA.y, std::min(this->pointB.y, this->pointC.y))));
    this->maxBound.x = std::max(this->min.x, std::max(this->max.x, std::max(this->pointA.x, std::max(this->pointB.x, this->pointC.x))));
    this->maxBound.y = std::max(this->min.y, std::max(this->max.y, std::max(this->pointA.y, std::max(this->pointB.y, this->pointC.y))));
}

std::vector<ivec2> Arrow::getBounds() {
    return {this->minBound, this->maxBound};
}