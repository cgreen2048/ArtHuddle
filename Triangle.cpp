#include "Triangle.hpp"

Triangle::Triangle() : a(ivec2{0, 0}), b(ivec2{0,0}), c(ivec2{0,0}), color(ivec3{0,0,0}) {}

Triangle::Triangle(ivec2 a, ivec2 b, ivec2 c, ivec3 color) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->color = color;
}

Triangle::~Triangle() {}

void Triangle::draw() {
    if (this->screen != nullptr) {
        this->screen->drawTriangle(this->a, this->b, this->c, this->color);
    }
}