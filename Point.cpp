#include "Point.hpp"

Point::Point() : coords({0, 0}), color({0, 0, 0}) {}

Point::Point(ivec2 coords, ivec3 color) {
    this->coords = coords;
    this->color = color;
}

Point::Point(const Point& cp) : Point() {
    this->coords = cp.coords;
    this->color = cp.color;
}

Point& Point::operator=(const Point& cp) {
    this->coords = cp.coords;
    this->color = cp.color;
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

void Point::draw() {
    this->screen->colorOnePixel(this->coords, this->color);
}