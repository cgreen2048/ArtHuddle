#include "Selected.hpp"

Selected::Selected() {}

Selected::~Selected() {
    
}

Selected& Selected::getInstance() {
    static Selected instance;
    return instance;
}

void Selected::setSelectedElement(GuiElement* updatedElement) {
    this->selectedElement = updatedElement;

    Point* point = dynamic_cast<Point*>(this->selectedElement);
    if (point) {
        ivec2 pointCoords = point->getCoords();
        this->minBound = pointCoords;
        this->maxBound = pointCoords;
        std::cout << this->minBound.x << ' ' << this->minBound.y << '\n';
        std::cout << this->maxBound.x << ' ' << this->maxBound.y << '\n';
        this->drawBoundingBox();
        return;
    }

    Line* line = dynamic_cast<Line*>(this->selectedElement);
    if (line) {
        this->minBound = line->getStart();
        this->maxBound = line->getEnd();
        std::cout << this->minBound.x << ' ' << this->minBound.y << '\n';
        std::cout << this->maxBound.x << ' ' << this->maxBound.y << '\n';
        this->drawBoundingBox();
        return;
    }

    Box* box = dynamic_cast<Box*>(this->selectedElement);
    if (box) {
        this->minBound = box->getMin();
        this->maxBound = box->getMax();
        std::cout << this->minBound.x << ' ' << this->minBound.y << '\n';
        std::cout << this->maxBound.x << ' ' << this->maxBound.y << '\n';
        this->drawBoundingBox();
        return;
    }

    Triangle* triangle = dynamic_cast<Triangle*>(this->selectedElement);
    if (triangle) {
        ivec2 pointA = triangle->getA();
        ivec2 pointB = triangle->getB();
        ivec2 pointC = triangle->getC();
        
        int minX = std::min(std::min(pointA.x, pointB.x), pointC.x);
        int minY = std::min(std::min(pointA.y, pointB.y), pointC.y);
        int maxX = std::max(std::max(pointA.x, pointB.x), pointC.x);
        int maxY = std::max(std::max(pointA.y, pointB.y), pointC.y);

        this->minBound = ivec2(minX, minY);
        this->maxBound = ivec2(maxX, maxY);
        std::cout << this->minBound.x << ' ' << this->minBound.y << '\n';
        std::cout << this->maxBound.x << ' ' << this->maxBound.y << '\n';
        this->drawBoundingBox();
        return;
    }

    Ellipse* ellipse = dynamic_cast<Ellipse*>(this->selectedElement);
    if (ellipse) {
        int radX = ellipse->getRadiusX();
        int radY = ellipse->getRadiusY();
        ivec2 center = ellipse->getCenter();

        this->minBound = ivec2(center.x - radX, center.y - radY);
        this->maxBound = ivec2(center.x + radX, center.y + radY);
        std::cout << this->minBound.x << ' ' << this->minBound.y << '\n';
        std::cout << this->maxBound.x << ' ' << this->maxBound.y << '\n';
        this->drawBoundingBox();
        return;
    }
}

GuiElement* Selected::getSelectedElement() {
    return this->selectedElement;
}

void Selected::setSelectedLayout(Layout* boundingBoxLayout) {
    this->selectedLayout = boundingBoxLayout;
}

void Selected::drawBoundingBox() {
    this->selectedLayout->clearElements();
    this->minBound.x -= 5;
    this->minBound.y -= 5;
    this->maxBound.x += 5;
    this->maxBound.y += 5;
    ElementParameters topParam;
    topParam.point1 = this->minBound;
    topParam.point2 = ivec2(this->maxBound.x, this->minBound.y);
    topParam.color = ivec3(20, 20, 255);
    topParam.point1Type = TagType::IVec;
    topParam.point2Type = TagType::IVec;
    topParam.name = "topBound";
    Line* topBound = dynamic_cast<Line*>(factory(guiElement::LINE, topParam));
    this->selectedLayout->addElement(topBound);

    ElementParameters bottomParam;
    bottomParam.point1 = ivec2(this->minBound.x, this->maxBound.y);
    bottomParam.point2 = this->maxBound;
    bottomParam.color = ivec3(20, 20, 255);
    bottomParam.point1Type = TagType::IVec;
    bottomParam.point2Type = TagType::IVec;
    bottomParam.name = "bottomBound";
    Line* bottomBound = dynamic_cast<Line*>(factory(guiElement::LINE, bottomParam));
    this->selectedLayout->addElement(bottomBound);

    ElementParameters leftParam;
    leftParam.point1 = this->minBound;
    leftParam.point2 = ivec2(this->minBound.x, this->maxBound.y);
    leftParam.color = ivec3(20, 20, 255);
    leftParam.point1Type = TagType::IVec;
    leftParam.point2Type = TagType::IVec;
    leftParam.name = "leftBound";
    Line* leftBound = dynamic_cast<Line*>(factory(guiElement::LINE, leftParam));
    this->selectedLayout->addElement(leftBound);

    ElementParameters rightParam;
    rightParam.point1 = ivec2(this->maxBound.x, this->minBound.y);
    rightParam.point2 = this->maxBound;
    rightParam.color = ivec3(20, 20, 255);
    rightParam.point1Type = TagType::IVec;
    rightParam.point2Type = TagType::IVec;
    rightParam.name = "rightBound";
    Line* rightBound = dynamic_cast<Line*>(factory(guiElement::LINE, rightParam));
    this->selectedLayout->addElement(rightBound);
}