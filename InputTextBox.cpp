#include "InputTextBox.hpp"
#include "Selected.hpp"

InputTextBox::InputTextBox(ElementParameters& ep) : TextBox(ep), visible(ep.active) {}

GuiElement* InputTextBox::clone() const {
    return new InputTextBox(*this);
}

void InputTextBox::writeXml(std::ostream& out, int depth) const {
    // Do nothing. Not meant to saved to an xml file.
}

void InputTextBox::draw(Screen *screen) {
    if (!visible) {
        return;
    }
    Box::draw(screen);
}

bool InputTextBox::resolveEvent(Event* e) {
    if (!visible) {
        return false;
    }

    if (e->getType() == EventType::CLICK) {
        setActive(true); // gain typing focus
        Selected::getInstance().setSelectedElement(this);
        return true;
    }

    return false;
}



void InputTextBox::drawOverlay(Screen *screen){
    if (!this->isActive()){
        return;
    }
    TextBox::drawOverlay(screen);
}

void InputTextBox::setVisible(bool value) {
    visible = value;
}

bool InputTextBox::isVisible() const {
    return visible;
}

