#include <iostream>
#include <cmath>
#include <vector>
#include "../vec2.hpp"
#include "../vec3.hpp"
#include "../GUIFile.hpp"
#include "../Layout.hpp"
#include "../Line.hpp"
#include "../Box.hpp"
#include "../Point.hpp"
#include "../Triangle.hpp"
#include "../GuiElement.hpp"
#include "../Button.hpp"

int readTest1();
int readTest2();
int readTest3();
int readTest4();
int readTest5();
int readTest6();
int readTest7();
int readTest8();
int writeTest1();
int writeTest2();
int writeTest3();

int compareSingleElement(GuiElement* actual, GuiElement* expected);
int layoutComparison(Layout* actual, Layout* expected);

static int toInt(float x);
static ivec2 toIVec2(float x, float y);
static ivec3 toIVec3(float x, float y, float z);

int main() {
    int failure = 0;

    if (readTest1()){ 
        failure = 1;
    }
    if (readTest2()) {
        failure = 1;
    }
    if (readTest3()) {
        failure = 1;
    }
    if (readTest4()) {
        failure = 1;
    }
    if (readTest5()) {
        failure = 1;
    }
    if(readTest6()){
        failure = 1;
    }
    if(readTest7()){
        failure = 1;
    }
    if(readTest8()){
        failure = 1;
    }
    if (writeTest1()) {
        failure = 1;
    }
    if (writeTest2()) {
        failure = 1;
    }
    if (writeTest3()) {
        failure = 1;
    }

    if (failure) {
        std::cout << "IMPLEMENTATION(S) FAILED, REVIEW TEST RESULTS\n";
    }
    else {
        std::cout << "ALL TESTS PASSED\n";
    }

    return failure;
}

static int toInt(float x) {
    return static_cast<int>(std::lround(x));
}

static ivec2 toIVec2(float x, float y) {
    return ivec2(toInt(x), toInt(y));
}

static ivec3 toIVec3(float x, float y, float z) {
    return ivec3(toInt(x), toInt(y), toInt(z));
}

int compareSingleElement(GuiElement* actual, GuiElement* expected) {
    if (!actual || !expected) {
        return 1;
    }

    if (auto* aLine = dynamic_cast<Line*>(actual)) {
        auto* eLine = dynamic_cast<Line*>(expected);
        if (!eLine) {
            return 1;
        }
        if (*aLine != *eLine) {
            return 1;
        }
        if (aLine->getName() != eLine->getName()) {
            return 1;
        }
        return 0;
    }

    if (auto* aBox = dynamic_cast<Box*>(actual)) {
        auto* eBox = dynamic_cast<Box*>(expected);
        if (!eBox) {
            return 1;
        }
        if (*aBox != *eBox) {
            return 1;
        }
        if (aBox->getName() != eBox->getName()) {
            return 1;
        }
        return 0;
    }

    if (auto* aPoint = dynamic_cast<Point*>(actual)) {
        auto* ePoint = dynamic_cast<Point*>(expected);
        if (!ePoint) {
            return 1;
        }
        if (*aPoint != *ePoint) {
            return 1;
        }
        if (aPoint->getName() != ePoint->getName()) {
            return 1;
        }
        return 0;
    }

    if (auto* aTriangle = dynamic_cast<Triangle*>(actual)) {
        auto* eTriangle = dynamic_cast<Triangle*>(expected);
        if (!eTriangle) {
            return 1;
        }
        if (*aTriangle != *eTriangle) {
            return 1;
        }
        if (aTriangle->getName() != eTriangle->getName()) {
            return 1;
        }
        return 0;
    }

    if (auto* aButton = dynamic_cast<Button*>(actual)) {
        auto* eButton = dynamic_cast<Button*>(expected);
        if (!eButton) {
            return 1;
        }
        if (*aButton != *eButton) {
            return 1;
        }
        if (aButton->getName() != eButton ->getName()) {
            return 1;
        }
        if (aButton->getText() != eButton ->getText()) {
            return 1;
        }
        if (aButton->getCallbackName() != eButton ->getCallbackName()) {
            return 1;
        }
        return 0;
    }

    if (auto* aTextBox = dynamic_cast<TextBox*>(actual)) {
        auto* eTextBox = dynamic_cast<TextBox*>(expected);
        if (!eTextBox) {
            return 1;
        }
        if (*aTextBox != *eTextBox) {
            return 1;
        }
        if (aTextBox->getName() != eTextBox->getName()) {
            return 1;
        }
        if (aTextBox->getText() != eTextBox->getText()) {
            return 1;
        }
        return 0;
    }

    return 1;
}

