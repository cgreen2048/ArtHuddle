#ifndef __EVENT_SYSTEM_HPP__
#define __EVENT_SYSTEM_HPP__

#include "Event.hpp"
#include <queue>
#include <memory>
#include <Layout.hpp>

class EventSystem{
    public:
        static EventSystem& getInstance();
        void push(std::unique_ptr<Event> e);
        EventSystem(const EventSystem&) = delete;
        EventSystem& operator=(const EventSystem&) = delete;
        std::unique_ptr<Event> poll();
        void processEvents(Layout *rootlayout);

    private:
        EventSystem();
        std::queue<std::unique_ptr<Event>> eventQueue;
};

#endif