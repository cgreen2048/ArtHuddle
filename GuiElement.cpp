#include "GuiElement.hpp"

GuiElement::GuiElement() {
    

}
GuiElement::~GuiElement() {
    
}
void GuiElement::draw(){
    
}
void GuiElement::setScreen(Screen* target) {
    this->screen = target;
}
Screen* GuiElement::getScreen() {
    return this->screen;
}