#include "Line.hpp"

Line::Line() : start({0.0f, 0.0f}), end({0.0f, 0.0f}), color({0.0f, 0.0f, 0.0f}) {
    std::cout << "Line created\n";
}
Line::Line(vec2 start, vec2 end, vec3 color) {
    this->start = start;
    this->end = end;
    this->color = color;
    std::cout << "Line constructor\n";
}
Line::~Line() {
    std::cout << "Line destroyed\n";
}
void Line::draw() {
    std::cout << "line!\n";
    // this->screen->drawBresenhamLine(this->start, this->end, this->color);
}