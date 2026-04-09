#include "EventSystem.hpp"
#include <iostream>
#include "ClickEvent.hpp"

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
            SoundEvent* sound = static_cast<SoundEvent*>(e.get());
            std::cout << "Processing sound event\n";
            switch (sound->getAction()) {
                case SoundActionType::PLAY:
                    soundPlayer->playSound(sound->getSoundName(), sound->shouldLoop());
                    break;

                case SoundActionType::PAUSE:
                    soundPlayer->togglePlayback();
                    break;

                case SoundActionType::STOP:
                    soundPlayer->stopSound(sound->getSoundName());
                    break;
            }
        }
        else{
            // Handle other event types here by trickling down through the layout tree and calling resolveEvent on each element
            root->resolveEvent(e.get());
        }
    }
}

void EventSystem::setSoundPlayer(SoundPlayer* soundPlayer) {
    this->soundPlayer = soundPlayer;
}

SoundPlayer* EventSystem::getSoundPlayer() {
    return soundPlayer;
}