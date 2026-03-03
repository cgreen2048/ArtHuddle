#include "Line.hpp"

Line::Line() : start({0.0f, 0.0f}), end({0.0f, 0.0f}), color({0.0f, 0.0f, 0.0f}) {}

Line::Line(vec2 start, vec2 end, vec3 color) {
    this->start = start;
    this->end = end;
    this->color = color;
}

Line::~Line() {}

void Line::draw() {
    this->screen->drawBresenhamLine(ivec2(static_cast<int>(this->start.x), static_cast<int>(this->start.y)), 
                                    ivec2(static_cast<int>(this->end.x), static_cast<int>(this->end.y)),
                                    ivec3(static_cast<int>(this->color.x), static_cast<int>(this->color.y), static_cast<int>(this->color.z)));
}