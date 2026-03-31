#include "EventSystem.hpp"

EventSystem::EventSystem() {}

EventSystem& EventSystem::getInstance() {
    static EventSystem instance;
    return instance;
}

void EventSystem::push(std::unique_ptr<Event> e) {
    eventQueue.push(std::move(e));
}

std::unique_ptr<Event> EventSystem::poll() {
    if (eventQueue.empty()) return nullptr;

    std::unique_ptr<Event> e = std::move(eventQueue.front());
    eventQueue.pop();
    return e;
}