#include "Point.hpp"

Point::Point() : coords({0, 0}), color({0, 0, 0}) {}

Point::Point(ivec2 coords, ivec3 color) {
    this->coords = coords;
    this->color = color;
}

Point::~Point() {}

void Point::draw() {
    this->screen->colorOnePixel(this->coords, this->color);
}