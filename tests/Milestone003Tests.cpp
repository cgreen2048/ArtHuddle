#include "../vec2.hpp"
#include "../vec3.hpp"
#include "../GUIFile.hpp"
#include "../Line.hpp"
#include "../Box.hpp"
#include "../Point.hpp"

int readTest1();
int readTest2();
int readTest3();
int readTest4();
int readTest5();
int writeTest1();
int writeTest2();
int writeTest3();
int elementsComparison(const std::vector<GuiElement*>& actual, const std::vector<GuiElement*>& expected);
void deleteAll(std::vector<GuiElement*>& v);


int main() {
    int failure = 0;

    if (readTest1()) {
        failure = 1;
    }

    // if (readTest2()) {
    //     failure = 1;
    // }

    // if (readTest3()) {
    //     failure = 1;
    // }
    // if (readTest4()) {
    //     failure = 1;
    // }
    // if (readTest5()) {
    //     failure = 1;
    // }
    // if (writeTest1()) {
    //     failure = 1;
    // }
    // if (writeTest2()) {
    //     failure = 1;
    // }
    // if (writeTest3()) {
    //     failure = 1;
    // }


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

    }

    return 0;
}



int readTest1() {
    int failure = 0;

    std::vector<GuiElement*> expected;
    expected.push_back(new Line(vec2(50.5, 902.47), vec2(75.6, 1024.6), vec3(244.0, 245.0, 103.3)));
    expected.push_back(new Box(vec2(250.3, 122.5), vec2(420.34, 254.9), vec3(212, 22, 124)));
    expected.push_back(new Point(vec2(480, 270), vec3(67, 200, 142)));

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

// int readTest2() {
//     int failure = 0;

//     GUIFile gui = GUIFile();
//     gui.readFile("testFiles/badInput.xml");

//     if ((gui.getLines().size() != 0) || (gui.getBoxes().size() != 0) || (gui.getPoints().size() != 0)) {
//         failure = 1;
//     }

//     if (failure) {
//         std::cout << "reading test 2 (invalid input file) FAILED\n";
//     }
//     else {
//         std::cout << "reading test 2 (invalid input file) passed\n";
//     }

//     return failure;
// }

// int readTest3() {
//     int failure = 0;

//     GUIFile gui = GUIFile();
//     gui.readFile("testFiles/malformedVector.xml");

//     std::vector<GUIFile::Line> guiLines = gui.getLines();
//     std::vector<GUIFile::Box> guiBoxes = gui.getBoxes();
//     std::vector<GUIFile::Point> guiPoints = gui.getPoints();

//     if ((gui.getLines().size() != 0) || (gui.getBoxes().size() != 0) || (gui.getPoints().size() != 0)) {
//         failure = 1;
//     }

//     if (failure) {
//         std::cout << "reading test 3 (malformed vector) FAILED\n";
//     }
//     else {
//         std::cout << "reading test 3 (malformed vector) passed\n";
//     }

//     return failure;
// }

// int readTest4() {
//     int failure = 0;

//     std::vector<GUIFile::Line> lines;
//     std::vector<GUIFile::Box> boxes;
//     std::vector<GUIFile::Point> points;


//     lines.push_back(GUIFile::Line{vec2(50.5, 902.47), vec2(75.6, 1024.6), vec3(244.0, 245.0, 103.3)});
//     boxes.push_back(GUIFile::Box{vec2(250.3, 122.5), vec2(420.34, 254.9), vec3(212, 22, 124)});
//     points.push_back(GUIFile::Point{vec2(480, 270), vec3(67, 200, 142)});

//     GUIFile gui = GUIFile();
//     gui.readFile("testFiles/oddSpacing.xml");

//     std::vector<GUIFile::Line> guiLines = gui.getLines();
//     std::vector<GUIFile::Box> guiBoxes = gui.getBoxes();
//     std::vector<GUIFile::Point> guiPoints = gui.getPoints();

//     if (linesComparsion(lines, guiLines)) {
//         failure = 1;
//     }
//     if (boxesComparsion(boxes, guiBoxes)) {
//         failure = 1;
//     }
//     if (pointsComparsion(points, guiPoints)) {
//         failure = 1;
//     }

//     if (failure) {
//         std::cout << "reading test 4 (weird spacing) FAILED\n";
//     }
//     else {
//         std::cout << "reading test 4 (weird spacing) passed\n";
//     }

//     return failure;
// }

// int readTest5() {
//     int failure = 0;

//     std::vector<GUIFile::Line> lines;
//     std::vector<GUIFile::Box> boxes;
//     std::vector<GUIFile::Point> points;


//     lines.push_back(GUIFile::Line{vec2(50.5, 902.47), vec2(75.6, 1024.6), vec3(244.0, 245.0, 103.3)});
//     boxes.push_back(GUIFile::Box{vec2(250.3, 122.5), vec2(420.34, 254.9), vec3(212, 22, 124)});
//     points.push_back(GUIFile::Point{vec2(480, 270), vec3(67, 200, 142)});

//     GUIFile gui = GUIFile();
//     gui.readFile("testFiles/missingTag.xml");

//     std::vector<GUIFile::Line> guiLines = gui.getLines();
//     std::vector<GUIFile::Box> guiBoxes = gui.getBoxes();
//     std::vector<GUIFile::Point> guiPoints = gui.getPoints();

//     if (linesComparsion(lines, guiLines)) {
//         failure = 1;
//     }
//     if (boxesComparsion(boxes, guiBoxes)) {
//         failure = 1;
//     }
//     if (guiPoints.size() != 0) {
//         failure = 1;
//     }


//     if (failure) {
//         std::cout << "reading test 5 (missing tag) FAILED\n";
//     }
//     else {
//         std::cout << "reading test 5 (missing tag) passed\n";
//     }

//     return failure;
// }

// int writeTest1() {
//     int failure = 0;

//     std::vector<GUIFile::Line> lines;
//     std::vector<GUIFile::Box> boxes;
//     std::vector<GUIFile::Point> points;


//     lines.push_back(GUIFile::Line{vec2(50.5, 902.47), vec2(75.6, 1024.6), vec3(244.0, 245.0, 103.3)});
//     boxes.push_back(GUIFile::Box{vec2(250.3, 122.5), vec2(420.34, 254.9), vec3(212, 22, 124)});
//     points.push_back(GUIFile::Point{vec2(480, 270), vec3(67, 200, 142)});

//     GUIFile gui = GUIFile();
//     gui.addLine(GUIFile::Line{vec2(50.5, 902.47), vec2(75.6, 1024.6), vec3(244.0, 245.0, 103.3)});
//     gui.addBox(GUIFile::Box{vec2(250.3, 122.5), vec2(420.34, 254.9), vec3(212, 22, 124)});
//     gui.addPoint(GUIFile::Point{vec2(480, 270), vec3(67, 200, 142)});
//     gui.writeFile("testFiles/output.xml");
    
//     gui.readFile("testFiles/output.xml");
//     std::vector<GUIFile::Line> guiLines = gui.getLines();
//     std::vector<GUIFile::Box> guiBoxes = gui.getBoxes();
//     std::vector<GUIFile::Point> guiPoints = gui.getPoints();

//     if (linesComparsion(lines, guiLines)) {
//         failure = 1;
//     }
//     if (boxesComparsion(boxes, guiBoxes)) {
//         failure = 1;
//     }
//     if (pointsComparsion(points, guiPoints)) {
//         failure = 1;
//     }

    
//     if (failure) {
//         std::cout << "writing test 1 (write then read) FAILED\n";
//     }
//     else {
//         std::cout << "writing test 1 (write then read) passed\n";
//     }

//     return failure;
// }

// int writeTest2() {
//     int failure = 0;

//     GUIFile gui = GUIFile();
//     gui.writeFile("testFiles/empty.xml");

//     gui.readFile("testFiles/empty.xml");
//     std::vector<GUIFile::Line> guiLines = gui.getLines();
//     std::vector<GUIFile::Box> guiBoxes = gui.getBoxes();
//     std::vector<GUIFile::Point> guiPoints = gui.getPoints();


//     if (guiLines.size() != 0) {
//         failure = 1;
//     }
//     if (guiBoxes.size() != 0) {
//         failure = 1;
//     }
//     if (guiPoints.size() != 0) {
//         failure = 1;
//     }


//     if (failure) {
//         std::cout << "writing test 2 (empty tag) FAILED\n";
//     }
//     else {
//         std::cout << "writing test 2 (empty tag) passed\n";
//     }

//     return failure;
// }

// int writeTest3() {
//     int failure = 0;

//     GUIFile gui = GUIFile();

//     std::vector<GUIFile::Line> expLines = {
//             {vec2(1.1, 2.2), vec2(3.3, 4.4), vec3(10.0, 20.0, 30.0), GUIFile::TagType::Vec, GUIFile::TagType::Vec, GUIFile::TagType::IVec},
//             {vec2(5.5, 6.6), vec2(7.7, 8.8), vec3(40.0, 50.0, 60.0), GUIFile::TagType::Vec, GUIFile::TagType::Vec, GUIFile::TagType::IVec},
//             {vec2(9.9, 10.01), vec2(11.11, 12.12), vec3(70.0, 80.0, 90.0), GUIFile::TagType::Vec, GUIFile::TagType::Vec, GUIFile::TagType::IVec}
//     };

//     std::vector<GUIFile::Box> expBoxes = {
//         {vec2(100.1, 200.2), vec2(300.3, 400.4), vec3(1.0, 2.0, 3.0)},
//         {vec2(500.5, 600.6), vec2(700.7, 800.8), vec3(4.0, 5.0, 6.0)}
//     };

//     std::vector<GUIFile::Point> expPoints = {
//         {vec2(13.0, 14.0), vec3(101.0, 102.0, 103.0), GUIFile::TagType::IVec, GUIFile::TagType::IVec},
//         {vec2(15.0, 16.0), vec3(104.0, 105.0, 106.0), GUIFile::TagType::IVec, GUIFile::TagType::IVec},
//         {vec2(17.0, 18.0), vec3(107.0, 108.0, 109.0)},
//         {vec2(19.0, 20.0), vec3(110.0, 111.0, 112.0)}
//     };

//     for (const auto& l : expLines) {
//         gui.addLine(l);
//     }
//     for (const auto& b : expBoxes) {
//         gui.addBox(b);
//     }
//     for (const auto& p : expPoints) {
//         gui.addPoint(p);
//     }
//     gui.writeFile("testFiles/multipleSurfaceObjects.xml");

//     gui.readFile("testFiles/multipleSurfaceObjects.xml");
//     std::vector<GUIFile::Line> guiLines = gui.getLines();
//     std::vector<GUIFile::Box> guiBoxes = gui.getBoxes();
//     std::vector<GUIFile::Point> guiPoints = gui.getPoints();

//     if (linesComparsion(expLines, guiLines)) {
//         failure = 1;
//     }
//     if (boxesComparsion(expBoxes, guiBoxes)) {
//         failure = 1;
//     }
//     if (pointsComparsion(expPoints, guiPoints)) {
//         failure = 1;
//     }

//     if (failure) {
//         std::cout << "writing test 3 (multiple surface objects) FAILED\n";
//     }
//     else {
//         std::cout << "writing test 3 (multiple surface objects) passed\n";
//     }

//     return failure;

// }