int layoutComparison(Layout* actual, Layout* expected) {
    if (!actual || !expected) {
        return 1;
    }

    if (actual->getStart() != expected->getStart()) {
        return 1;
    }

    if (actual->getEnd() != expected->getEnd()) {
        return 1;
    }

    if (actual->getName() != expected->getName()) {
        return 1;
    }

    const std::vector<GuiElement*>& actualChildren = actual->getElements();
    const std::vector<GuiElement*>& expectedChildren = expected->getElements();

    if (actualChildren.size() != expectedChildren.size()) {
        return 1;
    }

    for (size_t i = 0; i < actualChildren.size(); ++i) {
        GuiElement* a = actualChildren[i];
        GuiElement* e = expectedChildren[i];

        if (auto* aLayout = dynamic_cast<Layout*>(a)) {
            auto* eLayout = dynamic_cast<Layout*>(e);
            if (!eLayout) {
                return 1;
            }
            if (layoutComparison(aLayout, eLayout)) {
                return 1;
            }
        }
        else {
            if (compareSingleElement(a, e)) {
                return 1;
            }
        }
    }

    return 0;
}

int readTest1() {
    int failure = 0;

    Layout* expectedRoot = new Layout();
    expectedRoot->setStart(vec2(0.0f, 0.0f));
    expectedRoot->setEnd(vec2(1.0f, 1.0f));
    expectedRoot->setActive(true);
    expectedRoot->setName("Line-Box-Point-Layout");

    ElementParameters lineParam;
    lineParam.point1 = toIVec2(50.5f, 902.47f);
    lineParam.point2 = toIVec2(75.6f, 1024.6f);
    lineParam.color = toIVec3(244.0f, 245.0f, 103.3f);
    lineParam.point1Type = TagType::IVec;
    lineParam.point2Type = TagType::IVec;
    lineParam.colorType = TagType::IVec;
    GuiElement* l = factory(guiElement::LINE, lineParam);
    expectedRoot->addElement(l);

    ElementParameters buttonParam;
    buttonParam.name = "b1";
    buttonParam.callbackName = "testCallback";
    buttonParam.text = "Click me!";
    buttonParam.point1 = ivec2(50, 50);
    buttonParam.point2 = ivec2(150, 100);
    buttonParam.color = ivec3(255, 0, 0);
    buttonParam.point1Type = TagType::IVec;
    buttonParam.point2Type = TagType::IVec;
    buttonParam.colorType = TagType::IVec;
    GuiElement* btn = factory(guiElement::BUTTON, buttonParam);
    expectedRoot->addElement(btn);

    ElementParameters boxParam;
    boxParam.point1 = toIVec2(250.3f, 122.5f);
    boxParam.point2 = toIVec2(420.34f, 254.9f);
    boxParam.color = ivec3(212, 22, 124);
    boxParam.point1Type = TagType::IVec;
    boxParam.point2Type = TagType::IVec;
    boxParam.colorType = TagType::IVec;
    GuiElement* b = factory(guiElement::BOX, boxParam);
    expectedRoot->addElement(b);

    ElementParameters pointParam;
    pointParam.point1 = ivec2(480, 270);
    pointParam.color = ivec3(67, 200, 142);
    pointParam.point1Type = TagType::IVec;
    pointParam.colorType = TagType::IVec;
    GuiElement* p = factory(guiElement::POINT, pointParam);
    expectedRoot->addElement(p);

    ElementParameters triangleParam;
    triangleParam.point1 = ivec2(100, 100);
    triangleParam.point2 = ivec2(150, 100);
    triangleParam.point3 = ivec2(125, 150);
    triangleParam.color = ivec3(255, 0, 0);
    triangleParam.point1Type = TagType::IVec;
    triangleParam.point2Type = TagType::IVec;
    triangleParam.point3Type = TagType::IVec;
    triangleParam.colorType = TagType::IVec;
    GuiElement* t = factory(guiElement::TRIANGLE, triangleParam);
    expectedRoot->addElement(t);


    ElementParameters textBoxParam;
    textBoxParam.point1 = ivec2(100, 100);
    textBoxParam.point2 = ivec2(300, 150);
    textBoxParam.color = ivec3(255, 255, 255);
    textBoxParam.textColor = ivec3(0, 0, 0);
    textBoxParam.point1Type = TagType::IVec;
    textBoxParam.point2Type = TagType::IVec;
    textBoxParam.colorType = TagType::IVec;
    textBoxParam.textColorType = TagType::IVec;
    GuiElement* tb = factory(guiElement::TEXTBOX, textBoxParam);
    expectedRoot->addElement(tb);


    GUIFile gui;
    gui.readFile("testFiles/readTest1.xml");

    if (layoutComparison(gui.getRootLayout(), expectedRoot)) {
        failure = 1;
    }

    delete expectedRoot;

    std::cout << (failure ? "reading test 1 (good input) FAILED\n" : "reading test 1 (good input) passed\n");
    return failure;
}

