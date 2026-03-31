#include "Layout.hpp"
#include <iostream>

Layout::Layout() : active{false} {}

Layout::~Layout() {
    for (GuiElement *el : this->elements) {
        delete el;
    }
    this->elements.clear();
}


void Layout::setStart(const vec2& start) {
    this->start = start;
}

void Layout::setEnd(const vec2& end) {
    this->end = end;
}

void Layout::setParentStart(const ivec2& start) {
    GuiElement::setParentStart(start);
    this->hasParentStart = true;
}

void Layout::setParentEnd(const ivec2& end) {
    GuiElement::setParentEnd(end);
    this->hasParentEnd = true;
}

void Layout::setActive(bool value) {
    this->active = value;
}

bool Layout::isActive() {
    return this->active;
}

void Layout::addElement(GuiElement *element) {
    this->elements.push_back(element);
    element->setParentStart(ivec2{this->getAbsoluteStartX(), this->getAbsoluteStartY()});
    element->setParentEnd(ivec2{this->getAbsoluteEndX(), this->getAbsoluteEndY()});
}

void Layout::draw(Screen *screen) {
    if (!this->active || !this->hasParentStart || !this->hasParentEnd) {
        return;
    }

    for (auto start = this->elements.begin(); start != this->elements.end(); ++start) {
        (*start)->draw(screen);
    }
}

static std::string indent(int depth) {
    return std::string(depth * 2, ' ');  // 2 spaces per level
}

void Layout::writeXml(std::ostream& out, int depth) const {
    std::string pad = indent(depth);

    out << pad << "<layout "
        << "name=\"" << name << "\" "
        << "sX=\"" << start.x << "\" "
        << "sY=\"" << start.y << "\" "
        << "eX=\"" << end.x << "\" "
        << "eY=\"" << end.y << "\">\n";

    for (GuiElement* e : elements) {
        e->writeXml(out, depth + 1);  // increase depth
    }

    out << pad << "</layout>\n";
}

vec2 Layout::getStart() const {
    return start;
}

vec2 Layout::getEnd() const {
    return end;
}


const std::vector<GuiElement*>& Layout::getElements() const {
    return elements;
}


int Layout::getAbsoluteStartX() {
    return this->parentStart.x + static_cast<int>(this->start.x * (this->parentEnd.x - this->parentStart.x));
}

int Layout::getAbsoluteStartY() {
    return this->parentStart.y + static_cast<int>(this->start.y * (this->parentEnd.y - this->parentStart.y));
}

int Layout::getAbsoluteEndX() {
    return this->parentStart.x + static_cast<int>(this->end.x * (this->parentEnd.x - this->parentStart.x));
}

int Layout::getAbsoluteEndY() {
    return this->parentStart.y + static_cast<int>(this->end.y * (this->parentEnd.y - this->parentStart.y));
}