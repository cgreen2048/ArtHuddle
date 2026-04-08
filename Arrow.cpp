#include "Arrow.hpp"
#include "XmlWriteHelpers.hpp"

Arrow::Arrow() : stem(), point(), color({0, 0, 0}) {}

Arrow::Arrow(ivec2 min, ivec2 max, ivec2 a, ivec2 b, ivec2 c, ivec3 color) : stem(min, max, color), point(a, b, c, color), color(color) {
    
}

Arrow::Arrow(ElementParameters ep) {
    if (!isValid(ep)) {
        throw -1;
    }
    this->color = ep.color;
    this->stem = Box(ep.min, ep.max, ep.color);
    this->point = Triangle(ep.pointA, ep.pointB, ep.pointC, ep.color);
    this->name = ep.name;
}

Arrow::Arrow(const Arrow& cp) : stem(cp.stem), point(cp.point), color(cp.color) {
    this->name = cp.name;
}

Arrow& Arrow::operator=(const Arrow& cp) {
    this->color = cp.color;
    this->stem = cp.stem;
    this->point = cp.point;
    this->name = cp.name;
    return *this;
}

bool Arrow::operator==(Arrow rhs) {
    if ((this->stem != rhs.stem) || (this->point != rhs.point) || (this->color != rhs.color)) {
        return false;
    }
    return true;
}

bool Arrow::operator!=(Arrow rhs) {
    return !(*this == rhs);
}

Arrow::~Arrow() {}

void Arrow::draw(Screen *screen) {
    stem.setParentStart(this->getParentStart());
    stem.setParentEnd(this->getParentEnd());
    point.setParentStart(this->getParentStart());
    point.setParentEnd(this->getParentEnd());
    stem.draw(screen);
    point.draw(screen);
}

bool Arrow::isValid(ElementParameters ep) {
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