int readTest2() {
    int failure = 0;

    Layout* expectedRoot = new Layout();
    expectedRoot->setStart(vec2(0.0f, 0.0f));
    expectedRoot->setEnd(vec2(1.0f, 1.0f));
    expectedRoot->setActive(true);
    expectedRoot->setName("Layout1");


    ElementParameters triangleParam;
    triangleParam.point1 = ivec2(100, 100);
    triangleParam.point2 = ivec2(150, 100);
    triangleParam.point3 = ivec2(125, 150);
    triangleParam.color = ivec3(255, 0, 0);
    triangleParam.point1Type = TagType::IVec;
    triangleParam.point2Type = TagType::IVec;
    triangleParam.point3Type = TagType::IVec;
    triangleParam.colorType = TagType::IVec;
    GuiElement* t = factory(guiElement::TRIANGLE, triangleParam);
    expectedRoot->addElement(t);

    Layout* nested = new Layout();
    nested->setStart(vec2(0.25f, 0.25f));
    nested->setEnd(vec2(0.75f, 0.75f));
    nested->setActive(true);

    ElementParameters pParam;
    pParam.point1 = ivec2(480, 270);
    pParam.color = ivec3(67, 200, 142);
    pParam.point1Type = TagType::IVec;
    pParam.colorType = TagType::IVec;
    GuiElement* p = factory(guiElement::POINT, pParam);
    nested->addElement(p);

    ElementParameters boxParam;
    boxParam.point1 = toIVec2(250.3f, 122.5f);
    boxParam.point2 = toIVec2(420.34f, 254.9f);
    boxParam.color = ivec3(212, 22, 124);
    boxParam.point1Type = TagType::IVec;
    boxParam.point2Type = TagType::IVec;
    boxParam.colorType = TagType::IVec;
    GuiElement* b = factory(guiElement::BOX, boxParam);
    nested->addElement(b);

    ElementParameters buttonParam;
    buttonParam.name = "b1";
    buttonParam.callbackName = "testCallback";
    buttonParam.text = "Click me!";
    buttonParam.point1 = ivec2(50, 50);
    buttonParam.point2 = ivec2(150, 100);
    buttonParam.color = ivec3(255, 0, 0);
    buttonParam.point1Type = TagType::IVec;
    buttonParam.point2Type = TagType::IVec;
    buttonParam.colorType = TagType::IVec;
    GuiElement* btn = factory(guiElement::BUTTON, buttonParam);
    nested->addElement(btn);

    ElementParameters textBoxParam;
    textBoxParam.point1 = ivec2(100, 100);
    textBoxParam.point2 = ivec2(300, 150);
    textBoxParam.color = ivec3(255, 255, 255);
    textBoxParam.textColor = ivec3(0, 0, 0);
    textBoxParam.point1Type = TagType::IVec;
    textBoxParam.point2Type = TagType::IVec;
    textBoxParam.colorType = TagType::IVec;
    textBoxParam.textColorType = TagType::IVec;
    GuiElement* tb = factory(guiElement::TEXTBOX, textBoxParam);
    nested->addElement(tb);


    expectedRoot->addElement(nested);

    GUIFile gui;
    gui.readFile("testFiles/readTest2.xml");

    if (layoutComparison(gui.getRootLayout(), expectedRoot)) {
        failure = 1;
    }

    delete expectedRoot;

    std::cout << (failure ? "reading test 2 (good nested layouts) FAILED\n" : "reading test 2 (good nested layouts) passed\n");
    return failure;
}

