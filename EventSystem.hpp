#ifndef __EVENT_SYSTEM_HPP__
#define __EVENT_SYSTEM_HPP__

#include "Event.hpp"
#include <queue>
#include <memory>
#include "Layout.hpp"
#include "Sound.hpp"
#include "SoundState.hpp"
#include "SoundPlayer.hpp"
#include "SoundEvent.hpp"
#include "ClickEvent.hpp"
#include "ShowEvent.hpp"
#include "MouseDownEvent.hpp"
#include "MouseUpEvent.hpp"
#include "MouseMotionEvent.hpp"


class EventSystem{
    public:
        static EventSystem& getInstance();
        
        void push(std::unique_ptr<Event> e);
        EventSystem(const EventSystem&) = delete;
        EventSystem& operator=(const EventSystem&) = delete;
        std::unique_ptr<Event> poll();
        void processEvents(Layout *rootlayout);
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