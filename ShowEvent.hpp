#ifndef __SHOW_EVENT_HPP__
#define __SHOW_EVENT_HPP__

#include "Event.hpp"
#include <string>

enum class ShowAction {
    SHOW,
    HIDE
};

class ShowEvent : public Event {
    private: 
        std::string layoutName;
        ShowAction action;
    public:
        ShowEvent(const std::string& name);
        ShowEvent(const std::string& name, ShowAction action);
        const std::string& getLayoutName();
        ShowAction getAction();
};


#endif