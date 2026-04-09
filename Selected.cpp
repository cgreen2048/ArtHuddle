#include "Selected.hpp"

Selected::Selected() {}

Selected::~Selected() {
    
}

Selected& Selected::getInstance() {
    static Selected instance;
    return instance;
}

void Selected::setSelectedElement(GuiElement* updatedElement) {

}

GuiElement* Selected::getSelectedElement() {
    return this->selectedElement;
}