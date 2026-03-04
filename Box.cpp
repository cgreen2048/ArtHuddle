#include "Box.hpp"

Box::Box() : min({0, 0}), max({0, 0}), color({0, 0, 0}) {}

Box::Box(ivec2 min, ivec2 max, ivec3 color) {
    this->min = min;
    this->max = max;
    this->color = color;
}

Box::~Box() {}

void Box::draw() {
    this->screen->drawBox(this->min, this->max, this->color);
}