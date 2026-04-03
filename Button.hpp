#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include "Box.hpp"
#include "Event.hpp"
#include "ClickEvent.hpp"
#include "ElementParameters.hpp"
#include <string>
#include <functional>


class Button : public Box {
    private:
        std::function<void()> onClick;
        std::string callbackName;
        std::string text;

    public:
        Button();
        Button(const Button& cp);
        Button(ElementParameters ep);
        Button(ivec2 min, ivec2 max, ivec3 color, const std::function<void()>& callback, const std::string& callbackName, const std::string& text);
        ~Button() = default;
        Button& operator=(const Button& rhs) = default;

        bool resolveEvent(Event* event);
        void writeXml(std::ostream& out, int depth) const;
        bool isValid(ElementParameters ep);
        const std::string& getText() const;
        const std::string& getCallbackName() const;
};

#endif