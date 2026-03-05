#include "Box.hpp"

Box::Box() : min({0.0f, 0.0f}), max({0.0f, 0.0f}), color({0.0f, 0.0f, 0.0f}) {}

Box::Box(vec2 min, vec2 max, vec3 color) {
    this->min = min;
    this->max = max;
    this->color = color;
}

Box::~Box() {}

void Box::draw() {
    this->screen->drawBox(this->min, this->max, this->color);
}