#include "ArtHuddle/elements/Triangle.hpp"
#include "ArtHuddle/core/XmlWriteHelpers.hpp"

Triangle::Triangle() : a(ivec2{0, 0}), b(ivec2{0,0}), c(ivec2{0,0}), color(ivec3{0,0,0}) {}

Triangle::Triangle(ivec2 a, ivec2 b, ivec2 c, ivec3 color) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->color = color;
    this->setBounds();
}

Triangle::Triangle(ElementParameters ep) {
    if (!validateAndNormalize(ep)) {
        throw -1;
    }
    this->a = ep.pointA;
    this->b = ep.pointB;
    this->c = ep.pointC;
    this->color = ep.color;
    this->aType = ep.pointAType;
    this->bType = ep.pointBType;
    this->cType = ep.pointCType;
    this->colorType = ep.colorType;
    this->setBounds();
    this->name = ep.name;
}

Triangle::~Triangle() {}

Triangle::Triangle(const Triangle& cp) : Triangle() {
    this->a = cp.a;
    this->b = cp.b;
    this->c = cp.c;
    this->color = cp.color;
    this->aType = cp.aType;
    this->bType = cp.bType;
    this->cType = cp.cType;
    this->colorType = cp.colorType;
    this->setBounds();
    this->name = cp.name;
}

Triangle& Triangle::operator=(const Triangle& cp) {
    this->a = cp.a;
    this->b = cp.b;
    this->c = cp.c;
    this->color = cp.color;
    this->aType = cp.aType;
    this->bType = cp.bType;
    this->cType = cp.cType;
    this->colorType = cp.colorType;
    this->name = cp.name;
    this->setBounds();
    return *this;
}

bool Triangle::operator==(Triangle rhs) {
    if ((this->a != rhs.a) || (this->b != rhs.b) || (this->c != rhs.c) || (this->color != rhs.color) || (this->colorType != rhs.colorType)) {
        return false;
    }
    return true;
}

bool Triangle::operator!=(Triangle rhs) {
    return !(*this == rhs);
}

void Triangle::draw(Screen *screen) {
    screen->drawTriangle(this->a, this->b, this->c, this->color, this->getParentStart(), this->getParentEnd());
}

GuiElement* Triangle::clone() const {
    return new Triangle(*this);
}

void Triangle::setA(const ivec2& v, TagType t){
    this->a = v;
    this->aType = t;
    this->setBounds();
}

void Triangle::setB(const ivec2& v, TagType t){
    this->b = v;
    this->bType = t;
    this->setBounds();
}

void Triangle::setC(const ivec2& v, TagType t){
    this->c = v;
    this->cType = t;
    this->setBounds();
}

void Triangle::setColor(const ivec3& v, TagType t){
    this->color = v;
    this->colorType = t;
}

void Triangle::writeXml(std::ostream& out, int depth) const {
    std::string pad = std::string(depth * 2, ' ');

    out << pad << "<triangle " << "name=\"" << name << "\">\n";
    if (aType == TagType::IVec) {
        writeIVec2(out, a, pad);
    } else {
        writeVec2(out, toVec2(a), pad);
    }

    if (bType == TagType::IVec) {
        writeIVec2(out, b, pad);
    }
    else {
        writeVec2(out, toVec2(b), pad);
    }

    if (cType == TagType::IVec) {
        writeIVec2(out, c, pad);
    }
    else {
        writeVec2(out, toVec2(c), pad);
    }

    if (colorType == TagType::IVec) {
        writeIVec3(out, color, pad);
    }
    else {
        writeVec3(out, toVec3(color), pad);
    }
    out << pad <<"</triangle>\n";
}

ivec2 Triangle::getA() {
    return this->a;
}

ivec2 Triangle::getB() {
    return this->b;
}

ivec2 Triangle::getC() {
    return this->c;
}

bool Triangle::validateAndNormalize(ElementParameters& ep) {
    if ((ep.pointA.x == std::numeric_limits<int>::lowest()) || (ep.pointA.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.pointB.x == std::numeric_limits<int>::lowest()) || (ep.pointB.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.pointC.x == std::numeric_limits<int>::lowest()) || (ep.pointC.y == std::numeric_limits<int>::lowest())) {
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
    if (ep.elementType != guiElement::TRIANGLE) {
        ep.elementType = guiElement::TRIANGLE;
    }
    return true;
}

bool Triangle::isInside(ivec2 coordinates) {
    if ((this->getParentStart().x > coordinates.x) || (this->getParentStart().y > coordinates.y) || (this->getParentEnd().x <= coordinates.x) || (this->getParentEnd().y <= coordinates.y)) {
        return false;
    }
    vec2 center = vec2((float)(this->a.x + this->b.x + this->c.x) / 3, (float)(this->a.y + this->b.y + this->c.y) / 3.0f);

    vec2 dirA = vec2(this->a.x, this->a.y) - center;
    vec2 dirB = vec2(this->b.x, this->b.y) - center;
    vec2 dirC = vec2(this->c.x, this->c.y) - center;

    vec2 newA = vec2(this->a.x, this->a.y) + dirA.unit() * (float)PADDING;
    vec2 newB = vec2(this->b.x, this->b.y) + dirB.unit() * (float)PADDING;
    vec2 newC = vec2(this->c.x, this->c.y) + dirC.unit() * (float)PADDING;
    
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

    return !(hasPositive && hasNegative);
}

ElementParameters Triangle::getParameters() {
    ElementParameters ep;
    ep.elementType = guiElement::TRIANGLE;
    ep.pointA = this->a;
    ep.pointB = this->b;
    ep.pointC = this->c;
    ep.color = this->color;
    ep.pointAType = this->aType;
    ep.pointBType = this->bType;
    ep.pointCType = this->cType;
    ep.colorType = this->colorType;
    ep.name = this->name;
    return ep;
}

guiElement Triangle::getType() {
    return guiElement::TRIANGLE;
}

void Triangle::modifyColor(ivec3 newColor) {
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

void Triangle::setBounds() {
    this->minBound.x = std::min(this->a.x, std::min(this->b.x, this->c.x));
    this->minBound.y = std::min(this->a.y, std::min(this->b.y, this->c.y));
    this->maxBound.x = std::max(this->a.x, std::max(this->b.x, this->c.x));
    this->maxBound.y = std::max(this->a.y, std::max(this->b.y, this->c.y));
}

std::vector<ivec2> Triangle::getBounds() {
    return {this->minBound, this->maxBound};
}