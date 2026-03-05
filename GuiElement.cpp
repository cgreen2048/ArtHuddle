#include "GuiElement.hpp"

GuiElement::GuiElement() {
    
}
GuiElement::~GuiElement() {
    
}
void GuiElement::draw(){
    
}
void GuiElement::writeXml(std::ofstream& out) const{

}
void GuiElement::setScreen(Screen* target) {
    this->screen = target;
}