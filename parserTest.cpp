#include "GUIFile.hpp"


int main() {
    std::string name = "input.xml";
    GUIFile x = GUIFile();
    
    x.readFile(name);

}