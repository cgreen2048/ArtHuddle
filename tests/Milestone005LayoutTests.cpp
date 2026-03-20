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

    Line* l = new Line();
    l->setStart(toIVec2(50.5f, 902.47f), Line::TagType::Vec);
    l->setEnd(toIVec2(75.6f, 1024.6f), Line::TagType::Vec);
    l->setColor(toIVec3(244.0f, 245.0f, 103.3f), Line::TagType::Vec);
    expectedRoot->addElement(l);

    Box* b = new Box();
    b->setMin(toIVec2(250.3f, 122.5f), Box::TagType::Vec);
    b->setMax(toIVec2(420.34f, 254.9f), Box::TagType::Vec);
    b->setColor(ivec3(212, 22, 124), Box::TagType::Vec);
    expectedRoot->addElement(b);

    Point* p = new Point();
    p->setCoords(ivec2(480, 270), Point::TagType::IVec);
    p->setColor(ivec3(67, 200, 142), Point::TagType::IVec);
    expectedRoot->addElement(p);

    Triangle* t = new Triangle();
    t->setA(ivec2(100, 100), Triangle::TagType::IVec);
    t->setB(ivec2(150, 100), Triangle::TagType::IVec);
    t->setC(ivec2(125, 150), Triangle::TagType::IVec);
    t->setColor(ivec3(255, 0, 0), Triangle::TagType::IVec);
    expectedRoot->addElement(t);

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

    Triangle* t = new Triangle();
    t->setA(ivec2(100, 100), Triangle::TagType::IVec);
    t->setB(ivec2(150, 100), Triangle::TagType::IVec);
    t->setC(ivec2(125, 150), Triangle::TagType::IVec);
    t->setColor(ivec3(255, 0, 0), Triangle::TagType::IVec);
    expectedRoot->addElement(t);

    Layout* nested = new Layout();
    nested->setStart(vec2(0.25f, 0.25f));
    nested->setEnd(vec2(0.75f, 0.75f));
    nested->setActive(true);

    Point* p = new Point();
    p->setCoords(ivec2(480, 270), Point::TagType::IVec);
    p->setColor(ivec3(67, 200, 142), Point::TagType::IVec);
    nested->addElement(p);

    Box* b = new Box();
    b->setMin(toIVec2(250.3f, 122.5f), Box::TagType::Vec);
    b->setMax(toIVec2(420.34f, 254.9f), Box::TagType::Vec);
    b->setColor(ivec3(212, 22, 124), Box::TagType::Vec);
    nested->addElement(b);

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

    Line* l = new Line();
    l->setStart(toIVec2(1.1f, 2.2f), Line::TagType::Vec);
    l->setEnd(toIVec2(3.3f, 4.4f), Line::TagType::Vec);
    l->setColor(ivec3(10, 20, 30), Line::TagType::IVec);
    expectedRoot->addElement(l);

    Layout* nested = new Layout();
    nested->setStart(vec2(0.10f, 0.20f));
    nested->setEnd(vec2(0.90f, 0.95f));
    nested->setActive(true);

    Point* p = new Point();
    p->setCoords(ivec2(13, 14), Point::TagType::IVec);
    p->setColor(ivec3(101, 102, 103), Point::TagType::IVec);
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

    Line* l = new Line();
    l->setStart(toIVec2(50.5f, 902.47f), Line::TagType::Vec);
    l->setEnd(toIVec2(75.6f, 1024.6f), Line::TagType::Vec);
    l->setColor(toIVec3(244.0f, 245.0f, 103.3f), Line::TagType::Vec);
    root->addElement(l);

    Box* b = new Box();
    b->setMin(toIVec2(250.3f, 122.5f), Box::TagType::Vec);
    b->setMax(toIVec2(420.34f, 254.9f), Box::TagType::Vec);
    b->setColor(ivec3(212, 22, 124), Box::TagType::Vec);
    root->addElement(b);

    gui.setRootLayout(root);

    Layout* expectedRoot = new Layout();
    expectedRoot->setStart(vec2(0.0f, 0.0f));
    expectedRoot->setEnd(vec2(1.0f, 1.0f));
    expectedRoot->setActive(true);

    Line* el = new Line();
    el->setStart(toIVec2(50.5f, 902.47f), Line::TagType::Vec);
    el->setEnd(toIVec2(75.6f, 1024.6f), Line::TagType::Vec);
    el->setColor(toIVec3(244.0f, 245.0f, 103.3f), Line::TagType::Vec);
    expectedRoot->addElement(el);

    Box* eb = new Box();
    eb->setMin(toIVec2(250.3f, 122.5f), Box::TagType::Vec);
    eb->setMax(toIVec2(420.34f, 254.9f), Box::TagType::Vec);
    eb->setColor(ivec3(212, 22, 124), Box::TagType::Vec);
    expectedRoot->addElement(eb);

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

    Point* p1 = new Point();
    p1->setCoords(ivec2(13, 14), Point::TagType::IVec);
    p1->setColor(ivec3(101, 102, 103), Point::TagType::IVec);
    nested1->addElement(p1);

    Layout* nested2 = new Layout();
    nested2->setStart(vec2(0.50f, 0.50f));
    nested2->setEnd(vec2(1.00f, 1.00f));
    nested2->setActive(true);

    Triangle* t = new Triangle();
    t->setA(ivec2(100, 100), Triangle::TagType::IVec);
    t->setB(ivec2(150, 100), Triangle::TagType::IVec);
    t->setC(ivec2(125, 150), Triangle::TagType::IVec);
    t->setColor(ivec3(255, 0, 0), Triangle::TagType::IVec);
    nested2->addElement(t);

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

    Point* expectedPoint = new Point();
    expectedPoint->setCoords(ivec2(13, 14), Point::TagType::IVec);
    expectedPoint->setColor(ivec3(101, 102, 103), Point::TagType::IVec);
    expectedNested1->addElement(expectedPoint);

    Layout* expectedNested2 = new Layout();
    expectedNested2->setStart(vec2(0.50f, 0.50f));
    expectedNested2->setEnd(vec2(1.00f, 1.00f));
    expectedNested2->setActive(true);

    Triangle* expectedTriangle = new Triangle();
    expectedTriangle->setA(ivec2(100, 100), Triangle::TagType::IVec);
    expectedTriangle->setB(ivec2(150, 100), Triangle::TagType::IVec);
    expectedTriangle->setC(ivec2(125, 150), Triangle::TagType::IVec);
    expectedTriangle->setColor(ivec3(255, 0, 0), Triangle::TagType::IVec);
    expectedNested2->addElement(expectedTriangle);

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