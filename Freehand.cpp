#include "Freehand.hpp"
#include "ClickEvent.hpp"
#include "MouseDownEvent.hpp"
#include "MouseUpEvent.hpp"
#include "MouseMotionEvent.hpp"
#include "XmlWriteHelpers.hpp"
#include "helperFunctions.hpp"
#include "Selected.hpp"
#include <iostream>
#include <limits>
#include <stack>

Freehand::Freehand() : points{}, lastDrawnPoint{0,0}, color{0,0,0} {
    setName(generateElementName());
    this->setBounds();
}

Freehand::Freehand(ivec3 color, bool isFreehandShape) : points{}, lastDrawnPoint{0,0}, isFreehandShape{isFreehandShape}, color{color} {
    setName(generateElementName());
    this->setBounds();
}

Freehand::Freehand(const Freehand& cp) : Freehand() {
    this->hasFirstPoint = cp.hasFirstPoint;
    this->lastDrawnPoint = cp.lastDrawnPoint;
    this->finished = cp.finished;
    this->points = cp.points;
    this->color = cp.color;
    this->isFreehandShape = cp.isFreehandShape;
    this->name = cp.name;
    this->setBounds();
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
    this->minBound = ep.minBound;
    this->maxBound = ep.maxBound;
    this->setBounds();
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
    std::vector<ivec2> pointsToColor;
    std::vector<bool> visited(screen->getWidth() * screen->getHeight(), false);
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
        int id = p.y * screen->getWidth() + p.x;
        if (visited[id]) {
            continue;
        }

        // screen->colorOnePixel(p, this->color, this->parentStart, this->parentEnd);
        pointsToColor.push_back(p);
        visited[id] = true;
        updateBounds(p);

        st.push(ivec2(x + 1, y));
        st.push(ivec2(x - 1, y));
        st.push(ivec2(x, y + 1));
        st.push(ivec2(x, y - 1));
    }
    std::sort(pointsToColor.begin(), pointsToColor.end(), [](const ivec2& a, const ivec2& b) {
        return a.y == b.y ? a.x < b.x : a.y < b.y;
    });
    screen->drawFreehandFlood(pointsToColor, this->color, this->parentStart, this->parentEnd);
}

void Freehand::updateBounds(const ivec2& coords) {
    if (!hasBounds) {
        minBound = coords;
        maxBound = coords;
        hasBounds = true;
        return;
    }
    minBound.x = std::min(minBound.x, coords.x);
    minBound.y = std::min(minBound.y, coords.y);
    maxBound.x = std::max(maxBound.x, coords.x);
    maxBound.y = std::max(maxBound.y, coords.y);
}

GuiElement* Freehand::clone() const {
    return new Freehand(*this);
}

