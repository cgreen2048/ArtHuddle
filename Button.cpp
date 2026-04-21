#include "Button.hpp"
#include "XmlWriteHelpers.hpp"
#include <iostream>

Button::Button() : Box(), onClick([](){}), callbackName(""), text("") {}

Button::Button(const Button& cp) : Box(cp.min, cp.max, cp.color), onClick(cp.onClick), callbackName(cp.callbackName), text(cp.text) {}

bool Button::operator==(Button rhs) {
    if (!Box::operator==(rhs)) {
        return false;
    }
    if ((textColor != rhs.textColor) || (this->textColorType != rhs.textColorType)){
        return false;
    }
    return true;
}

bool Button::operator!=(Button rhs) {
    return !(*this == rhs);
}


Button::Button(ElementParameters ep) : Box(ep) {
    if (!validateAndNormalize(ep)) {
        throw -1;
    }

    this->onClick = ep.callback;
    this->callbackName = ep.callbackName;
    this->text = ep.text;
    this->textColor = ep.textColor;
    this->textColorType = ep.textColorType;
}

void Button::drawOverlay(Screen *screen){
    screen->drawTextCentered(min, max, text, textColor);
}

Button::Button(ivec2 min, ivec2 max, ivec3 color, const std::function<void()>& callback, const std::string& callbackName, const std::string& text = "") : Box(min, max, color), onClick(callback), callbackName(callbackName), text(text) {}

GuiElement* Button::clone() const {
    return new Button(*this);
}

bool Button::resolveEvent(Event* event) {
    if (event->getType() == EventType::CLICK) {
        ClickEvent* clickEvent = dynamic_cast<ClickEvent*>(const_cast<Event*>(event));
        if (this->inBounds(ivec2(clickEvent->getMouseX(), clickEvent->getMouseY()))) {
            if (onClick) {
                onClick();
                return true;
            }
        }
    }
    return false;
}

void Button::writeXml(std::ostream& out, int depth) const {
    std::string pad = std::string(depth * 2, ' ');

    out << pad << "<button " << "name=\"" << name <<  "\" text=\"" << text << "\" onClick=\"" << callbackName << "\">\n";
    if (minType == TagType::IVec) {
        writeIVec2(out, min, pad);
    } else {
        writeVec2(out, toVec2(min), pad);
    }

    if (maxType == TagType::IVec) {
        writeIVec2(out, max, pad);
    }
    else {
        writeVec2(out, toVec2(max), pad);
    }

    if (colorType == TagType::IVec) {
        writeIVec3(out, color, pad);
    }
    else {
        writeVec3(out, toVec3(color), pad);
    }

    if (textColorType == TagType::IVec) {
        writeIVec3(out, textColor, pad);
    } 
    else {
        writeVec3(out, toVec3(textColor), pad);
    }
    out << pad << "</button>\n";
}

bool Button::validateAndNormalize(ElementParameters& ep) {
    Box::validateAndNormalize(ep);
    if ((ep.min.x == std::numeric_limits<int>::lowest()) || (ep.min.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if (ep.textColor.z == std::numeric_limits<int>::lowest()) {
        ep.color.z = 125;
    }
    if (ep.textColor.x == std::numeric_limits<int>::lowest()) {
        ep.color.x = 125;
    }
    if (ep.textColor.y == std::numeric_limits<int>::lowest()) {
        ep.color.y = 125;
    }
    if (ep.textColor.z == std::numeric_limits<int>::lowest()) {
        ep.color.z = 125;
    }
    if (ep.callbackName == "") {
        return false;
    }

    return true;
}

const std::string& Button::getText() const {
    return text;
}

const std::string& Button::getCallbackName() const {
    return callbackName;
}

ElementParameters Button::getParameters() {
    ElementParameters ep;
    ep.min = this->min;
    ep.max = this->max;
    ep.color = this->color;
    ep.callback = this->onClick;
    ep.callbackName = this->callbackName;
    ep.text = this->text;
    ep.textColor = this->textColor;
    ep.textColorType = this->textColorType;
    ep.name = this->name;
    return ep;
}

guiElement Button::getType() {
    return guiElement::BUTTON;
}