#include "MouseDownEvent.cpp"

MouseDownEvent::MouseDownEvent(ivec2 coords) : Event(EventType::MOUSE_DOWN), coords{coords} {}

ivec2 MouseDownEvent::getCoords() {
    return this->coords;
}
