#include "ArtHuddle/events/MouseEvent.hpp"

MouseEvent::MouseEvent(EventType type, ivec2 coords) : Event(type), coords(coords) {}

ivec2 MouseEvent::getCoords() const { return coords; } 