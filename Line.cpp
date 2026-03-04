#include "Line.hpp"

Line::Line() : start({0, 0}), end({0, 0}), color({0, 0, 0}) {}

Line::Line(ivec2 start, ivec2 end, ivec3 color) {
    this->start = start;
    this->end = end;
    this->color = color;
}

Line::Line(const Line& cp) : Line() {
    this->start = cp.start;
    this->end = cp.end;
    this->color = cp.color;
}

Line& Line::operator=(const Line& cp) {
    this->start = cp.start;
    this->end = cp.end;
    this->color = cp.color;
    return *this;
}

bool Line::operator==(Line rhs) {
    if ((this->start != rhs.start) || (this->end != rhs.end) || (this->color != rhs.color)) {
        return false;
    }
    return true;
}

bool Line::operator!=(Line rhs) {
    return !(*this == rhs);
}

Line::~Line() {}

void Line::draw() {
    this->screen->drawBresenhamLine(this->start, this->end, this->color);
    // this->screen->drawBresenhamLine(ivec2(static_cast<int>(this->start.x), static_cast<int>(this->start.y)), 
    //                                 ivec2(static_cast<int>(this->end.x), static_cast<int>(this->end.y)),
    //                                 ivec3(static_cast<int>(this->color.x), static_cast<int>(this->color.y), static_cast<int>(this->color.z)));
}