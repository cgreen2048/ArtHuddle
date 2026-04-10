#include "EventSystem.hpp"
#include <iostream>


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
        else {
            if (targetedElement != nullptr &&
                    (e->getType() == EventType::MOUSE_DOWN 
                    || e->getType() == EventType::MOUSE_MOTION
                    ||e->getType() == EventType::MOUSE_UP)
                ) {
                Freehand *fr = dynamic_cast<Freehand*>(targetedElement);
                if (fr != nullptr) {
                    bool success = fr->resolveEvent(e.get());

                    if (!success && fr->isFinishedFreehandDrawing()) {
                        // ADD ROOT DELETE FUNCTON TO DELETE INCOMPLETE FREEHAND
                    }

                    if (e->getType() == EventType::MOUSE_UP) {
                        targetedElement = nullptr;
                    }
                }

            }
            else {
                root->resolveEvent(e.get());
            }
        }
    }
}

void EventSystem::setSoundPlayer(SoundPlayer* soundPlayer) {
    this->soundPlayer = soundPlayer;
}

void EventSystem::setTargetedElement(GuiElement* e) {
    this->targetedElement = e;
}

SoundPlayer* EventSystem::getSoundPlayer() {
    return soundPlayer;
}

GuiElement* EventSystem::getTargetedElement() {
    return targetedElement;
}