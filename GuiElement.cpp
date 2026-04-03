#include "GuiElement.hpp"
#include <iostream>
GuiElement::GuiElement() {
    
}
GuiElement::~GuiElement() {
    
}
void GuiElement::draw(Screen *screen){
    
}
void GuiElement::writeXml(std::ostream& out, int depth) const{

}
bool GuiElement::resolveEvent(Event *e){
    return false;
}
void GuiElement::setParentStart(const ivec2& start) {
    this->parentStart = start;
}
void GuiElement::setParentEnd(const ivec2& end) {
    this->parentEnd = end;
}
void GuiElement::setName(const std::string& n){
    this->name = n;
}
ivec2 GuiElement::getParentStart() {
    return this->parentStart;
}
ivec2 GuiElement::getParentEnd() {
    return this->parentEnd;
}
const std::string& GuiElement::getName() const {
    return name;
}
