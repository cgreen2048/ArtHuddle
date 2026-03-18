#include "GuiElement.hpp"

GuiElement::GuiElement() {
    
}
GuiElement::~GuiElement() {
    
}
void GuiElement::draw(){
    
}
void GuiElement::writeXml(std::ostream& out, int depth) const{

}
void GuiElement::setScreen(Screen* target) {
    this->screen = target;
}
void GuiElement::setParentStart(const ivec2& start) {
    this->parentStart = start;
}
void GuiElement::setParentEnd(const ivec2& end) {
    this->parentEnd = end;
}
Screen* GuiElement::getScreen() {
    return this->screen;
}