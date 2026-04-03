#ifndef __SHOW_EVENT_HPP__
#define __SHOW_EVENT_HPP__

#include "Event.hpp"
#include <string>

enum class ShowActionType {
    SHOW,
    HIDE
};

class ShowEvent : public Event {
    private: 
        std::string layoutName;
        ShowActionType action;
    public:
        ShowEvent(const std::string& name);
        ShowEvent(const std::string& name, ShowActionType act);
        const std::string& getLayoutName();
        ShowActionType getAction();
};


#endif