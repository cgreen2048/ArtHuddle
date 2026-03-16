#include "../vec2.hpp"
#include "../vec3.hpp"
#include "../GUIFile.hpp"
#include "../Line.hpp"
#include "../Box.hpp"
#include "../Point.hpp"
#include "../Factory.hpp"
#include "../GuiElement.hpp"

int readTest1();
int readTest2();
int readTest3();
int readTest4();
int readTest5();
int writeTest1();
int writeTest2();
int writeTest3();
int elementsComparison(const std::vector<GuiElement*>& actual, const std::vector<GuiElement*>& expected);
static int toInt(float x);
static ivec2 toIVec2(float x, float y);
static ivec3 toIVec3(float x, float y, float z);
void deleteAll(std::vector<GuiElement*>& v);


int main() {
    int failure = 0;

    if (readTest1()) {
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

void deleteAll(std::vector<GuiElement*>& v) {
    for (auto* p : v) {
        delete p;
    }
    v.clear();
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

int elementsComparison(const std::vector<GuiElement*>& actual, const std::vector<GuiElement*>& expected)
{
    if (actual.size() != expected.size()) {
        return 1;
    }

    for (size_t i = 0; i < actual.size(); ++i) {

        GuiElement* a = actual[i];
        GuiElement* e = expected[i];

        // ---- Line ----
        if (auto* aLine = dynamic_cast<Line*>(a)) {
            auto* eLine = dynamic_cast<Line*>(e);
            if (!eLine) {
                return 1;
            }
            if (*aLine != *eLine) {
                return 1; // uses Line::operator!= or operator==
            }
        }

        // ---- Box ----
        else if (auto* aBox = dynamic_cast<Box*>(a)) {
            auto* eBox = dynamic_cast<Box*>(e);
            if (!eBox) {
                return 1;
            }
            if (*aBox != *eBox) {
                return 1;
            }
        }

        // ---- Point ----
        else if (auto* aPoint = dynamic_cast<Point*>(a)) {
            auto* ePoint = dynamic_cast<Point*>(e);
            if (!ePoint) {
                return 1;
            }
            if (*aPoint != *ePoint) {
                return 1;
            }
        }

        // ---- Triangle ----
        else if (auto* aTriangle = dynamic_cast<Triangle*>(a)) {
            auto* eTriangle = dynamic_cast<Triangle*>(e);
            if (!eTriangle) {
                return 1;
            }
            if (*aTriangle != *eTriangle) {
                return 1;
            }
        }
    }


    return 0;
}



int readTest1() {
    int failure = 0;

    std::vector<GuiElement*> expected;
    
    auto* l = new Line();
    l->setStart(toIVec2(50.5f, 902.47f), Line::TagType::Vec);
    l->setEnd(toIVec2(75.6f, 1024.6f), Line::TagType::Vec);
    l->setColor(toIVec3(244.0f, 245.0f, 103.3f), Line::TagType::Vec);

    auto* b = new Box();
    b->setMin(toIVec2(250.3f, 122.5f), Box::TagType::Vec);
    b->setMax(toIVec2(420.34f, 254.9f), Box::TagType::Vec);   // lround(254.9)=255
    b->setColor(ivec3(212, 22, 124), Box::TagType::Vec);

    auto* p = new Point();
    p->setCoords(ivec2(480, 270), Point::TagType::IVec); // if the XML uses <ivec2>
    p->setColor(ivec3(67, 200, 142), Point::TagType::IVec); // if <ivec3>

    auto* t = new Triangle();
    t->setA(ivec2(100, 100), Triangle::TagType::IVec);
    t->setB(ivec2(150, 100), Triangle::TagType::IVec);
    t->setC(ivec2(125, 150), Triangle::TagType::IVec);
    t->setColor(ivec3(255, 0, 0), Triangle::TagType::IVec);
    
    expected.push_back(l);
    expected.push_back(b);
    expected.push_back(p);
    expected.push_back(t);
    
    GUIFile gui = GUIFile();
    gui.readFile("testFiles/input.xml");

    if (elementsComparison(gui.getElements(), expected)) {
        failure = 1;
    }

    deleteAll(expected);

    if (failure) {
        std::cout << "reading test 1 (good input) FAILED\n";
    }
    else {
        std::cout << "reading test 1 (good input) passed\n";
    }

    return failure;
}

int readTest2() {
    int failure = 0;

    GUIFile gui = GUIFile();
    gui.readFile("testFiles/badInput.xml");


    if (gui.getElements().size() != 0) {
        failure = 1;
    }

    if (failure) {
        std::cout << "reading test 2 (invalid input file) FAILED\n";
    }
    else {
        std::cout << "reading test 2 (invalid input file) passed\n";
    }

    return failure;
}

int readTest3() {
    int failure = 0;

    GUIFile gui = GUIFile();
    gui.readFile("testFiles/malformedVector.xml");

    if (gui.getElements().size() != 0) {
        failure = 1;
    }

    if (failure) {
        std::cout << "reading test 3 (malformed vector) FAILED\n";
    }
    else {
        std::cout << "reading test 3 (malformed vector) passed\n";
    }

    return failure;
}

int readTest4() {
    int failure = 0;

    std::vector<GuiElement*> expected;
    
    auto* l = new Line();
    l->setStart(toIVec2(50.5f, 902.47f), Line::TagType::Vec);
    l->setEnd(toIVec2(75.6f, 1024.6f), Line::TagType::Vec);
    l->setColor(toIVec3(244.0f, 245.0f, 103.3f), Line::TagType::Vec);

    auto* b = new Box();
    b->setMin(toIVec2(250.3f, 122.5f), Box::TagType::Vec);
    b->setMax(toIVec2(420.34f, 254.9f), Box::TagType::Vec);
    b->setColor(ivec3(212, 22, 124), Box::TagType::Vec);

    auto* p = new Point();
    p->setCoords(ivec2(480, 270), Point::TagType::IVec);
    p->setColor(ivec3(67, 200, 142), Point::TagType::IVec); 
    
    expected.push_back(l);
    expected.push_back(b);
    expected.push_back(p);

    GUIFile gui = GUIFile();
    gui.readFile("testFiles/oddSpacing.xml");

    if (elementsComparison(gui.getElements(), expected)) {
        failure = 1;
    }

    deleteAll(expected);

    if (failure) {
        std::cout << "reading test 4 (weird spacing) FAILED\n";
    }
    else {
        std::cout << "reading test 4 (weird spacing) passed\n";
    }

    return failure;
}

int readTest5() {
    int failure = 0;

     std::vector<GuiElement*> expected;
    
    auto* l = new Line();
    l->setStart(toIVec2(50.5f, 902.47f), Line::TagType::Vec);
    l->setEnd(toIVec2(75.6f, 1024.6f), Line::TagType::Vec);
    l->setColor(toIVec3(244.0f, 245.0f, 103.3f), Line::TagType::Vec);

    auto* b = new Box();
    b->setMin(toIVec2(250.3f, 122.5f), Box::TagType::Vec);
    b->setMax(toIVec2(420.34f, 254.9f), Box::TagType::Vec);
    b->setColor(ivec3(212, 22, 124), Box::TagType::Vec);

    
    expected.push_back(l);
    expected.push_back(b);

    GUIFile gui = GUIFile();
    gui.readFile("testFiles/missingTag.xml");

    if (elementsComparison(gui.getElements(), expected)) {
        failure = 1;
    }

    deleteAll(expected);

    if (failure) {
        std::cout << "reading test 5 (missing tag) FAILED\n";
    }
    else {
        std::cout << "reading test 5 (missing tag) passed\n";
    }

    return failure;
}

int writeTest1() {
    int failure = 0;

    std::vector<GuiElement*> expected;
    
    auto* l = new Line();
    l->setStart(toIVec2(50.5f, 902.47f), Line::TagType::Vec);
    l->setEnd(toIVec2(75.6f, 1024.6f), Line::TagType::Vec);
    l->setColor(toIVec3(244.0f, 245.0f, 103.3f), Line::TagType::Vec);

    auto* b = new Box();
    b->setMin(toIVec2(250.3f, 122.5f), Box::TagType::Vec);
    b->setMax(toIVec2(420.34f, 254.9f), Box::TagType::Vec);
    b->setColor(ivec3(212, 22, 124), Box::TagType::Vec);

    auto* p = new Point();
    p->setCoords(ivec2(480, 270), Point::TagType::IVec);
    p->setColor(ivec3(67, 200, 142), Point::TagType::IVec); 

    auto* t = new Triangle();
    t->setA(ivec2(100, 100), Triangle::TagType::IVec);
    t->setB(ivec2(150, 100), Triangle::TagType::IVec);
    t->setC(ivec2(125, 150), Triangle::TagType::IVec);
    t->setColor(ivec3(255, 0, 0), Triangle::TagType::IVec);
    
    expected.push_back(l);
    expected.push_back(b);
    expected.push_back(p);
    expected.push_back(t);

    GUIFile gui = GUIFile();
    gui.addLine(new Line(*l));
    gui.addBox(new Box(*b));
    gui.addPoint(new Point(*p));
    gui.addTriangle(new Triangle(*t));
    gui.writeFile("testFiles/output.xml");
    
    gui.readFile("testFiles/output.xml");
    
   if (elementsComparison(gui.getElements(), expected)) {
        failure = 1;
    }

    deleteAll(expected);

    
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

    GUIFile gui = GUIFile();
    gui.writeFile("testFiles/empty.xml");

    gui.readFile("testFiles/empty.xml");
    
    if (gui.getElements().size() != 0) {
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

    GUIFile gui = GUIFile();

    std::vector<GuiElement*> expected;

    auto* l1 = new Line();
    l1->setStart(toIVec2(1.1f, 2.2f), Line::TagType::Vec);
    l1->setEnd(toIVec2(3.3f, 4.4f), Line::TagType::Vec);
    l1->setColor(ivec3(10, 20, 30), Line::TagType::IVec);
    expected.push_back(l1);
    gui.addLine(new Line(*l1));

    auto* l2 = new Line();
    l2->setStart(toIVec2(5.5f, 6.6f), Line::TagType::Vec);
    l2->setEnd(toIVec2(7.7f, 8.8f), Line::TagType::Vec);
    l2->setColor(ivec3(40, 50, 60), Line::TagType::IVec);
    expected.push_back(l2);
    gui.addLine(new Line(*l2));

    auto* l3 = new Line();
    l3->setStart(toIVec2(9.9f, 10.01f), Line::TagType::Vec);
    l3->setEnd(toIVec2(11.11f, 12.12f), Line::TagType::Vec);
    l3->setColor(ivec3(70, 80, 90), Line::TagType::IVec);
    expected.push_back(l3);
    gui.addLine(new Line(*l3));

    auto* b1 = new Box();
    b1->setMin(toIVec2(100.1f, 200.2f), Box::TagType::Vec);
    b1->setMax(toIVec2(300.3f, 400.4f), Box::TagType::Vec);
    b1->setColor(toIVec3(1.0, 2.0, 3.0), Box::TagType::Vec);
    expected.push_back(b1);
    gui.addBox(new Box(*b1));

    auto* b2 = new Box();
    b2->setMin(toIVec2(500.5f, 600.6f), Box::TagType::Vec);
    b2->setMax(toIVec2(700.7f, 800.8f), Box::TagType::Vec);
    b2->setColor(ivec3(4, 5, 6), Box::TagType::IVec);
    expected.push_back(b2);
    gui.addBox(new Box(*b2));

    auto* p1 = new Point();
    p1->setCoords(ivec2(13, 14), Point::TagType::IVec);
    p1->setColor(ivec3(101, 102, 103), Point::TagType::IVec);
    expected.push_back(p1);
    gui.addPoint(new Point(*p1));

    auto* p2 = new Point();
    p2->setCoords(ivec2(15, 16), Point::TagType::IVec);
    p2->setColor(ivec3(104, 105, 106), Point::TagType::IVec);
    expected.push_back(p2);
    gui.addPoint(new Point(*p2));

    auto* p3 = new Point();
    p3->setCoords(ivec2(17, 18), Point::TagType::IVec);
    p3->setColor(ivec3(107, 108, 109), Point::TagType::IVec);
    expected.push_back(p3);
    gui.addPoint(new Point(*p3));

    auto* p4 = new Point();
    p4->setCoords(ivec2(19, 20), Point::TagType::IVec);
    p4->setColor(ivec3(110, 111, 112), Point::TagType::IVec);
    expected.push_back(p4);
    gui.addPoint(new Point(*p4));

    auto* t1 = new Triangle();
    t1->setA(ivec2(100, 100), Triangle::TagType::IVec);
    t1->setB(ivec2(150, 100), Triangle::TagType::IVec);
    t1->setC(ivec2(125, 150), Triangle::TagType::IVec);
    t1->setColor(ivec3(255, 0, 0), Triangle::TagType::IVec);
    expected.push_back(t1);
    gui.addTriangle(new Triangle(*t1));

    auto* t2 = new Triangle();
    t2->setA(ivec2(100, 100), Triangle::TagType::IVec);
    t2->setB(ivec2(150, 100), Triangle::TagType::IVec);
    t2->setC(ivec2(125, 150), Triangle::TagType::IVec);
    t2->setColor(ivec3(255, 0, 0), Triangle::TagType::IVec);
    expected.push_back(t2);
    gui.addTriangle(new Triangle(*t2));

    
    gui.writeFile("testFiles/multipleSurfaceObjects.xml");

    gui.readFile("testFiles/multipleSurfaceObjects.xml");
    

    if (elementsComparison(gui.getElements(), expected)) {
        failure = 1;
    }

    deleteAll(expected);

    if (failure) {
        std::cout << "writing test 3 (multiple surface objects) FAILED\n";
    }
    else {
        std::cout << "writing test 3 (multiple surface objects) passed\n";
    }

    return failure;

}
