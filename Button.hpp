#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include "Box.hpp"
#include <string>


class Button : public Box {
    private:
        std::function<void()> onClick;
        std::string text;

    public:
        Button() = default;
        Button(const Button& cp) = default;
        Button(ivec2 min, ivec2 max, ivec3 color, std::function<void()>& callback);
        ~Button() = default;
        operator(const Button& rhs) = default;

        bool resolveEvent(const Event& event);
        void writeXml(std::ostream& out, int depth) const;
}