bool Freehand::resolveEvent(Event *e) {
    if (e->getType() == EventType::CLICK) {
        Selected::getInstance().setSelectedElement(this);
        return true;
    }

    if (e->getType() == EventType::MOUSE_DOWN) {
        MouseDownEvent* md = static_cast<MouseDownEvent*>(e);

        if (!hasFirstPoint) {
            lastDrawnPoint = md->getCoords();
            hasFirstPoint = true;
            this->points.push_back(ivec2{lastDrawnPoint});
            this->updateBounds(ivec2{lastDrawnPoint});
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

        // int dx = current.x - lastDrawnPoint.x;
        // int dy = current.y - lastDrawnPoint.y;

        // if ((dx * dx + dy * dy) < (PIXEL_DRAW_DIST_THRESHOLD * PIXEL_DRAW_DIST_THRESHOLD)) {  
        //     return true;
        // }
        this->points.push_back(ivec2{current});
        this->setPoints();
        this->updateBounds(ivec2{current});
        lastDrawnPoint = current;
        return true;
    }

    if (e->getType() == EventType::MOUSE_UP) {
        MouseUpEvent* mu = static_cast<MouseUpEvent*>(e);

        ivec2 current = mu->getCoords();
        // this->points.push_back(ivec2{lastDrawnPoint});
        // this->updateBounds(ivec2{lastDrawnPoint});
        

        if (isFreehandShape) {
            int dx = current.x - points[0].x;
            int dy = current.y - points[0].y;

            if (dx * dx + dy * dy > SHAPE_COMPLETION_DIST_THRESHOLD * SHAPE_COMPLETION_DIST_THRESHOLD) {  
                if (!this->finished) {
                    this->points.clear();
                    lastDrawnPoint = current;
                    return false;
                }
                
            }
            this->finished = true;
            this->points.push_back(points[0]);
            lastDrawnPoint = points[0];
            this->updateBounds(ivec2{lastDrawnPoint});
        }
        return true;
    }

    return false;
}

void Freehand::writeXml(std::ostream& out, int depth) const {
    std::string pad = std::string(depth * 2, ' ');
    std::string shapeMode = isFreehandShape ? "true" : "false";

    out << pad << "<freehand " << "name=\"" << this->getName() << "\" shapeMode=\"" << shapeMode << "\">\n";

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
    if (ep.elementType != guiElement::FREEHAND) {
        ep.elementType = guiElement::FREEHAND;
    }

    return true;
}

bool Freehand::isInside(ivec2 coordinates) {
    ivec2 center(0, 0);
    for (const ivec2& point : this->points) {
        int dx = coordinates.x - point.x;
        int dy = coordinates.y - point.y;
        center.x += point.x;
        center.y += point.y;
        if ((dx * dx + dy * dy) <= (PADDING * PADDING)) {
            return true;
        }
    }
    if (this->isFreehandShape) {
        bool inside = false;
        size_t n = points.size();

        for (size_t i = 0, j = n - 1; i < n; j = i++) {
            const ivec2& pi = points[i];
            const ivec2& pj = points[j];

            bool intersects =
                ((pi.y > coordinates.y) != (pj.y > coordinates.y)) &&
                (coordinates.x < (pj.x - pi.x) * (coordinates.y - pi.y) / static_cast<double>(pj.y - pi.y) + pi.x);

            if (intersects) {
                inside = !inside;
            }
        }
        return inside;
    }
        
    return false;
}

bool Freehand::isFinished() const {
    return finished;
}

bool Freehand::isFreehandShapeMode() const {
    return isFreehandShape;
}

std::vector<ivec2>& Freehand::getPoints() {
    return points;
}

ivec2 Freehand::getMinBound() const {
    return minBound;
}

ivec2 Freehand::getMaxBound() const {
    return maxBound;
}

bool Freehand::hasDrawBounds() const {
    return hasBounds;
}

ElementParameters Freehand::getParameters() {
    ElementParameters ep;
    ep.elementType = guiElement::FREEHAND;
    ep.points = this->points;
    ep.hasFirstPoint = this->hasFirstPoint;
    ep.lastDrawnPoint = this->lastDrawnPoint;
    ep.finished = this->finished;
    ep.color = this->color;
    ep.isFreehandShape = this->isFreehandShape;
    ep.name = this->name;
    ep.minBound = minBound;
    ep.maxBound = maxBound;
    return ep;
}

guiElement Freehand::getType() {
    return guiElement::FREEHAND;
}

void Freehand::setPoints() {
    if (!(this->points.size() > 2)) {
        return;
    }
    ivec2 end = this->points.back();
    this->points.pop_back();
    int x0 = this->points.back().x;
    int y0 = this->points.back().y;
    int x1 = end.x;
    int y1 = end.y;
    int dx = std::abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -std::abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;
    while (true) {
        this->points.push_back(ivec2(x0, y0));
        if (x0 == x1 && y0 == y1) {
            break;
        }
        int e2 = 2 * error;
        if (e2 >= dy){
            error += dy;
            x0 += sx;
        }
        if (e2 <= dx){
            error += dx;
            y0 += sy;
        }
    }
}

void Freehand::modifyColor(ivec3 newColor) {
    this->color += newColor;
    if (color.x < 0) {
        color.x = 0;
    }
    else if (color.x > 255) {
        color.x = 255;
    }
    if (color.y < 0) {
        color.y = 0;
    }
    else if (color.y > 255) {
        color.y = 255;
    }
    if (color.z < 0) {
        color.z = 0;
    }
    else if (color.z > 255) {
        color.z = 255;
    }
}

void Freehand::setBounds() {
    if (points.empty()) {
        return;
    }
    minBound = points[0];
    maxBound = points[0];
    for (auto point : points) {
        minBound.x = std::min(minBound.x, point.x);
        minBound.y = std::min(minBound.y, point.y);
        maxBound.x = std::max(maxBound.x, point.x);
        maxBound.y = std::max(maxBound.y, point.y);
    }
}

std::vector<ivec2> Freehand::getBounds() {
    return {this->minBound, this->maxBound};
}

void Freehand::movePoints(ivec2 delta) {
    for (int i = 0; i < this->points.size(); ++i) {
        this->points[i] += delta;
    }
}