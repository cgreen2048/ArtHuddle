#include "ShowEvent.hpp"

ShowEvent::ShowEvent(const std::string& name) : Event(EventType::SHOW), layoutName{name}, action{ShowAction::SHOW} {}

ShowEvent::ShowEvent(const std::string& name, ShowAction act) : Event(EventType::SHOW), layoutName{name}, action{act} {}

const std::string& ShowEvent::getLayoutName() {
    return this->layoutName;
}

ShowAction ShowEvent::getAction() {
    return this->action;
}