int readTest3() {
    int failure = 0;

    GUIFile gui;
    gui.readFile("testFiles/readTest3.xml");

    if (gui.getRootLayout() != nullptr) {
        failure = 1;
    }

    std::cout << (failure ? "reading test 3 (invalid layout attributes) FAILED\n" : "reading test 3 (invalid layout attributes) passed\n");
    return failure;
}



int readTest4() {
    int failure = 0;

    GUIFile gui;
    gui.readFile("testFiles/readTest4.xml");

    if (gui.getRootLayout() != nullptr) {
        failure = 1;
    }

    std::cout << (failure ? "reading test 4 (missing closing tag) FAILED\n" : "reading test 4 (missing closing tag) passed\n");
    return failure;
}

int readTest5() {
    int failure = 0;

    Layout* expectedRoot = new Layout();
    expectedRoot->setStart(vec2(0.0f, 0.0f));
    expectedRoot->setEnd(vec2(1.0f, 1.0f));
    expectedRoot->setActive(true);
    expectedRoot->setName("layout1");

    ElementParameters lineParam;
    lineParam.point1 = toIVec2(1.1f, 2.2f);
    lineParam.point2 = toIVec2(3.3f, 4.4f);
    lineParam.color = ivec3(10, 20, 30);
    lineParam.point1Type = TagType::IVec;
    lineParam.point2Type = TagType::IVec;
    lineParam.colorType = TagType::IVec;
    GuiElement* l = factory(guiElement::LINE, lineParam);
    expectedRoot->addElement(l);

    Layout* nested = new Layout();
    nested->setStart(vec2(0.10f, 0.20f));
    nested->setEnd(vec2(0.90f, 0.95f));
    nested->setActive(true);

    ElementParameters pParam;
    pParam.point1 = ivec2(13, 14);
    pParam.color = ivec3(101, 102, 103);
    pParam.point1Type = TagType::IVec;
    pParam.colorType = TagType::IVec;
    GuiElement* p = factory(guiElement::POINT, pParam);
    nested->addElement(p);

    expectedRoot->addElement(nested);

    GUIFile gui;
    gui.readFile("testFiles/readTest5.xml");

    if (layoutComparison(gui.getRootLayout(), expectedRoot)) {
        failure = 1;
    }

    delete expectedRoot;

    std::cout << (failure ? "reading test 5 (weird spacing) FAILED\n" : "reading test 5 (weird spacing) passed\n");
    return failure;
}

int readTest6() {
    int failure = 0;

    GUIFile gui;
    gui.readFile("testFiles/badInput.xml");


    if (gui.getRootLayout() != nullptr) {
        failure = 1;
    }

    if (failure) {
        std::cout << "reading test 6 (invalid input file) FAILED\n";
    }
    else {
        std::cout << "reading test 6 (invalid input file) passed\n";
    }

    return failure;
}

int readTest7() {
    int failure = 0;

    GUIFile gui;
    gui.readFile("testFiles/readTest7.xml");


    if (gui.getRootLayout() != nullptr) {
        failure = 1;
    }

    if (failure) {
        std::cout << "reading test 7 (malformed vector) FAILED\n";
    }
    else {
        std::cout << "reading test 7 (malformed vector) passed\n";
    }

    return failure;
}

int readTest8() {
    int failure = 0;

    GUIFile gui;
    gui.readFile("testFiles/readTest8.xml");


    if (gui.getRootLayout() != nullptr) {
        failure = 1;
    }

    if (failure) {
        std::cout << "reading test 8 (empty xml) FAILED\n";
    }
    else {
        std::cout << "reading test 8 (empty xml) passed\n";
    }

    return failure;
}


