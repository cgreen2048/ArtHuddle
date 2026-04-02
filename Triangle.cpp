#include "Triangle.hpp"
#include "XmlWriteHelpers.hpp"

Triangle::Triangle() : a(ivec2{0, 0}), b(ivec2{0,0}), c(ivec2{0,0}), color(ivec3{0,0,0}) {}

Triangle::Triangle(ivec2 a, ivec2 b, ivec2 c, ivec3 color) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->color = color;
}

Triangle::Triangle(ElementParameters ep) {
    if (!isValid(ep)) {
        throw -1;
    }
    this->a = ep.point1;
    this->b = ep.point2;
    this->c = ep.point3;
    this->color = ep.color;
    this->aType = ep.point1Type;
    this->bType = ep.point2Type;
    this->cType = ep.point2Type;
    this->colorType = ep.colorType;
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
    return *this;
}

bool Triangle::operator==(Triangle rhs) {
    if ((this->a != rhs.a) || (this->b != rhs.b) || (this->c != rhs.c) || (this->color != rhs.color)) {
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

void Triangle::setA(const ivec2& v, TagType t){
    this->a = v;
    this->aType = t;
}

void Triangle::setB(const ivec2& v, TagType t){
    this->b = v;
    this->bType = t;
}

void Triangle::setC(const ivec2& v, TagType t){
    this->c = v;
    this->cType = t;
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

bool Triangle::isValid(ElementParameters ep) {
    if ((ep.point1.x == std::numeric_limits<int>::lowest()) || (ep.point1.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.point2.x == std::numeric_limits<int>::lowest()) || (ep.point2.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.point3.x == std::numeric_limits<int>::lowest()) || (ep.point3.y == std::numeric_limits<int>::lowest())) {
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