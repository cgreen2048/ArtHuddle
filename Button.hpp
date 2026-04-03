#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include "Box.hpp"
#include "Event.hpp"
#include "ClickEvent.hpp"
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
        Button(ivec2 min, ivec2 max, ivec3 color, const std::function<void()>& callback, const std::string& callbackName, const std::string& text);
        ~Button() = default;
        Button& operator=(const Button& rhs) = default;

        bool resolveEvent(const Event* event);
        void writeXml(std::ostream& out, int depth) const;
        const std::string& getText() const;
};

#endif