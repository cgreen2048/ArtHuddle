#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include "ArtHuddle/elements/Box.hpp"
#include "ArtHuddle/events/Event.hpp"
#include "ArtHuddle/events/ClickEvent.hpp"
#include "ArtHuddle/core/ElementParameters.hpp"
#include <string>
#include <functional>


class Button : public Box {
    private:
        std::function<void()> onClick;
        std::string callbackName;
        std::string text;
        ivec3 textColor;
        bool active;
        TagType textColorType = TagType::Vec;        


    public:
        Button();
        Button(const Button& cp);
        Button(ElementParameters ep);
        Button(ivec2 min, ivec2 max, ivec3 color, const std::function<void()>& callback, const std::string& callbackName, const std::string& text);
        ~Button() = default;
        Button& operator=(const Button& rhs) = default;
        bool operator==(Button rhs);
        bool operator!=(Button rhs);
        void draw(Screen *screen);
        void drawOverlay(Screen *screen);
        GuiElement* clone() const;
        void setActive(bool value);
        bool resolveEvent(Event* event);
        void writeXml(std::ostream& out, int depth) const;
        bool validateAndNormalize(ElementParameters& ep);
        const std::string& getText() const;
        const std::string& getCallbackName() const;
        ElementParameters getParameters();
        guiElement getType();
        void modifyColor(ivec3 newColor);
        void setText(std::string newText);
};

#endif