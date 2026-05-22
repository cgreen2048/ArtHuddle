#include "ArtHuddle/events/ClickEvent.hpp"

ClickEvent::ClickEvent(int x, int y) : Event(EventType::CLICK), mouseX{x}, mouseY{y} {}

int ClickEvent::getMouseX() {
    return this->mouseX;
}

int ClickEvent::getMouseY() {
    return this->mouseY;
}