#include "ArtHuddle/utility/GUIFile.hpp"


int main() {
    // std::string name = "input.xml";
    // GUIFile x = GUIFile();
    
    // x.readFile(name);

    GUIFile gui = GUIFile();
    gui.addLine(new Line{vec2(), vec2(), vec3()});
    gui.addBox(new Box{vec2(), vec2(), vec3()});
    gui.addPoint(new Point{vec2(), vec3()});
    gui.addTriangle(new Triangle{vec2(), vec2(), vec2(), vec3()});
    gui.writeFile("out.xml");

}