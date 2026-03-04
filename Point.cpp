#include "Point.hpp"

Point::Point() : coords({0.0f, 0.0f}), color({0.0f, 0.0f, 0.0f}) {
    
}

Point::Point(vec2 coords, vec3 color) {
    
    this->coords = coords;
    this->color = color;
}
Point::~Point() {
    
}
void Point::draw() {
    
    this->screen->colorOnePixel(this->coords, this->color);
}