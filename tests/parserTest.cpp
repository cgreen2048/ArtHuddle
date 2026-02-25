#include "GUIFile.hpp"


int main() {
    // std::string name = "input.xml";
    // GUIFile x = GUIFile();
    
    // x.readFile(name);

    GUIFile::Line myLine = GUIFile::Line{vec2(),vec2(),vec3()};
    GUIFile::Box myBox = GUIFile::Box{vec2(),vec2(),vec3()};
    GUIFile::Point myPoint = GUIFile::Point{vec2(),vec3()};

    GUIFile gui = GUIFile();
    gui.addLine(myLine);
    gui.addBox(myBox);
    gui.addPoint(myPoint);
    gui.writeFile("out.xml");

}