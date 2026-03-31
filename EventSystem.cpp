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

void EventSystem::processEvents(Layout *root){
    while(!eventQueue.empty()){
        std::unique_ptr<Event> e = poll();

        if (!e) {
            break;
        }

        if(e->getType() == EventType::SOUND){
            // SoundEvent* sound = static_cast<SoundEvent*>(e.get()); // Sound class need to be implemented.
            // play sound.
        }
        else{
            root->resolveEvent(e.get());
        }
    }
}