#include "GuiElement.hpp"

GuiElement::GuiElement() {
    
}
GuiElement::~GuiElement() {
    
}
void GuiElement::draw(){
    
}
void GuiElement::writeXml(std::ostream& out) const{

}
void GuiElement::setScreen(Screen* target) {
    this->screen = target;
}
Screen* GuiElement::getScreen() {
    return this->screen;
}
void GuiElement::setParentStart(const ivec2& start) {
    this->parentStart = start;
}
void GuiElement::setParentEnd(const ivec2& end) {
    this->parentEnd = end;
}
ivec2 GuiElement::getParentStart() {
    return this->parentStart;
}
ivec2 GuiElement::getParentEnd() {
    return this->parentEnd;
}