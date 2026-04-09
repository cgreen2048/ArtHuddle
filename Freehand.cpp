#include "Freehand.hpp"

Freehand::Freehand() : elements{}, lastDrawnPoint{0,0} {}

Freehand::Freehand(const Freehand& cp) : Freehand() {
    this->hasFirstPoint = cp.hasFirstPoint;
    this->lastDrawnPoint = cp.lastDrawnPoint;
    this->finished = cp.finished;

    for (GuiElement *e : cp.elements) {
        this->elements.push_back(e->clone());
    }
}

void Freehand::draw(Screen *screen) {
    for (GuiElement *e : this->elements) {
        e->draw(screen);
    }
}

bool Freehand::resolveEvent(Event *e) {
    if (e->getType() == EventType::CLICK) {
        ClickEvent* click = static_cast<ClickEvent*>(e);
    }

    if (e->getType() == EventType::MOUSE_DOWN) {
        
    }
}