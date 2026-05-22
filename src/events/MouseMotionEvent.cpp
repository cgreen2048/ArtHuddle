#include "ArtHuddle/events/MouseMotionEvent.hpp"

MouseMotionEvent::MouseMotionEvent(ivec2 coords, bool mouseDown) : MouseEvent(EventType::MOUSE_MOTION, coords), mouseDown(mouseDown) {}


bool MouseMotionEvent::isMouseDown() const { return mouseDown; }