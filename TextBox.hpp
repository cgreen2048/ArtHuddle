#ifndef __TEXT_BOX_HPP__
#define __TEXT_BOX_HPP__

#include "Box.hpp"
#include "Event.hpp"
#include "ClickEvent.hpp"
#include "ElementParameters.hpp"
#include <string>


class TextBox : public Box {
    private:
        std::string text;
        ivec3 textColor;
        bool active;
        TagType textColorType = TagType::Vec;

    public:
        TextBox();
        TextBox(const TextBox& cp);
        TextBox(ElementParameters ep);
        TextBox(ivec2 min, ivec2 max, ivec3 color, ivec3 textColor, const std::string& text);
        ~TextBox() = default;
        TextBox& operator=(const TextBox& rhs) = default;
        bool operator==(TextBox rhs);
		bool operator!=(TextBox rhs);
        void drawOverlay(Screen *screen);
        void setActive(bool value);
        bool isActive() const;
        void appendText(const std::string& s);
        void backspace();
        bool containsPoint(int x, int y) const;
        bool shouldShowCursor() const;
        std::string getVisibleText() const;
        ivec2 getCursorPosition() const;

        void writeXml(std::ostream& out, int depth) const;
        bool isValid(ElementParameters ep);
        const std::string& getText() const;
};

#endif