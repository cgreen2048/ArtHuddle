#include "Layout.hpp"

Layout::Layout() : active{false} {}

Layout::Layout(ElementParameters ep) {
    if (!isValid(ep)) {
        throw -1;
    }
    this->start = ep.layoutStart;
    this->end = ep.layoutEnd;
    if (ep.parentStart.x != std::numeric_limits<int>::max()) {
        this->hasParentStart = true;
        this->parentStart = ep.parentStart;
    }
    else {
        this->hasParentStart = false;
    }
    if (ep.parentEnd.x != std::numeric_limits<int>::lowest()) {
        this->hasParentEnd = true;
        this->parentEnd = ep.parentEnd;
    }
    else {
        this->hasParentEnd = false;
    }
    this->active = ep.active;
    for (int i = 0; i < ep.elements.size(); ++i) {
        this->addElement(ep.elements[i]);
    }
    this->name = ep.name;
}

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

void Layout::drawOverlay(Screen *screen){
     if (!this->active || !this->hasParentStart || !this->hasParentEnd) {
        return;
    }

    for (auto start = this->elements.begin(); start != this->elements.end(); ++start) {
        if (dynamic_cast<Button*>(*start) || dynamic_cast<TextBox*>(*start)) {
            (*start)->drawOverlay(screen);
        }
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

bool Layout::resolveEvent(Event* e) {
     if (e == nullptr) {
        return false;
    }
    
    if (e->getType() == EventType::SHOW) {
        ShowEvent* show = static_cast<ShowEvent*>(e);
        if (this->getName() == show->getLayoutName()) {
            if (show->getAction() == ShowActionType::SHOW) {
                active = true;
            }
            else {
                active = false;
            }
            return true;
        }
    }

    if (!active) {
        return false;
    }

    for (GuiElement* child : elements) {
        if (child->resolveEvent(e)) {
            return true;
        }
    }

    if (e->getType() == EventType::CLICK) {
        for (auto ritr = elements.rbegin(); ritr != elements.rend(); ++ritr) {
            GuiElement* object = *ritr;
            ClickEvent* click = dynamic_cast<ClickEvent*>(e);
            if (object->isInside(ivec2(click->getMouseX(), click->getMouseY()))) {
                Layout* downcast = dynamic_cast<Layout*>(object);
                if (downcast) {
                    if (downcast->resolveEvent(e)) {
                        return true;
                    }
                }
                else {
                    Selected::getInstance().setSelectedElement(object);
                    return true;
                }
            }
        }
    }
    
    Selected::getInstance().setSelectedElement(nullptr);

    return false;
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

bool Layout::isValid(ElementParameters ep) {
    if ((ep.layoutStart.x == std::numeric_limits<float>::lowest()) || (ep.layoutStart.y == std::numeric_limits<float>::lowest())) {
        return false;
    }
    if ((ep.layoutEnd.x == std::numeric_limits<float>::lowest()) || (ep.layoutEnd.y == std::numeric_limits<float>::lowest())) {
        return false;
    }
    return true;
}

bool Layout::isInside(ivec2 coordinates) {
    if ((this->getParentStart().x > coordinates.x) || (this->getParentStart().y > coordinates.y) || (this->getParentEnd().x <= coordinates.x) || (this->getParentEnd().y <= coordinates.y)) {
        return false;
    }
    if ((this->getAbsoluteStartX() > coordinates.x) || (this->getAbsoluteStartY() > coordinates.y) || (this->getAbsoluteEndX() <= coordinates.x) || (this->getAbsoluteEndY() <= coordinates.y)) {
        return false;
    }
    return true;
}

void Layout::clearElements() {
    this->elements.clear();
}