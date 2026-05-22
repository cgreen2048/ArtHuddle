#include <iostream>
#include <vector>
#include "ArtHuddle/core/vec2.hpp"
#include "ArtHuddle/core/vec3.hpp"
#include "ArtHuddle/utility/GUIFile.hpp"
#include "ArtHuddle/elements/Layout.hpp"
#include "ArtHuddle/elements/Line.hpp"
#include "ArtHuddle/elements/Box.hpp"
#include "ArtHuddle/elements/Point.hpp"
#include "ArtHuddle/elements/Triangle.hpp"
#include "ArtHuddle/elements/GuiElement.hpp"
#include "ArtHuddle/elements/Button.hpp"

int main() {
    int failure = 0;

    Layout* expectedRoot = new Layout();
    expectedRoot->setStart(vec2(0.0f, 0.0f));
    expectedRoot->setEnd(vec2(1.0f, 1.0f));
    expectedRoot->setActive(true);
    expectedRoot->setName("Line-Ellipse-Box-Point-Layout");

    ElementParameters lineParam;
    lineParam.start = ivec2(50, 902);
    lineParam.end = ivec2(75, 1024);
    lineParam.startType = TagType::IVec;
    lineParam.endType = TagType::IVec;
    lineParam.name = "l1";
    GuiElement* l = factory(guiElement::LINE, lineParam);
    expectedRoot->addElement(l);

    ElementParameters ellipseParam;
    ellipseParam.name = "e1";
    ellipseParam.center = ivec2(50, 20);
    ellipseParam.radiusX = 4;
    ellipseParam.radiusY = 6;
    ellipseParam.color = ivec3(255,0,0);
    ellipseParam.centerType = TagType::IVec;
    ellipseParam.colorType = TagType::IVec;
    GuiElement* eli = factory(guiElement::ELLIPSE, ellipseParam); 
    expectedRoot->addElement(eli);

    ElementParameters buttonParam;
    buttonParam.name = "b1";
    buttonParam.callbackName = "testCallback";
    buttonParam.text = "Click me!";
    buttonParam.min = ivec2(50, 50);
    buttonParam.max = ivec2(150, 100);
    buttonParam.color = ivec3(255, 0, 0);
    buttonParam.minType = TagType::IVec;
    buttonParam.maxType = TagType::IVec;
    buttonParam.colorType = TagType::IVec;
    GuiElement* btn = factory(guiElement::BUTTON, buttonParam);
    expectedRoot->addElement(btn);

    ElementParameters boxParam;
    boxParam.min = ivec2(250, 122);
    boxParam.max = ivec2(420, 254);
    boxParam.color = ivec3(212, 22, 124);
    boxParam.minType = TagType::IVec;
    boxParam.maxType = TagType::IVec;
    boxParam.colorType = TagType::IVec;
    GuiElement* b = factory(guiElement::BOX, boxParam);
    expectedRoot->addElement(b);

    ElementParameters pointParam;
    pointParam.coords = ivec2(480, 270);
    pointParam.color = ivec3(67, 200, 142);
    pointParam.coordsType = TagType::IVec;
    pointParam.colorType = TagType::IVec;
    pointParam.name = "p1";
    GuiElement* p = factory(guiElement::POINT, pointParam);
    expectedRoot->addElement(p);

    ElementParameters triangleParam;
    triangleParam.pointA = ivec2(100, 100);
    triangleParam.pointB = ivec2(150, 100);
    triangleParam.pointC = ivec2(125, 150);
    triangleParam.color = ivec3(255, 0, 0);
    triangleParam.pointAType = TagType::IVec;
    triangleParam.pointBType = TagType::IVec;
    triangleParam.pointCType = TagType::IVec;
    triangleParam.colorType = TagType::IVec;
    GuiElement* t = factory(guiElement::TRIANGLE, triangleParam);
    expectedRoot->addElement(t);

    ElementParameters arrowParam;
    arrowParam.min = ivec2(250, 250);
    arrowParam.max = ivec2(500, 400);
    arrowParam.pointA = ivec2(500, 150);
    arrowParam.pointB = ivec2(500, 500);
    arrowParam.pointC = ivec2(650, 325);
    arrowParam.minType = TagType::IVec;
    arrowParam.maxType = TagType::IVec;
    arrowParam.pointAType = TagType::IVec;
    arrowParam.pointBType = TagType::IVec;
    arrowParam.pointCType = TagType::IVec;
    arrowParam.color = ivec3(125, 125, 125);
    arrowParam.colorType = TagType::IVec;
    arrowParam.name = "a1";
    GuiElement* a = factory(guiElement::ARROW, arrowParam);
    expectedRoot->addElement(a);

    expectedRoot->deleteElement(pointParam.name);
    for (GuiElement *e : expectedRoot->getElements()) {
        if (e->getName() == pointParam.name) {
            failure = 1;
        }
    }

    if (failure == 1) {
        std::cout << "LAYOUT DELETE FAILED\n";
    }
    else {
        std::cout << "Layout delete passed\n";
    }
    return failure;
}