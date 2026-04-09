#include "TextBox.hpp"
#include "XmlWriteHelpers.hpp"
#include <iostream>

TextBox::TextBox() : Box(), textColor({0,0,0}), text(""), active(false) {}

TextBox::TextBox(const TextBox& cp) : Box(cp.min, cp.max, cp.color), textColor(cp.textColor), text(cp.text), active(cp.active) {}

TextBox::TextBox(ivec2 min, ivec2 max, ivec3 color, ivec3 textColor, const std::string& text): Box(min, max, color), textColor(textColor), text(text), active(false) {}


TextBox::TextBox(ElementParameters ep) : Box(ep) {
    if (!isValid(ep)) {
        throw -1;
    }
    this->text = ep.text;
    this->textColor = ep.textColor;
}


// bool Button::resolveEvent(Event* event) {
//     if (event->getType() == EventType::CLICK) {
//         ClickEvent* clickEvent = dynamic_cast<ClickEvent*>(const_cast<Event*>(event));
//         if (this->inBounds(ivec2(clickEvent->getMouseX(), clickEvent->getMouseY()))) {
//             onClick();
//             return true;
//         }
//     }
//     return false;
// }

void TextBox::writeXml(std::ostream& out, int depth) const {
    std::string pad = std::string(depth * 2, ' ');

    out << pad << "<textbox " << "name=\"" << name <<  "\" text=\"" << text << "\">\n";
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
        writeIVec3(out, color, pad);
    }
    else {
        writeVec3(out, toVec3(color), pad);
    }
    out << pad << "</textbox>\n";
}

bool TextBox::isValid(ElementParameters ep) {
    if ((ep.point1.x == std::numeric_limits<int>::lowest()) || (ep.point1.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if ((ep.point2.x == std::numeric_limits<int>::lowest()) || (ep.point2.y == std::numeric_limits<int>::lowest())) {
        return false;
    }
    if (ep.color.x == std::numeric_limits<int>::lowest()) {
        ep.color.x = 125;
    }
    if (ep.color.y == std::numeric_limits<int>::lowest()) {
        ep.color.y = 125;
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

    return true;
}

const std::string& TextBox::getText() const {
    return text;
}





