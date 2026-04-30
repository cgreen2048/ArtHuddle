#ifndef __INPUT_TEXT_BOX_HPP__
#define __INPUT_TEXT_BOX_HPP__

#include "TextBox.hpp"
#include "Event.hpp"
#include "ClickEvent.hpp"
#include "ElementParameters.hpp"
#include <string>


class InputTextBox : public TextBox {
    private:
        bool visible = false;
    public:
        InputTextBox(ElementParameters ep);
        GuiElement* clone() const;
        void draw(Screen *screen);
        void drawOverlay(Screen *screen);
        void writeXml(std::ostream& out, int depth) const;
        bool resolveEvent(Event* event);
        void setVisible(bool value);
        bool isVisible() const;
};

#endif