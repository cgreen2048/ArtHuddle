#ifndef __EVENT_HPP__
#define __EVENT_HPP__

enum class EventType {
    CLICK,
    SHOW,
    SOUND,
    MOUSE_DOWN,
    MOUSE_UP,
    MOUSE_MOTION,
    BUTTON_CLICK
};

class Event {
    private: 
        EventType type;
    public:
        Event();
        Event(EventType t);
        Event(const Event& cp);
        Event& operator=(const Event& rhs);
        virtual ~Event();

        EventType getType() const;
};

#endif