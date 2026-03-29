#include "Event.hpp"

Event::Event() {}

Event::Event(EventType t) : type{t} {}

Event::Event(const Event& cp) : type{cp.type} {}

Event& Event::operator=(const Event& rhs) {
    this->type = rhs.type;
    return *this;
}

Event::~Event() {}

EventType Event::getType() const {
    return this->type;
}