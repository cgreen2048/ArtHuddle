#include "MouseMotionEvent.hpp"

MouseMotionEvent::MouseMotionEvent(ivec2 coords, ivec2 previousCoords, bool mouseDown) : MouseEvent(EventType::MOUSE_MOTION, coords), previousCoords{previousCoords}, mouseDown(mouseDown) {}

ivec2 MouseMotionEvent::getPreviousCoords const { return previousCoords; }

bool MouseMotionEvent::isMouseDown() const { return mouseDown; }