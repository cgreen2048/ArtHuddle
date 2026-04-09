#include "Button.hpp"
#include "XmlWriteHelpers.hpp"
#include <iostream>

Button::Button() : Box(), onClick([](){}), callbackName(""), text("") {}

Button::Button(const Button& cp) : Box(cp.min, cp.max, cp.color), onClick(cp.onClick), callbackName(cp.callbackName), text(cp.text) {}

Button::Button(ElementParameters ep) : Box(ep) {
    if (!isValid(ep)) {
        throw -1;
    }

    this->onClick = ep.callback;
    this->callbackName = ep.callbackName;
    this->text = ep.text;
}

Button::Button(ivec2 min, ivec2 max, ivec3 color, const std::function<void()>& callback, const std::string& callbackName, const std::string& text = "") : Box(min, max, color), onClick(callback), callbackName(callbackName), text(text) {}

GuiElement* Button::clone() const {
    return new Button(*this);
}

bool Button::resolveEvent(Event* event) {
    if (event->getType() == EventType::CLICK) {
        ClickEvent* clickEvent = dynamic_cast<ClickEvent*>(const_cast<Event*>(event));
        if (this->inBounds(ivec2(clickEvent->getMouseX(), clickEvent->getMouseY()))) {
            onClick();
            return true;
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
    out << pad << "</button>\n";
}

bool Button::isValid(ElementParameters ep) {
    if ((ep.min.x == std::numeric_limits<int>::lowest()) || (ep.min.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.max.x == std::numeric_limits<int>::lowest()) || (ep.max.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if (ep.color.x == std::numeric_limits<int>::lowest()) {
        ep.color.x = 125;
    }
    if (ep.color.y == std::numeric_limits<int>::lowest()) {
        ep.color.y = 125;
    }
    if (ep.color.z == std::numeric_limits<int>::lowest()) {
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