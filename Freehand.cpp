#include "Freehand.hpp"
#include <iostream>

Freehand::Freehand() : points{}, lastDrawnPoint{0,0}, color{0,0,0} {}

Freehand::Freehand(ivec3 color, bool isFreehandShape) : points{}, lastDrawnPoint{0,0}, color{color}, isFreehandShape{isFreehandShape} {}

Freehand::Freehand(const Freehand& cp) : Freehand() {
    this->hasFirstPoint = cp.hasFirstPoint;
    this->lastDrawnPoint = cp.lastDrawnPoint;
    this->finished = cp.finished;
    this->points = cp.points;
    this->color = cp.color;
    this->isFreehandShape = cp.isFreehandShape;
    this->name = cp.name;
}

Freehand::Freehand(ElementParameters ep) {
    if (!validateAndNormalize(ep)) {
        throw -1;
    }
    this->points = ep.points;
    this->hasFirstPoint = ep.hasFirstPoint;
    this->lastDrawnPoint = ep.lastDrawnPoint;
    this->finished = ep.finished;
    this->color = ep.color;
    this->isFreehandShape = ep.isFreehandShape;
    this->name = ep.name;
}

void Freehand::draw(Screen *screen) {
    if (points.empty()) {
        return;
    }

    if (points.size() == 1) {
        screen->colorOnePixel(points[0], color, this->parentStart, this->parentEnd);
        return;
    }

    for (size_t i = 1; i < points.size(); ++i) {
        screen->drawBresenhamLine(points[i - 1], points[i], color, this->parentStart, this->parentEnd);
    }

    if (this->isFreehandShape && this->finished) {
        ivec2 center(0, 0);
        for (const ivec2& p : points) {
            center.x += p.x;
            center.y += p.y;
        }
        center.x /= points.size();
        center.y /= points.size();
        this->floodFill(center, screen);
    }
}

void Freehand::floodFill(ivec2 start, Screen* screen) {
    std::stack<ivec2> st;
    st.push(start);

    while (!st.empty()) {
        ivec2 p = st.top();
        st.pop();

        int x = p.x;
        int y = p.y;

        if (x < 0 || x >= screen->getWidth() || y < 0 || y >= screen->getHeight()) {
            continue;
        }

        ivec3 current = screen->getPixelColor(p);

        if (current == this->color) {
            continue;
        }

        screen->colorOnePixel(p, this->color, this->parentStart, this->parentEnd);

        st.push(ivec2(x + 1, y));
        st.push(ivec2(x - 1, y));
        st.push(ivec2(x, y + 1));
        st.push(ivec2(x, y - 1));
    }
}

GuiElement* Freehand::clone() const {
    return new Freehand(*this);
}

bool Freehand::resolveEvent(Event *e) {
    if (this->finished) {
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

            if (dx * dx + dy * dy < PIXEL_DRAW_DIST_THRESHOLD * PIXEL_DRAW_DIST_THRESHOLD) {  
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
            this->finished = true;

            if (isFreehandShape) {
                int dx = current.x - points[0].x;
                int dy = current.y - points[0].y;

                if (dx * dx + dy * dy > SHAPE_COMPLETION_DIST_THRESHOLD * SHAPE_COMPLETION_DIST_THRESHOLD) {  
                    this->points.clear();
                    lastDrawnPoint = current;
                    return false;
                }

                this->points.push_back(points[0]);
                lastDrawnPoint = points[0];
            }
            
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

bool Freehand::validateAndNormalize(ElementParameters& ep) {
    if (ep.points.empty()) {
        return false;
    }

    // Make sure the last drawn point is the last point in points
    ep.lastDrawnPoint = ep.points.back();

    // Prevent created Freehand elements from being in incomplete state
    if (!ep.finished) {
        ep.finished = true;
    }

    if (!ep.hasFirstPoint) {
        ep.hasFirstPoint = true;
    }

    if (ep.color.x == std::numeric_limits<int>::lowest()) {
        ep.color.x = 125;
    }
    if (ep.color.y == std::numeric_limits<int>::lowest()) {
        ep.color.y = 125;
    }
    if (ep.color.z == std::numeric_limits<int>::lowest()) {
        ep.color.z = 125;
    }

    return true;
}

bool Freehand::isInside(ivec2 coordinates) {
    for (const ivec2& point : this->points) {
        int dx = coordinates.x - point.x;
        int dy = coordinates.y - point.y;
        if (dx * dx + dy * dy <= PIXEL_DRAW_DIST_THRESHOLD * PIXEL_DRAW_DIST_THRESHOLD) {
            return true;
        }
    }
    return false;
}

bool Freehand::isFinished() const {
    return finished;
}

bool Freehand::isFreehandShapeMode() const {
    return isFreehandShape;
}