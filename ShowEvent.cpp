#include "ShowEvent.hpp"

ShowEvent::ShowEvent(const std::string& name) : Event(EventType::SHOW), layoutName{name}, action{ShowActionType::SHOW} {}

ShowEvent::ShowEvent(const std::string& name, ShowActionType act) : Event(EventType::SHOW), layoutName{name}, action{act} {}

const std::string& ShowEvent::getLayoutName() {
    return this->layoutName;
}

ShowActionType ShowEvent::getAction() {
    return this->action;
}