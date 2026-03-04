#include "GuiElement.hpp"

GuiElement::GuiElement() {
    std::cout << "GuiElement constructor\n";

}
GuiElement::~GuiElement() {
    std::cout << "GuiElement destroyed\n";
}
void GuiElement::draw(){
    std::cout << "Draw\n";
}
void GuiElement::setScreen(Screen* target) {
    this->screen = target;
}
Screen* GuiElement::getScreen() {
    return this->screen;
}