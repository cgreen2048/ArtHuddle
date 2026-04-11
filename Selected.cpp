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

    if (!this->selectedElement) {
        this->selectedLayout->clearElements();
        return;
    }

    Point* point = dynamic_cast<Point*>(this->selectedElement);
    if (point) {
        ivec2 pointCoords = point->getCoords();
        this->minBound = pointCoords;
        this->maxBound = pointCoords;
        this->drawBoundingBox();
        return;
    }

    Line* line = dynamic_cast<Line*>(this->selectedElement);
    if (line) {
        ivec2 start = line->getStart();
        ivec2 end = line->getEnd();
        int minX = std::min(start.x, end.x);
        int minY = std::min(start.y, end.y);
        int maxX = std::max(start.x, end.x);
        int maxY = std::max(start.y, end.y);

        this->minBound = ivec2(minX, minY);
        this->maxBound = ivec2(maxX, maxY);
        this->drawBoundingBox();
        return;
    }

    Box* box = dynamic_cast<Box*>(this->selectedElement);
    if (box) {
        ivec2 min = box->getMin();
        ivec2 max = box->getMax();
        int minX = std::min(min.x, max.x);
        int minY = std::min(min.y, max.y);
        int maxX = std::max(min.x, max.x);
        int maxY = std::max(min.y, max.y);

        this->minBound = ivec2(minX, minY);
        this->maxBound = ivec2(maxX, maxY);
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
        this->drawBoundingBox();
        return;
    }

    Arrow* arrow = dynamic_cast<Arrow*>(this->selectedElement);
    if (arrow) {
        ivec2 min = arrow->getMin();
        ivec2 max = arrow->getMax();
        ivec2 pointA = arrow->getA();
        ivec2 pointB = arrow->getB();
        ivec2 pointC = arrow->getC();
        
        int minX = std::min(std::min(std::min(std::min(pointA.x, pointB.x), pointC.x), min.x), max.x);
        int minY = std::min(std::min(std::min(std::min(pointA.y, pointB.y), pointC.y), min.y), max.y);
        int maxX = std::max(std::max(std::max(std::max(pointA.x, pointB.x), pointC.x), min.x), max.x);
        int maxY = std::max(std::max(std::max(std::max(pointA.y, pointB.y), pointC.y), min.y), max.y);

        this->minBound = ivec2(minX, minY);
        this->maxBound = ivec2(maxX, maxY);

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
    topParam.start = this->minBound;
    topParam.end = ivec2(this->maxBound.x, this->minBound.y);
    topParam.color = ivec3(20, 20, 255);
    topParam.startType = TagType::IVec;
    topParam.endType = TagType::IVec;
    topParam.name = "topBound";
    Line* topBound = dynamic_cast<Line*>(factory(guiElement::LINE, topParam));
    this->selectedLayout->addElement(topBound);

    ElementParameters bottomParam;
    bottomParam.start = ivec2(this->minBound.x, this->maxBound.y);
    bottomParam.end = this->maxBound;
    bottomParam.color = ivec3(20, 20, 255);
    bottomParam.startType = TagType::IVec;
    bottomParam.endType = TagType::IVec;
    bottomParam.name = "bottomBound";
    Line* bottomBound = dynamic_cast<Line*>(factory(guiElement::LINE, bottomParam));
    this->selectedLayout->addElement(bottomBound);

    ElementParameters leftParam;
    leftParam.start = this->minBound;
    leftParam.end = ivec2(this->minBound.x, this->maxBound.y);
    leftParam.color = ivec3(20, 20, 255);
    leftParam.startType = TagType::IVec;
    leftParam.endType = TagType::IVec;
    leftParam.name = "leftBound";
    Line* leftBound = dynamic_cast<Line*>(factory(guiElement::LINE, leftParam));
    this->selectedLayout->addElement(leftBound);

    ElementParameters rightParam;
    rightParam.start = ivec2(this->maxBound.x, this->minBound.y);
    rightParam.end = this->maxBound;
    rightParam.color = ivec3(20, 20, 255);
    rightParam.startType = TagType::IVec;
    rightParam.endType = TagType::IVec;
    rightParam.name = "rightBound";
    Line* rightBound = dynamic_cast<Line*>(factory(guiElement::LINE, rightParam));
    this->selectedLayout->addElement(rightBound);
}