#include "Point.hpp"

Point::Point() : coords({0.0f, 0.0f}), color({0.0f, 0.0f, 0.0f}) {
    std::cout << "Point created\n";
}

Point::Point(vec2 coords, vec3 color) {
    std::cout << "Point created\n";
    this->coords = coords;
    this->color = color;
    std::cout << this->coords[0] << '\n';
}
Point::~Point() {
    std::cout << "Point destroyed\n";
}
void Point::draw() {
    std::cout << "point!\n";
    this->screen->colorOnePixel(this->coords, this->color);
}