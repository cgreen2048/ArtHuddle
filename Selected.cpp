#include "Selected.hpp"

Selected::Selected() {}

Selected::~Selected() {
    
}

Selected& Selected::getInstance() {
    static Selected instance;
    return instance;
}

void Selected::setSelectedElement(GuiElement* updatedElement) {
    this->selectedElement = updatedElement;
}

GuiElement* Selected::getSelectedElement() {
    return this->selectedElement;
}