int writeTest1() {
    int failure = 0;

    GUIFile gui;

    Layout* root = new Layout();
    root->setStart(vec2(0.0f, 0.0f));
    root->setEnd(vec2(1.0f, 1.0f));
    root->setActive(true);

    ElementParameters lineParam;
    lineParam.point1 = toIVec2(50.5f, 902.47f);
    lineParam.point2 = toIVec2(75.6f, 1024.6f);
    lineParam.color = toIVec3(244.0f, 245.0f, 103.3f);
    lineParam.point1Type = TagType::Vec;
    lineParam.point2Type = TagType::Vec;
    lineParam.colorType = TagType::Vec;
    GuiElement* l = factory(guiElement::LINE, lineParam);
    root->addElement(l);

    ElementParameters boxParam;
    boxParam.point1 = toIVec2(250.3f, 122.5f);
    boxParam.point2 = toIVec2(420.34f, 254.9f);
    boxParam.color = ivec3(212, 22, 124);
    boxParam.point1Type = TagType::Vec;
    boxParam.point2Type = TagType::Vec;
    boxParam.colorType = TagType::Vec;
    GuiElement* b = factory(guiElement::BOX, boxParam);
    root->addElement(b);

    ElementParameters buttonParam;
    buttonParam.name = "writeButton";
    buttonParam.callbackName = "testCallback";
    buttonParam.text = "Click me!";
    buttonParam.point1 = ivec2(50, 50);
    buttonParam.point2 = ivec2(150, 100);
    buttonParam.color = ivec3(255, 0, 0);
    buttonParam.point1Type = TagType::IVec;
    buttonParam.point2Type = TagType::IVec;
    buttonParam.colorType = TagType::IVec;
    GuiElement* btn = factory(guiElement::BUTTON, buttonParam);
    root->addElement(btn);

    ElementParameters textBoxParam;
    textBoxParam.point1 = ivec2(100, 100);
    textBoxParam.point2 = ivec2(300, 150);
    textBoxParam.color = ivec3(255, 255, 255);
    textBoxParam.textColor = ivec3(0, 0, 0);
    textBoxParam.point1Type = TagType::IVec;
    textBoxParam.point2Type = TagType::IVec;
    textBoxParam.colorType = TagType::IVec;
    textBoxParam.textColorType = TagType::IVec;
    GuiElement* tb = factory(guiElement::TEXTBOX, textBoxParam);
    root->addElement(tb);

    gui.setRootLayout(root);

    Layout* expectedRoot = new Layout();
    expectedRoot->setStart(vec2(0.0f, 0.0f));
    expectedRoot->setEnd(vec2(1.0f, 1.0f));
    expectedRoot->setActive(true);

    ElementParameters newLineParam;
    newLineParam.point1 = toIVec2(50.5f, 902.47f);
    newLineParam.point2 = toIVec2(75.6f, 1024.6f);
    newLineParam.color = toIVec3(244.0f, 245.0f, 103.3f);
    newLineParam.point1Type = TagType::Vec;
    newLineParam.point2Type = TagType::Vec;
    newLineParam.colorType = TagType::Vec;
    GuiElement* el = factory(guiElement::LINE, newLineParam);
    expectedRoot->addElement(el);

    ElementParameters newBoxParam;
    newBoxParam.point1 = toIVec2(250.3f, 122.5f);
    newBoxParam.point2 = toIVec2(420.34f, 254.9f);
    newBoxParam.color = ivec3(212, 22, 124);
    newBoxParam.point1Type = TagType::Vec;
    newBoxParam.point2Type = TagType::Vec;
    newBoxParam.colorType = TagType::Vec;
    GuiElement* eb = factory(guiElement::BOX, boxParam);
    expectedRoot->addElement(eb);

    ElementParameters expectedButtonParam;
    expectedButtonParam.name = "writeButton";
    expectedButtonParam.callbackName = "testCallback";
    expectedButtonParam.text = "Click me!";
    expectedButtonParam.point1 = ivec2(50, 50);
    expectedButtonParam.point2 = ivec2(150, 100);
    expectedButtonParam.color = ivec3(255, 0, 0);
    expectedButtonParam.point1Type = TagType::IVec;
    expectedButtonParam.point2Type = TagType::IVec;
    expectedButtonParam.colorType = TagType::IVec;
    GuiElement* expectedButton = factory(guiElement::BUTTON, expectedButtonParam);
    expectedRoot->addElement(expectedButton);

    ElementParameters expectedtextBoxParam;
    expectedtextBoxParam.point1 = ivec2(100, 100);
    expectedtextBoxParam.point2 = ivec2(300, 150);
    expectedtextBoxParam.color = ivec3(255, 255, 255);
    expectedtextBoxParam.textColor = ivec3(0, 0, 0);
    expectedtextBoxParam.point1Type = TagType::IVec;
    expectedtextBoxParam.point2Type = TagType::IVec;
    expectedtextBoxParam.colorType = TagType::IVec;
    expectedtextBoxParam.textColorType = TagType::IVec;
    GuiElement* etb = factory(guiElement::TEXTBOX, expectedtextBoxParam);
    expectedRoot->addElement(etb);

    

    gui.writeFile("testFiles/writeTest1.xml");
    gui.readFile("testFiles/writeTest1.xml");

    if (layoutComparison(gui.getRootLayout(), expectedRoot)) {
        failure = 1;
    }

    delete expectedRoot;

    if (failure) {
        std::cout << "writing test 1 (write then read) FAILED\n";
    }
    else {
        std::cout << "writing test 1 (write then read) passed\n";
    }

    return failure;
}

