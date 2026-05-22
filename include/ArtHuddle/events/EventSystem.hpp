#ifndef __EVENT_SYSTEM_HPP__
#define __EVENT_SYSTEM_HPP__

#include "ArtHuddle/events/Event.hpp"
#include <queue>
#include <memory>

class GuiElement;
class Layout;
class SoundPlayer;

class EventSystem{
    public:
        static EventSystem& getInstance();
        
        void push(std::unique_ptr<Event> e);
        EventSystem(const EventSystem&) = delete;
        EventSystem& operator=(const EventSystem&) = delete;
        std::unique_ptr<Event> poll();
        bool processEvents(Layout *root);
        void setSoundPlayer(SoundPlayer* soundPlayer);
        void setTargetedElement(GuiElement* e);
        SoundPlayer* getSoundPlayer();
        GuiElement* getTargetedElement();

    private:
        EventSystem();
        std::queue<std::unique_ptr<Event>> eventQueue;
        SoundPlayer* soundPlayer;
        GuiElement* targetedElement = nullptr;
};

#endif