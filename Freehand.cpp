#include "Freehand.hpp"

Freehand::Freehand() : elements{}, lastDrawnPoint{0,0}, color{0,0,0} {}

Freehand::Freehand(ivec3 color) : elements{}, lastDrawnPoint{0,0}, color{color} {}

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

GuiElement* Freehand::clone() const {
    return new Freehand(*this);
}

bool Freehand::resolveEvent(Event *e) {
    if (finished) {
        if (e->getType() == EventType::CLICK) {
            ClickEvent* click = static_cast<ClickEvent*>(e);
            // run selection logic
            return true;
        }
        return false;
    }
    else {
        if (e->getType() == EventType::MOUSE_DOWN) {
            MouseDownEvent* md = static_cast<MouseDownEvent*>(e);

            if (!hasFirstPoint) {
                lastDrawnPoint = md->getCoords();
                hasFirstPoint = true;
                drawPoint(lastDrawnPoint);
                return true;
            }

            return false;
        }

         if (e->getType() == EventType::MOUSE_MOTION) {
            MouseMotionEvent* mm = static_cast<MouseMotionEvent*>(e);

            if (!hasFirstPoint || !mm->isMouseDown()) {
                return false;
            }

            ivec2 current = mm->getCoords();

            if (current == lastDrawnPoint) {
                return true;
            }

            elements.push_back(new Line(lastDrawnPoint, current, color));
            lastDrawnPoint = current;
            drawPoint(lastDrawnPoint);
            return true;
        }

        if (e->getType() == EventType::MOUSE_UP) {
            MouseUpEvent* mu = static_cast<MouseUpEvent*>(e);

            ivec2 current = mu->getCoords();
            elements.push_back(new Line(lastDrawnPoint, current, color));
            lastDrawnPoint = current;
            this->finished = true;
            return true;
        } 
    }

    return false;
}

void Freehand::writeXml(std::ostream& out, int depth) const {

}

bool Freehand::isValid(ElementParameters ep) {
    return true;
}