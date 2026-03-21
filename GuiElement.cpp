#include "GuiElement.hpp"

GuiElement::GuiElement() {
    
}
GuiElement::~GuiElement() {
    
}
void GuiElement::draw(Screen *screen){
    
}
void GuiElement::writeXml(std::ostream& out, int depth) const{

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