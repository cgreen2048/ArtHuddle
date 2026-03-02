#include "Box.hpp"

Box::Box() : min({0.0f, 0.0f}), max({0.0f, 0.0f}), color({0.0f, 0.0f, 0.0f}) {
    std::cout << "Box created\n";
}
Box::Box(vec2 min, vec2 max, vec3 color) {
    this->min = min;
    this->max = max;
    this->color = color;
    std::cout << "Box constructor\n";
}
Box::~Box() {
    std::cout << "Box destroyed\n";
}
void Box::draw() {
    std::cout << "box!\n";
    this->screen->drawBox(this->min, this->max, this->color);
}