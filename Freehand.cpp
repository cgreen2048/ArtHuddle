#include "Freehand.hpp"
#include <iostream>

Freehand::Freehand() : points{}, lastDrawnPoint{0,0}, color{0,0,0} {}

Freehand::Freehand(ivec3 color) : points{}, lastDrawnPoint{0,0}, color{color} {}

Freehand::Freehand(const Freehand& cp) : Freehand() {
    this->hasFirstPoint = cp.hasFirstPoint;
    this->lastDrawnPoint = cp.lastDrawnPoint;
    this->finished = cp.finished;
    this->points = cp.points;
}

void Freehand::draw(Screen *screen) {
    if (points.empty()) {
        return;
    }

    if (points.size() == 1) {
        screen->colorOnePixel(points[0], color, parentStart, parentEnd);
        return;
    }

    for (size_t i = 1; i < points.size(); ++i) {
        screen->drawBresenhamLine(points[i - 1], points[i], color, parentStart, parentEnd);
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
                this->points.push_back(ivec2{lastDrawnPoint});
                return true;
            }

            return false;
        }

         if (e->getType() == EventType::MOUSE_MOTION) {
            
            MouseMotionEvent* mm = static_cast<MouseMotionEvent*>(e);

            if (!hasFirstPoint || !mm->isMouseDown()) {
                return true;
            }

            ivec2 current = mm->getCoords();

            if (current == lastDrawnPoint) {
                return true;
            }

            int dx = current.x - lastDrawnPoint.x;
            int dy = current.y - lastDrawnPoint.y;

            if (dx * dx + dy * dy < PIXEL_DISTANCE_THRESHOLD * PIXEL_DISTANCE_THRESHOLD) {  
                return true;
            }

            this->points.push_back(ivec2{lastDrawnPoint});
            lastDrawnPoint = current;
            return true;
        }

        if (e->getType() == EventType::MOUSE_UP) {
            MouseUpEvent* mu = static_cast<MouseUpEvent*>(e);

            ivec2 current = mu->getCoords();
            this->points.push_back(ivec2{lastDrawnPoint});
            lastDrawnPoint = current;
            this->finished = true;
            return true;
        } 
    }

    return false;
}

void Freehand::writeXml(std::ostream& out, int depth) const {
    std::string pad = std::string(depth * 2, ' ');

    out << pad << "<freehand>\n";

    for (ivec2 point : this->points) {
        writeIVec2(out, point, pad);
    }

    out << pad << "</freehand>\n";
}

bool Freehand::isValid(ElementParameters ep) {
    return true;
}