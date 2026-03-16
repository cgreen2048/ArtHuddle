#include "Layout.hpp"

Layout::Layout() : active{false} {}

Layout::~Layout() {
    // maybe delete all elements in elements? Instead of making GuiFile handle it
}

void Layout::setStart(const vec2& start) {
    this->start = start;
}

void Layout::setEnd(const vec2& end) {
    this->end = end;
}

void Layout::setParentStart(const ivec2& start) {
    this->parentStart = start;
    this->hasParentStart = true;
}

void Layout::setParentEnd(const ivec2& end) {
    this->parentEnd = end;
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

void Layout::draw() {
    if (!this->active || !this->hasParentStart || !this->hasParentEnd) {
        return;
    }

    for (auto start = this->elements.begin(); start != this->elements.end(); ++start) {
        (*start)->draw();
    }
}

void writeXml(std::ostream& out) const {
    out << LAYOUT_OPEN << "\n";

    for (auto start = this->elements.begin(); start != this->elements.end(); ++start) {
        (*start)->writeXml(out);
    }

    out << LAYOUT_CLOSE << "\n";
}

const std::vector<GuiElement*>& getElements() const {
    return this->elements;
}

int Layout::getAbsoluteStartX() {
    return this->parentStart.x + static_cast<int>(this->startX * (this->parentEnd.x - this->parentStart.x));
}

int Layout::getAbsoluteStartY() {
    return this->parentStart.y + static_cast<int>(this->startY * (this->parentEnd.y - this->parentStart.y));
}

int Layout::getAbsoluteEndX() {
    return this->parentStart.x + static_cast<int>(this->endX * (this->parentEnd.x - this->parentStart.x));
}

int Layout::getAbsoluteEndY() {
    return this->parentStart.y + static_cast<int>(this->endY * (this->parentEnd.y - this->parentStart.y));
}