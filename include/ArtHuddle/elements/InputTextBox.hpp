#ifndef __INPUT_TEXT_BOX_HPP__
#define __INPUT_TEXT_BOX_HPP__

#include "ArtHuddle/elements/TextBox.hpp"
#include "ArtHuddle/events/Event.hpp"
#include "ArtHuddle/events/ClickEvent.hpp"
#include "ArtHuddle/core/ElementParameters.hpp"
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