#include "../vec2.hpp"
#include "../vec3.hpp"
#include "../GUIFile.hpp"

int readTest1();
int readTest2();
int readTest3();
int readTest4();

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


    if (failure) {
        std::cout << "IMPLEMENTATION(S) FAILED, REVIEW TEST RESULTS\n";
    }
    else {
        std::cout << "ALL TESTS PASSED\n";
    }

    return failure;
}

int readTest1() {
    int failure = 0;

    std::vector<GUIFile::Line> lines;
    std::vector<GUIFile::Box> boxes;
    std::vector<GUIFile::Point> points;


    lines.push_back(GUIFile::Line{vec2(50.5, 902.47), vec2(75.6, 1024.6), vec3(244.0, 245.0, 103.3)});
    boxes.push_back(GUIFile::Box{vec2(250.3, 122.5), vec2(420.34, 254.9), vec3(212, 22, 124)});
    points.push_back(GUIFile::Point{vec2(480, 270), vec3(67, 200, 142)});

    GUIFile gui = GUIFile();
    gui.readFile("../input.xml");

    std::vector<GUIFile::Line> guiLines = gui.getLines();
    std::vector<GUIFile::Box> guiBoxes = gui.getBoxes();
    std::vector<GUIFile::Point> guiPoints = gui.getPoints();

    if (lines.size() == guiLines.size()) {
        for (GUIFile::Line l: lines) {
            for (GUIFile::Line gl: gui.getLines()) {
                if ((l.start != gl.start) || (l.end != gl.end) || (l.color != gl.color)) {
                    failure = 1;
                }
            }
        }
    }
    else {
        failure = 1;
    }

    if (boxes.size() == guiBoxes.size()) {
        for (GUIFile::Box b: boxes) {
            for (GUIFile::Box gb: gui.getBoxes()) {
                if ((b.min != gb.min) || (b.max != gb.max) || (b.color != gb.color)) {
                    failure = 1;
                }
            }
        }
    }
    else {
        failure = 1;
    }

    if (points.size() == guiPoints.size()) {
        for (GUIFile::Point p: points) {
            for (GUIFile::Point gp: gui.getPoints()) {
                if ((p.position != gp.position) || (p.color != gp.color)) {
                    failure = 1;
                }
            }
        }
    }
    else {
        failure = 1;
    }

    if (failure) {
        std::cout << "reading test (good input) FAILED\n";
    }
    else {
        std::cout << "reading test (good input) passed\n";
    }

    return failure;
}

int readTest2() {
    int failure = 0;

    GUIFile gui = GUIFile();
    gui.readFile("../badInput.xml");

    if ((gui.getLines().size() != 0) || (gui.getBoxes().size() != 0) || (gui.getPoints().size() != 0)) {
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

int readTest3() {   // need to kill GUIFile if line, box, or point has too few or too many inputs
    int failure = 0;

    std::vector<GUIFile::Line> lines;
    std::vector<GUIFile::Box> boxes;
    std::vector<GUIFile::Point> points;


    lines.push_back(GUIFile::Line{vec2(50.5, 902.47), vec2(75.6, 1024.6), vec3(244.0, 245.0, 103.3)});
    boxes.push_back(GUIFile::Box{vec2(250.3, 122.5), vec2(420.34, 254.9), vec3(212, 22, 124)});
    points.push_back(GUIFile::Point{vec2(480, 270), vec3(67, 200, 142)});

    GUIFile gui = GUIFile();
    gui.readFile("../malformed.xml");

    std::vector<GUIFile::Line> guiLines = gui.getLines();
    std::vector<GUIFile::Box> guiBoxes = gui.getBoxes();
    std::vector<GUIFile::Point> guiPoints = gui.getPoints();

    std::cout << gui.getLines().size();
    std::cout << gui.getBoxes().size();
    std::cout << gui.getPoints().size();

    if ((gui.getLines().size() != 0) || (gui.getBoxes().size() != 0) || (gui.getPoints().size() != 0)) {
        failure = 1;
    }

    if (failure) {
        std::cout << "reading test 3 (malformed input) FAILED\n";
    }
    else {
        std::cout << "reading test 3 (malformed input) passed\n";
    }

    return failure;
}

int readTest4() {
    int failure = 0;

    std::vector<GUIFile::Line> lines;
    std::vector<GUIFile::Box> boxes;
    std::vector<GUIFile::Point> points;


    lines.push_back(GUIFile::Line{vec2(50.5, 902.47), vec2(75.6, 1024.6), vec3(244.0, 245.0, 103.3)});
    boxes.push_back(GUIFile::Box{vec2(250.3, 122.5), vec2(420.34, 254.9), vec3(212, 22, 124)});
    points.push_back(GUIFile::Point{vec2(480, 270), vec3(67, 200, 142)});

    GUIFile gui = GUIFile();
    gui.readFile("../oddSpacing.xml");

    std::vector<GUIFile::Line> guiLines = gui.getLines();
    std::vector<GUIFile::Box> guiBoxes = gui.getBoxes();
    std::vector<GUIFile::Point> guiPoints = gui.getPoints();

    if (lines.size() == guiLines.size()) {
        for (GUIFile::Line l: lines) {
            for (GUIFile::Line gl: gui.getLines()) {
                if ((l.start != gl.start) || (l.end != gl.end) || (l.color != gl.color)) {
                    failure = 1;
                }
            }
        }
    }
    else {
        failure = 1;
    }

    if (boxes.size() == guiBoxes.size()) {
        for (GUIFile::Box b: boxes) {
            for (GUIFile::Box gb: gui.getBoxes()) {
                if ((b.min != gb.min) || (b.max != gb.max) || (b.color != gb.color)) {
                    failure = 1;
                }
            }
        }
    }
    else {
        failure = 1;
    }

    if (points.size() == guiPoints.size()) {
        for (GUIFile::Point p: points) {
            for (GUIFile::Point gp: gui.getPoints()) {
                if ((p.position != gp.position) || (p.color != gp.color)) {
                    failure = 1;
                }
            }
        }
    }
    else {
        failure = 1;
    }

    if (failure) {
        std::cout << "reading test 4 (weird spacing) FAILED\n";
    }
    else {
        std::cout << "reading test 4 (weird spacing) passed\n";
    }

    return failure;
}