int writeTest2() {
    int failure = 0;

    GUIFile gui;

    Layout* root = new Layout();
    root->setStart(vec2(0.0f, 0.0f));
    root->setEnd(vec2(1.0f, 1.0f));
    root->setActive(true);

    gui.setRootLayout(root);

    gui.writeFile("testFiles/writeTest2.xml");
    gui.readFile("testFiles/writeTest2.xml");

    Layout* actual = gui.getRootLayout();
    if (!actual) {
        failure = 1;
    }
    else if (actual->getElements().size() != 0) {
        failure = 1;
    }

    if (failure) {
        std::cout << "writing test 2 (empty tag) FAILED\n";
    }
    else {
        std::cout << "writing test 2 (empty tag) passed\n";
    }

    return failure;
}

int writeTest3() {
    int failure = 0;

    GUIFile gui;

    Layout* root = new Layout();
    root->setStart(vec2(0.0f, 0.0f));
    root->setEnd(vec2(1.0f, 1.0f));
    root->setActive(true);

    Layout* nested1 = new Layout();
    nested1->setStart(vec2(0.25f, 0.25f));
    nested1->setEnd(vec2(0.75f, 0.75f));
    nested1->setActive(true);

    ElementParameters p1Param;
    p1Param.point1 = ivec2(13, 14);
    p1Param.color = ivec3(101, 102, 103);
    p1Param.point1Type = TagType::IVec;
    p1Param.colorType = TagType::IVec;
    GuiElement* p1 = factory(guiElement::POINT, p1Param);
    nested1->addElement(p1);

    Layout* nested2 = new Layout();
    nested2->setStart(vec2(0.50f, 0.50f));
    nested2->setEnd(vec2(1.00f, 1.00f));
    nested2->setActive(true);

    ElementParameters triangleParam;
    triangleParam.point1 = ivec2(100, 100);
    triangleParam.point2 = ivec2(150, 100);
    triangleParam.point3 = ivec2(125, 150);
    triangleParam.color = ivec3(255, 0, 0);
    triangleParam.point1Type = TagType::IVec;
    triangleParam.point2Type = TagType::IVec;
    triangleParam.point3Type = TagType::IVec;
    triangleParam.colorType = TagType::IVec;
    GuiElement* t = factory(guiElement::TRIANGLE, triangleParam);
    nested2->addElement(t);

    ElementParameters buttonParam;
    buttonParam.name = "deepButton";
    buttonParam.callbackName = "testCallback";
    buttonParam.text = "Deep";
    buttonParam.point1 = ivec2(200, 200);
    buttonParam.point2 = ivec2(280, 240);
    buttonParam.color = ivec3(0, 0, 255);
    buttonParam.point1Type = TagType::IVec;
    buttonParam.point2Type = TagType::IVec;
    buttonParam.colorType = TagType::IVec;
    GuiElement* btn = factory(guiElement::BUTTON, buttonParam);
    nested2->addElement(btn);

    ElementParameters textBoxParam;
    textBoxParam.point1 = ivec2(100, 100);
    textBoxParam.point2 = ivec2(300, 150);
    textBoxParam.color = ivec3(255, 255, 255);
    textBoxParam.textColor = ivec3(0, 0, 0);
    textBoxParam.point1Type = TagType::IVec;
    textBoxParam.point2Type = TagType::IVec;
    textBoxParam.colorType = TagType::IVec;
    textBoxParam.textColorType = TagType::IVec;
    GuiElement* tb = factory(guiElement::TEXTBOX, textBoxParam);
    nested2->addElement(tb);

    nested1->addElement(nested2);
    root->addElement(nested1);
    gui.setRootLayout(root);

    Layout* expectedRoot = new Layout();
    expectedRoot->setStart(vec2(0.0f, 0.0f));
    expectedRoot->setEnd(vec2(1.0f, 1.0f));
    expectedRoot->setActive(true);

    Layout* expectedNested1 = new Layout();
    expectedNested1->setStart(vec2(0.25f, 0.25f));
    expectedNested1->setEnd(vec2(0.75f, 0.75f));
    expectedNested1->setActive(true);

    ElementParameters pointParam;
    pointParam.point1 = ivec2(13, 14);
    pointParam.color = ivec3(101, 102, 103);
    pointParam.point1Type = TagType::IVec;
    pointParam.colorType = TagType::IVec;
    GuiElement* expectedPoint = factory(guiElement::POINT, pointParam);
    expectedNested1->addElement(expectedPoint);

    Layout* expectedNested2 = new Layout();
    expectedNested2->setStart(vec2(0.50f, 0.50f));
    expectedNested2->setEnd(vec2(1.00f, 1.00f));
    expectedNested2->setActive(true);

    ElementParameters triangleParam2;
    triangleParam2.point1 = ivec2(100, 100);
    triangleParam2.point2 = ivec2(150, 100);
    triangleParam2.point3 = ivec2(125, 150);
    triangleParam2.color = ivec3(255, 0, 0);
    triangleParam2.point1Type = TagType::IVec;
    triangleParam2.point2Type = TagType::IVec;
    triangleParam2.point3Type = TagType::IVec;
    triangleParam2.colorType = TagType::IVec;
    GuiElement* expectedTriangle = factory(guiElement::TRIANGLE, triangleParam2);
    expectedNested2->addElement(expectedTriangle);

    ElementParameters expectedButtonParam;
    expectedButtonParam.name = "deepButton";
    expectedButtonParam.callbackName = "testCallback";
    expectedButtonParam.text = "Deep";
    expectedButtonParam.point1 = ivec2(200, 200);
    expectedButtonParam.point2 = ivec2(280, 240);
    expectedButtonParam.color = ivec3(0, 0, 255);
    expectedButtonParam.point1Type = TagType::IVec;
    expectedButtonParam.point2Type = TagType::IVec;
    expectedButtonParam.colorType = TagType::IVec;
    GuiElement* expectedButton = factory(guiElement::BUTTON, expectedButtonParam);
    expectedNested2->addElement(expectedButton);

    ElementParameters expectedtextBoxParam;
    expectedtextBoxParam.point1 = ivec2(100, 100);
    expectedtextBoxParam.point2 = ivec2(300, 150);
    expectedtextBoxParam.color = ivec3(255, 255, 255);
    expectedtextBoxParam.textColor = ivec3(0, 0, 0);
    expectedtextBoxParam.point1Type = TagType::IVec;
    expectedtextBoxParam.point2Type = TagType::IVec;
    expectedtextBoxParam.colorType = TagType::IVec;
    expectedtextBoxParam.textColorType = TagType::IVec;
    GuiElement* etb = factory(guiElement::TEXTBOX, expectedtextBoxParam);
    expectedNested2->addElement(etb);

    expectedNested1->addElement(expectedNested2);
    expectedRoot->addElement(expectedNested1);

    gui.writeFile("testFiles/writeTest3.xml");
    gui.readFile("testFiles/writeTest3.xml");

    if (layoutComparison(gui.getRootLayout(), expectedRoot)) {
        failure = 1;
    }

    delete expectedRoot;

    if (failure) {
        std::cout << "writing test 3 (deep nested layouts) FAILED\n";
    }
    else {
        std::cout << "writing test 3 (deep nested layouts) passed\n";
    }

    return failure;
}