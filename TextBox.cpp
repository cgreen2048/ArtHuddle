#include "TextBox.hpp"
#include "XmlWriteHelpers.hpp"
#include <iostream>

TextBox::TextBox() : Box(), text(""), textColor({0,0,0}), active(false) {}

TextBox::TextBox(const TextBox& cp) : Box(cp.min, cp.max, cp.color), text(cp.text), textColor(cp.textColor), active(cp.active) {}

TextBox::TextBox(ivec2 min, ivec2 max, ivec3 color, ivec3 textColor, const std::string& text): Box(min, max, color), text(text), textColor(textColor), active(false) {}


bool TextBox::operator==(TextBox rhs) {
    if (!Box::operator==(rhs)) {
        return false;
    }
    if ((textColor != rhs.textColor) || (this->textColorType != rhs.textColorType)){
        return false;
    }
    return true;
}

bool TextBox::operator!=(TextBox rhs) {
    return !(*this == rhs);
}

TextBox::TextBox(ElementParameters ep) : Box(ep) {
    if (!validateAndNormalize(ep)) {
        throw -1;
    }
    this->text = ep.text;
    this->textColor = ep.textColor;
    this->textColorType = ep.textColorType;
}



void TextBox::drawOverlay(Screen *screen) {
    // Draws clipped text
    screen->drawTextClipped(min, max, text, textColor);

    // Draws a blinking cursor on where the current character is.
    if (shouldShowCursor()) {
        screen->drawCursor(getCursorPosition(), textColor);
    }
}

GuiElement* TextBox::clone() const {
    return new TextBox(*this);
}

bool TextBox::shouldShowCursor() const {
    if (!active) {
        return false;
    }

    Uint64 ticks = SDL_GetTicks();
    return ((ticks / 500) % 2 == 0);
}

std::string TextBox::getVisibleText() const {
    int padding = 5;
    int boxWidth = max.x - min.x;
    int usableWidth = boxWidth - 2 * padding;

    if(usableWidth <= 0){
        return "";
    }

    int maxChars = usableWidth / 8;
    if(maxChars <=0){
        return "";
    }

    std::string visibleText = text;
    if (static_cast<int>(visibleText.size()) > maxChars) {
        visibleText = visibleText.substr(visibleText.size() - maxChars);
    }

    return visibleText;
}

ivec2 TextBox::getCursorPosition() const {
    int padding = 5;
    std::string visibleText = getVisibleText();

    int cursorX = min.x + padding + static_cast<int>(visibleText.size()) * 8;
    int cursorY = min.y + padding;

    return ivec2(cursorX, cursorY);
}

void TextBox::setActive(bool value) { 
    active = value; 
}

bool TextBox::isActive() const { 
    return active; 
}

void TextBox::setText(std::string newText) {
    this->text = newText;
}

void TextBox::appendText(const std::string& s) {
    text += s;
}

void TextBox::backspace() {
    if (!text.empty()) {
        text.pop_back();
    }
}

bool TextBox::containsPoint(int x, int y) const {
    return x >= min.x && x <= max.x && y >= min.y && y <= max.y;
}


void TextBox::writeXml(std::ostream& out, int depth) const {
    std::string pad = std::string(depth * 2, ' ');

    out << pad << "<textbox "
        << "name=\"" << name << "\" "
        << "text=\"" << text << "\">\n";

    if (minType == TagType::IVec) {
        writeIVec2(out, min, pad);
    } 
    else {
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

    out << pad << "</textbox>\n";
}

bool TextBox::validateAndNormalize(ElementParameters &ep) {
    Box::validateAndNormalize(ep);
    if (ep.textColor.x == std::numeric_limits<int>::lowest()) {
        ep.textColor.x = 125;
    }
    if (ep.textColor.y == std::numeric_limits<int>::lowest()) {
        ep.textColor.y = 125;
    }
    if (ep.textColor.z == std::numeric_limits<int>::lowest()) {
        ep.textColor.z = 125;
    }
    ivec2 newMin;
    ivec2 newMax;
    newMin.x = std::min(ep.min.x, ep.max.x);
    newMin.y = std::min(ep.min.y, ep.max.y);
    newMax.x = std::max(ep.min.x, ep.max.x);
    newMax.y = std::max(ep.min.y, ep.max.y);
    ep.min = newMin;
    ep.max = newMax;
    if (ep.elementType != guiElement::TEXTBOX) {
        ep.elementType = guiElement::TEXTBOX;
    }
    return true;
}

const std::string& TextBox::getText() const {
    return text;
}

ElementParameters TextBox::getParameters() {
    ElementParameters ep;
    ep.elementType = guiElement::TEXTBOX;
    ep.name = this->name;
    ep.min = this->min;
    ep.max = this->max;
    ep.minType = this->minType;
    ep.maxType = this->maxType;
    ep.color = this->color;
    ep.colorType = this->colorType;
    ep.text = this->text;
    ep.textColor = this->textColor;
    ep.textColorType = this->textColorType;
    return ep;
}

guiElement TextBox::getType() {
    return guiElement::TEXTBOX;
}

void TextBox::modifyColor(ivec3 newColor) {
    this->color += newColor;
    if (color.x < 0) {
        color.x = 0;
    }
    else if (color.x > 255) {
        color.x = 255;
    }
    if (color.y < 0) {
        color.y = 0;
    }
    else if (color.y > 255) {
        color.y = 255;
    }
    if (color.z < 0) {
        color.z = 0;
    }
    else if (color.z > 255) {
        color.z = 255;
    }
}