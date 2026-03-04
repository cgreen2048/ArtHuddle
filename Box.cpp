#include "Box.hpp"

Box::Box() : min({0, 0}), max({0, 0}), color({0, 0, 0}) {}

Box::Box(ivec2 min, ivec2 max, ivec3 color) {
    this->min = min;
    this->max = max;
    this->color = color;
}

Box::Box(const Box& cp) : Box() {
    this->min = cp.min;
    this->max = cp.max;
    this->color = cp.color;
}

Box& Box::operator=(const Box& cp) {
    this->min = cp.min;
    this->max = cp.max;
    this->color = cp.color;
    return *this;
}

bool Box::operator==(Box rhs) {
    if ((this->min != rhs.min) || (this->max != rhs.max) || (this->color != rhs.color)) {
        return false;
    }
    return true;
}

bool Box::operator!=(Box rhs) {
    return !(*this == rhs);
}

Box::~Box() {}

void Box::draw() {
    this->screen->drawBox(this->min, this->max, this->color);
}