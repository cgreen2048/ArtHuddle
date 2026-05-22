#include "ArtHuddle/events/MouseUpEvent.hpp"

MouseUpEvent::MouseUpEvent(ivec2 coords) : MouseEvent(EventType::MOUSE_UP, coords) {}